#include <windows.h>
#include "common.h"
#include "patcher.h"
#include "CdStream.h"
#include "rwcore.h"
#include "RwHelper.h"

#define CDDEBUG(f, ...)   debug ("%s: " f "\n", "cdvd_stream", ## __VA_ARGS__)
#define CDTRACE(f, ...)   printf("%s: " f "\n", "cdvd_stream", ## __VA_ARGS__)

struct CdReadInfo
{
	uint32 nSectorOffset;
	uint32 nSectorsToRead;
	void *pBuffer;
	char field_C;
	bool bLocked;
	bool bInUse;
	char _pad0;
	int32 nStatus;
	HANDLE hSemaphore;
	HANDLE hFile;
	OVERLAPPED Overlapped;
};
VALIDATE_SIZE(CdReadInfo, 0x30);

char gCdImageNames[MAX_CDIMAGES+1][64];
int32 gNumImages;
int32 gNumChannels;

HANDLE gImgFiles[MAX_CDIMAGES];

HANDLE _gCdStreamThread;
HANDLE gCdStreamSema;
DWORD _gCdStreamThreadId;

CdReadInfo *gpReadInfo;
Queue gChannelRequestQ;

int32 lastPosnRead;

BOOL _gbCdStreamOverlapped;
BOOL _gbCdStreamAsync;
DWORD _gdwCdStreamFlags;


void
CdStreamInitThread(void)
{
	SetLastError(0);
	
	if ( gNumChannels > 0 )
	{
		for ( int32 i = 0; i < gNumChannels; i++ )
		{
			gpReadInfo[i].hSemaphore = CreateSemaphore(nil, 0, 2, nil);
			
			if ( gpReadInfo[i].hSemaphore == nil )
			{
				CDTRACE("failed to create sync semaphore");
				ASSERT(0);
				return;
			}
		}
	}
	
	gChannelRequestQ.items = (int32 *)LocalAlloc(LMEM_ZEROINIT, sizeof(int32) * (gNumChannels + 1));
	gChannelRequestQ.head = 0;
	gChannelRequestQ.tail = 0;
	gChannelRequestQ.size = gNumChannels + 1;
	ASSERT(gChannelRequestQ.items != nil );
	
	gCdStreamSema = CreateSemaphore(nil, 0, 5, "CdStream");
	
	if ( gCdStreamSema == nil )
	{
		CDTRACE("failed to create stream semaphore");
		ASSERT(0);
		return;
	}
	
	_gCdStreamThread = CreateThread(nil, 64*1024/*64KB*/, CdStreamThread, nil, CREATE_SUSPENDED, &_gCdStreamThreadId);
	
	if ( _gCdStreamThread == nil )
	{
		CDTRACE("failed to create streaming thread");
		ASSERT(0);
		return;
	}

	SetThreadPriority(_gCdStreamThread, GetThreadPriority(GetCurrentThread()) - 1);
		
	ResumeThread(_gCdStreamThread);	
}

void
CdStreamInit(int32 numChannels)
{
	DWORD SectorsPerCluster;
	DWORD BytesPerSector;
	DWORD NumberOfFreeClusters;
	DWORD TotalNumberOfClusters;

	GetDiskFreeSpace(nil, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);
	
	_gdwCdStreamFlags = 0;
	
	if ( BytesPerSector <= CDSTREAM_SECTOR_SIZE )
	{
		_gdwCdStreamFlags |= FILE_FLAG_NO_BUFFERING;
		debug("Using no buffered loading for streaming\n");
	}
	
	_gbCdStreamOverlapped = TRUE;

	_gdwCdStreamFlags |= FILE_FLAG_OVERLAPPED;
	
	_gbCdStreamAsync = FALSE;
	
	void *pBuffer = (void *)RwMallocAlign(CDSTREAM_SECTOR_SIZE, BytesPerSector);
	ASSERT( pBuffer != nil );
	
	SetLastError(0);
	
	gNumImages = 0;
	
	gNumChannels = numChannels;
	
	gpReadInfo = (CdReadInfo *)LocalAlloc(LMEM_ZEROINIT, sizeof(CdReadInfo) * numChannels);
	ASSERT( gpReadInfo != nil );
	
	CDDEBUG("read info %p", gpReadInfo);
	
	CdStreamAddImage("MODELS\\GTA3.IMG");
	
	int32 nStatus = CdStreamRead(0, pBuffer, 0, 1);
	
	CdStreamRemoveImages();
	
	if ( nStatus == STREAM_SUCCESS )
	{
		_gbCdStreamAsync = TRUE;
		
		debug("Using async loading for streaming\n");
	}
	else
	{
		_gdwCdStreamFlags &= ~FILE_FLAG_OVERLAPPED;
		
		_gbCdStreamOverlapped = FALSE;
		
		_gbCdStreamAsync = TRUE;
		
		debug("Using sync loading for streaming\n");
	}
	
	CdStreamInitThread();
	
	ASSERT( pBuffer != nil );
	RwFreeAlign(pBuffer);
}

uint32
GetGTA3ImgSize(void)
{
	ASSERT( gImgFiles[0] != nil );
	return (uint32)GetFileSize(gImgFiles[0], nil);
}

void
CdStreamShutdown(void)
{
	if ( _gbCdStreamAsync )
	{
		LocalFree(gChannelRequestQ.items);
		CloseHandle(gCdStreamSema);
		CloseHandle(_gCdStreamThread);
		
		for ( int32 i = 0; i < gNumChannels; i++ )
			CloseHandle(gpReadInfo[i].hSemaphore);
	}
	
	LocalFree(gpReadInfo);
}



int32
CdStreamRead(int32 channel, void *buffer, uint32 offset, uint32 size)
{
	ASSERT( channel < gNumChannels );
	ASSERT( buffer != nil );
	
	lastPosnRead = size + offset;
	
	ASSERT( _GET_INDEX(offset) < MAX_CDIMAGES );
	HANDLE hImage = gImgFiles[_GET_INDEX(offset)];
	ASSERT( hImage != nil );
	
	
	CdReadInfo *pChannel = &gpReadInfo[channel];
	ASSERT( pChannel != nil );
	
	pChannel->hFile = hImage;
	
	SetLastError(0);
	
	if ( _gbCdStreamAsync )
	{
		if ( pChannel->nSectorsToRead != 0 || pChannel->bInUse )
			return STREAM_NONE;
		
		pChannel->nStatus = STREAM_NONE;
		pChannel->nSectorOffset = _GET_OFFSET(offset);
		pChannel->nSectorsToRead = size;
		pChannel->pBuffer = buffer;
		pChannel->bLocked = 0;
		
		AddToQueue(&gChannelRequestQ, channel);
		
		if ( !ReleaseSemaphore(gCdStreamSema, 1, nil) )
			printf("Signal Sema Error\n");
		
		return STREAM_SUCCESS;
	}
	
	if ( _gbCdStreamOverlapped )
	{
		ASSERT( channel < gNumChannels );
		CdReadInfo *pChannel = &gpReadInfo[channel];
		ASSERT( pChannel != nil );
		
		pChannel->Overlapped.Offset = _GET_OFFSET(offset) * CDSTREAM_SECTOR_SIZE;
		
		if ( !ReadFile(hImage, buffer, size * CDSTREAM_SECTOR_SIZE, NULL, &pChannel->Overlapped)
					&& GetLastError() != ERROR_IO_PENDING )
			return STREAM_NONE;
		else
			return STREAM_SUCCESS;
	}
	
	SetFilePointer(hImage, _GET_OFFSET(offset) * CDSTREAM_SECTOR_SIZE, nil, FILE_BEGIN);
	
	DWORD NumberOfBytesRead;
	
	if ( !ReadFile(hImage, buffer, size * CDSTREAM_SECTOR_SIZE, &NumberOfBytesRead, nil) )
		return STREAM_NONE;
	else
		return STREAM_SUCCESS;
}

int32
CdStreamGetStatus(int32 channel)
{
	ASSERT( channel < gNumChannels );
	CdReadInfo *pChannel = &gpReadInfo[channel];
	ASSERT( pChannel != nil );
	
	if ( _gbCdStreamAsync )
	{
		if ( pChannel->bInUse )
			return STREAM_READING;
		
		if ( pChannel->nSectorsToRead != 0 )
			return STREAM_WAITING;
		
		if ( pChannel->nStatus != STREAM_NONE )
		{
			int32 status = pChannel->nStatus;
			
			pChannel->nStatus = STREAM_NONE;
			
			return status;
		}
		
		return STREAM_NONE;
	}
	
	if ( _gbCdStreamOverlapped )
	{
		ASSERT( pChannel->hFile != nil );
		if ( WaitForSingleObjectEx(pChannel->hFile, 0, TRUE) == WAIT_OBJECT_0 )
			return STREAM_NONE;
		else
			return STREAM_READING;
	}
	
	return STREAM_NONE;
}

int32
CdStreamGetLastPosn(void)
{
	return lastPosnRead;
}

int32
CdStreamSync(int32 channel)
{
	ASSERT( channel < gNumChannels );
	CdReadInfo *pChannel = &gpReadInfo[channel];
	ASSERT( pChannel != nil );
	
	if ( _gbCdStreamAsync )
	{
		if ( pChannel->nSectorsToRead != 0 )
		{
			pChannel->bLocked = true;

			ASSERT( pChannel->hSemaphore != nil );

			WaitForSingleObject(pChannel->hSemaphore, INFINITE);
		}

		pChannel->bInUse = false;
		
		return pChannel->nStatus;
	}
	
	DWORD NumberOfBytesTransferred;

	if ( _gbCdStreamOverlapped && pChannel->hFile )
	{
		ASSERT(pChannel->hFile != nil );
		if ( GetOverlappedResult(pChannel->hFile, &pChannel->Overlapped, &NumberOfBytesTransferred, TRUE) )
			return STREAM_NONE;
		else
			return STREAM_ERROR;
	}
	
	return STREAM_NONE;
}

void
AddToQueue(Queue *queue, int32 item)
{
	ASSERT( queue != nil );
	ASSERT( queue->items != nil );
	queue->items[queue->tail] = item;
	
	queue->tail = (queue->tail + 1) % queue->size;
	
	if ( queue->head == queue->tail )
		debug("Queue is full\n");
}

int32 
GetFirstInQueue(Queue *queue)
{
	ASSERT( queue != nil );
	if ( queue->head == queue->tail )
		return -1;

	ASSERT( queue->items != nil );
	return queue->items[queue->head];
}

void
RemoveFirstInQueue(Queue *queue)
{	
	ASSERT( queue != nil );
	if ( queue->head == queue->tail )
	{
		debug("Queue is empty\n");
		return;
	}

	queue->head = (queue->head + 1) % queue->size;
}

DWORD
WINAPI CdStreamThread(LPVOID lpThreadParameter)
{
	debug("Created cdstream thread\n");
	
	while ( true )
	{
		WaitForSingleObject(gCdStreamSema, INFINITE);
		
		int32 channel = GetFirstInQueue(&gChannelRequestQ);
		ASSERT( channel < gNumChannels );
		
		CdReadInfo *pChannel = &gpReadInfo[channel];
		ASSERT( pChannel != nil );
		
		pChannel->bInUse = true;
		
		if ( pChannel->nStatus == STREAM_NONE )
		{
			if ( _gbCdStreamOverlapped )
			{
				pChannel->Overlapped.Offset = pChannel->nSectorOffset * CDSTREAM_SECTOR_SIZE;
				
				ASSERT(pChannel->hFile != nil );
				ASSERT(pChannel->pBuffer != nil );
				
				DWORD NumberOfBytesTransferred;
				
				if ( ReadFile(pChannel->hFile,
						pChannel->pBuffer,
						pChannel->nSectorsToRead * CDSTREAM_SECTOR_SIZE,
						NULL,
						&pChannel->Overlapped) )
				{
					pChannel->nStatus = STREAM_NONE;
				}
				else if ( GetLastError() == ERROR_IO_PENDING
						&& GetOverlappedResult(pChannel->hFile, &pChannel->Overlapped, &NumberOfBytesTransferred, TRUE) )
				{
					pChannel->nStatus = STREAM_NONE;
				}
				else
				{
					pChannel->nStatus = STREAM_ERROR;
				}
			}
			else
			{
				ASSERT(pChannel->hFile != nil );
				ASSERT(pChannel->pBuffer != nil );
				
				SetFilePointer(pChannel->hFile, pChannel->nSectorOffset * CDSTREAM_SECTOR_SIZE, nil, FILE_BEGIN);

				DWORD NumberOfBytesRead;
				if ( ReadFile(pChannel->hFile,
						pChannel->pBuffer,
						pChannel->nSectorsToRead * CDSTREAM_SECTOR_SIZE,
						&NumberOfBytesRead,
						NULL) )
				{
					pChannel->nStatus = STREAM_NONE;
				}
			}
		}
		
		RemoveFirstInQueue(&gChannelRequestQ);
		
		pChannel->nSectorsToRead = 0;
		
		if ( pChannel->bLocked )
		{
			ASSERT( pChannel->hSemaphore != nil );
			ReleaseSemaphore(pChannel->hSemaphore, 1, NULL);
		}
		
		pChannel->bInUse = false;
	}
}

bool
CdStreamAddImage(char const *path)
{
	ASSERT(path != nil);
	ASSERT(gNumImages < MAX_CDIMAGES);
	
	SetLastError(0);
	
	gImgFiles[gNumImages] = CreateFile(path,
	                                   GENERIC_READ,
	                                   FILE_SHARE_READ,
	                                   nil,
	                                   OPEN_EXISTING,
	                                   _gdwCdStreamFlags | FILE_FLAG_RANDOM_ACCESS | FILE_ATTRIBUTE_READONLY,
	                                   nil);
	
	ASSERT( gImgFiles[gNumImages] != nil );
	if ( gImgFiles[gNumImages] == NULL )
		return false;
	
	strcpy(gCdImageNames[gNumImages], path);
	
	gNumImages++;
	
	return true;
}

char *
CdStreamGetImageName(int32 cd)
{
	ASSERT(cd < MAX_CDIMAGES);
	if ( gImgFiles[cd] != nil )
		return gCdImageNames[cd];
	
	return nil;
}

void
CdStreamRemoveImages(void)
{	
	for ( int32 i = 0; i < gNumChannels; i++ )
		CdStreamSync(i);
	
	for ( int32 i = 0; i < gNumImages; i++ )
	{
		SetLastError(0);
		
		CloseHandle(gImgFiles[i]);
		gImgFiles[i] = nil;
	}
	
	gNumImages = 0;
}

int32
CdStreamGetNumImages(void)
{	
	return gNumImages;
}


STARTPATCHES
	InjectHook(0x405B50, CdStreamInitThread, PATCH_JUMP);
	InjectHook(0x405C80, CdStreamInit, PATCH_JUMP);
	//InjectHook(0x405DB0, debug, PATCH_JUMP);
	InjectHook(0x405DC0, GetGTA3ImgSize, PATCH_JUMP);
	InjectHook(0x405DD0, CdStreamShutdown, PATCH_JUMP);
	InjectHook(0x405E40, CdStreamRead, PATCH_JUMP);
	InjectHook(0x405F90, CdStreamGetStatus, PATCH_JUMP);
	InjectHook(0x406000, CdStreamGetLastPosn, PATCH_JUMP);
	InjectHook(0x406010, CdStreamSync, PATCH_JUMP);
	InjectHook(0x4060B0, AddToQueue, PATCH_JUMP);
	InjectHook(0x4060F0, GetFirstInQueue, PATCH_JUMP);
	InjectHook(0x406110, RemoveFirstInQueue, PATCH_JUMP);
	InjectHook(0x406140, CdStreamThread, PATCH_JUMP);
	InjectHook(0x406270, CdStreamAddImage, PATCH_JUMP);
	InjectHook(0x4062E0, CdStreamGetImageName, PATCH_JUMP);
	InjectHook(0x406300, CdStreamRemoveImages, PATCH_JUMP);
	InjectHook(0x406370, CdStreamGetNumImages, PATCH_JUMP);
ENDPATCHES
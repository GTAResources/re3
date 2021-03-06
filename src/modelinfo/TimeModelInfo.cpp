#include "common.h"
#include "patcher.h"
#include "Camera.h"
#include "ModelInfo.h"

CTimeModelInfo*
CTimeModelInfo::FindOtherTimeModel(void)
{
	char name[40];
	char *p;
	int i;

	strcpy(name, GetName());
	// change _nt to _dy
	if(p = strstr(name, "_nt"))
		strncpy(p, "_dy", 4);
	// change _dy to _nt
	else if(p = strstr(name, "_dy"))
		strncpy(p, "_nt", 4);
	else
		return nil;

	for(i = 0; i < MODELINFOSIZE; i++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(i);
		if(mi && mi->m_type == MITYPE_TIME &&
		   strncmp(name, mi->GetName(), 24) == 0){
			m_otherTimeModelID = i;
			return (CTimeModelInfo*)mi;
		}
	}
	return nil;
}

STARTPATCHES
	InjectHook(0x517C80, &CTimeModelInfo::FindOtherTimeModel, PATCH_JUMP);
ENDPATCHES

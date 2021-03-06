#if (!defined(_PLATFORM_WIN_H))
#define _PLATFORM_WIN_H

#if (!defined(RSREGSETBREAKALLOC))
#define RSREGSETBREAKALLOC(_name) /* No op */
#endif /* (!defined(RSREGSETBREAKALLOC)) */

enum eGameState
{
	GS_START_UP = 0,
	GS_INIT_LOGO_MPEG,
	GS_LOGO_MPEG,
	GS_INIT_INTRO_MPEG,
	GS_INTRO_MPEG,
	GS_INIT_ONCE,
	GS_INIT_FRONTEND,
	GS_FRONTEND,
	GS_INIT_PLAYING_GAME,
	GS_PLAYING_GAME,
	GS_ANIMVIEWER,
};

enum eWinVersion
{
	OS_WIN95 = 0,
	OS_WIN98,
	OS_WINNT,
	OS_WIN2000,
	OS_WINXP,
};

extern DWORD &_dwOperatingSystemVersion;

extern RwUInt32 &gGameState;

/* platform specfic global data */
typedef struct
{
	HWND		window;
	HINSTANCE	instance;
	RwBool		fullScreen;
	RwV2d		lastMousePos;
	
	DWORD field_14;

	LPDIRECTINPUT8		 dinterface;
	LPDIRECTINPUTDEVICE8 mouse;
	LPDIRECTINPUTDEVICE8 joy1;
	LPDIRECTINPUTDEVICE8 joy2;
}
psGlobalType;

#define PSGLOBAL(var) (((psGlobalType *)(RsGlobal.ps))->var)

enum eJoypads
{
	JOYSTICK1 = 0,
	JOYSTICK2,
	MAX_JOYSTICKS
};

enum eJoypadState
{
	JOYPAD_UNUSED,
	JOYPAD_ATTACHED,
};

struct tJoy
{
	eJoypadState m_State;
	bool         m_bInitialised;
	bool         m_bHasAxisZ;
	bool         m_bHasAxisR;
	char _pad0;
	int          m_nVendorID;
	int          m_nProductID;
};

class CJoySticks
{
public:
	tJoy m_aJoys[MAX_JOYSTICKS];
	
	CJoySticks();
	void ClearJoyInfo(int joyID);
};

extern CJoySticks AllValidWinJoys;

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern LRESULT      CALLBACK
MainWndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

RwBool IsForegroundApp();

HRESULT _InputInitialise();
HRESULT _InputInitialiseMouse();
HRESULT CapturePad(RwInt32 padID);
void _InputInitialiseJoys();
void _InputAddJoyStick(LPDIRECTINPUTDEVICE8 lpDevice, INT num);
HRESULT _InputAddJoys();
HRESULT _InputGetMouseState(DIMOUSESTATE2 *state);
void _InputShutdown();
BOOL CALLBACK _InputEnumDevicesCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
BOOL _InputTranslateKey(RsKeyCodes *rs, UINT flag, UINT key);
void _InputTranslateShiftKeyUpDown(RsKeyCodes *rs);;
BOOL _InputTranslateShiftKey(RsKeyCodes *rs, UINT key, BOOLEAN bDown);
BOOL _InputIsExtended(INT flag);

void InitialiseLanguage();
RwBool _psSetVideoMode(RwInt32 subSystem, RwInt32 videoMode);
void CenterVideo(void);
void CloseClip(void);

RwChar **_psGetVideoModeList();
RwInt32 _psGetNumVideModes();

void _psSelectScreenVM(RwInt32 videoMode);
void HandleExit();

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


extern DWORD &_dwOperatingSystemVersion;
#endif /* (!defined(_PLATFORM_WIN_H)) */

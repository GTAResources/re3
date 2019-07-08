#pragma once

// same as RW skeleton
/*
enum Key
{
	// ascii...

	KEY_ESC   = 128,

	KEY_F1    = 129,
	KEY_F2    = 130,
	KEY_F3    = 131,
	KEY_F4    = 132,
	KEY_F5    = 133,
	KEY_F6    = 134,
	KEY_F7    = 135,
	KEY_F8    = 136,
	KEY_F9    = 137,
	KEY_F10   = 138,
	KEY_F11   = 139,
	KEY_F12   = 140,

	KEY_INS   = 141,
	KEY_DEL   = 142,
	KEY_HOME  = 143,
	KEY_END   = 144,
	KEY_PGUP  = 145,
	KEY_PGDN  = 146,

	KEY_UP    = 147,
	KEY_DOWN  = 148,
	KEY_LEFT  = 149,
	KEY_RIGHT = 150,

	// some stuff ommitted

	KEY_BACKSP = 168,
	KEY_TAB    = 169,
	KEY_CAPSLK = 170,
	KEY_ENTER  = 171,
	KEY_LSHIFT = 172,
	KEY_RSHIFT = 173,
	KEY_LCTRL  = 174,
	KEY_RCTRL  = 175,
	KEY_LALT   = 176,
	KEY_RALT   = 177,

	KEY_NULL,	// unused
	KEY_NUMKEYS
};
*/


class CControllerState
{
public:
	int16 LeftStickX, LeftStickY;
	int16 RightStickX, RightStickY;
	int16 LeftShoulder1, LeftShoulder2;
	int16 RightShoulder1, RightShoulder2;
	int16 DPadUp, DPadDown, DPadLeft, DPadRight;
	int16 Start, Select;
	int16 Square, Triangle, Cross, Circle;
	int16 LeftShock, RightShock;
	int16 NetworkTalk;
	float GetLeftStickX(void) { return LeftStickX/32767.0f; };
	float GetLeftStickY(void) { return LeftStickY/32767.0f; };
	float GetRightStickX(void) { return RightStickX/32767.0f; };
	float GetRightStickY(void) { return RightStickY/32767.0f; };

	void Clear(void);
};
VALIDATE_SIZE(CControllerState, 0x2A);

class CMouseControllerState
{
public:
	//uint32 btns;	// bit 0-2 button 1-3

	bool LMB;
	bool RMB;
	bool MMB;
	bool WHEELUP;
	bool WHEELDN;
	bool MXB1;
	bool MXB2;
	char _pad0;
	
	float x, y;
	
	CMouseControllerState();
	void Clear();
};

VALIDATE_SIZE(CMouseControllerState, 0x10);

class CMousePointerStateHelper
{
public:
	bool bInvertHorizontally;
	bool bInvertVertically;
	
	CMouseControllerState GetMouseSetUp();
};

VALIDATE_SIZE(CMousePointerStateHelper, 0x2);

extern CMousePointerStateHelper &MousePointerStateHelper;


class CKeyboardState
{
public:
	int16 F[12];
	int16 VK_KEYS[256];
	int16 ESC;
	int16 INS;
	int16 DEL;
	int16 HOME;
	int16 END;
	int16 PGUP;
	int16 PGDN;
	int16 UP;
	int16 DOWN;
	int16 LEFT;
	int16 RIGHT;
	int16 SCROLLLOCK;
	int16 PAUSE;
	int16 NUMLOCK;
	int16 DIV;
	int16 MUL;
	int16 SUB;
	int16 ADD;
	int16 ENTER;
	int16 DECIMAL;
	int16 NUM1;
	int16 NUM2;
	int16 NUM3;
	int16 NUM4;
	int16 NUM5;
	int16 NUM6;
	int16 NUM7;
	int16 NUM8;
	int16 NUM9;
	int16 NUM0;
	int16 BACKSP;
	int16 TAB;
	int16 CAPSLOCK;
	int16 EXTENTER;
	int16 LSHIFT;
	int16 RSHIFT;
	int16 SHIFT;
	int16 LCTRL;
	int16 RCTRL;
	int16 LALT;
	int16 RALT;
	int16 LWIN;
	int16 RWIN;
	int16 APPS;
	
	void Clear();
};

VALIDATE_SIZE(CKeyboardState, 0x270);

enum
{
	// taken from miss2
	PAD1 = 0,
	PAD2,
	
	MAX_PADS
};

class CPad
{
public:
	CControllerState NewState;
	CControllerState OldState;
	CControllerState PCTempKeyState;
	CControllerState PCTempJoyState;
	CControllerState PCTempMouseState;
	// straight out of my IDB
	int16 Phase;
	int16 Mode;
	int16 ShakeDur;
	uint8 ShakeFreq;
	int8 bHornHistory[5];
	uint8 iCurrHornHistory;
	bool DisablePlayerControls;
	int8 bApplyBrakes;
	char _unk[12]; //int32 unk[3];
	char _pad0[3];
	int32 LastTimeTouched;
	int32 AverageWeapon;
	int32 AverageEntries;
	
	CPad() { }
	~CPad() { }

	static bool &bDisplayNoControllerMessage;
	static bool &bObsoleteControllerMessage;
	static bool &m_bMapPadOneToPadTwo;
	
	static CKeyboardState &OldKeyState;
	static CKeyboardState &NewKeyState;
	static CKeyboardState &TempKeyState;
	static char KeyBoardCheatString[18];
	static CMouseControllerState &OldMouseControllerState;
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &PCTempMouseControllerState;
	
	
	
	
	void Clear(bool bResetPlayerControls);
	void ClearMouseHistory();
	void UpdateMouse();
	CControllerState ReconcileTwoControllersInput(CControllerState const &State1, CControllerState const &State2);
	void StartShake(int16 nDur, uint8 nFreq);
	void StartShake_Distance(int16 nDur, uint8 nFreq, float fX, float fY, float fz);
	void StartShake_Train(float fX, float fY);
	void AddToPCCheatString(char c);

	static void UpdatePads(void);
	void ProcessPCSpecificStuff(void);
	void Update(int16 unk);
	
	static void DoCheats(void);
	void DoCheats(int16 unk);
	
	static void StopPadsShaking(void);
	void StopShaking(int16 unk);
	
	static CPad *GetPad(int32 pad);
	
	int16 GetSteeringLeftRight(void);
	int16 GetSteeringUpDown(void);
	int16 GetCarGunUpDown(void);
	int16 GetCarGunLeftRight(void);
	int16 GetPedWalkLeftRight(void);
	int16 GetPedWalkUpDown(void);
	int16 GetAnalogueUpDown(void);
	bool GetLookLeft(void);
	bool GetLookRight(void);
	bool GetLookBehindForCar(void);
	bool GetLookBehindForPed(void);
	bool GetHorn(void);
	bool HornJustDown(void);
	bool GetCarGunFired(void);
	bool CarGunJustDown(void);
	int16 GetHandBrake(void);
	int16 GetBrake(void);
	bool GetExitVehicle(void);
	bool ExitVehicleJustDown(void);
	int32 GetWeapon(void);
	bool WeaponJustDown(void);
	int16 GetAccelerate(void);
	bool CycleCameraModeUpJustDown(void);
	bool CycleCameraModeDownJustDown(void);
	bool ChangeStationJustDown(void);
	bool CycleWeaponLeftJustDown(void);
	bool CycleWeaponRightJustDown(void);
	bool GetTarget(void);
	bool TargetJustDown(void);
	bool JumpJustDown(void);
	bool GetSprint(void);
	bool ShiftTargetLeftJustDown(void);
	bool ShiftTargetRightJustDown(void);
	bool GetAnaloguePadUp(void);
	bool GetAnaloguePadDown(void);
	bool GetAnaloguePadLeft(void);
	bool GetAnaloguePadRight(void);
	bool GetAnaloguePadLeftJustUp(void);
	bool GetAnaloguePadRightJustUp(void);
	bool ForceCameraBehindPlayer(void);
	bool SniperZoomIn(void);
	bool SniperZoomOut(void);
	int16 SniperModeLookLeftRight(void);
	int16 SniperModeLookUpDown(void);
	int16 LookAroundLeftRight(void);
	int16 LookAroundUpDown(void);
	void ResetAverageWeapon(void);
	static void PrintErrorMessage(void);
	static void ResetCheats(void);
	static char *EditString(char *pStr, int32 nSize);
	static int32 *EditCodesForControls(int32 *pRsKeys, int32 nSize);

	// mouse
	bool GetLeftMouseJustDown() { return !!(NewMouseControllerState.LMB && !OldMouseControllerState.LMB); }

	// keyboard
	
	bool GetCharJustDown(int32 c) { return !!(NewKeyState.VK_KEYS[c] && !OldKeyState.VK_KEYS[c]); }
	bool GetFJustDown(int32 n)   { return !!(NewKeyState.F[n] && !OldKeyState.F[n]); }
	bool GetEscapeJustDown()     { return !!(NewKeyState.ESC && !OldKeyState.ESC); }
	bool GetInsertJustDown()     { return !!(NewKeyState.INS && !OldKeyState.INS); }
	bool GetDeleteJustDown()     { return !!(NewKeyState.DEL && !OldKeyState.DEL); }
	bool GetHomeJustDown()       { return !!(NewKeyState.HOME && !OldKeyState.HOME); }
	bool GetEndJustDown()        { return !!(NewKeyState.END && !OldKeyState.END); }
	bool GetPageUpJustDown()     { return !!(NewKeyState.PGUP && !OldKeyState.PGUP); }
	bool GetPageDownJustDown()   { return !!(NewKeyState.PGDN && !OldKeyState.PGDN); }
	bool GetUpJustDown()         { return !!(NewKeyState.UP && !OldKeyState.UP); }
	bool GetDownJustDown()       { return !!(NewKeyState.DOWN && !OldKeyState.DOWN); }
	bool GetLeftJustDown()       { return !!(NewKeyState.LEFT && !OldKeyState.LEFT); }
	bool GetRightJustDown()      { return !!(NewKeyState.RIGHT && !OldKeyState.RIGHT); }
	bool GetScrollLockJustDown() { return !!(NewKeyState.SCROLLLOCK && !OldKeyState.SCROLLLOCK); }
	bool GetPauseJustDown()      { return !!(NewKeyState.PAUSE && !OldKeyState.PAUSE); }
	bool GetNumLockJustDown()    { return !!(NewKeyState.NUMLOCK && !OldKeyState.NUMLOCK); }
	bool GetDivideJustDown()     { return !!(NewKeyState.DIV && !OldKeyState.DIV); }
	bool GetTimesJustDown()      { return !!(NewKeyState.MUL && !OldKeyState.MUL); }
	bool GetMinusJustDown()      { return !!(NewKeyState.SUB && !OldKeyState.SUB); }
	bool GetPlusJustDown()       { return !!(NewKeyState.ADD && !OldKeyState.ADD); }
	bool GetPadEnterJustDown()   { return !!(NewKeyState.ENTER && !OldKeyState.ENTER); } //  GetEnterJustDown
	bool GetPadDelJustDown()     { return !!(NewKeyState.DECIMAL && !OldKeyState.DECIMAL); }
	bool GetPad1JustDown()       { return !!(NewKeyState.NUM1 && !OldKeyState.NUM1); }
	bool GetPad2JustDown()       { return !!(NewKeyState.NUM2 && !OldKeyState.NUM2); }
	bool GetPad3JustDown()       { return !!(NewKeyState.NUM3 && !OldKeyState.NUM3); }
	bool GetPad4JustDown()       { return !!(NewKeyState.NUM4 && !OldKeyState.NUM4); }
	bool GetPad5JustDown()       { return !!(NewKeyState.NUM5 && !OldKeyState.NUM5); }
	bool GetPad6JustDown()       { return !!(NewKeyState.NUM6 && !OldKeyState.NUM6); }
	bool GetPad7JustDown()       { return !!(NewKeyState.NUM7 && !OldKeyState.NUM7); }
	bool GetPad8JustDown()       { return !!(NewKeyState.NUM8 && !OldKeyState.NUM8); }
	bool GetPad9JustDown()       { return !!(NewKeyState.NUM9 && !OldKeyState.NUM9); }
	bool GetPad0JustDown()       { return !!(NewKeyState.NUM0 && !OldKeyState.NUM0); }
	bool GetBackspaceJustDown()  { return !!(NewKeyState.BACKSP && !OldKeyState.BACKSP); }
	bool GetTabJustDown()        { return !!(NewKeyState.TAB && !OldKeyState.TAB); }
	bool GetCapsLockJustDown()   { return !!(NewKeyState.CAPSLOCK && !OldKeyState.CAPSLOCK); }
	bool GetEnterJustDown()      { return !!(NewKeyState.EXTENTER && !OldKeyState.EXTENTER); }
	bool GetLeftShiftJustDown()  { return !!(NewKeyState.LSHIFT && !OldKeyState.LSHIFT); }
	bool GetShiftJustDown()      { return !!(NewKeyState.SHIFT && !OldKeyState.SHIFT); }
	bool GetRightShiftJustDown() { return !!(NewKeyState.RSHIFT && !OldKeyState.RSHIFT); }
	bool GetLeftCtrlJustDown()   { return !!(NewKeyState.LCTRL && !OldKeyState.LCTRL); }
	bool GetRightCtrlJustDown()  { return !!(NewKeyState.RCTRL && !OldKeyState.RCTRL); }
	bool GetLeftAltJustDown()    { return !!(NewKeyState.LALT && !OldKeyState.LALT); }
	bool GetRightAltJustDown()   { return !!(NewKeyState.RALT && !OldKeyState.RALT); }
	bool GetLeftWinJustDown()    { return !!(NewKeyState.LWIN && !OldKeyState.LWIN); }
	bool GetRightWinJustDown()   { return !!(NewKeyState.RWIN && !OldKeyState.RWIN); }
	bool GetAppsJustDown()       { return !!(NewKeyState.APPS && !OldKeyState.APPS); }
	
	// pad

	bool GetTriangleJustDown()       { return !!(NewState.Triangle && !OldState.Triangle); }
	bool GetCircleJustDown()         { return !!(NewState.Circle && !OldState.Circle); }
	bool GetCrossJustDown()          { return !!(NewState.Cross && !OldState.Cross); }
	bool GetSquareJustDown()         { return !!(NewState.Square && !OldState.Square); }
	bool GetDPadUpJustDown()         { return !!(NewState.DPadUp && !OldState.DPadUp); }
	bool GetDPadDownJustDown()       { return !!(NewState.DPadDown && !OldState.DPadDown); }
	bool GetDPadLeftJustDown()       { return !!(NewState.DPadLeft && !OldState.DPadLeft); }
	bool GetDPadRightJustDown()      { return !!(NewState.DPadRight && !OldState.DPadRight); }
	bool GetLeftShoulder1JustDown()  { return !!(NewState.LeftShoulder1 && !OldState.LeftShoulder1); }
	bool GetLeftShoulder2JustDown()  { return !!(NewState.LeftShoulder2 && !OldState.LeftShoulder2); }
	bool GetRightShoulder1JustDown() { return !!(NewState.RightShoulder1 && !OldState.RightShoulder1); }
	bool GetRightShoulder2JustDown() { return !!(NewState.RightShoulder2 && !OldState.RightShoulder2); }
	
	int32 GetLeftShoulder1(void)  { return NewState.LeftShoulder1; }
	int32 GetLeftShoulder2(void)  { return NewState.LeftShoulder2; }
	int32 GetRightShoulder1(void) { return NewState.RightShoulder1; }
	int32 GetRightShoulder2(void) { return NewState.RightShoulder2; }
};
VALIDATE_SIZE(CPad, 0xFC);

#define IsButtonJustDown(pad, btn) \
	(!(pad)->OldState.btn && (pad)->NewState.btn)
	
void LittleTest(void);
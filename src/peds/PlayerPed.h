#pragma once

#include "Ped.h"
#include "Wanted.h"
#include "Pad.h"

class CPlayerPed : public CPed
{
public:
	CWanted *m_pWanted;
	CCopPed *m_pArrestingCop;
	float m_fMoveSpeed;
	float m_fCurrentStamina;
	float m_fMaxStamina;
	float m_fStaminaProgress;
	int8 m_nSelectedWepSlot;	// eWeaponType
	bool m_bSpeedTimerFlag;
	uint8 m_nEvadeAmount;
	int8 field_1367;
	uint32 m_nSpeedTimer;
	int32 m_nShotDelay;
	float field_1376;	// m_fAttackButtonCounter?
	bool m_bHaveTargetSelected;	// may have better name
	int8 field_1381;
	int8 field_1382;
	int8 field_1383;
	CEntity *m_pEvadingFrom;	// is this CPhysical?
	int32 m_nTargettableObjects[4];
	bool m_bAdrenalineActive;
	bool m_bHasLockOnTarget;
	int8 field_1406;
	int8 field_1407;
	uint32 m_nAdrenalineTime;
	bool m_bCanBeDamaged;
	int8 field_1413;
	int8 field_1414;
	int8 field_1415;
	CVector m_vecSafePos[6]; // safe places from the player, for example behind a tree
	CPed *m_pPedAtSafePos[6];
	float m_fWalkAngle;
	float m_fFPSMoveHeading;

	CPlayerPed();
	~CPlayerPed();
	void SetMoveAnim() { };

	void ReApplyMoveAnims(void);
	void ClearWeaponTarget(void);
	void SetWantedLevel(int32 level);
	void SetWantedLevelNoDrop(int32 level);
	void KeepAreaAroundPlayerClear(void);
	void AnnoyPlayerPed(bool);
	void MakeChangesForNewWeapon(int8);
	void SetInitialState(void);
	void ProcessControl(void);
	void ClearAdrenaline(void);
	void UseSprintEnergy(void);
	class CPlayerInfo *GetPlayerInfoForThisPlayerPed();
	void SetRealMoveAnim(void);
	void RestoreSprintEnergy(float);
	bool DoWeaponSmoothSpray(void);
	void DoStuffToGoOnFire(void);
	bool DoesTargetHaveToBeBroken(CVector, CWeapon*);
	void RunningLand(CPad*);
	bool IsThisPedAttackingPlayer(CPed*);
	void PlayerControlSniper(CPad*);
	void PlayerControlM16(CPad*);
	void PlayerControlFighter(CPad*);
	void ProcessWeaponSwitch(CPad*);
	void MakeObjectTargettable(int32);
	void PlayerControl1stPersonRunAround(CPad *padUsed);
	void EvaluateNeighbouringTarget(CEntity*, CEntity**, float*, float, float, bool);
	void EvaluateTarget(CEntity*, CEntity**, float*, float, float, bool);
	bool FindNextWeaponLockOnTarget(CEntity*, bool);
	bool FindWeaponLockOnTarget(void);
	void ProcessAnimGroups(void);
	void ProcessPlayerWeapon(CPad*);
	void PlayerControlZelda(CPad*);

	static void SetupPlayerPed(int32);
	static void DeactivatePlayerPed(int32);
	static void ReactivatePlayerPed(int32);
};

static_assert(sizeof(CPlayerPed) == 0x5F0, "CPlayerPed: error");

#include "common.h"
#include "patcher.h"
#include "main.h"
#include "Darkel.h"
#include "PlayerPed.h"
#include "Timer.h"
#include "DMAudio.h"
#include "Population.h"
#include "Weapon.h"
#include "World.h"
#include "Stats.h"
#include "Font.h"
#include "Text.h"
#include "Vehicle.h"

#define FRENZY_ANY_PED -1
#define FRENZY_ANY_CAR -2

int32 &CDarkel::TimeLimit = *(int32*)0x885BAC;
int32 &CDarkel::PreviousTime = *(int32*)0x885B00;
int32 &CDarkel::TimeOfFrenzyStart = *(int32*)0x9430D8;
int32 &CDarkel::WeaponType = *(int32*)0x9430F0;
int32 &CDarkel::AmmoInterruptedWeapon = *(int32*)0x8E29C8;
int32 &CDarkel::KillsNeeded = *(int32*)0x8F1AB8;
int8 &CDarkel::InterruptedWeapon = *(int8*)0x95CD60;

/*
 * bStandardSoundAndMessages is a completely beta thing,
 * makes game handle sounds & messages instead of SCM (just like in GTA2)
 * but it's never been used in the game. Has unused sliding text when frenzy completed etc.
 */
int8 &CDarkel::bStandardSoundAndMessages = *(int8*)0x95CDB6;
int8 &CDarkel::bNeedHeadShot = *(int8*)0x95CDCA;
int8 &CDarkel::bProperKillFrenzy = *(int8*)0x95CD98;
uint16 &CDarkel::Status = *(uint16*)0x95CCB4;
uint16 (&CDarkel::RegisteredKills)[NUM_DEFAULT_MODELS] = *(uint16(*)[NUM_DEFAULT_MODELS]) * (uintptr*)0x6EDBE0;
int32 &CDarkel::ModelToKill = *(int32*)0x8F2C78;
int32 &CDarkel::ModelToKill2 = *(int32*)0x885B40;
int32 &CDarkel::ModelToKill3 = *(int32*)0x885B3C;
int32 &CDarkel::ModelToKill4 = *(int32*)0x885B34;
wchar *CDarkel::pStartMessage = (wchar*)0x8F2C08;

uint8
CDarkel::CalcFade(uint32 time, uint32 start, uint32 end)
{
	if (time >= start && time <= end) {
		if (time >= start + 500) {
			if (time <= end - 500)
				return 255;
			else
				return 255 * (end - time) / 500;
		} else
			return 255 * (time - start) / 500;
	} else
		return 0;
}

// Screen positions taken from VC
void
CDarkel::DrawMessages()
{
	switch (Status) {
		case KILLFRENZY_ONGOING:
		{
			CFont::SetJustifyOff();
			CFont::SetBackgroundOff();
			CFont::SetCentreSize(SCREEN_SCALE_FROM_RIGHT(30.0f));
			CFont::SetCentreOn();
			CFont::SetPropOn();
			uint32 timePassedSinceStart = CTimer::GetTimeInMilliseconds() - CDarkel::TimeOfFrenzyStart;
			if (CDarkel::bStandardSoundAndMessages) {
				if (timePassedSinceStart >= 3000 && timePassedSinceStart < 11000) {
					CFont::SetScale(SCREEN_SCALE_X(1.3f), SCREEN_SCALE_Y(1.3f));
					CFont::SetJustifyOff();
					CFont::SetColor(CRGBA(255, 255, 128, CalcFade(timePassedSinceStart, 3000, 11000)));
					CFont::SetFontStyle(FONT_BANK);
					if (pStartMessage) {
						CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, pStartMessage);
					}
				}
			} else {
				if (timePassedSinceStart < 8000) {
					CFont::SetScale(SCREEN_SCALE_X(1.3f), SCREEN_SCALE_Y(1.3f));
					CFont::SetJustifyOff();
					CFont::SetColor(CRGBA(255, 255, 128, CalcFade(timePassedSinceStart, 0, 8000)));
					CFont::SetFontStyle(FONT_BANK);
					if (pStartMessage) {
						CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, pStartMessage);
					}
				}
			}
			CFont::SetScale(SCREEN_SCALE_X(0.75f), SCREEN_SCALE_Y(1.5f));
			CFont::SetCentreOff();
			CFont::SetRightJustifyOn();
			CFont::SetFontStyle(FONT_HEADING);
			if (CDarkel::TimeLimit >= 0) {
				uint32 timeLeft = CDarkel::TimeLimit - (CTimer::GetTimeInMilliseconds() - CDarkel::TimeOfFrenzyStart);
				sprintf(gString, "%d:%02d", timeLeft / 60000, timeLeft % 60000 / 1000);
				AsciiToUnicode(gString, gUString);
				if (timeLeft > 4000 || CTimer::GetFrameCounter() & 1) {
					CFont::SetColor(CRGBA(0, 0, 0, 255));
					CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(35.0f), SCREEN_SCALE_Y(109.0f), gUString);
					CFont::SetColor(CRGBA(150, 100, 255, 255));
					CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(34.0f), SCREEN_SCALE_Y(108.0f), gUString);
				}
			}
			sprintf(gString, "%d", (CDarkel::KillsNeeded >= 0 ? CDarkel::KillsNeeded : 0));
			AsciiToUnicode(gString, gUString);
			CFont::SetColor(CRGBA(0, 0, 0, 255));
			CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(35.0f), SCREEN_SCALE_Y(144.0f), gUString);
			CFont::SetColor(CRGBA(255, 128, 128, 255));
			CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(34.0f), SCREEN_SCALE_Y(143.0f), gUString);
			break;
		}
		case KILLFRENZY_PASSED:
		{
			if (CDarkel::bStandardSoundAndMessages) {
				uint32 timePassedSinceStart = CTimer::GetTimeInMilliseconds() - CDarkel::TimeOfFrenzyStart;
				if (CTimer::GetTimeInMilliseconds() - CDarkel::TimeOfFrenzyStart < 5000) {
					CFont::SetBackgroundOff();
					CFont::SetCentreSize(SCREEN_SCALE_FROM_RIGHT(20.0f));
					CFont::SetCentreOn();
					CFont::SetScale(SCREEN_SCALE_X(1.5f), SCREEN_SCALE_Y(1.5f));
					CFont::SetJustifyOff();
					CFont::SetColor(CRGBA(128, 255, 128, CalcFade(timePassedSinceStart, 0, 5000)));
					CFont::SetFontStyle(FONT_BANK);
					int y = SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(25.0f - timePassedSinceStart * 0.01f);
					CFont::PrintString(SCREEN_WIDTH / 2, y, TheText.Get("KF_3"));
				}
			}
			break;
		}
		default:
			break;
	}
}

void
CDarkel::Init()
{
	Status = KILLFRENZY_NONE;
}

uint16
CDarkel::QueryModelsKilledByPlayer(int32 modelId)
{
	return RegisteredKills[modelId];
}


bool
CDarkel::FrenzyOnGoing()
{
	return Status == KILLFRENZY_ONGOING;
}


uint16
CDarkel::ReadStatus()
{
	return Status;
}

#if 0
WRAPPER void CDarkel::RegisterCarBlownUpByPlayer(CVehicle *vehicle) { EAXJMP(0x421070); }
#else
void
CDarkel::RegisterCarBlownUpByPlayer(CVehicle *vehicle)
{
	if (FrenzyOnGoing()) {
		int32 model = vehicle->GetModelIndex();
		if (ModelToKill == FRENZY_ANY_CAR || ModelToKill == model || ModelToKill2 == model || ModelToKill3 == model || ModelToKill4 == model) {
			KillsNeeded--;
			DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_CAR_BLOWN, 0);
		}
	}
	RegisteredKills[vehicle->GetModelIndex()]++;
	CStats::CarsExploded++;
}
#endif

#if 0
WRAPPER void CDarkel::RegisterKillByPlayer(CPed *victim, eWeaponType weapontype, bool headshot) { EAXJMP(0x420F60); }
#else
void
CDarkel::RegisterKillByPlayer(CPed *victim, eWeaponType weapon, bool headshot)
{
	if (FrenzyOnGoing() && (weapon == WeaponType
			|| weapon == WEAPONTYPE_EXPLOSION
			|| weapon == WEAPONTYPE_UZI_DRIVEBY && WeaponType == WEAPONTYPE_UZI
			|| weapon == WEAPONTYPE_RAMMEDBYCAR && WeaponType == WEAPONTYPE_RUNOVERBYCAR
			|| weapon == WEAPONTYPE_RUNOVERBYCAR && WeaponType == WEAPONTYPE_RAMMEDBYCAR
			|| weapon == WEAPONTYPE_FLAMETHROWER && WeaponType == WEAPONTYPE_MOLOTOV)) {
		int32 model = victim->GetModelIndex();
		if (ModelToKill == FRENZY_ANY_PED || ModelToKill == model || ModelToKill2 == model || ModelToKill3 == model || ModelToKill4 == model) {
			if (!bNeedHeadShot || headshot) {
				KillsNeeded--;
				DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_KILL, 0);
			}
		}
	}
	CStats::PeopleKilledByPlayer++;
	RegisteredKills[victim->GetModelIndex()]++;
	CStats::PedsKilledOfThisType[victim->bChrisCriminal ? PEDTYPE_CRIMINAL : victim->m_nPedType]++;
	if (headshot)
		CStats::HeadsPopped++;
	CStats::KillsSinceLastCheckpoint++;
}
#endif

void
CDarkel::RegisterKillNotByPlayer(CPed* victim, eWeaponType weapontype)
{
	CStats::PeopleKilledByOthers++;
}

void
CDarkel::ResetModelsKilledByPlayer()
{
	for (int i = 0; i < NUM_DEFAULT_MODELS; i++)
		RegisteredKills[i] = 0;
}

#if 0
WRAPPER void CDarkel::ResetOnPlayerDeath() { EAXJMP(0x420E70); }
#else
void
CDarkel::ResetOnPlayerDeath()
{
	if (Status != KILLFRENZY_ONGOING)
		return;

	CPopulation::m_AllRandomPedsThisType = -1;
	Status = KILLFRENZY_FAILED;
	TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

	eWeaponType fixedWeapon;
	if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
		fixedWeapon = WEAPONTYPE_UZI;
	else
		fixedWeapon = (eWeaponType)WeaponType;

	CPlayerPed *player = FindPlayerPed();
	if (fixedWeapon < WEAPONTYPE_TOTALWEAPONS) {
		player->m_nSelectedWepSlot = InterruptedWeapon;
		player->GetWeapon(player->GetWeaponSlot(fixedWeapon)).m_nAmmoTotal = CDarkel::AmmoInterruptedWeapon;
	}

	if (FindPlayerVehicle()) {
		player->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(player->GetWeapon()->m_eWeaponType)->m_nModelId);
		player->m_currentWeapon = player->m_nSelectedWepSlot;
		player->MakeChangesForNewWeapon(player->m_currentWeapon);
	}
}
#endif

#if 0
WRAPPER void CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, uint16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot) { EAXJMP(0x4210E0); }
#else
void
CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, uint16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot)
{
	eWeaponType fixedWeapon;
	if (weaponType == WEAPONTYPE_UZI_DRIVEBY)
		fixedWeapon = WEAPONTYPE_UZI;
	else
		fixedWeapon = weaponType;

	WeaponType = weaponType;
	Status = KILLFRENZY_ONGOING;
	KillsNeeded = kill;
	ModelToKill = modelId0;
	ModelToKill2 = modelId2;
	ModelToKill3 = modelId3;
	ModelToKill4 = modelId4;
	pStartMessage = text;

	if (text == TheText.Get("PAGE_00")) {
		CDarkel::bProperKillFrenzy = 1;
		CDarkel::pStartMessage = 0;
	} else
		bProperKillFrenzy = 0;
	
	bStandardSoundAndMessages = standardSound;
	bNeedHeadShot = needHeadShot;
	TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();
	TimeLimit = time;
	PreviousTime = time / 1000;

	CPlayerPed *player = FindPlayerPed();
	if (fixedWeapon < WEAPONTYPE_TOTALWEAPONS) {
		InterruptedWeapon = player->m_currentWeapon;
		player->GiveWeapon(fixedWeapon, 0);
		AmmoInterruptedWeapon = player->GetWeapon(player->GetWeaponSlot(fixedWeapon)).m_nAmmoTotal;
		player->GiveWeapon(fixedWeapon, 30000);
		player->m_nSelectedWepSlot = player->GetWeaponSlot(fixedWeapon);
		player->MakeChangesForNewWeapon(player->m_nSelectedWepSlot);

		if (FindPlayerVehicle()) {
			player->m_currentWeapon = player->m_nSelectedWepSlot;
			player->GetWeapon()->m_nAmmoInClip = min(player->GetWeapon()->m_nAmmoTotal, CWeaponInfo::GetWeaponInfo(player->GetWeapon()->m_eWeaponType)->m_nAmountofAmmunition);
			player->ClearWeaponTarget();
		}
	}
	if (CDarkel::bStandardSoundAndMessages)
		DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_START, 0);
}
#endif

void
CDarkel::Update()
{
	if (Status != KILLFRENZY_ONGOING)
		return;

	int32 FrameTime = TimeLimit - (CTimer::GetTimeInMilliseconds() - TimeOfFrenzyStart);
	if (FrameTime > 0 || TimeLimit < 0) {

		DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_ONGOING, FrameTime);

		int32 PrevTime = FrameTime / 1000;

		if (PrevTime != PreviousTime) {
			if (PreviousTime < 12)
				DMAudio.PlayFrontEndSound(SOUND_CLOCK_TICK, PrevTime);
			PreviousTime = PrevTime;
		}

	} else {
		CPopulation::m_AllRandomPedsThisType = -1;
		Status = KILLFRENZY_FAILED;
		TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

		eWeaponType fixedWeapon;
		if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
			fixedWeapon = WEAPONTYPE_UZI;
		else
			fixedWeapon = (eWeaponType)WeaponType;

		CPlayerPed *player = FindPlayerPed();
		if (fixedWeapon < WEAPONTYPE_TOTALWEAPONS) {
			player->m_nSelectedWepSlot = InterruptedWeapon;
			player->GetWeapon(player->GetWeaponSlot(fixedWeapon)).m_nAmmoTotal = CDarkel::AmmoInterruptedWeapon;
		}

		if (FindPlayerVehicle()) {
			player->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(player->GetWeapon()->m_eWeaponType)->m_nModelId);
			player->m_currentWeapon = player->m_nSelectedWepSlot;
			player->MakeChangesForNewWeapon(player->m_currentWeapon);
		}

		if (bStandardSoundAndMessages)
			DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_FAILED, 0);
	}

	if (KillsNeeded <= 0) {
		CPopulation::m_AllRandomPedsThisType = -1;
		Status = KILLFRENZY_PASSED;

		if (bProperKillFrenzy)
			CStats::AnotherKillFrenzyPassed();

		TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

		FindPlayerPed()->m_pWanted->SetWantedLevel(0);

		eWeaponType fixedWeapon;
		if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
			fixedWeapon = WEAPONTYPE_UZI;
		else
			fixedWeapon = (eWeaponType)WeaponType;

		CPlayerPed* player = FindPlayerPed();
		if (fixedWeapon < WEAPONTYPE_TOTALWEAPONS) {
			player->m_nSelectedWepSlot = InterruptedWeapon;
			player->GetWeapon(player->GetWeaponSlot(fixedWeapon)).m_nAmmoTotal = CDarkel::AmmoInterruptedWeapon;
		}

		if (FindPlayerVehicle()) {
			player->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(player->GetWeapon()->m_eWeaponType)->m_nModelId);
			player->m_currentWeapon = player->m_nSelectedWepSlot;
			player->MakeChangesForNewWeapon(player->m_currentWeapon);
		}

		if (bStandardSoundAndMessages)
			DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_PASSED, 0);
	}
}

STARTPATCHES
	InjectHook(0x421380, CDarkel::CalcFade, PATCH_JUMP);
	InjectHook(0x420650, CDarkel::Init, PATCH_JUMP);
	InjectHook(0x420660, CDarkel::Update, PATCH_JUMP);
	InjectHook(0x420E60, CDarkel::FrenzyOnGoing, PATCH_JUMP);
	InjectHook(0x420E50, CDarkel::ReadStatus, PATCH_JUMP);
	InjectHook(0x420E70, CDarkel::ResetOnPlayerDeath, PATCH_JUMP);
	InjectHook(0x4210E0, CDarkel::StartFrenzy, PATCH_JUMP);
	InjectHook(0x421370, CDarkel::QueryModelsKilledByPlayer, PATCH_JUMP);
	InjectHook(0x421060, CDarkel::RegisterKillNotByPlayer, PATCH_JUMP);
	InjectHook(0x421310, CDarkel::ResetModelsKilledByPlayer, PATCH_JUMP);
	InjectHook(0x420920, CDarkel::DrawMessages, PATCH_JUMP);
	InjectHook(0x421070, CDarkel::RegisterCarBlownUpByPlayer, PATCH_JUMP);
	InjectHook(0x420F60, CDarkel::RegisterKillByPlayer, PATCH_JUMP);
ENDPATCHES
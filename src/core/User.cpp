#include "common.h"
#include "patcher.h"

#include "Hud.h"
#include "PlayerPed.h"
#include "Text.h"
#include "User.h"
#include "Vehicle.h"
#include "World.h"
#include "Zones.h"

CPlaceName& CUserDisplay::PlaceName = *(CPlaceName*)0x8F29BC;
COnscreenTimer& CUserDisplay::OnscnTimer = *(COnscreenTimer*)0x862238;
CPager& CUserDisplay::Pager = *(CPager*)0x8F2744;
CCurrentVehicle& CUserDisplay::CurrentVehicle = *(CCurrentVehicle*)0x8F5FE8;

CPlaceName::CPlaceName()
{
	Init();
}

void
CPlaceName::Init()
{
	m_pZone = nil;
	m_pZone2 = nil;
	m_nAdditionalTimer = 0;
}

void
CPlaceName::Process()
{
	CVector pos = CWorld::Players[CWorld::PlayerInFocus].GetPos();
	CZone *navigZone = CTheZones::FindSmallestZonePositionType(&pos, ZONE_TYPE1);
	CZone *audioZone = CTheZones::FindSmallestZonePositionType(&pos, ZONE_AUDIO);

	if (navigZone == nil) m_pZone = nil;
	if (audioZone == nil) m_pZone2 = nil;

	if (navigZone == m_pZone) {
		if (audioZone == m_pZone2 || m_pZone != nil) {
			if (navigZone != nil || audioZone != nil) {
				if (m_nAdditionalTimer != 0)
					m_nAdditionalTimer--;
			} else {
				m_nAdditionalTimer = 0;
				m_pZone = nil;
				m_pZone2 = nil;
			}
		} else {
			m_pZone2 = audioZone;
			m_nAdditionalTimer = 250;
		}
	} else {
		m_pZone = navigZone;
		m_nAdditionalTimer = 250;
	}
	Display();
}

void
CPlaceName::Display()
{
	wchar *text;
	if (m_pZone != nil)
		text = m_pZone->GetTranslatedName();
	else if (m_pZone2 != nil)
		text = m_pZone2->GetTranslatedName();
#ifdef FIX_BUGS
	else
		text = nil;
#endif
	CHud::SetZoneName(text);
}

CCurrentVehicle::CCurrentVehicle()
{
	Init();
}

void
CCurrentVehicle::Init()
{
	m_pCurrentVehicle = nil;
}

void
CCurrentVehicle::Process()
{
	if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->InVehicle())
		m_pCurrentVehicle = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pMyVehicle;
	else
		m_pCurrentVehicle = nil;
	Display();
}

void
CCurrentVehicle::Display()
{
	wchar *text = nil;
	if (m_pCurrentVehicle != nil)
		text = TheText.Get(((CVehicleModelInfo*)CModelInfo::GetModelInfo(m_pCurrentVehicle->GetModelIndex()))->m_gameName);
	CHud::SetVehicleName(text);
}

void
CUserDisplay::Init()
{
	PlaceName.Init();
	OnscnTimer.Init();
	Pager.Init();
	CurrentVehicle.Init();
}

void
CUserDisplay::Process()
{
	PlaceName.Process();
	OnscnTimer.Process();
	Pager.Process();
	CurrentVehicle.Process();
}

STARTPATCHES
	InjectHook(0x4AD4C0, &CPlaceName::Init, PATCH_JUMP);
	InjectHook(0x4AD4E0, &CPlaceName::Process, PATCH_JUMP);
	InjectHook(0x4AD5B0, &CPlaceName::Display, PATCH_JUMP);

	InjectHook(0x4AD5F0, &CCurrentVehicle::Init, PATCH_JUMP);
	InjectHook(0x4AD600, &CCurrentVehicle::Process, PATCH_JUMP);
	InjectHook(0x4AD630, &CCurrentVehicle::Display, PATCH_JUMP);

	InjectHook(0x4AD660, &CUserDisplay::Init, PATCH_JUMP);
	InjectHook(0x4AD690, &CUserDisplay::Process, PATCH_JUMP);
ENDPATCHES
#include "common.h"
#include "patcher.h"
#include "ModelIndices.h"
#include "Gangs.h"

CGangInfo(&CGangs::Gang)[NUM_GANGS] = *(CGangInfo(*)[NUM_GANGS])*(uintptr*)0x6EDF78;

CGangInfo::CGangInfo() :
	m_nVehicleMI(MI_BUS),
	m_nPedModelOverride(-1),
	m_Weapon1(WEAPONTYPE_UNARMED),
	m_Weapon2(WEAPONTYPE_UNARMED)
{}

void CGangs::Initialize(void)
{
	Gang[GANG_MAFIA].m_nVehicleMI = MI_MAFIA;
	Gang[GANG_TRIAD].m_nVehicleMI = MI_BELLYUP;
	Gang[GANG_DIABLOS].m_nVehicleMI = MI_DIABLOS;
	Gang[GANG_YAKUZA].m_nVehicleMI = MI_YAKUZA;
	Gang[GANG_YARDIE].m_nVehicleMI = MI_YARDIE;
	Gang[GANG_COLUMB].m_nVehicleMI = MI_COLUMB;
	Gang[GANG_HOODS].m_nVehicleMI = MI_HOODS;
	Gang[GANG_7].m_nVehicleMI = -1;
	Gang[GANG_8].m_nVehicleMI = -1;
}

void CGangs::SetGangVehicleModel(int16 gang, int32 model)
{
	GetGangInfo(gang)->m_nVehicleMI = model;
}

void CGangs::SetGangWeapons(int16 gang, eWeaponType weapon1, eWeaponType weapon2)
{
	CGangInfo *gi = GetGangInfo(gang);
	gi->m_Weapon1 = weapon1;
	gi->m_Weapon2 = weapon2;
}

void CGangs::SetGangPedModelOverride(int16 gang, int8 ovrd)
{
	GetGangInfo(gang)->m_nPedModelOverride = ovrd;
}

int8 CGangs::GetGangPedModelOverride(int16 gang)
{
	return GetGangInfo(gang)->m_nPedModelOverride;
}

void CGangs::SaveAllGangData(uint8 *buf, uint32 *size)
{
INITSAVEBUF

	*size = SAVE_HEADER_SIZE + sizeof(Gang);
	WriteSaveHeader(buf, 'G','N','G','\0', *size - SAVE_HEADER_SIZE);
	for (int i = 0; i < NUM_GANGS; i++)
		WriteSaveBuf(buf, Gang[i]);

VALIDATESAVEBUF(*size);
}

void CGangs::LoadAllGangData(uint8 *buf, uint32 size)
{
	Initialize();

INITSAVEBUF

	WriteSaveHeader(buf, 'G','N','G','\0', size - SAVE_HEADER_SIZE);
	for (int i = 0; i < NUM_GANGS; i++)
		Gang[i] = ReadSaveBuf<CGangInfo>(buf);

VALIDATESAVEBUF(size);
}

STARTPATCHES
	InjectHook(0x4C3FB0, CGangs::Initialize, PATCH_JUMP);
	InjectHook(0x4C4010, CGangs::SetGangVehicleModel, PATCH_JUMP);
	InjectHook(0x4C4030, CGangs::SetGangWeapons, PATCH_JUMP);
	InjectHook(0x4C4050, CGangs::SetGangPedModelOverride, PATCH_JUMP);
	InjectHook(0x4C4070, CGangs::GetGangPedModelOverride, PATCH_JUMP);
	InjectHook(0x4C4080, CGangs::SaveAllGangData, PATCH_JUMP);
	InjectHook(0x4C4100, CGangs::LoadAllGangData, PATCH_JUMP);
ENDPATCHES

#pragma once

#include "Weapon.h"

struct CGangInfo
{
	int32 m_nVehicleMI;
	int8 m_nPedModelOverride;
	int8 field_5;
	int16 field_6;
	eWeaponType m_Weapon1;
	eWeaponType m_Weapon2;

	CGangInfo();
};

static_assert(sizeof(CGangInfo) == 0x10, "CGangInfo: error");

enum {
	GANG_MAFIA = 0,
	GANG_TRIAD,
	GANG_DIABLOS,
	GANG_YAKUZA,
	GANG_YARDIE,
	GANG_COLUMB,
	GANG_HOODS,
	GANG_7,
	GANG_8,
	NUM_GANGS
};

class CGangs
{
public:
	static void Initialize(void);
	static void SetGangVehicleModel(int16, int32);
	static void SetGangWeapons(int16, eWeaponType, eWeaponType);
	static void SetGangPedModelOverride(int16, int8);
	static int8 GetGangPedModelOverride(int16);
	static void SaveAllGangData(uint8 *, uint32 *);
	static void LoadAllGangData(uint8 *, uint32);

	static int32 GetGangVehicleModel(int16 gang) { return Gang[gang].m_nVehicleMI; }
	static eWeaponType GetGangWeapon1(int16 gang) { return Gang[gang].m_Weapon1; }
	static eWeaponType GetGangWeapon2(int16 gang) { return Gang[gang].m_Weapon2; }
	static CGangInfo* GetGangInfo(int16 gang) { return &Gang[gang]; }

private:

	static CGangInfo(&Gang)[NUM_GANGS];
};

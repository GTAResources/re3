#include "common.h"
#include "patcher.h"
#include "PedPlacement.h"
#include "World.h"

void
CPedPlacement::FindZCoorForPed(CVector* pos)
{
	float zForPed;
	float startZ = pos->z - 100.0f;
	float foundColZ = -100.0f;
	float foundColZ2 = -100.0f;
	CColPoint foundCol;
	CEntity* foundEnt;

	CVector vec(
		pos->x,
		pos->y,
		pos->z + 1.0f
	);

	if (CWorld::ProcessVerticalLine(vec, startZ, foundCol, foundEnt, true, false, false, false, true, false, nil))
		foundColZ = foundCol.point.z;

	// Adjust coords and do a second test
	vec.x += 0.1f;
	vec.y += 0.1f;

	if (CWorld::ProcessVerticalLine(vec, startZ, foundCol, foundEnt, true, false, false, false, true, false, nil))
		foundColZ2 = foundCol.point.z;

	zForPed = max(foundColZ, foundColZ2);

	if (zForPed > -99.0f)
		pos->z = 1.04f + zForPed;
}

CEntity*
CPedPlacement::IsPositionClearOfCars(CVector* pos)
{
	return CWorld::TestSphereAgainstWorld(*pos, 0.25f, nil, true, true, false, false, false, false);
}

bool
CPedPlacement::IsPositionClearForPed(CVector* pos)
{
	int16 count;
	CWorld::FindObjectsKindaColliding(*pos, 0.75f, true, &count, 2, nil, false, true, true, false, false);
	return count == 0;
}

STARTPATCHES
	InjectHook(0x4EE340, &CPedPlacement::FindZCoorForPed, PATCH_JUMP);
	InjectHook(0x4EE310, &CPedPlacement::IsPositionClearOfCars, PATCH_JUMP);
ENDPATCHES

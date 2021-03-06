#pragma once
#include "common.h"

class CVehicle;

class CCranes
{
public:
	static bool IsThisCarBeingTargettedByAnyCrane(CVehicle*);
	static bool IsThisCarBeingCarriedByAnyCrane(CVehicle*);
	static bool IsThisCarPickedUp(float, float, CVehicle*);
	static bool HaveAllCarsBeenCollectedByMilitaryCrane();
	static void ActivateCrane(float, float, float, float, float, float, float, float, bool, bool, float, float);
	static void DeActivateCrane(float, float);
	static void InitCranes(void);
	static void UpdateCranes(void);
};

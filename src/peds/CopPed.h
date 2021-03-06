#pragma once
#include "Ped.h"

enum eCopType
{
	COP_STREET = 0,
	COP_FBI = 1,
	COP_SWAT = 2,
	COP_ARMY = 3,
};

class CCopPed : public CPed
{
public:
	int16 m_wRoadblockNode;
	int8 field_1342;
	int8 field_1343;
	float m_fDistanceToTarget;
	int8 m_bIsInPursuit;
	int8 m_bIsDisabledCop;
	int8 field_1350;
	int8 field_1351;
	int8 m_bZoneDisabledButClose;
	int8 m_bZoneDisabled;
	int8 field_1354;
	int8 field_1355;
	int32 field_1356;
	eCopType m_nCopType;
	int8 field_1364;
	int8 field_1365;
	int8 field_1366;
	int8 field_1367;

	CCopPed(eCopType);
	~CCopPed();

	void ClearPursuit(void);
	void ProcessControl(void);
	void SetArrestPlayer(CPed*);
};

static_assert(sizeof(CCopPed) == 0x558, "CCopPed: error");

#include "common.h"
#include "patcher.h"
#include "Building.h"
#include "Streaming.h"
#include "Pools.h"

void *CBuilding::operator new(size_t sz) { return CPools::GetBuildingPool()->New();  }
void CBuilding::operator delete(void *p, size_t sz) { CPools::GetBuildingPool()->Delete((CBuilding*)p); }

void
CBuilding::ReplaceWithNewModel(int32 id)
{
	DeleteRwObject();

	if(CModelInfo::GetModelInfo(m_modelIndex)->m_refCount == 0)
		CStreaming::RemoveModel(m_modelIndex);
	m_modelIndex = id;

	if(bIsBIGBuilding)
		if(m_level == LEVEL_NONE || m_level == CGame::currLevel)
			CStreaming::RequestModel(id, STREAMFLAGS_DONT_REMOVE);
}

class CBuilding_ : public CBuilding
{
public:
	CBuilding *ctor(void) { return ::new (this) CBuilding(); }
	void dtor(void) { CBuilding::~CBuilding(); }
};

STARTPATCHES
	InjectHook(0x4057D0, &CBuilding_::ctor, PATCH_JUMP);
	InjectHook(0x405800, &CBuilding_::dtor, PATCH_JUMP);
	InjectHook(0x405850, &CBuilding::ReplaceWithNewModel, PATCH_JUMP);
ENDPATCHES

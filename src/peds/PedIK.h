#pragma once
#include "common.h"
#include "PedModelInfo.h"
#include "AnimBlendClumpData.h"

struct LimbOrientation
{
	float phi;
	float theta;
};

struct LimbMovementInfo {
	float maxYaw;
	float minYaw;
	float yawD;
	float maxPitch;
	float minPitch;
	float pitchD;
};

enum LimbMoveStatus {
	ANGLES_SET_TO_MAX, // because given angles were unreachable
	ONE_ANGLE_COULDNT_BE_SET_EXACTLY, // because it can't be reached in a jiffy
	ANGLES_SET_EXACTLY
};

class CPed;

class CPedIK
{
public:
	enum {
		FLAG_1 = 1,
		LOOKING = 2, // looking while in car?
		AIMS_WITH_ARM = 4,
	};

	CPed *m_ped;
	LimbOrientation m_headOrient;
	LimbOrientation m_torsoOrient;
	LimbOrientation m_upperArmOrient;
	LimbOrientation m_lowerArmOrient;
	int32 m_flags;

	static LimbMovementInfo ms_torsoInfo;
	static LimbMovementInfo ms_headInfo;
	static LimbMovementInfo ms_headRestoreInfo;
	static LimbMovementInfo ms_upperArmInfo;
	static LimbMovementInfo ms_lowerArmInfo;

	CPedIK(CPed *ped);
	bool PointGunInDirection(float phi, float theta);
	bool PointGunInDirectionUsingArm(float phi, float theta);
	bool PointGunAtPosition(CVector const& position);
	void GetComponentPosition(RwV3d *pos, PedNode node);
	static RwMatrix *GetWorldMatrix(RwFrame *source, RwMatrix *destination);
	void RotateTorso(AnimBlendFrameData* animBlend, LimbOrientation* limb, bool changeRoll);
	void ExtractYawAndPitchLocal(RwMatrixTag *mat, float *yaw, float *pitch);
	void ExtractYawAndPitchWorld(RwMatrixTag *mat, float *yaw, float *pitch);
	LimbMoveStatus MoveLimb(LimbOrientation &limb, float approxPhi, float approxTheta, LimbMovementInfo &moveInfo);
	bool RestoreGunPosn(void);
	bool LookInDirection(float phi, float theta);
	bool LookAtPosition(CVector const& pos);
	bool RestoreLookAt(void);
};
static_assert(sizeof(CPedIK) == 0x28, "CPedIK: error");

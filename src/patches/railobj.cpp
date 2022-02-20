#include "GX.h"
#include "OS.h"

#include "sms/mapobj/MapObjNormalLift.hxx"

#include "SME.hxx"
#include "defines.h"
#include "macros.h"

#ifdef SME_EXTRA_OBJECTS

void checkInstantReset_NormalLift(u32 *railflags) {
  s16 *mRailObj;
  SME_FROM_GPR(31, mRailObj);

  u32 flag = railflags[2];
  if (flag & 0x2000) {
    mRailObj[0x14A / 2] = 0;
  } else {
    mRailObj[0x14A / 2] = 180;
  }
}

s16 *checkInstantReset_RailObj(s16 *railObj, u32 *railflags) {
  u32 flag = railflags[2];
  if (flag & 0x2000) {
    railObj[0x14A / 2] = 0;
  } else {
    railObj[0x14A / 2] = 180;
  }
  *reinterpret_cast<u8 *>(railObj[0x148 / 2]) = 2;
  return railObj;
}
SME_PATCH_BL(SME_PORT_REGION(0x801F0B90, 0, 0, 0),
             checkInstantReset_NormalLift);
SME_PATCH_B(SME_PORT_REGION(0x801F1054, 0, 0, 0), checkInstantReset_RailObj);

void checkResetToNode(TNormalLift *lift) {
  TGraphWeb *graph = lift->mGraphTracer->mGraph;
  TRailNode *node;
  {
    s32 nodeIdx = lift->mGraphTracer->mPreviousNode;
    node = reinterpret_cast<TRailNode *>(graph->mNodes[nodeIdx << 2]);
  }
  if (node->mFlags & 0x2000) {
    lift->mPosition.set(
        graph->getNearestPosOnGraphLink(lift->mInitialPosition));
    lift->mRotation.set(lift->mInitialRotation);
    lift->mRailStatus = 0;
    lift->mContextTimer = 180;
    lift->mLastRailStatus = 1;
    {
      int idx = graph->findNearestNodeIndex(lift->mPosition, 0xFFFFFFFF);
      lift->mGraphTracer->setTo(idx);
    }
    lift->readRailFlag();
  } else {
    lift->resetPosition();
  }
}
SME_PATCH_BL(SME_PORT_REGION(0x801EFBDC, 0, 0, 0), checkResetToNode);
SME_WRITE_32(SME_PORT_REGION(0x801EFBE0, 0, 0, 0), 0x60000000);
SME_WRITE_32(SME_PORT_REGION(0x801EFBE4, 0, 0, 0), 0x60000000);
SME_WRITE_32(SME_PORT_REGION(0x801EFBE8, 0, 0, 0), 0x60000000);
SME_PATCH_BL(SME_PORT_REGION(0x801F13FC, 0, 0, 0), checkResetToNode);
SME_WRITE_32(SME_PORT_REGION(0x801F1400, 0, 0, 0), 0x60000000);
SME_WRITE_32(SME_PORT_REGION(0x801F1404, 0, 0, 0), 0x60000000);
SME_WRITE_32(SME_PORT_REGION(0x801F1408, 0, 0, 0), 0x60000000);

#endif
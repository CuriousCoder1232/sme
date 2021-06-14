#include "CARD.h"
#include "printf.h"
#include "sms/JSystem/J2D/J2DOrthoGraph.hxx"
#include "sms/JSystem/J2D/J2DTextBox.hxx"
#include "sms/talk/Talk2D2.hxx"
#include "string.h"

#include "SME.hxx"

using namespace SME;

extern J2DTextBox gDebugTextBox;

// this is ran once
// extern -> SME.cpp
void Patch::CKit::onSetup(TMarDirector *director) {
  gDebugTextBox = J2DTextBox(gpSystemFont->mFont, "Debug Mode");

  // run replaced call
  director->setupObjects();
}

// this is ran every frame
// extern -> SME.cpp
s32 Patch::CKit::onUpdate(void *director) { // movie director
  // xyzModifierMario();
  // Patch::Cheat::drawCheatText(); //currently bugged

  // run replaced call
  u32 func;
  SME_FROM_GPR(12, func);

  TMarioGamePad *controller = gpApplication.mGamePad1;
  if ((controller->mButtons.mInput & 0x260) == 0x260) { // L + R + B + D-PAD UP
    SME::Util::Mario::switchCharacter(gpMarioAddress,
                                      SME::Util::Mario::getPlayerIDFromInput(
                                          controller->mButtons.mInput & 0xF),
                                      true);
  }
  return ((s32(*)(void *))func)(director);
}

// this is ran when drawing is needed
// extern -> SME.cpp
void Patch::CKit::onDraw2D(J2DOrthoGraph *graph) {
  // run replaced call
  graph->setup2D();
}

// 0x802A8B58
// extern -> SME.cpp
bool Util::SMS::isExMap() {
  return SME::Class::TStageParams::sStageConfig->mIsExStage.get();
}

// 0x802A8B30
// extern -> SME.cpp
bool Util::SMS::isMultiplayerMap() {
  return SME::Class::TStageParams::sStageConfig->mIsMultiplayerStage.get();
}

// 0x802A8AFC
// extern -> SME.cpp
bool Util::SMS::isDivingMap() {
  return SME::Class::TStageParams::sStageConfig->mIsDivingStage.get();
}

// 0x802A8AE0
// extern -> SME.cpp
bool Util::SMS::isOptionMap() {
  return SME::Class::TStageParams::sStageConfig->mIsOptionStage.get();
}

// 0x8027C6A4
// extern -> SME.cpp
bool Patch::CKit::manageLightSize() {
  s32 &CurrentShineCount = TFlagManager::smInstance->Type4Flag.mShineCount;
  s32 &PrevShineCount = SME::TGlobals::sLightData.mPrevShineCount;
  switch (SME::TGlobals::sLightData.mLightType) {
  case TLightContext::ActiveType::STATIC: {
    if (SME::Class::TStageParams::sStageConfig->mLightDarkLevel.get() != 255)
      gpModelWaterManager->mDarkLevel =
          SME::Class::TStageParams::sStageConfig->mLightDarkLevel.get();
    else if (CurrentShineCount < SME_MAX_SHINES)
      gpModelWaterManager->mDarkLevel =
          SME::Util::Math::lerp<u8>(30, 190,
                                    static_cast<f32>(CurrentShineCount) /
                                        static_cast<f32>(SME_MAX_SHINES));
    else {
      if (gpModelWaterManager->mDarkLevel < 255)
        gpModelWaterManager->mDarkLevel += 1;
      else
        SME::TGlobals::sLightData.mLightType =
            TLightContext::ActiveType::DISABLED;
    }

    gShineShadowPos = SME::TGlobals::sLightData.mShineShadowCoordinates;

    const f32 sigOfs = 300.0f;
    const f32 sigStrength =
        CurrentShineCount >= PrevShineCount ? 0.04f : -0.04f;

    if (!SME::TGlobals::sLightData.mSizeMorphing) {
      if (CurrentShineCount > PrevShineCount) {
        SME::TGlobals::sLightData.mPrevSize = gpModelWaterManager->mSize;
        SME::TGlobals::sLightData.mNextSize = gpModelWaterManager->mSize;

        for (u32 i = 0; i < (CurrentShineCount - PrevShineCount); ++i)
          SME::TGlobals::sLightData.mNextSize +=
              (10000.0f / SME_MAX_SHINES) + (PrevShineCount + i) * 2.0f;

        SME::TGlobals::sLightData.mSizeMorphing = true;
        SME::TGlobals::sLightData.mStepContext = 0.0f;
      } else if (CurrentShineCount < PrevShineCount) {
        SME::TGlobals::sLightData.mPrevSize = gpModelWaterManager->mSize;
        SME::TGlobals::sLightData.mNextSize = gpModelWaterManager->mSize;

        for (u32 i = 0; i < (PrevShineCount - CurrentShineCount); ++i)
          SME::TGlobals::sLightData.mNextSize -=
              (10000.0f / SME_MAX_SHINES) + (PrevShineCount - i) * 2.0f;

        SME::TGlobals::sLightData.mSizeMorphing = true;
        SME::TGlobals::sLightData.mStepContext = 0.0f;
      } else {
        break;
      }
    }

    const f32 cur = SME::Util::Math::sigmoidCurve(
        SME::TGlobals::sLightData.mStepContext,
        SME::TGlobals::sLightData.mPrevSize,
        SME::TGlobals::sLightData.mNextSize, sigOfs, sigStrength);

    if (gpModelWaterManager->mSize > 70000.0f) {
      gpModelWaterManager->mSize = 70000.0f;
      SME::TGlobals::sLightData.mSizeMorphing = false;
    } else if (gpModelWaterManager->mSize < 0.0f) {
      gpModelWaterManager->mSize = 0.0f;
      SME::TGlobals::sLightData.mSizeMorphing = false;
    } else if (cur != SME::TGlobals::sLightData.mNextSize &&
               cur != SME::TGlobals::sLightData.mPrevSize) {
      gpModelWaterManager->mSize = cur;
      gpModelWaterManager->mSphereStep = cur / 2.0f;
      SME::TGlobals::sLightData.mStepContext += 1.0f;
    } else {
      gpModelWaterManager->mSize = cur;
      gpModelWaterManager->mSphereStep = cur / 2.0f;
      PrevShineCount = CurrentShineCount;
      SME::TGlobals::sLightData.mSizeMorphing = false;
    }
    break;
  }
  case TLightContext::ActiveType::FOLLOWPLAYER: {
    gpModelWaterManager->mDarkLevel =
        SME::Class::TStageParams::sStageConfig->mLightDarkLevel.get();
    gShineShadowPos.x =
        gpMarioPos->x + SME::TGlobals::sLightData.mShineShadowCoordinates.x;
    gShineShadowPos.y =
        gpMarioPos->y + SME::TGlobals::sLightData.mShineShadowCoordinates.y;
    gShineShadowPos.z =
        gpMarioPos->z + SME::TGlobals::sLightData.mShineShadowCoordinates.z;
    break;
  }
  default:
    break;
  }
  return SME::TGlobals::sLightData.mLightType !=
             TLightContext::ActiveType::DISABLED &&
         gpMarDirector->mAreaID != TGameSequence::OPTION;
}

// 0x802571F0
/*
f32 velocityCoordinatePatches(f32 floorCoordinateY)
{
    TMario *gpMario = (TMario *)*(u32 *)TMarioInstance;

    if (gpMario->mState != TMario::State::IDLE)
    { //Y storage
        gpMario->mSpeed.y = 0;
    }

    if (floorCoordinateY < gpMario->mPosition.y - 20)
    { //Downwarping
        floorCoordinateY = gpMario->mPosition.y;
    }
    asm("lfs 0, -0x0EC8 (2)");
    return floorCoordinateY;
}
*/

/*0x8018987C
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A6C
mtctr r4
bctrl
lwz r0, 0x000C (sp)
*/
// 0x80004A6C
/*
f32 downWarpPatch(TMario *gpMario, f32 yVelocity)
{
    if (yVelocity < -100)
    {
        return gpMario->mSpeed.y;
    }
    else
    {
        return yVelocity;
    }
}
*/

/*0x8018987C
addi r3, r31, 0
lis r4, 0x8000
ori r4, r4, 0x4A6C
mtctr r4
bctrl
lwz r0, 0x000C (sp)
*/
/*
f32 upWarpPatch(TMario *gpMario, f32 yVelocity)
{
    if (yVelocity > 1000000)
    {
        return gpMario->mSpeed.y;
    }
    else
    {
        return yVelocity;
    }
}
*/

// MESSAGE MODIFICATIONS //

// 0x80153DE8, 0x80153E1C
// extern -> SME.cpp
void Patch::CKit::formatTalkMessage(Talk2D2 *talker, char *msgfield,
                                    u32 *entrydata) {
  String fmtMessage(1024);

  const char *basemsg = msgfield + *entrydata + talker->curMsgIndex;
  const char *newmsg = fmtMessage.data() - (*entrydata + talker->curMsgIndex);

  fmtMessage.assign(basemsg);
  SME::Util::formatBMG(fmtMessage);

  setupTextBox__8TTalk2D2FPCvP12JMSMesgEntry(talker, newmsg, entrydata);
}

static void maintainYoshi(TYoshi *yoshi) {
  if (yoshi->isGreenYoshi()) {
    *(f32 *)0x80415F4C = 480.0f; // tounge
    *(f32 *)0x80415F68 = 16384.0f;
  } else {
    *(f32 *)0x80415F4C = 300.0f;
    *(f32 *)0x80415F68 = 10000.0f;
  }
}

// 0x8024D3A8
// extern -> SME.cpp
void Patch::CKit::realTimeCustomAttrsHandler(TMario *player) {
  maintainYoshi(player->mYoshi);
  setPositions__6TMarioFv(player);
}
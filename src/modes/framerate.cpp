#include "OS.h"
#include "SME.hxx"
#include "types.h"


using namespace SME;

static f32 sLastFPS = 30.0f;

#if SME_VARIABLE_FPS

// extern -> boot.cpp
void updateFPSAsync(OSAlarm *alarm, OSContext *context) {
  const f32 curFPS = TGlobals::isVariableFrameRate() ? TGlobals::getFrameRate()
                                                     : TGlobals::getFrameRate();
  if (curFPS != sLastFPS) {
    JDrama::TDisplay *display = gpApplication.mDisplay;
    if (display) {
      const f32 factor = curFPS / 30.0f;
      *(f32 *)SME_PORT_REGION(0x804167B8, 0, 0, 0) = 0.5f * factor;
      *(f32 *)SME_PORT_REGION(0x80414904, 0, 0, 0) = 0.001f * factor;
      display->mRetraceCount = curFPS > 30.0f ? 1 : 2;

      sLastFPS = curFPS;
    }
  }
}


static f32 setBoidSpeed(f32 thing) {
    return sqrt__Q29JGeometry8TUtil_f(thing) * (30.0f / SME::TGlobals::getFrameRate());
}
SME_PATCH_BL(SME_PORT_REGION(0x800066E4, 0, 0, 0), setBoidSpeed);

static void requestFadeTimeScaled(TSMSFader *fader, TSMSFader::WipeRequest *request) {
    #if 0
    const f32 scale = (SME::TGlobals::getFrameRate() / 30.0f);
    request->mWipeSpeed *= scale;
    request->mDelayTime *= scale;
    #endif
    fader->requestWipe(request);
}
SME_PATCH_BL(SME_PORT_REGION(0x8013FE84, 0, 0, 0), requestFadeTimeScaled);

#else

void updateFPSAsync(OSAlarm *alarm, OSContext *context);

#endif
#include "libs/sAssert.hxx"
#include "sms/spc/SpcInterp.hxx"
#include "sms/spc/SpcSlice.hxx"
#include "types.h"

namespace SME::Util::Spc {

enum class ValueType { INT, FLOAT };

namespace Stack {

TSpcSlice popItem(TSpcInterp *interp);
void pushItem(TSpcInterp *interp, u32 value, ValueType type);

} // namespace Stack

void setActorPosToOther(TSpcInterp *interp, u32 argc);
void setActorRotToOther(TSpcInterp *interp, u32 argc);
void getActorPos(TSpcInterp *interp, u32 argc);
void setActorPos(TSpcInterp *interp, u32 argc);
void getActorRot(TSpcInterp *interp, u32 argc);
void setActorRot(TSpcInterp *interp, u32 argc);
void spawnObjByID(TSpcInterp *interp, u32 argc);
void isMultiplayerActive(TSpcInterp *interp, u32 argc);
void isFreePlayActive(TSpcInterp *interp, u32 argc);
void isCompletionRewardActive(TSpcInterp *interp, u32 argc);
void getActivePlayers(TSpcInterp *interp, u32 argc);
void getMaxPlayers(TSpcInterp *interp, u32 argc);
void getPlayerByIndex(TSpcInterp *interp, u32 argc);
void getDateAsStr(TSpcInterp *interp, u32 argc);
void getTimeAsStr(TSpcInterp *interp, u32 argc);
void getPlayerInputByIndex(TSpcInterp *interp, u32 argc);
void read8(TSpcInterp *interp, u32 argc);
void read16(TSpcInterp *interp, u32 argc);
void read32(TSpcInterp *interp, u32 argc);
void write8(TSpcInterp *interp, u32 argc);
void write16(TSpcInterp *interp, u32 argc);
void write32(TSpcInterp *interp, u32 argc);
void memcpy_(TSpcInterp *interp, u32 argc);
void memmove_(TSpcInterp *interp, u32 argc);
void memcmp_(TSpcInterp *interp, u32 argc);
void memset_(TSpcInterp *interp, u32 argc);
void formatStrBySpec(TSpcInterp *interp, u32 argc);
void queueStream(TSpcInterp *interp, u32 argc);
void playStream(TSpcInterp *interp, u32 argc);
void pauseStream(TSpcInterp *interp, u32 argc);
void stopStream(TSpcInterp *interp, u32 argc);
void seekStream(TSpcInterp *interp, u32 argc);
void nextStream(TSpcInterp *interp, u32 argc);
void skipStream(TSpcInterp *interp, u32 argc);
void getStreamVolume(TSpcInterp *interp, u32 argc);
void setStreamVolume(TSpcInterp *interp, u32 argc);
void getStreamLooping(TSpcInterp *interp, u32 argc);
void setStreamLooping(TSpcInterp *interp, u32 argc);

} // namespace SME::Util::Spc
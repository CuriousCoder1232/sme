#pragma once

#include "sms/mapobj/MapObjBall.hxx"
#include "sms/mapobj/MapObjInit.hxx"
#include "sms/nozzle/Watergun.hxx"
#include "types.h"

class TWaterBalloon : public TMapObjBall {
public:
  TWaterBalloon(const char *name);
  virtual ~TWaterBalloon();

  virtual void init(TLiveManager *) override;
  virtual void perform(u32, JDrama::TGraphics *) override;
  virtual bool receiveMessage(THitActor *, u32) override;
  virtual void control() override;
  virtual void kill() override;
  virtual void appear() override;
  virtual void touchActor(THitActor *actor) override;
  virtual s32 getLivingTime() const override;
  virtual s32 getFlushTime() const override;
  virtual void hold(TTakeActor *) override;
  virtual void put() override;
  virtual void thrown() override;
  virtual void touchGround(TVec3f *) override;
  virtual void touchWall(TVec3f *,
                         TBGWallCheckRecord *) override;
  virtual void touchRoof(TVec3f *) override;
  virtual void touchPollution() override;
  virtual void touchWaterSurface() override;
  virtual void touchWater(THitActor *) override;
  virtual void kicked() override;

  void initActorData();
  void blast(TVec3f blastSpd);

  bool mIsPopped;
  f32 mForwardSpeed;

  static TWaterEmitInfo *sEmitInfo;

private:
  void getReflectionDir(const TVec3f &, TVec3f &) const;
};

extern ObjData waterBalloonData;
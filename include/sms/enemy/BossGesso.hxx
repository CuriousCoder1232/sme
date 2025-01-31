#pragma once

#include "JDrama/JDRActor.hxx"
#include "JGeometry.hxx"
#include "sms/actor/SpineEnemy.hxx"
#include "types.h"


class TBGPolDrop : JDrama::TActor {

public:
  enum DropStatus { DEAD, ALIVE, HIT };

  TVec3f mVelocity; // 0x0044
  u32 _06[0x8 / 4];                // 0x0050
  u32 mStatus;                     // 0x0058
};

class TBossGesso : public TSpineEnemy {

public:
  enum Attacks { SINGLE, DOUBLE, SKIPROPE, UNISON, SHOOT };

  TBossGesso(const char *);
  ~TBossGesso();

  bool beakHeld() const;
  void calcRootMatrix();
  void changeAllTentacleState(int);
  void changeAttackMode(int);
  void doAttackDouble();
  void doAttackShoot();
  void doAttackSingle();
  void doAttackSkipRope();
  void doAttackUnison();
  void gotTentacleDamage();
  void *getBasNameTable() const;
  void init(TLiveManager *);
  bool is2ndFightNow() const;
  void launchPolDrop();
  f32 lenFromToeToMario();
  void moveObject();
  void perform(u32, JDrama::TGraphics *);
  bool receiveMessage(THitActor *, u32);
  void rumblePad(int, const JGeometry::TVec3<float> &);
  void showMessage(u32);
  void stopIfRoll();
  bool tentacleHeld() const;

  u32 _00[0x18 / 4];          // 0x0150
  u32 mAttackState;           // 0x0168
  u32 mAttackTimer;           // 0x016C
  u32 _01[0x10 / 4];          // 0x0170
  TBGPolDrop *mPollutionDrop; // 0x0180
  u32 _02[0xC / 4];           // 0x0184
  u16 _03;                    // 0x0190
  u8 _04;                     // 0x0192
  u8 mGoopLevel;              // 0x0193
  u16 mAttackCount;           // 0x0194
  u16 _05;                    // 0x0196
  u32 _06[0x18 / 4];          // 0x0198
};
#ifndef EGGYOSHI_H
#define EGGYOSHI_H

#include "types.h"
#include "sms/mapobj/MapObjBase.hxx"
#include "sms/actor/Mario.hxx"

class TEggYoshi : public TMapObjBase
{

public:
    u32 _00[0x10 / 4]; //0x0138
    MActor *mActor;    //0x0148
    u32 mWantedFruit;  //0x014C
    TMario *mMario;    //0x0150
};

#endif
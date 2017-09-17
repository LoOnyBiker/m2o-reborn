#pragma once
#include "CommonHeaders.h"

#include "CFrame.hpp"

namespace M2
{
    class ICGfxEffects
    {
    public:
    };

    class C_GfxEffects : public GameClassWrapper<C_GfxEffects, ICGfxEffects, 0x1AC18F4>
    {
    public:
        C_Frame * CreateEffect(int type, int unkBool)
        {
            return Mem::InvokeFunction<Mem::call_this, C_Frame*>(0x12B4B90, this, type, unkBool);
        }
    };
};

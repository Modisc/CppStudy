#pragma once
#include "Stage.h"
class StageHard : public Stage
{
public:
    StageHard();
    virtual ~StageHard();

public:
    virtual bool Init();
    virtual void Run();
};


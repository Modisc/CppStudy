#pragma once
#include "Stage.h"
class StageEasy : public Stage
{
public:
    StageEasy();
    virtual ~StageEasy();

public:
    virtual bool Init();
    virtual void Run();
};


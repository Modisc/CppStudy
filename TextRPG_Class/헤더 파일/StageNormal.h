#pragma once
#include "Stage.h"
class StageNormal : public Stage
{
public:
    StageNormal();
    virtual ~StageNormal();

public:
    virtual bool Init();
    virtual void Run();
};


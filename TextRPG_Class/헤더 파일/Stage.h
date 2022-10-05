#pragma once
#include "value.h"

class Stage
{
public:
	Stage();
	virtual ~Stage();

public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
};


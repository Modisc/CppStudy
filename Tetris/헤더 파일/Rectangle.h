#pragma once
#include "Shape.h"

class Rectangle :
    public Shape
{
public:
    Rectangle();
    ~Rectangle();

public:
    virtual bool Init();
};


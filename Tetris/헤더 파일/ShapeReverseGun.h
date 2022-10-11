#pragma once
#include "Shape.h"
class ShapeReverseGun :
    public Shape
{
public:
    ShapeReverseGun();
    ~ShapeReverseGun();

public:
    virtual bool Init();
    virtual void Rotation();
};


#pragma once
#include "Shape.h"

class ShapeRectangle :
    public Shape
{
public:
    ShapeRectangle();
    ~ShapeRectangle();

public:
    virtual bool Init();
    virtual void Rotation();
};


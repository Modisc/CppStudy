#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle()
{
}

ShapeRectangle::~ShapeRectangle()
{
}

bool ShapeRectangle::Init()
{
    if (!Shape::Init())
        return false;

    base_shape_[2][0] = '0';
    base_shape_[2][1] = '0';
    base_shape_[3][0] = '0';
    base_shape_[3][1] = '0';

    width_count_ = 2;
    pos_.x = 4;
    pos_.y = 0;

    return true;
}

void ShapeRectangle::Rotation()
{
    return;
}

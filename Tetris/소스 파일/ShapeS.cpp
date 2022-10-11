#include "ShapeS.h"

ShapeS::ShapeS()
{
}

ShapeS::~ShapeS()
{
}

bool ShapeS::Init()
{
    if (!Shape::Init())
        return false;

    base_shape_[2][1] = '0';
    base_shape_[2][2] = '0';
    base_shape_[3][0] = '0';
    base_shape_[3][1] = '0';

    width_count_ = 3;
    pos_.x = 4;
    pos_.y = 0;

    dir_ = static_cast<int>(RotationDir::right);

    return true;
}

void ShapeS::Rotation()
{
    dir_ = dir_ == static_cast<int>(RotationDir::right) ? static_cast<int>(RotationDir::down) : static_cast<int>(RotationDir::right);

    memset(base_shape_, '1', sizeof(base_shape_));

    switch (dir_)
    {
    case static_cast<int>(RotationDir::right):
        base_shape_[2][1] = '0';
        base_shape_[2][2] = '0';
        base_shape_[3][0] = '0';
        base_shape_[3][1] = '0';

        width_count_ = 3;
        break;
    case static_cast<int>(RotationDir::down):
        base_shape_[1][0] = '0';
        base_shape_[2][0] = '0';
        base_shape_[2][1] = '0';
        base_shape_[3][1] = '0';

        width_count_ = 2;
        break;
    }
}

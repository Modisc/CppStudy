#include "ShapeZ.h"

ShapeZ::ShapeZ()
{
}

ShapeZ::~ShapeZ()
{
}

bool ShapeZ::Init()
{
    if (!Shape::Init())
        return false;

    base_shape_[2][0] = '0';
    base_shape_[2][1] = '0';
    base_shape_[3][1] = '0';
    base_shape_[3][2] = '0';

    width_count_ = 3;
    pos_.x = 4;
    pos_.y = 0;

    dir_ = static_cast<int>(RotationDir::left);
    return true;
}

void ShapeZ::Rotation()
{
    dir_ = dir_ == static_cast<int>(RotationDir::left) ? static_cast<int>(RotationDir::up) : static_cast<int>(RotationDir::left);

    memset(base_shape_, '1', sizeof(base_shape_));

    switch (dir_)
    {
    case static_cast<int>(RotationDir::left):
        base_shape_[2][0] = '0';
        base_shape_[2][1] = '0';
        base_shape_[3][1] = '0';
        base_shape_[3][2] = '0';

        width_count_ = 3;
        break;
    case static_cast<int>(RotationDir::up):
        base_shape_[1][1] = '0';
        base_shape_[2][0] = '0';
        base_shape_[2][1] = '0';
        base_shape_[3][0] = '0';

        width_count_ = 2;
        break;
    }
}

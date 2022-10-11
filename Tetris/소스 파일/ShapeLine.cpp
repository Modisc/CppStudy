#include "ShapeLine.h"

ShapeLine::ShapeLine()
{
}

ShapeLine::~ShapeLine()
{
}

bool ShapeLine::Init()
{
    if (!Shape::Init())
        return false;

    base_shape_[3][0] = '0';
    base_shape_[3][1] = '0';
    base_shape_[3][2] = '0';
    base_shape_[3][3] = '0';

    width_count_ = 4;
    pos_.x = 4;
    pos_.y = 0;

    dir_ = static_cast<int>(RotationDir::down);

    return true;
}

void ShapeLine::Rotation()
{
    dir_ = dir_ == static_cast<int>(RotationDir::down) ? static_cast<int>(RotationDir::up) : static_cast<int>(RotationDir::down);

    memset(base_shape_, '1', sizeof(base_shape_));

    switch (dir_)
    {
    case static_cast<int>(RotationDir::up):
        base_shape_[0][0] = '0';
        base_shape_[1][0] = '0';
        base_shape_[2][0] = '0';
        base_shape_[3][0] = '0';

        width_count_ = 4;
        break;
    case static_cast<int>(RotationDir::down):
        base_shape_[3][0] = '0';
        base_shape_[3][1] = '0';
        base_shape_[3][2] = '0';
        base_shape_[3][3] = '0';

        width_count_ = 4;
        break;
    }
}

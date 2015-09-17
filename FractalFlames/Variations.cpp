//
//  Variations.cpp
//  FractalFlames
//
//  Created by Evgeniy Morozov on 17.09.15.
//  Copyright © 2015 Eugene Morozov. All rights reserved.
//

#include "FractalFlame.hpp"

#include <cmath>

using namespace std;
using namespace FractalFlame;

#define R(x,y) sqrt((x)*(x)+(y)*(y))
#define T(x,y) atan2((x),(y))
#define F(x,y) atan2((y),(x))

Point Variations::V1(const Point & point)
{
    Point result(point.x, point.y);
    return result;
}

Point Variations::V2(const Point & point)
{
    Point result(0, 0);
    result.x = sin(point.x);
    result.y = sin(point.y);
    return result;
}

Point Variations::V7(const Point & point)
{
    Point result(0, 0);
    double r = R(point.x, point.y), theta = T(point.x, point.y);
    result.x =  r * sin(theta * r);
    result.y = -r * cos(theta * r);
    return result;
}

//
//  FractalFlame.hpp
//  FractalFlames
//
//  Created by Evgeniy Morozov on 17.09.15.
//  Copyright © 2015 Eugene Morozov. All rights reserved.
//

#ifndef FractalFlame_hpp
#define FractalFlame_hpp

#include <iostream>
#include <string>

namespace FractalFlame
{
    enum Axes : char {AXIS_X = 'x', AXIS_Y = 'y'};
    enum CoefNames : char { NAME_A = 'a', NAME_B = 'b', NAME_C = 'c' };
    
    struct Point
    {
        double x;
        double y;
    };
    
    class FractalFlameBuilder
    {
        unsigned outputWidth, outputHeight;
        unsigned basisSize;
        unsigned * colors, colorsLength;
        double ** coef;
        
    public:
        
        FractalFlameBuilder(unsigned outWidth, unsigned outHeight);
        ~FractalFlameBuilder();
        
        bool setCoeficients(const double ** coef, unsigned count);
        bool setCoeficients(const char * pathToFile);
        double getCoefficient(unsigned functionNumber, Axes axis, CoefNames name);
        unsigned getBasisSize();
        
        bool setOutputResolution(unsigned  x, unsigned  y);
        bool getOutputResolution(unsigned &x, unsigned &y);
        
        bool setColors(const unsigned * colors, unsigned colorsCount);
        bool setColors(const char * pathToFile);
        unsigned * getColors();
        unsigned getColorsCount();
        
        Point applyFunctionToPoint(unsigned functionNumber, const Point * point);
        Point biUnitPointToScreenPoint(const Point * point);
    };
}



#endif /* FractalFlame_hpp */

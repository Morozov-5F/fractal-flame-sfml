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

class FractalFlame
{
    unsigned outputWidth, outputHeight;
    unsigned basisSize;
    unsigned * colors, colorsLength;
    double ** coef;
    
public:
    
    enum Axes : char {AXIS_X = 'x', AXIS_Y = 'y'};
    enum CoefNames : char { NAME_A = 'a', NAME_B = 'b', NAME_C = 'c' };
    
    FractalFlame(unsigned outWidth, unsigned outHeight);
    ~FractalFlame();
    
    bool setCoeficients(const double ** coef, unsigned count);
    bool setCoeficients(const char * pathToFile);
    double getCoefficient(unsigned functionNumber, Axes axis, CoefNames name);
    
    bool setOutputResolution(unsigned  x, unsigned  y);
    bool getOutputResolution(unsigned &x, unsigned &y);

    bool setColors(const unsigned * colors, unsigned colorsCount);
    bool setColors(const char * pathToFile);
    unsigned * getColors();
    unsigned getColorsCount();
};

#endif /* FractalFlame_hpp */

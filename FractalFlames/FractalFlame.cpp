//
//  FractalFlame.cpp
//  FractalFlames
//
//  Created by Evgeniy Morozov on 17.09.15.
//  Copyright © 2015 Eugene Morozov. All rights reserved.
//

#include "FractalFlame.hpp"

using namespace FractalFlame;

#include <algorithm>
#include <random>
#include <fstream>

#define COEFS_IN_ROW 6
#define LETTER_A_ASCII_OFFSET 97

#define NULLPTR_CHECK(ptr)\
if ((ptr) == nullptr)\
    return false;

#define B_UNIT_SQUARE_CHECK(x, y)\
(((std::min(-1.0, (x)) == -1.0) && (std::max((x), 1.0) == 1)) && (((std::min(-1.0, (y)) == -1.0) && (std::max((y), 1.0) == 1))))

Point & operator += (Point &left, const Point &right)
{
    left.x += right.x;
    left.y += right.y;
    
    return left;
}

const Point operator + (const Point &left, const Point &right)
{
    return Point(left.x + right.x, left.y + right.y);
}

FractalFlameBuilder::FractalFlameBuilder(unsigned outWidth, unsigned outHeight)
{
    colors = nullptr;
    coef = nullptr;
    
    basisSize = colorsLength = 0;
    
    setOutputResolution(outWidth, outHeight);
}

FractalFlameBuilder::~FractalFlameBuilder()
{
    if (colors != nullptr)
        delete [] colors;
    colorsLength = 0;
    
    for (unsigned i = 0; (i < basisSize) && (coef != nullptr); ++i)
        if (coef[i] != nullptr)
            delete [] coef[i];
    
    if (coef != nullptr);
        delete [] coef;
    
    basisSize = 0;
    
    outputHeight = outputWidth = 0;
}

bool FractalFlameBuilder::setCoeficients(const double ** coef, unsigned count)
{
    NULLPTR_CHECK(coef);
    
    basisSize = count;
    this->coef = new double * [basisSize];
    
    NULLPTR_CHECK(this->coef);
    
    for (unsigned i = 0; i < basisSize; ++i)
    {
        this->coef[i] = new double[COEFS_IN_ROW];
        NULLPTR_CHECK(this->coef[i]);
        
        if (std::copy(coef[i], coef[i] + COEFS_IN_ROW, this->coef[i]) != this->coef[i])
            return false;
    }
    return true;
}

bool FractalFlameBuilder::setCoeficients(const char * pathToFile)
{
    std::ifstream inputFile(pathToFile);
    if (!inputFile.good() || !inputFile.is_open())
        return false;
    
    inputFile >> basisSize;
    
    coef = new double * [basisSize];
    NULLPTR_CHECK(coef);
    
    for (unsigned i = 0; i < basisSize; ++i)
    {
        coef[i] = new double[COEFS_IN_ROW];
        NULLPTR_CHECK(coef[i]);
        for (unsigned j = 0; j < COEFS_IN_ROW; ++j)
        {
            if (!inputFile.good())
                return false;
            inputFile >> coef[i][j];
        }
    }
    return true;
}

double FractalFlameBuilder::getCoefficient(unsigned functionNumber, Axes axis, CoefNames name)
{
    if (functionNumber >= basisSize)
        return NAN;
    
    NULLPTR_CHECK(coef);
    NULLPTR_CHECK(coef[functionNumber]);
    
    unsigned coefIndex = ((axis == AXIS_X) ? 0 : 3) + (name - LETTER_A_ASCII_OFFSET);
    
    return coef[functionNumber][coefIndex];
}

unsigned FractalFlameBuilder::getBasisSize()
{
    return basisSize;
}

bool FractalFlameBuilder::setOutputResolution(unsigned x, unsigned y)
{
    outputWidth = x;
    outputHeight = y;
    
    return true;
}

bool FractalFlameBuilder::getOutputResolution(unsigned &x, unsigned &y)
{
    x = outputWidth;
    y = outputHeight;
    
    return true;
}

bool FractalFlameBuilder::setColors(const unsigned * colors, unsigned colorsCount)
{
    NULLPTR_CHECK(colors);
    
    colorsLength = colorsCount;
    this->colors = new unsigned[colorsLength];
    NULLPTR_CHECK(this->colors);
    
    if(std::copy(colors, colors + colorsCount, this->colors) != this->colors)
        return false;
    
    return true;
}

bool FractalFlameBuilder::setColors(const char * pathToFile)
{
    std::ifstream inputFile(pathToFile);
    if (!inputFile.good() || !inputFile.is_open())
        return false;
    
    NULLPTR_CHECK(colors);
    
    inputFile >> colorsLength;
    for (unsigned i = 0; i < colorsLength; ++i)
    {
        if (!inputFile.good())
            return false;
        inputFile >> colors[i];
    }
    return true;
}

unsigned * FractalFlameBuilder::getColors()
{
    return colors;
}

unsigned FractalFlameBuilder::getColorsCount()
{
    return colorsLength;
}

Point FractalFlameBuilder::applyFunctionToPoint(unsigned functionNumber, const Point & point)
{
    Point result(0, 0);
    if (functionNumber >= basisSize || !B_UNIT_SQUARE_CHECK(point.x, point.y))
    {
        return result;
    }
    result = Variations::V2(point);
//    result.x = getCoefficient(functionNumber, AXIS_X, NAME_A) * point->x +
//               getCoefficient(functionNumber, AXIS_X, NAME_B) * point->y +
//               getCoefficient(functionNumber, AXIS_X, NAME_C);
    
//    result.y = getCoefficient(functionNumber, AXIS_Y, NAME_A) * point->x +
//               getCoefficient(functionNumber, AXIS_Y, NAME_B) * point->y +
//               getCoefficient(functionNumber, AXIS_Y, NAME_C);
    
    return result;
}

Point FractalFlameBuilder::biUnitPointToScreenPoint(const Point & point)
{
    Point result(0, 0);
    if (!B_UNIT_SQUARE_CHECK(point.x, point.y))
    {
        result.x = result.y = NAN;
        return result;
    }
    
    result.x = (point.x + 1) * outputWidth / 2;
    result.y = (point.y + 1) * outputHeight / 2;

    return result;
}
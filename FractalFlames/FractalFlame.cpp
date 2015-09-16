//
//  FractalFlame.cpp
//  FractalFlames
//
//  Created by Evgeniy Morozov on 17.09.15.
//  Copyright © 2015 Eugene Morozov. All rights reserved.
//

#include "FractalFlame.hpp"

#include <random>
#include <fstream>

#define COEFS_IN_ROW 6
#define LETTER_A_ASCII_OFFSET 97

#define NULLPTR_CHECK(ptr)\
if (ptr == nullptr)\
    return false;

FractalFlame::FractalFlame(unsigned outWidth, unsigned outHeight)
{
    setOutputResolution(outputWidth, outputHeight);
}

FractalFlame::~FractalFlame()
{
    delete [] colors;
    colorsLength = 0;
    
    for (unsigned i = 0; i < basisSize; delete [] coef[i]);
    delete [] coef;
    basisSize = 0;
    
    outputHeight = outputWidth = 0;
}

bool FractalFlame::setCoeficients(const double ** coef, unsigned count)
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

bool FractalFlame::setCoeficients(const char * pathToFile)
{
    std::ifstream inputFile(pathToFile);
    if (!inputFile.good() || !inputFile.is_open())
        return false;
    
    NULLPTR_CHECK(coef);
    
    inputFile >> basisSize;
    for (unsigned i = 0; i < basisSize; ++i)
    {
        NULLPTR_CHECK(coef[i]);
        for (unsigned j = 0; (j < COEFS_IN_ROW); ++i)
        {
            if (!inputFile.good())
                return false;
            inputFile >> coef[i][j];
        }
    }
    return true;
}

double FractalFlame::getCoefficient(unsigned functionNumber, Axes axis, CoefNames name)
{
    if (functionNumber > basisSize)
        return NAN;
    
    NULLPTR_CHECK(coef);
    NULLPTR_CHECK(coef[functionNumber]);
    
    unsigned coefIndex = ((axis == AXIS_X) ? 0 : 3) + (name - LETTER_A_ASCII_OFFSET);
    
    return coef[functionNumber][coefIndex];
}

bool FractalFlame::setOutputResolution(unsigned x, unsigned y)
{
    outputWidth = x;
    outputHeight = y;
    
    return true;
}

bool FractalFlame::getOutputResolution(unsigned &x, unsigned &y)
{
    x = outputWidth;
    y = outputHeight;
    
    return true;
}

bool FractalFlame::setColors(const unsigned * colors, unsigned colorsCount)
{
    NULLPTR_CHECK(colors);
    
    colorsLength = colorsCount;
    this->colors = new unsigned[colorsLength];
    NULLPTR_CHECK(this->colors);
    
    if(std::copy(colors, colors + colorsCount, this->colors) != this->colors)
        return false;
    
    return true;
}

bool FractalFlame::setColors(const char * pathToFile)
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

unsigned * FractalFlame::getColors()
{
    return colors;
}

unsigned FractalFlame::getColorsCount()
{
    return colorsLength;
}


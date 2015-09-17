//
//  main.cpp
//  FractalFlames
//
//  Created by Evgeniy Morozov on 17.09.15.
//  Copyright © 2015 Eugene Morozov. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

#include "FractalFlame.hpp"

using namespace sf;
using namespace FractalFlame;

#define WIDTH 1024
#define HEIGHT 800
#define MAX_ITERATIONS 40000

int main(int argc, char const** argv)
{
    Image canvas;
    canvas.create(WIDTH, HEIGHT);
    
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<unsigned> intDistribution(0, 2);
    std::uniform_real_distribution<double> realDistribution(-1.0, 1.0);
    
    FractalFlameBuilder ffBuilder(WIDTH, HEIGHT);
    if (!ffBuilder.setCoeficients("Coefs_Serpinsky"))
        return EXIT_FAILURE;
    
    Point point;
    point.x = realDistribution(generator);
    point.y = realDistribution(generator);
    
    std::cout << "Starting fractal flame building" << std::endl;
    for (unsigned i = 0; i < MAX_ITERATIONS; ++i)
    {
        unsigned k = intDistribution(generator);
        point = ffBuilder.applyFunctionToPoint(k, &point);
        
        if (i < 20)
            continue;
        
        Point intPoint = ffBuilder.biUnitPointToScreenPoint(&point);
        canvas.setPixel((unsigned)intPoint.x, (unsigned)intPoint.y, Color::White);
    }
    std::cout << "Finished fractal flame building" << std::endl;
    canvas.saveToFile("serpinsky.png");
    
    return EXIT_SUCCESS;
}

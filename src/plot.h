/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_PLOT_H_
#define MANDELBROT_PLOT_H_

#include <stdlib.h>

#include "mandelbrot_dumb.h"
#include "mandelbrot_avx.h"

const uint8_t red_coeff   = 15;
const uint8_t green_coeff = 30;
const uint8_t blue_coeff  = 40;

struct Plot {
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    
    uint8_t* colors;
    
    unsigned width;
    unsigned height;
};

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

void plot_create(Plot* plot, const char* name, unsigned width, unsigned height);

/**
 * @brief
 * 
 * @param width
 * @param height
 * @param counters
 * @param plot_name
 * @return 
 */
void mbrot_plot(Plot* plot, const unsigned* counters);

void mbrot_render(Plot* plot, unsigned* counters);

inline void plot_destroy(Plot* plot)
{
    free(plot->colors);
} 

#endif // MANDELBROT_PLOT_H_

/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_PLOT_H_
#define MANDELBROT_PLOT_H_

#include "mandelbrot.h"

const uint8_t red_coeff   = 15;
const uint8_t green_coeff = 30;
const uint8_t blue_coeff  = 40;

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

/**
 * @brief
 * 
 * @param width
 * @param height
 * @param counters
 * @param plot_name
 * @return 
 */
bool mbrot_plot(unsigned width, unsigned height, const unsigned* counters,
                const char* plot_name);

#endif // MANDELBROT_PLOT_H_

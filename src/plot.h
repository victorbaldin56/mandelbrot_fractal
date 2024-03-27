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

#include "../sfml_wrapper/sfml_wrapper.h"

const uint8_t red_coeff   = 15;
const uint8_t green_coeff = 30;
const uint8_t blue_coeff  = 40;

/**
 * @brief
 * 
 * @param plot     A workspace to render in.
 * @param counters Array of each point's counters. 
 */
void mf_draw_plot(SfmlGui* plot, const unsigned* counters);


void mf_handle_window(SfmlGui* plot, unsigned* counters);

#endif // MANDELBROT_PLOT_H_

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

/**
 * @brief
 * 
 * @param plot     A workspace to render in.
 * @param counters Array of each point's counters. 
 */
void mf_draw_plot(SfmlGui* plot, const unsigned* counters);

/**
 * @brief Draws a window inside the loop and handles window events.
 * 
 * @param plot Window entities to draw.
 * @param counters An array with each point's counter.
 */
void mf_handle_window(SfmlGui* plot, unsigned* counters);

#endif // MANDELBROT_PLOT_H_

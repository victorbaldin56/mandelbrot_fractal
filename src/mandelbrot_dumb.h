/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "common.h"

/**
 * @brief
 *
 * @param widht
 * @param height
 * @param counters
 */
void mf_calculate(unsigned width, unsigned height, unsigned* counters,
                  MfPlotParams params);

#endif // MANDELBROT_H_

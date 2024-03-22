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

#include "config.h"

/**
 * @brief
 *
 * @param widht
 * @param height
 * @param counters
 */
void mbrot_calculate(unsigned width, unsigned height, unsigned* counters,
                     float x_offset, float y_offset, float scale);

#endif // MANDELBROT_H_

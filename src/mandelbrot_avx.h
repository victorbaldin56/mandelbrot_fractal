/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_AVX_H_
#define MANDELBROT_AVX_H_

#include <sys/time.h>

#include "common.h"

/**
 * @brief
 *
 * @param widht
 * @param height
 * @param counters
 * @param x_offset
 * @param y_offset
 * @param scale
 */
void mf_calculate_avx(unsigned width, unsigned height, unsigned* counters,
                      MfPlotParams params);

#endif // MANDELBROT_AVX_H_

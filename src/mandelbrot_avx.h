/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_AVX_H_
#define MANDELBROT_AVX_H_

/**
 * @brief
 *
 * @param widht
 * @param height
 * @param counters
 */
void mbrot_calculate_avx(unsigned width, unsigned height, unsigned* counters,
                         float x_offset, float y_offset, float scale);

#endif // MANDELBROT_AVX_H_

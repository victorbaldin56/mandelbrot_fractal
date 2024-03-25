/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_AVX_H_
#define MANDELBROT_AVX_H_

#include <sys/time.h>

/**
 * @brief
 *
 * @param widht
 * @param height
 * @param counters
 */
void mbrot_calculate_avx(unsigned width, unsigned height, unsigned* counters,
                         float x_offset, float y_offset, float scale);

static inline double get_time(timeval start, timeval stop)
{
    return (double)(stop.tv_sec - start.tv_sec) 
                + (double)(stop.tv_usec - start.tv_usec) / 1e6;
}

#endif // MANDELBROT_AVX_H_

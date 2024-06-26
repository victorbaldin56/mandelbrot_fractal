/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_COMMON_H_
#define MANDELBROT_COMMON_H_

#include "config.h"

/**
 * @brief
 */
struct MfPlotParams {
    float x_offset = mf_x_offset;
    float y_offset = mf_y_offset;
    float scale = 1.f;
    
    uint8_t red_coeff = mf_red_coeff;
    uint8_t green_coeff = mf_green_coeff;
    uint8_t blue_coeff = mf_blue_coeff;
};

#endif // MANDELBROT_COMMON_H_

/******************************************************************************
 * @file
 * @brief Contains key constant values. 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_CONFIG_H_
#define MANDELBROT_CONFIG_H_

#include <inttypes.h>

const unsigned mf_num_iterations = 256u;

const unsigned mf_screen_height = 1024u;
const unsigned mf_screen_width  = 1024u;

const float mf_pixel_width = 0.0025f;

const float mf_x_offset = mf_screen_width * mf_pixel_width / 2;
const float mf_y_offset = mf_screen_height * mf_pixel_width / 2;

const float mf_x_step = 0.1f;
const float mf_y_step = 0.1f;

const float mf_scale_step = 1.1f;

const float mf_max_r2 = 100.0f;

const uint8_t mf_red_coeff   = 15;
const uint8_t mf_green_coeff = 30;
const uint8_t mf_blue_coeff  = 40;


#endif // MANDELBROT_CONFIG_H_

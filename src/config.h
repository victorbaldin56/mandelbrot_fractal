/******************************************************************************
 * @file
 * @brief Contains key constant values. 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_CONFIG_H_
#define MANDELBROT_CONFIG_H_

const unsigned mbrot_num_iterations = 256u;

const unsigned mbrot_screen_height = 1024u;
const unsigned mbrot_screen_width  = 1024u;

const float mbrot_pixel_width = 0.0025f;

const float mbrot_x_offset = 1.75f;
const float mbrot_y_offset = 1.25f;

const float mbrot_max_r2 = 100.0f;

#endif // MANDELBROT_CONFIG_H_

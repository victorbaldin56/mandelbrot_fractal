/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "mandelbrot_dumb.h"

inline unsigned mf_calculate_point_counter(float x_0, float y_0);

void mf_calculate(unsigned width, unsigned height, unsigned* counters,
                  MfPlotParams params)
{
    assert(width && height && counters != nullptr);
     
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            float x_0 = ((float)x * mf_pixel_width - params.x_offset) 
                * params.scale;
            float y_0 = ((float)y * mf_pixel_width - params.y_offset) 
                * params.scale;
            counters[y * width + x] = mf_calculate_point_counter(x_0, y_0);
        }
    }
}

inline unsigned mf_calculate_point_counter(float x_0, float y_0)
{
    unsigned counter = 0;
    float x_cur = x_0, y_cur = y_0;
    
    for (; counter < mf_num_iterations; ++counter) {
        float x2 = x_cur * x_cur, y2 = y_cur * y_cur;
        if (x2 + y2 > mf_max_r2)
            break; 

        float x_next = x2 - y2 + x_0;
        float y_next = 2 * x_cur * y_cur + y_0;
        x_cur = x_next;
        y_cur = y_next;
    }
    
    return counter;
}

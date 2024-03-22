/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include <stdlib.h>

#include "config.h"
#include "mandelbrot.h"
#include "plot.h"

int main() 
{
    unsigned* counters = (unsigned*)calloc(mbrot_screen_width 
                                               * mbrot_screen_height,
                                           sizeof(*counters));
    mbrot_calculate(mbrot_screen_width, mbrot_screen_height, counters);
    mbrot_plot(mbrot_screen_width, mbrot_screen_height, counters, 
               "Mandelbrot set");
    free(counters);
    return 0;
}

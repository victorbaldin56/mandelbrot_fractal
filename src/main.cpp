/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include <stdlib.h>

#include <sys/time.h>

#include "config.h"
#include "mandelbrot.h"
#include "plot.h"

static void run_benchmark()
{
    unsigned* counters = (unsigned*)calloc(mbrot_screen_width 
                                               * mbrot_screen_height,
                                           sizeof(*counters));
    
    timeval start = {}, stop = {};
    gettimeofday(&start, nullptr);
    for (int i = 0; i < 10; ++i) {
        mbrot_calculate(mbrot_screen_width, mbrot_screen_height, counters);
    }
    gettimeofday(&stop, nullptr);
    double time = (double)(stop.tv_sec - start.tv_sec) 
                    + (double)(stop.tv_usec - start.tv_usec) / 1e6;
    printf("Duration of 100 calculations: %lf\n", time);
   
    Plot plot = {}; 
    plot_create(&plot, "Mandelbrot set", mbrot_screen_width, 
                mbrot_screen_height);
    mbrot_plot(&plot, counters);
    plot_destroy(&plot);
    free(counters);
}

int main() 
{
    run_benchmark();
    return 0;
}

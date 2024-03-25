/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include <stdlib.h>
#include <getopt.h>

#include <sys/time.h>

#include "config.h"
#include "mandelbrot_dumb.h"
#include "plot.h"

const int num_calculations = 100;

const char help_message[] = "Mandelbrot fractal simulation\n"
                            "Usage:...";

typedef void MbrotCalculationFunc(unsigned width, unsigned height, unsigned* counters,
                                  float x_offset, float y_offset, float scale);

static inline void print_help() {
    puts(help_message);
}

static void mbrot_run(unsigned* counters)
{
    Plot plot = {}; 
    plot_create(&plot, "Mandelbrot set", mbrot_screen_width, 
                mbrot_screen_height);
    mbrot_render(&plot, counters);
    plot_destroy(&plot);
}   

static inline double get_time(timeval start, timeval stop)
{
    return (double)(stop.tv_sec - start.tv_sec) 
                + (double)(stop.tv_usec - start.tv_usec) / 1e6;
}

static void mbrot_test_calculation_func(unsigned* counters,
                                        MbrotCalculationFunc* func, 
                                        const char* func_name)
{
    assert(counters != nullptr && func != nullptr && output != nullptr
            && func_name != nullptr);
    
    timeval start = {}, stop = {};
    gettimeofday(&start, nullptr);
    
    fprintf(stderr, "Testing %s implementation... ", func_name);
    for (int i = 0; i < num_calculations; ++i) {
        (*func)(mbrot_screen_width, mbrot_screen_height, counters,
                mbrot_x_offset, mbrot_y_offset, 1.0f);
    }
    gettimeofday(&stop, nullptr);
    double time = get_time(start, stop);
    fprintf(stderr, "OK\n"
                    "Time of %d calculations: %lf s\n",
                    num_calculations, time); 
}

static void mbrot_run_benchmark(unsigned* counters)
{
    assert(filename != nullptr);
    
    mbrot_test_calculation_func(counters, mbrot_calculate, "dumb");
    mbrot_test_calculation_func(counters, mbrot_calculate_avx, "AVX2");
}

enum RunMode {
    run_regular = 0,
    run_test    = 1,
};

static inline int mbrot_run_mode(RunMode mode)
{
    unsigned* counters = (unsigned*)aligned_alloc(32, mbrot_screen_width
                                                        * mbrot_screen_height
                                                        * sizeof(*counters));
    if (counters == nullptr) {
        perror("");
        return EXIT_FAILURE;
    }
    
    if (mode == run_test)
        mbrot_run_benchmark(counters);
    else
        mbrot_run(counters);
    
    free(counters);
    return 0;
}    

int main(int argc, char** argv) 
{    
    option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"test", no_argument, 0, 't'},
        {     0,           0, 0,  0 },
    };

    while (optind < argc) {
        int option_code = getopt_long(argc, argv, "ht", long_options, nullptr);
        
        switch (option_code) {
        case 'h':
            print_help();
            return 0;
        case 't':
	        fprintf(stderr, "-----------------------------------------------------------\n"
                   "%s\n", argv[0]);
            return mbrot_run_mode(run_test);
        case '?':
            print_help();
            return EXIT_FAILURE;
        default:
            assert(0 && "Unexpected case");
        }                           
    }
    
    return mbrot_run_mode(run_regular);
}


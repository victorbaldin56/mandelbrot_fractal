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

typedef void MFCalculationfunc(unsigned width, unsigned height, unsigned* counters,
                                  float x_offset, float y_offset, float scale);

static inline void print_help() {
    puts(help_message);
}

static void mf_run(unsigned* counters)
{
    SfmlGui plot = {};
    SfmlGuiText text = {.font_name = "Consolas",
                        .color = sf::Color::Green,
                        .font_size = 20};
    if (!sfml_gui_create(&plot, "Mandelbrot set", mf_screen_width, 
                mf_screen_height, text))
        return;

    mf_handle_window(&plot, counters);
    sfml_gui_destroy(&plot);
}   

static void mf_test_calculation_func(unsigned* counters,
                                        MFCalculationfunc* func, 
                                        const char* func_name)
{
    assert(counters != nullptr && func != nullptr
            && func_name != nullptr);
    
    timeval start = {}, stop = {};
    gettimeofday(&start, nullptr);
    
    fprintf(stderr, "Testing %s implementation... ", func_name);
    for (int i = 0; i < num_calculations; ++i) {
        (*func)(mf_screen_width, mf_screen_height, counters,
                mf_x_offset, mf_y_offset, 1.0f);
    }
    gettimeofday(&stop, nullptr);
    double time = get_time(start, stop);
    fprintf(stderr, "OK\n"
                    "Time of %d calculations: %lf s\n",
                    num_calculations, time); 
}

static void mf_run_benchmark(unsigned* counters)
{
    assert(counters != nullptr);
    mf_test_calculation_func(counters, mf_calculate, "dumb");
    mf_test_calculation_func(counters, mf_calculate_avx, "AVX2");
}

enum RunMode {
    run_regular = 0,
    run_test    = 1,
};

static inline int mf_run_mode(RunMode mode)
{
    unsigned* counters = (unsigned*)aligned_alloc(32, mf_screen_width
                                                        * mf_screen_height
                                                        * sizeof(*counters));
    if (counters == nullptr) {
        perror("");
        return EXIT_FAILURE;
    }
    
    if (mode == run_test)
        mf_run_benchmark(counters);
    else
        mf_run(counters);
    
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
            return mf_run_mode(run_test);
        case '?':
            print_help();
            return EXIT_FAILURE;
        default:
            assert(0 && "Unexpected case");
        }                           
    }
    
    return mf_run_mode(run_regular);
}


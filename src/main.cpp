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
#include "performance_test.h"

const char help_message[] = "Mandelbrot fractal simulation\n"
                            "Usage:...";

inline void print_help() 
{
    puts(help_message);
}

static inline int mf_run_normal();

int main(int argc, char** argv) 
{    
    option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"test", required_argument, 0, 't'},
        {     0,           0, 0,  0 },
    };
    
    while (optind < argc) {
        int option_code = getopt_long(argc, argv, "ht:", long_options, nullptr);
        
        switch (option_code) {
        case 'h':
            print_help();
            return 0;
        case 't':        
            return mf_run_perfomance_test(optarg);
        case '?':
            print_help();
            return EXIT_FAILURE;
        default:
            assert(0 && "Unexpected case");
        }                           
    }
    
    return mf_run_normal();
}

static inline int mf_run_normal()
{
    unsigned* counters = (unsigned*)aligned_alloc(32, mf_screen_width
                                                    * mf_screen_height
                                                    * sizeof(*counters));
    if (counters == nullptr) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }
    
    SfmlGui plot = {};
    SfmlGuiText text = {.font_name = "Monospace",
                        .color = sf::Color::Green,
                        .font_size = 20};
    if (!sfml_gui_create(&plot, "Mandelbrot set", mf_screen_width, 
                         mf_screen_height, text))    
        return EXIT_FAILURE;
    
    mf_handle_window(&plot, counters);
    sfml_gui_destroy(&plot);
    return 0;
}

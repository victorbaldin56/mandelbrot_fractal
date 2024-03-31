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

inline void print_help(const char* const* argv)
{
    printf("Mandelbrot fractal view\n"
           "Copyright (C) Victor Baldin, 2024\n"
           "Usage: %s [options]\n"
           "Options:\n"
           "    -h, --help                      Print this message and quit\n"
           "    -t, --test [output file]        Test performance, write measured data to csv output\n",
           argv[0]);
}

inline int mf_run_normal();

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
            print_help(argv);
            return 0;
        case 't':
            return mf_run_perfomance_test(optarg);
        case '?':
            print_help(argv);
            return EXIT_FAILURE;
        default:
            assert(0 && "Unexpected case");
        }
    }

    return mf_run_normal();
}

inline int mf_run_normal()
{
    unsigned* counters = (unsigned*)aligned_alloc(32, mf_screen_width
                                                    * mf_screen_height
                                                    * sizeof(*counters));
    if (counters == nullptr) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    SfmlGui plot = {};
    SfmlGuiText text = {
        .font_name = "Monospace",
        .color = sf::Color::Green,
        .font_size = 20
    };

    if (!sfml_gui_create(&plot, "Mandelbrot set", mf_screen_width,
                         mf_screen_height, text))
        return EXIT_FAILURE;

    mf_handle_window(&plot, counters);
    sfml_gui_destroy(&plot);
    free(counters);
    return 0;
}

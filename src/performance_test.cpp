/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "performance_test.h"

#include <immintrin.h>

#include "mandelbrot_dumb.h"
#include "mandelbrot_avx.h"

typedef unsigned long long ull;

/**
 * @brief Runs one test of both implementations.
 * 
 * @param num_iters Number of iterations that signle test should do.
 * @param output    Output stream to write data into.
 * @param counters  Array of each point's counters.
 */
static void mf_run_single_test(FILE* output, unsigned num_iters,
                               unsigned* counters);

int mf_run_perfomance_test(const char* output_file)
{
    assert(output_file != nullptr);
    
    int exit_status = 0;
    
    FILE* output = fopen(output_file, "w");
    if (output == nullptr) {
        perror("");
        return EXIT_FAILURE;
    }
    
    unsigned* counters = (unsigned*)aligned_alloc(32, mf_screen_width
                                                    * mf_screen_height
                                                    * sizeof(*counters));
    if (counters == nullptr) {
        fprintf(stderr, "Allocation failure\n");
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }   
    
    fprintf(output, "N,Dumb,AVX2\n"
                    "0,0,0\n");
    
    for (unsigned iters = mf_test_step; iters <= mf_num_test_points 
        * mf_test_step; iters += mf_test_step) {
        mf_run_single_test(output, iters, counters);
    }

cleanup:
    free(counters);
    fclose(output);
    return exit_status;
}

static void mf_run_single_test(FILE* output, unsigned num_iters,
                               unsigned* counters)
{
    assert(output != nullptr);
    
    ull start = __rdtsc();
    for (unsigned i = 0; i < num_iters; ++i) {
        mf_calculate(mf_screen_width, mf_screen_height, counters,
                     mf_x_offset, mf_y_offset, 1.f);
    }
    ull end = __rdtsc();
    
    fprintf(output, "%u,%llu,", num_iters, end - start);
    
    start = __rdtsc();
    for (unsigned i = 0; i < num_iters; ++i) {
        mf_calculate_avx(mf_screen_width, mf_screen_height, counters,
                         mf_x_offset, mf_y_offset, 1.f);
    }
    end = __rdtsc();
    
    fprintf(output, "%llu\n", end - start);
} 

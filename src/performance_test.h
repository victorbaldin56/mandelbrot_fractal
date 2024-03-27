/******************************************************************************
 * @file Contains perfomance testing functions.
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#ifndef MANDELBROT_TEST_H_
#define MANDELBROT_TEST_H_

#include <stdint.h>

const unsigned mf_num_test_points = 20; ///< Number of data points to collect
const unsigned mf_test_step       = 5;

/**
 * @brief Measures perfomance of both implementations using `__rdtsc()`.
 *
 * @param output_file The name of file in which data will be written.
 * @return `0` on success; `EXIT_FAILURE` on failure
 */
int mf_run_perfomance_test(const char* output_file);

#endif // MANDELBROT_TEST_H_

/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "mandelbrot_avx.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <immintrin.h>

#include "config.h"

// #define DEBUG

#ifdef DEBUG
#define ON_DEBUG(x) x
#else
#define ON_DEBUG(x) 
#endif

const __m256 vector_x_offsets = _mm256_set_ps(7, 6, 5, 4, 3, 2, 1, 0) 
                                    * mf_pixel_width;
const __m256 max_r2_vector = _mm256_set1_ps(mf_max_r2);

static inline __m256i calculate_counters_vector(__m256 x_0, __m256 y_0);

void mf_calculate_avx(unsigned width, unsigned height, unsigned* counters,
                         float x_offset, float y_offset, float scale)
{
    assert(width && height && counters != nullptr);
    assert((uintptr_t)counters % 32 == 0 && "Wrong alignment");

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; x += 8) {
            __m256 x_0 = _mm256_set1_ps(((float)x * mf_pixel_width 
                                            - x_offset) * scale);
            x_0 += vector_x_offsets * scale;
            __m256 y_0 = _mm256_set1_ps(((float)y * mf_pixel_width
                                            - y_offset) * scale);
            
            // Here right alignment is guaranteed by assert.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
            _mm256_store_si256((__m256i*)(counters + y * width + x),
                               calculate_counters_vector(x_0, y_0));
#pragma GCC diagnostic pop
            
            // Very dumb and slow log, do not turn it on again!
#ifdef DEBUG
            for (unsigned i = 0; i < 8; ++i) {
                fprintf(stderr, "%x ", counters[y * width + x + i]);
            } 
            fputc('\n', stderr);
#endif
        }
    }
}

static inline __m256i calculate_counters_vector(__m256 x_0, __m256 y_0)
{
    __m256i counters = {};
    __m256 x_cur = x_0, y_cur = y_0;
    
    for (unsigned i = 0; i < mf_num_iterations; ++i) {
        __m256 x2 = x_cur * x_cur, y2 = y_cur * y_cur;
        __m256i cmp = (__m256i)_mm256_cmp_ps(x2 + y2, max_r2_vector,
                                             _CMP_LE_OQ);
        
        // Comparing with zero.
        if (_mm256_testz_si256(cmp, cmp) == 1)
            break;
        
        counters = _mm256_sub_epi32(counters, cmp);
        __m256 x_next = x2 - y2 + x_0;
        __m256 y_next = 2 * x_cur * y_cur + y_0;
        x_cur = x_next;
        y_cur = y_next;
    }
    
    return counters;
}

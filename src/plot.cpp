/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "plot.h"

#include <stdlib.h>
#include <sys/time.h>

static void mf_to_colors(SfmlGui* plot, const unsigned* counters);
inline void mf_apply_zoom(float* x_offset, float* y_offset, float* scale, 
                          bool increase);
inline void mf_reset_zoom(float* x_offset, float* y_offset, float* scale); 

static void mf_render(SfmlGui* plot, unsigned* counters,
                         float x_offset, float y_offset, float scale)
{
    timeval start = {}, stop = {};
    gettimeofday(&start, nullptr);
    mf_calculate_avx(plot->width, plot->height, counters,
                        x_offset, y_offset, scale);
    mf_draw_plot(plot, counters);
    gettimeofday(&stop, nullptr);
    int fps = (int)(1 / get_time(start, stop));
    
    char buf[100] = "";
    snprintf(buf, sizeof(buf), "FPS: %d", fps);
    plot->text.setString(buf);
}  

void mf_handle_window(SfmlGui* plot, unsigned* counters)
{   
    assert(plot != nullptr && counters != nullptr);
    
    float x_offset = mf_x_offset;
    float y_offset = mf_y_offset;
    float scale = 1.0f;
    
    // REVIEW 
render:
    mf_render(plot, counters, x_offset, y_offset, scale);
    
    while (plot->window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x_offset += mf_x_step;
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x_offset -= mf_x_step;
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y_offset -= mf_y_step;
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y_offset += mf_y_step;
            goto render;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            mf_apply_zoom(&x_offset, &y_offset, &scale, true);
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            mf_apply_zoom(&x_offset, &y_offset, &scale, false);
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            mf_reset_zoom(&x_offset, &y_offset, &scale);
            goto render;
        }
        
        sf::Event event;
        while (plot->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                plot->window.close();
                return;
            } 
            if (event.type == sf::Event::MouseWheelScrolled) {
                (event.mouseWheelScroll.delta > 0) ? 
                    scale /= mf_scale_step : scale *= mf_scale_step;
                goto render;
            }
        }
    }
}

inline void mf_reset_zoom(float *x_offset, float* y_offset, float* scale)
{
    assert(x_offset != nullptr && y_offset != nullptr && scale != nullptr);
    *x_offset = mf_x_offset;
    *y_offset = mf_y_offset;
    *scale    = 1.f;
}

inline void mf_apply_zoom(float* x_offset, float* y_offset, float* scale, 
                          bool increase)
{
    assert(x_offset != nullptr && y_offset != nullptr && scale != nullptr);
    
    float new_scale = 0;
    
    if (increase)
        new_scale = *scale / mf_scale_step;
    else
        new_scale = *scale * mf_scale_step;
    
    *x_offset += (*scale - new_scale) * *x_offset;
    *y_offset += (*scale - new_scale) * *y_offset;
    *scale = new_scale;
}

void mf_draw_plot(SfmlGui* plot, const unsigned* counters)
{
    assert(plot != nullptr && counters != nullptr);
   
    plot->window.clear();
    mf_to_colors(plot, counters);
    plot->texture.update(plot->colors);
    plot->window.draw(plot->sprite);
    plot->window.draw(plot->text);
    plot->window.display();   
}

static void mf_to_colors(SfmlGui* plot, const unsigned* counters)
{
    assert(plot != nullptr);
    
    for (size_t i = 0; i < plot->width * plot->height; ++i) {
        ((RgbaPixel*)plot->colors)[i] = {.red   = (uint8_t)(counters[i] * red_coeff % 256),
                                         .green = (uint8_t)(counters[i] * green_coeff % 256),
                                         .blue  = (uint8_t)(counters[i] * blue_coeff % 256),
                                         .alpha = 0xff};
    }
}

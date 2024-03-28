/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "plot.h"

#include <stdlib.h>

#include <sys/time.h>

#include "common.h"

inline void mf_update_texture(SfmlGui* plot, MfPlotParams params,
                              unsigned* counters);
static void mf_to_colors(SfmlGui* plot, const unsigned* counters);
inline void mf_apply_zoom(MfPlotParams* params, bool increase);
inline void mf_get_fps(SfmlGui* plot, timeval start, timeval stop);

void mf_handle_window(SfmlGui* plot, unsigned* counters)
{   
    assert(plot != nullptr && counters != nullptr);

    
    MfPlotParams params = {}; 
    mf_update_texture(plot, params, counters);
 
    while (plot->window.isOpen()) { 
        sf::Event event;
        if (plot->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                plot->window.close();
                return;
            } 
        }

        plot->window.clear();
        
        timeval start;
        gettimeofday(&start, nullptr);
           
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            params.x_offset += mf_x_step;
            mf_update_texture(plot, params, counters);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            params.x_offset -= mf_x_step;
            mf_update_texture(plot, params, counters);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            params.y_offset -= mf_y_step;
            mf_update_texture(plot, params, counters);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            params.y_offset += mf_y_step;
            mf_update_texture(plot, params, counters);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            mf_apply_zoom(&params, true);
            mf_update_texture(plot, params, counters);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            mf_apply_zoom(&params, false);
            mf_update_texture(plot, params, counters);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            params = {};
            mf_update_texture(plot, params, counters);
        }
        
        plot->window.draw(plot->sprite);
        
        timeval stop;
        gettimeofday(&stop, nullptr);
        mf_get_fps(plot, start, stop);

        plot->window.display();
    }
}

inline void mf_get_fps(SfmlGui* plot, timeval start, timeval stop)
{
    unsigned fps = 1e6 / (1e6 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec
        - start.tv_usec));
    
    char buf[100] = {};
    sprintf(buf, "FPS: %u", fps);
    plot->text.setString(buf);
    plot->window.draw(plot->text);
}

// FIXME
inline void mf_apply_zoom(MfPlotParams* params, bool increase)
{
    assert(params != nullptr);
    
    float new_scale = 0;
    
    if (increase)
        new_scale = params->scale / mf_scale_step;
    else
        new_scale = params->scale * mf_scale_step;
    
    params->x_offset += (params->scale - new_scale) * params->x_offset;
    params->y_offset += (params->scale - new_scale) * params->y_offset;
    params->scale = new_scale;
}

inline void mf_update_texture(SfmlGui* plot, MfPlotParams params,
                              unsigned* counters)
{
    assert(plot && counters);
    
    mf_calculate_avx(mf_screen_width, mf_screen_height, counters, params);
    mf_to_colors(plot, counters);
    plot->texture.update(plot->colors);
}

static void mf_to_colors(SfmlGui* plot, const unsigned* counters)
{
    assert(plot != nullptr);
    
    for (size_t i = 0; i < plot->width * plot->height; ++i) {
        ((RgbaPixel*)plot->colors)[i] = {
            .red   = (uint8_t)(counters[i] * red_coeff % 256),
            .green = (uint8_t)(counters[i] * green_coeff % 256),
            .blue  = (uint8_t)(counters[i] * blue_coeff % 256),
            .alpha = 0xff
        };
    }
}

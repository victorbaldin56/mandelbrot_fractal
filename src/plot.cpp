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
            scale /= mf_scale_step;
            goto render;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            scale *= mf_scale_step;
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

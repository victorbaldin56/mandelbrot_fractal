/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "plot.h"

#include <stdlib.h>

static void mbrot_to_colors(Plot* plot, const unsigned* counters);

void plot_create(Plot* plot, const char* name, 
                        unsigned width, unsigned height)
{
    assert(plot != nullptr);
    
    plot->window.create(sf::VideoMode(width, height), name);
    plot->texture.create(width, height);
    plot->sprite.setTexture(plot->texture);
    plot->colors = (uint8_t*)calloc(width * height * 4, sizeof(*plot->colors));
    plot->width = width;
    plot->height = height;
}

void mbrot_render(Plot* plot, unsigned* counters)
{   
    assert(plot != nullptr && counters != nullptr);
    
    float x_offset = mbrot_x_offset;
    float y_offset = mbrot_y_offset;
    float scale = 1.0f;
    
    while (plot->window.isOpen()) {
        mbrot_calculate_avx(plot->width, plot->height, counters,
                            x_offset, y_offset, scale);
        mbrot_plot(plot, counters);
    
    no_render:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x_offset += mbrot_x_step;
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x_offset -= mbrot_x_step;
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y_offset -= mbrot_y_step;
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y_offset += mbrot_y_step;
            continue;
        }
        // TODO show zoom in window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            scale /= mbrot_scale_step;
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            scale *= mbrot_scale_step;
            continue;
        }
        
        sf::Event event;
        while (plot->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                plot->window.close();
                return;
            }
        }
        
        goto no_render; // FIXME
    }
}

void mbrot_plot(Plot* plot, const unsigned* counters)
{
    assert(plot != nullptr && counters != nullptr);
   
    plot->window.clear();
    mbrot_to_colors(plot, counters);
    plot->texture.update(plot->colors);
    plot->window.draw(plot->sprite);
    plot->window.display();   
}

static void mbrot_to_colors(Plot* plot, const unsigned* counters)
{
    assert(plot != nullptr);
    
    for (size_t i = 0; i < plot->width * plot->height; ++i) {
        ((Pixel*)plot->colors)[i] = {.red   = (uint8_t)(counters[i] * red_coeff % 256),
                                     .green = (uint8_t)(counters[i] * green_coeff % 256),
                                     .blue  = (uint8_t)(counters[i] * blue_coeff % 256),
                                     .alpha = 0xff};
    }
}

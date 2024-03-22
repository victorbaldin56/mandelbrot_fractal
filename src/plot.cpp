/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "plot.h"

#include <stdlib.h>

static void mbrot_to_colors(Plot* plot, const unsigned* counters);

bool mbrot_plot(Plot* plot, const unsigned* counters)
{
    assert(plot != nullptr && counters != nullptr);
   
    plot->window.clear();
    mbrot_to_colors(plot, counters);
    plot->texture.update(plot->colors);
    plot->window.draw(plot->sprite);
    plot->window.display();
    
    while (plot->window.isOpen()) {
        sf::Event event;
        while (plot->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                plot->window.close();
        }
    }

    return true;
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

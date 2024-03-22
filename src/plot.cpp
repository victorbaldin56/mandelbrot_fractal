/******************************************************************************
 * @file
 * @brief 
 * 
 * @copyright (C) Victor Baldin, 2024.
 *****************************************************************************/

#include "plot.h"

#include <stdlib.h>

static uint8_t* mbrot_to_colors(const unsigned* counters, size_t size);

bool mbrot_plot(unsigned width, unsigned height, const unsigned *counters,
                const char* plot_name)
{
    assert(counters != nullptr);
    
    sf::RenderWindow window(sf::VideoMode(width, height), plot_name);
    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    
    uint8_t* colors = mbrot_to_colors(counters, width * height);
    if (colors == nullptr)
        return false;

    window.clear();
    texture.update(colors);
    window.draw(sprite);
    window.display();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    free(colors);
    return true;
}

static uint8_t* mbrot_to_colors(const unsigned* counters, size_t size) {
    assert(counters != nullptr);
    
    uint8_t* colors = (uint8_t*)calloc(size * sizeof(unsigned), 
                                       sizeof(*colors));
    if (colors == nullptr)
        return nullptr;
    
    for (size_t i = 0; i < size; ++i) {
        ((Pixel*)colors)[i] = {.red   = (uint8_t)(counters[i] * red_coeff % 256),
                               .green = (uint8_t)(counters[i] * green_coeff % 256),
                               .blue  = (uint8_t)(counters[i] * blue_coeff % 256),
                               .alpha = 0xff};
    }
    
    return colors;
}

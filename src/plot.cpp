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
static void mf_to_colors(SfmlGui* plot, MfPlotParams params,
                         const unsigned* counters);
inline void mf_apply_zoom(MfPlotParams* params, bool increase);
inline void mf_print_info(SfmlGui* plot, MfPlotParams params,
                          timeval start, timeval stop);

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

        plot->window.clear();
        plot->window.draw(plot->sprite);

        timeval stop;
        gettimeofday(&stop, nullptr);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
            plot->text.setString(mf_window_help_message);
        else
            mf_print_info(plot, params, start, stop);

        plot->window.draw(plot->text);
        plot->window.display();
    }
}

inline void mf_print_info(SfmlGui* plot, MfPlotParams params,
                          timeval start, timeval stop)
{
    unsigned fps = (unsigned)(1e6 / (1e6 * (double)(stop.tv_sec - start.tv_sec)
        + (double)(stop.tv_usec - start.tv_usec)));

    char buf[100] = {};
    sprintf(buf, "FPS: %u\n"
                 "Scale: %g", fps, 1 / params.scale);
    plot->text.setString(buf);
}

inline void mf_apply_zoom(MfPlotParams* params, bool increase)
{
    assert(params != nullptr);

    float new_scale = 0;

    if (increase)
        new_scale = params->scale / mf_scale_step;
    else
        new_scale = params->scale * mf_scale_step;

    float offset_coeff = (new_scale - params->scale) / new_scale;

    params->x_offset += offset_coeff * ((float)mf_screen_width * mf_pixel_width / 2
        - params->x_offset);
    params->y_offset += offset_coeff * ((float)mf_screen_height * mf_pixel_width / 2
        - params->y_offset);
    params->scale = new_scale;
}

inline void mf_update_texture(SfmlGui* plot, MfPlotParams params,
                              unsigned* counters)
{
    assert(plot && counters);

    mf_calculate_avx(plot->width, plot->height, counters, params);
    mf_to_colors(plot, params, counters);
    plot->texture.update(plot->colors);
}

static void mf_to_colors(SfmlGui* plot, MfPlotParams params,
                         const unsigned* counters)
{
    assert(plot != nullptr);

    for (size_t i = 0; i < plot->width * plot->height; ++i) {
        ((RgbaPixel*)plot->colors)[i] = {
            .red   = (uint8_t)(counters[i] * params.red_coeff % 256),
            .green = (uint8_t)(counters[i] * params.green_coeff % 256),
            .blue  = (uint8_t)(counters[i] * params.blue_coeff % 256),
            .alpha = 0xff
        };
    }
}

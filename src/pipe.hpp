//
// Created by ayesdie on 04/10/20.
//

#ifndef BIRDPOCALYPSE_PIPE_HPP
#define BIRDPOCALYPSE_PIPE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.hpp"

namespace bi {
    class pipe {
        float gap_width;
        float gap_height;
        sf::Vector2f pipe_position;
        sf::Vector2f pipe_velocity;

        sf::RectangleShape pipe_upper;
        sf::RectangleShape pipe_lower;
        sf::RectangleShape ground;

        bool on_screen;

    public:
        pipe() {
            on_screen = true;

            gap_width = 90;
            gap_height = 210;

            pipe_position = sf::Vector2f(WINDOW_WIDTH, random_uniform(40 + gap_height / 2, WINDOW_WIDTH - 50 - gap_height / 2));
            pipe_velocity = sf::Vector2f(-10, 0);

            pipe_upper = sf::RectangleShape(sf::Vector2f(gap_width, 2000));
            pipe_upper.setFillColor(sf::Color::Green);
            pipe_lower = sf::RectangleShape(sf::Vector2f(gap_width, 2000));
            pipe_lower.setFillColor(sf::Color::Green);

            ground = sf::RectangleShape(sf::Vector2f(620, 20));
            ground.setFillColor(sf::Color::Blue);
            ground.setPosition(sf::Vector2f(0, 700));
        }

        void draw(sf::RenderWindow* window) {
            pipe_upper.setPosition(pipe_position + sf::Vector2f(- gap_width / 2, - 2000 - (gap_height / 2)));
            pipe_lower.setPosition(pipe_position + sf::Vector2f(- gap_width / 2, gap_height / 2));

            window->draw(pipe_upper);
            window->draw(pipe_lower);
            window->draw(ground);
        }

        void update() {
            pipe_position += pipe_velocity;

            if (pipe_position.x < - 50)
            {
                on_screen = false;
            }
        }

        bool check_collision(const sf::Vector2f& position) {
            bool collision_too_high = (position.x > pipe_position.x - gap_width / 2) && (position.x < pipe_position.x + gap_width / 2) && (position.y < - 40);
            bool collision_upper = (position.x > pipe_position.x - gap_width / 2) && (position.x < pipe_position.x + gap_width / 2) && (position.y > - 100) && (position.y < pipe_position.y - gap_height / 2);
            bool collision_lower = (position.x > pipe_position.x - gap_width / 2) && (position.x < pipe_position.x + gap_width / 2) && (position.y > pipe_position.y + gap_height / 2) && (position.y < 1500);
            bool collision_ground = position.y > 700;
            return collision_too_high || collision_upper || collision_lower || collision_ground;
        }

        bool is_on_screen() { return on_screen; }

        sf::Vector2f get_pipe_end_position() {
            return pipe_position + sf::Vector2f(gap_width / 2, 0);
        }
    };
}

#endif //BIRDPOCALYPSE_PIPE_HPP

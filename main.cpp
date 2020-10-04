//
// Created by ayesdie on 04/10/20.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/population.hpp"

int main() {
    auto window = new sf::RenderWindow(sf::VideoMode(bi::WINDOW_WIDTH, bi::WINDOW_HEIGHT), "birdpocalypse",sf::Style::Titlebar | sf::Style::Close);

    bi::population pop(100);

    sf::Clock clock;
    sf::Time time;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
//                case sf::Event::KeyPressed:
//                    switch (event.key.code) {
//                        case sf::Keyboard::Space:
//                            pop.flap();
//                            break;
//                    }
//                    break;
                case sf::Event::Closed:
                    window->close();
                    break;

            }
        }

        time = clock.getElapsedTime();
        if (time.asMilliseconds() >= 20)
        {
            if (pop.is_all_dead()) {
                pop.natural_selection();
                pop.mutate(0.1);
            }
            else {
                window->clear(sf::Color(0, 206, 209));
                pop.update();
                pop.draw(window);
                window->display();
            }

            clock.restart();
        }
    }

    return 0;
}

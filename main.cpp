//
// Created by ayesdie on 04/10/20.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/population.hpp"

int main() {
    auto window = new sf::RenderWindow(sf::VideoMode(bi::WINDOW_WIDTH, bi::WINDOW_HEIGHT), "birdpocalypse",sf::Style::Titlebar | sf::Style::Close);

    bi::population pop(100);

    bi::brain chad_brain;
    chad_brain.load("../big_brains/4-1/pogger_brain_gasm_2.txt");

    bi::bird chad_bird;
    chad_bird.set_brain(chad_brain);

    pop.set_chad_bird(chad_bird);

    sf::Clock clock;
    sf::Time time;

    std::vector<double> refresh_rate({20, 10, 5, 1, 0.0001});
    int current_rate = 1;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::D:
                            current_rate = (current_rate + 1) % refresh_rate.size();
                            std::cout << current_rate;
                            break;
                        case sf::Keyboard::A:
                            current_rate = (current_rate - 1 < 0) ? refresh_rate.size() : current_rate - 1;
                            std::cout << current_rate;
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window->close();
                    break;

            }
        }

        time = clock.getElapsedTime();
        // time for a speedrun :)
        if (time.asMilliseconds() >= refresh_rate[current_rate])
        {
            if (pop.is_all_dead()) {
                pop.natural_selection();
                pop.mutate(0.3);
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

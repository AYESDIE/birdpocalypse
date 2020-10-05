//
// Created by ayesdie on 04/10/20.
//

#ifndef BIRDPOCALYPSE_POPULATION_HPP
#define BIRDPOCALYPSE_POPULATION_HPP

#include <iostream>
#include <vector>
#include "bird.hpp"
#include "pipe.hpp"

namespace bi {
    class population {
        std::vector<bird> birds;
        std::vector<pipe> pipes;
        std::vector<pipe> finished_pipes;

        bird best_bird;

        size_t current_generation;
        size_t babies_per_generation;
        int babies_alive;
        bool all_dead;
        size_t score;

        double fitness_score_sum;
        double best_fitness_score;
        size_t best_score;

        size_t step;

        void info(sf::RenderWindow* window) {
            sf::RectangleShape rect(sf::Vector2f(600, 30));
            rect.setFillColor(sf::Color::Black);
            rect.setPosition(0, 720);
            window->draw(rect);

            sf::Text text;
            sf::Font font;

            font.loadFromFile("arial.ttf");
            text.setFont(font);
            text.setFillColor(sf::Color(255, 255, 255));
            text.setCharacterSize(10);

            text.setString("Generation: " + std::to_string(current_generation));
            text.setPosition(10, 725);
            window->draw(text);

            text.setString("Score: " + std::to_string(score));
            text.setPosition(10, 735);
            window->draw(text);

            text.setString("Babies Alive: " + std::to_string(babies_alive));
            text.setPosition(210, 725);
            window->draw(text);

            text.setString("Best Fitness Score: " + std::to_string(best_fitness_score));
            text.setPosition(210, 735);
            window->draw(text);

            text.setString("Best Score: " + std::to_string(best_score));
            text.setPosition(410, 725);
            window->draw(text);
        }

        bird get_fit_parent_bird() {
            auto rng = bi::random_uniform<double>(0, fitness_score_sum);
            double running_sum = 0;
            for (auto &bird : birds) {
                running_sum += bird.get_fitness_score();
                if (running_sum > rng) {
                    return bird;
                }
            }

            return birds[int(random_uniform<double>(0, birds.size() - 1))];
        }

        void calculate_fitness_score_sum() {
            fitness_score_sum = 0;
            for (auto &bird : birds) {
                fitness_score_sum += bird.get_fitness_score();
            }
        }


    public:
        population(size_t babies) {
            babies_per_generation = babies;
            babies_alive = babies;
            current_generation = 1;
            score = 0;

            birds = std::vector<bird>(babies);
            pipes = std::vector<pipe>(1);

            best_fitness_score = 0;
            best_score = 0;

            step = 0;
            all_dead = false;
        }

        bool is_all_dead() { return all_dead; }

        void set_chad_bird(bird chad_bird) {
            birds[0] = chad_bird;
        }

        void draw(sf::RenderWindow* window) {
            for (auto &bird : birds) {
                bird.draw(window);
            }

            for (auto &pipe : pipes) {
                pipe.draw(window);
            }

            for (auto &finished_pipe : finished_pipes) {
                finished_pipe.draw(window);
            }

            info(window);
        }

        void update() {
            for (auto &bird : birds) {
                bird.update(pipes[0]);

                for (auto &point : bird.get_collision_points()) {
                    if (bird.is_alive() && pipes.begin()->check_collision(point)) {
                        bird.set_alive(false);
                        bird.calculate_fitness_score();

                        if (bird.get_fitness_score() > best_fitness_score) {
                            best_fitness_score = bird.get_fitness_score();
                            bird.save_bird();
                            best_bird = bird;
                        }

                        babies_alive--;
                    }
                }
            }

            for (auto &pipe : pipes) {
                pipe.update();
            }

            if (pipes.begin()->get_pipe_end_position().x < birds.begin()->get_collision_points()[3].x){
                finished_pipes.emplace_back(pipes[0]);
                pipes.erase(pipes.begin());

                score++;
            }

            for (auto &finished_pipe : finished_pipes) {
                finished_pipe.update();
            }

            if (finished_pipes.size() > 0 && !finished_pipes.begin()->is_on_screen()) {
                finished_pipes.erase(finished_pipes.begin());
            }

            if (step > 0 && step % 34 == 0) {
                pipes.emplace_back(pipe());
            }

            step++;
            if (babies_alive <= 0) {
                all_dead = true;
            }
            else
            {
                all_dead = false;
            }
        }

        void flap() {
            for (auto &item : birds) {
                item.flap();
            }
        }

        void natural_selection() {
            calculate_fitness_score_sum();

            std::vector<bird> new_birds;
            new_birds.clear();

            new_birds.push_back(best_bird * best_bird);
            for (int i = 1; i < babies_per_generation; i++) {
                if (i % 2 == 0) {
                    new_birds.push_back(get_fit_parent_bird() * get_fit_parent_bird());
                }
                else {
                    auto single_dad = get_fit_parent_bird();
                    new_birds.push_back(single_dad * single_dad);
                }
            }

            current_generation++;
            babies_alive = babies_per_generation;
            all_dead = false;
            birds = new_birds;

            finished_pipes.clear();
            pipes = std::vector<pipe>(1);
            step = 0;

            if (score > best_score) {
                best_score = score;
            }

            score = 0;
        }

        void mutate(double mutation_rate) {
            for (int i = 1; i < babies_per_generation; ++i) {
                birds[i].mutate(mutation_rate);
            }
        }
    };
}

#endif //BIRDPOCALYPSE_POPULATION_HPP

//
// Created by ayesdie on 04/10/20.
//

#ifndef BIRDPOCALYPSE_BIRD_HPP
#define BIRDPOCALYPSE_BIRD_HPP

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "brain.hpp"
#include "pipe.hpp"

namespace bi {
    class bird {
        brain bird_brain;

        double fitness_score;

        float bird_radius;
        sf::Vector2f bird_position;
        sf::Vector2f bird_velocity;
        sf::CircleShape bird_body;

        bool alive;

        size_t step;

    public:
        bird() {
            alive = true;
            bird_radius = 10;
            bird_position = sf::Vector2f(100, 100);
            bird_velocity = sf::Vector2f(0, 0);
            bird_body = sf::CircleShape(bird_radius);

            int R = bi::random_uniform(0,150);
            int G = bi::random_uniform(0,150);
            int B = bi::random_uniform(0,150);

            bird_body.setFillColor(sf::Color(R, G, B, 200));
            bird_body.setPosition(bird_position);

            fitness_score = 0;
            step = 0;
        }

        void draw(sf::RenderWindow* window) {
            if (alive) {
                bird_body.setPosition(bird_position);
                window->draw(bird_body);
            }
        }

        void update(pipe& pipe) {
            if (alive) {
                bird_velocity.y += GRAVITY;
                bird_position += bird_velocity;

                Eigen::MatrixXd sense(1, 4);
                sense(0, 0) = 1 / (pipe.get_pipe_end_position().x - bird_position.x);
                sense(0, 1) = 1 / (pipe.get_pipe_end_position().y - bird_position.y);
                sense(0, 2) = 1 / bird_position.y;
                sense(0, 3) = 1 / bird_velocity.y;

                if (bird_brain.calculate_flap(sense)) {
                    flap();
                }

                step++;
            }
        }

        void flap() {
            bird_velocity.y = -20;
        }

        std::vector<sf::Vector2f> get_collision_points() {
            std::vector<sf::Vector2f> points;
            points.push_back(bird_position + sf::Vector2f(0, bird_radius));
            points.push_back(bird_position + sf::Vector2f(0, - bird_radius));
            points.push_back(bird_position + sf::Vector2f(bird_radius, 0));
            points.push_back(bird_position + sf::Vector2f(- bird_radius, 0));
            return points;
        }

        void set_alive(bool is) {
            alive = is;
        }

        bool is_alive() { return alive; }

        void calculate_fitness_score() {
            fitness_score = std::pow(step, 2) / 1000;
        }

        double get_fitness_score() { return fitness_score; }

        void set_brain(brain B) {
            bird_brain = B;
        }

        bird operator*(bird const &rhs) {
            bird baby_bird;
            baby_bird.set_brain(bird_brain * rhs.bird_brain);
            return baby_bird;
        }

        void mutate(double mutation_rate) {
            bird_brain.mutate(mutation_rate);
        }


        void save_bird() {
            std::ofstream file("best_bird.txt");
            if (file.is_open())
            {
                file << "Score: " << step << "\n";
                file << "Fitness Score: " << fitness_score << "\n";
            }

            file.close();
            bird_brain.save_brain();
        }
    };
}

#endif //BIRDPOCALYPSE_BIRD_HPP

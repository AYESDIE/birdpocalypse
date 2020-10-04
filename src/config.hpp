//
// Created by ayesdie on 04/10/20.
//

#ifndef BIRDPOCALYPSE_CONFIG_HPP
#define BIRDPOCALYPSE_CONFIG_HPP

#include <random>

namespace bi {
    float GRAVITY = 2;
    int WINDOW_WIDTH = 600;
    int WINDOW_HEIGHT = 750;

    template <typename T>
    T random_uniform(T lower_bound, T upper_bound) {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(lower_bound,upper_bound);
        return dist(e2);
    }

    template <typename T>
    T random_normal(T lower_bound, T upper_bound) {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::normal_distribution<> dist(lower_bound,upper_bound);
        return dist(e2);
    }
}

#endif //BIRDPOCALYPSE_CONFIG_HPP

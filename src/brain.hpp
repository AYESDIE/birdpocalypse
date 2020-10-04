//
// Created by ayesdie on 04/10/20.
//

#ifndef BIRDPOCALYPSE_BRAIN_HPP
#define BIRDPOCALYPSE_BRAIN_HPP

#include <Eigen/Dense>
#include <fstream>

#define E 2.71828182845904523536

namespace bi {
    class brain {
    private:
        std::vector<Eigen::MatrixXd> weights;

    public:
        brain() {
            weights.emplace_back(Eigen::MatrixXd::Random(2, 6));
            weights.emplace_back(Eigen::MatrixXd::Random(6, 1));
        }

        brain(std::vector<Eigen::MatrixXd> custom_weights) {
            weights = custom_weights;
        }

        bool calculate_flap(Eigen::MatrixXd& input) {
            auto hidden_layer_in = input * weights[0];
            auto hidden_layer_activated = hidden_layer_in.unaryExpr([](double x){ return (1 / (1 + std::pow(E, -x))); });

            auto output_layer_in = hidden_layer_activated * weights[1];
            auto output_layer_activated = output_layer_in.unaryExpr([](double x){ return (1 / (1 + std::pow(E, -x))); });

            return (output_layer_activated(0, 0) > 0.5);
        }

        brain operator*(brain const &rhs) {
            brain res;
            for (int x = 0; x < weights.size(); x++) {
                for (int i = 0; i < weights[x].rows(); ++i) {
                    for (int j = 0; j < weights[x].cols(); ++j) {
                        auto rng = bi::random_uniform<double>(0, 1);
                        res.weights[x](i, j) = (rng <= 0.5) ? weights[x](i, j) : rhs.weights[x](i, j);
                    }
                }
            }
            return res;
        }

        void mutate(double mutation_rate) {
            for (int x = 0; x < weights.size(); x++) {
                for (int i = 0; i < weights[x].rows(); ++i) {
                    for (int j = 0; j < weights[x].cols(); ++j) {
                        auto rng = bi::random_uniform<double>(0, 1);
                        if (rng < mutation_rate) {
                            weights[x](i, j) += bi::random_normal<double>(-1, 1);

                            if (weights[x](i, j) > 1) {
                                weights[x](i, j) = 1;
                            }
                            else if (weights[x](i, j) < -1) {
                                weights[x](i, j) = -1;
                            }
                        }
                    }
                }
            }
        }

        void save_brain() {
            std::ofstream file("best_brain.txt");
            if (file.is_open())
            {
                for (auto &weight : weights) {
                    for (int i = 0; i < weight.rows(); ++i) {
                        for (int j = 0; j < weight.cols(); ++j) {
                            file << weight(i, j) << " ";
                        }
                    }
                    file << "\n";
                }
            }

            file.close();
        }
    };
}

#endif //BIRDPOCALYPSE_BRAIN_HPP

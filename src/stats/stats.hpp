//
// Created by chromeilion on 11/25/23.
//

#ifndef NUMOOP_STATS_HPP
#define NUMOOP_STATS_HPP
#include "armadillo"
#include <vector>
#include <variant>
#include <string>

template<typename T>
class DataFrame {
private:
    std::vector<arma::Col<std::variant<T>>> cols;
    arma::Col<int> &factorize(std::vector<std::string> &categorical);
public:
    // Read a csv and populate the DataFrame with its contents.
    void read_csv(std::string &csv_path);
    std::variant<T> &operator[](std::size_t idx);
};

template<typename T>
arma::Col<int> &DataFrame<T>::factorize(std::vector<std::string> &categorical) {
    return <#initializer#>;
}

template<typename T>
std::variant<T> &DataFrame<T>::operator[](std::size_t idx) {
    return this->col[idx];
}

template<typename T>
void DataFrame<T>::read_csv(std::string &csv_path) {
    // TODO
}


#endif //NUMOOP_STATS_HPP

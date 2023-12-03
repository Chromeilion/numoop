//
// Created by uki on 11/24/23.
//
#include <stats/stats.hpp>
#include <iostream>

int main() {
    // Initialize the DataFrame object
    oop::stats::DataFrame data;
    // The location of our dataset
    std::string filepath{"./tests/dataset.csv"};
    // Load the dataset into our dataframe
    oop::stats::load(filepath, data, true);
    data.summarize();

    auto header = data.column_labels();
    arma::uword target = std::find((*header).begin(), (*header).end(),
                            "Target") - (*header).begin();
    auto target_map = data.get_map(target);
    for (auto& [key, value]: target_map) {
        std::cout << key << ": " << value << std::endl;
    }
    return 0;
}

//
// Created by uki on 11/24/23.
//
#include <stats/stats.hpp>
#include <iostream>

int main() {
    std::cout << "Let's perform some statistics on the Students Performance dataset "
                 "from Kaggle!" << std::endl;
    std::cout << "This dataset can be found at: " << std::endl <<
    "https://www.kaggle.com/datasets/thedevastator/higher-education-predictors-of-student-retention"
    << std::endl << std::endl;

    // Initialize the DataFrame object
    oop::stats::DataFrame data;
    // The location of our dataset on disk
    std::string filepath{"./tests/dataset.csv"};
    // Load the dataset into our dataframe
    std::vector<std::string> col_types;
    col_types = oop::stats::load(filepath, data, true);

    std::cout << "Column types have been autodetected as: " << std::endl;
    for (auto type: col_types) {
        std::cout << type << ", ";
    }
    std::cout << std::endl << std::endl;
    std::cout << "We can run DataFrame.summarize() to get a summary of our data: "
    << std::endl;
    data.summarize();

    auto header = data.column_labels();
    arma::uword target = std::find((*header).begin(), (*header).end(),
                            "Target") - (*header).begin();
    auto target_map = data.get_map(target);
    std::cout << std::endl << "The mappings for the 'Target' column are: "
    << std::endl;
    for (auto& [key, value]: target_map) {
        std::cout << key << ": " << value << std::endl;
    }

    // Let's calculate the percentage of students that graduate.
    // We can easily unpack the std::variant with std::get, because we know what
    // the autodetected type of the column is.
    auto graduate = std::get<arma::Col<arma::uword>>(data("Target"));
    std::cout << std::endl <<  "The probability of being a graduate in this dataset is: ";
    arma::uword count{0};
    for (const auto &student: graduate) {if (student==1) {count = count+1;}}
    std::cout << (float)count/(float)graduate.size() << std::endl;
    return 0;
}

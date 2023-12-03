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
    std::cout << "Loading dataset from: " << filepath << std::endl
    << "Make sure to run this script from the project root directory!" << std::endl
    << std::endl;
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
    std::cout << std::endl <<  "The proportion of graduates in this dataset is: ";
    arma::uword count{0};
    for (const auto &student: graduate) {if (student==1) {count = count+1;}}
    std::cout << (float)count/(float)graduate.size() << std::endl << std::endl;

    // As a test, lets try loading only the 3rd column in the CSV:
    oop::stats::DataFrame application_mode;
    // Load the dataset into our dataframe
    std::vector<std::string> partial_col_types;
    std::vector<int> cols;
    cols.push_back(2);
    partial_col_types = oop::stats::load(filepath, application_mode, true, cols);
    std::cout << "Loading only the 3rd column from the CSV file gets the "
                 "following DataFrame: " << std::endl;
    application_mode.summarize(); std::cout << std::endl;

    // Let's investigate the correlation between graduating and having a scholarship:
    auto scholarship = std::get<arma::Col<arma::sword>>(data("Scholarship holder"));
    std::cout << "The correlation between Scholarship holder and Target is: " <<
    arma::cor(arma::conv_to<arma::colvec>::from(scholarship), arma::conv_to<arma::colvec>::from(graduate)) << std::endl << std::endl;

    // Now let's sum the curricular units in the first and second semesters and
    // add it as a new column in the DataFrame:
    std::cout << "Appending total evaluation credits from the 1st and 2nd semesters "
                 "into a new column at the end of the dataframe called 'credit_sums': " << std::endl;
    auto first_sem_cred = std::get<arma::Col<arma::sword>>(data("Curricular units 1st sem (evaluations)"));
    auto second_sem_cred = std::get<arma::Col<arma::sword>>(data("Curricular units 2nd sem (evaluations)"));
    auto first_second_total_cred = arma::Col<long long>(first_sem_cred.size());
    first_second_total_cred = first_sem_cred + second_sem_cred;
    data.append_column(first_second_total_cred, "credit_sums");
    data.summarize();
    return 0;
}

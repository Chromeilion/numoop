//
// Created by uki on 11/24/23.
//
// Some tests make use of this dataset from Kaggle:
// "https://www.kaggle.com/datasets/thedevastator/higher-education-predictors-of-student-retention"
//
#include <stats/stats.hpp>
#include <iostream>
#include <gtest/gtest.h>


typedef std::pair<oop::stats::DataFrame, std::optional<std::vector<std::string>>> dataframe_col;
class DataFrameTest : public testing::Test {
protected:
    // Set up all static members when the first test is run.
    static void SetUpTestSuite() {
        if (d2_ == nullptr and d3_ == nullptr) {
            d2_ = new dataframe_col;
            d2_->second = oop::stats::load(filepath, d2_->first, true);
            d3_ = new dataframe_col;
            d3_->second = oop::stats::load(filepath, d2_->first, true);
        }
    }
    // Remember to delete all the pointers when we're done.
    static void TearDownTestSuite() {
        delete d2_;
        d2_ = nullptr;
        delete d3_;
        d3_ = nullptr;
    }
    oop::stats::DataFrame d0_;
    oop::stats::DataFrame d1_{{{0, 1.5, 4}, {3, 14.99, 50}, {10, 8.12, 33}},
                              {{"tc_1", "tc_2", "tc_3"}}};
    static const inline std::string filepath = "./tests/dataset.csv";
    static dataframe_col* d2_; // DataFrame with CSV data
    static dataframe_col* d3_; // DataFrame with partial CSV data
};
dataframe_col* DataFrameTest::d2_ = nullptr;
dataframe_col* DataFrameTest::d3_ = nullptr;

TEST_F(DataFrameTest, LoadCSV) {
    // Load the dataset into our dataframe
    std::vector<std::string> col_types;
    oop::stats::load(filepath, d0_, true);
}

TEST_F(DataFrameTest, LoadCSVPartially) {
    std::vector<int> cols;
    cols.push_back(2);
    oop::stats::load(filepath, d3_->first, true, cols);
}

TEST_F(DataFrameTest, LoadCSVHeader) {
    std::vector<std::string> correct_header{
        "\xEF\xBB\xBFMarital status","Application mode","Application order","Course",
        "Daytime/evening attendance","Previous qualification","Nationality",
        "Mother's qualification","Father's qualification","Mother's occupation",
        "Father's occupation","Displaced","Educational special needs","Debtor",
        "Tuition fees up to date","Gender","Scholarship holder","Age at enrollment",
        "International","Curricular units 1st sem (credited)",
        "Curricular units 1st sem (enrolled)","Curricular units 1st sem (evaluations)",
        "Curricular units 1st sem (approved)","Curricular units 1st sem (grade)",
        "Curricular units 1st sem (without evaluations)",
        "Curricular units 2nd sem (credited)","Curricular units 2nd sem (enrolled)",
        "Curricular units 2nd sem (evaluations)","Curricular units 2nd sem (approved)",
        "Curricular units 2nd sem (grade)","Curricular units 2nd sem (without evaluations)",
        "Unemployment rate","Inflation rate","GDP", "Target"
    };
    ASSERT_TRUE(d2_->first.column_labels()) << "Header not found in CSV file.";
    EXPECT_EQ(*(d2_->first.column_labels()), correct_header) << "Loaded header is incorrect";
}

TEST_F(DataFrameTest, LoadCSVTypesAutodetect) {
    std::vector<std::string> correct_types{
        "long long", "long long", "long long", "long long", "long long",
        "long long", "long long", "long long", "long long", "long long",
        "long long", "long long", "long long", "long long", "long long",
        "long long", "long long", "long long", "long long", "long long",
        "long long", "long long", "long long", "float", "long long", "long long",
        "long long", "long long", "long long", "float", "long long", "float",
        "float", "float", "Catagorical (arma::uword)"};
    EXPECT_EQ(*d2_->second, correct_types);
}

TEST_F(DataFrameTest, LoadCSVCatMap) {
    std::unordered_map<arma::uword, std::string> correct_catmap{
            {0, "Dropout"}, {1, "Graduate"}, {2, "Enrolled"}
    };
    std::unordered_map<arma::uword, std::string> map = d2_->first.get_map(34);
    EXPECT_EQ(map.size(), 3);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_TRUE(map[i]=="Dropout" or map[i]=="Graduate" or map[i]=="Enrolled");
    }
}

TEST_F(DataFrameTest, LoadCSVCorrectShape) {
    EXPECT_EQ(d2_->first.shape().first, 998) << "Wrong number of rows returned by .shape()";
    EXPECT_EQ(d2_->first.shape().second, 35) << "Wrong number of columns returned by .shape()";
}

TEST_F(DataFrameTest, Summarize) {
    std::string correct_output{"tc_1, tc_2, tc_3, \n0 1.5 4 \n3 14.99 50 \n10 8.12 33 \nDataset shape: (3, 3)\n"};
    testing::internal::CaptureStdout();
    d1_.summarize();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, correct_output);
}

TEST_F(DataFrameTest, Indexing) {
    auto col1 = std::get<arma::icolvec>(d1_[0]);
    auto col2 = std::get<arma::colvec>(d1_[1]);
    auto col3 = std::get<arma::icolvec>(d1_[2]);

    arma::Col<long long> correct_col1{0, 3, 10};
    arma::Col<double> correct_col2{1.5, 14.99, 8.12};
    arma::Col<long long> correct_col3{4, 50, 33};
    std::string message{"Indexed column has the wrong values."};
    EXPECT_TRUE(arma::approx_equal(col1, correct_col1, "absdiff",
                                   0)) << message;
    EXPECT_TRUE(arma::approx_equal(col2, correct_col2, "absdiff",
                                   0.001)) << message;
    EXPECT_TRUE(arma::approx_equal(col3, correct_col3, "absdiff",
                                   0)) << message;
}

TEST_F(DataFrameTest, AppendColumn) {
    oop::stats::sup_col_types new_column{arma::vec{5.2, 5.5, 6.4}};
    d1_.append_column(new_column, "New Column");
    ASSERT_TRUE(d1_.shape().second == 4);
    ASSERT_TRUE(d1_.shape().first == 3);
    ASSERT_EQ((*d1_.column_labels())[(*d1_.column_labels()).size()-1],
              "New Column");
}

TEST_F(DataFrameTest, AppendInvalidColumn) {
    oop::stats::sup_col_types invalid_column{arma::vec{3.3}};
    ASSERT_ANY_THROW(d1_.append_column(invalid_column));
}

TEST_F(DataFrameTest, InsertColumn) {
    const std::string new_column_label{"New Column"};
    const arma::vec new_column{5.2, 5.5, 6.4};
    oop::stats::sup_col_types new_column_var{new_column};
    d1_.insert_column(new_column_var, 0, new_column_label);
    EXPECT_TRUE(d1_.shape().second == 4);
    EXPECT_TRUE(d1_.shape().first == 3);
    EXPECT_EQ((*d1_.column_labels())[0], new_column_label);
    auto col = std::get<arma::vec>(d1_[0]);
    EXPECT_TRUE(arma::approx_equal(col, new_column, "absdiff", 0));
    EXPECT_NO_THROW(d1_.insert_column(new_column_var, 0));
}

TEST_F(DataFrameTest, InsertInvalidColumn) {
    oop::stats::sup_col_types invalid_column{arma::vec{3.3}};
    ASSERT_ANY_THROW(d1_.insert_column(invalid_column, 0));
}

TEST_F(DataFrameTest, AppendRow) {
    std::vector<oop::stats::sup_single_types> new_row{5, 5.5, 6};

    ASSERT_NO_THROW(d1_.append_row(new_row));
    EXPECT_TRUE(d1_.shape().first == 4);
    EXPECT_TRUE(d1_.shape().second == 3);
}

TEST_F(DataFrameTest, AppendInvalidRowType) {
    std::vector<oop::stats::sup_single_types> invalid_row{5.9, 2.2, 66.4};
    EXPECT_ANY_THROW(d1_.append_row(invalid_row));
}

TEST_F(DataFrameTest, AppendInvalidRowLen) {
    std::vector<oop::stats::sup_single_types> invalid_row{9, 99.9, 5, 44};
    EXPECT_ANY_THROW(d1_.append_row(invalid_row));
}

TEST_F(DataFrameTest, SetValidLabel) {
    std::vector<std::string> new_labels{"l1", "l2", "l3"};
    EXPECT_NO_THROW(d1_.set_column_labels(new_labels));
    EXPECT_EQ(d1_.column_labels(), new_labels) << "Column labels were set incorrectly.";
}

TEST_F(DataFrameTest, SetInvalidLabel) {
    std::vector<std::string> new_labels{"l1", "l2", "l3", "l4"};
    ASSERT_ANY_THROW(d1_.set_column_labels(new_labels));
}

TEST_F(DataFrameTest, CorrectShape) {
    EXPECT_EQ(d1_.shape().first, 3) << "Wrong number of rows returned by .shape()";
    EXPECT_EQ(d1_.shape().second, 3) << "Wrong number of columns returned by .shape()";
}

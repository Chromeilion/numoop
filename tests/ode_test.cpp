//
// Created by kiki on 01/02/2024.
//

#include "ode/ode.hpp"
#include <iostream>
#include <gtest/gtest.h>

using namespace oop::ode_scal;
using namespace oop::ode_vec;
using func_scal = std::function<double(double,double)>;
using func_vec = std::function<arma::Col<double>(double, const arma::Col<double>&)>;

class ODETest : public testing::Test {

protected:

    // Attributes for instantiation
    func_scal f_sc = [](double t, double y) -> double {
        // Example scalar ODE: dy/dt = y + t
        return t + y;
    };
    func_vec f = [](double t, const arma::Col<double>& y) -> arma::Col<double> {
        // Example system: dy0/dt = y1, dy1/dt = -y0
        t = 0;
        return arma::Col<double>({y(1)+t, -y(0)});
    };
    double y0_sc = 1.0;
    arma::Col<double> y0 = {0.0, 1.0};
    double h = 0.05;
    double end = 0.5;

    // Helper function to compare two CSV files
    void CompareCSV(const std::string& generated_csv, const std::string& reference_csv) {
        // Load the generated CSV file
        arma::Mat<double> generated_mat;
        generated_mat.load(generated_csv, arma::csv_ascii);

        // Load the reference CSV file
        arma::Mat<double> reference_mat;
        reference_mat.load(reference_csv, arma::csv_ascii);

        // Compare the generated CSV with the reference CSV
        ASSERT_TRUE(arma::approx_equal(generated_mat, reference_mat, "absdiff", 1e-6));
    }

    // Test case for scalar Euler
    void TestEulerScal() {
        // Instantiate Euler_Scal object
        Euler_Scal<> eulerObj(f_sc, y0_sc, h, end);

        // Call ode() to perform the method and save the result to a CSV file
        eulerObj.ode();

        // Compare the generated CSV with the reference CSV
        const std::string reference_csv = "csvtests/euler_scalar.csv";
        CompareCSV("build/result_euler_scalar.csv", reference_csv);
    }

    // Test case for scalar Midpoint
    void TestMidpointScal() {

        Midpoint_Scal<> midpointObj(f_sc, y0_sc, h, end);
        midpointObj.ode();
        const std::string reference_csv = "csvtests/midpoint_scalar.csv";
        CompareCSV("build/result_midpoint_scalar.csv", reference_csv);
    }

    // Test case for scalar RungeKutta4
    void TestRK4Scal() {

        RK4_Scal<> rk4Obj(f_sc, y0_sc, h, end);
        rk4Obj.ode();
        const std::string reference_csv = "csvtests/rk4_scalar.csv";
        CompareCSV("build/result_rk4_scalar.csv", reference_csv);
    }

    // Test case for vector Euler
    void TestEulerVec() {

        oop::ode_vec::Euler<> eulerObj(f, y0, h, end);
        eulerObj.ode();
        const std::string reference_csv = "csvtests/euler_vector.csv";
        CompareCSV("build/result_euler_vector.csv", reference_csv);
    }

    // Test case for vector Midpoint
    void TestMidpointVec() {

        Midpoint<> midpointObj(f, y0, h, end);
        midpointObj.ode();
        const std::string reference_csv = "csvtests/midpoint_vector.csv";
        CompareCSV("build/result_midpoint_vector.csv", reference_csv);
    }

    // Test case for vector RungeKutta4
    void TestRK4Vec() {

        RK4<> rk4Obj(f, y0, h, end);
        rk4Obj.ode();
        const std::string reference_csv = "csvtests/rk4_vector.csv";
        CompareCSV("build/result_rk4_vector.csv", reference_csv);
    }
};

// Test case for scalar Euler
TEST_F(ODETest, TestEulerScal) {
    TestEulerScal();
}

// Test case for scalar Midpoint
TEST_F(ODETest, TestMidpointScal) {
    TestMidpointScal();
}

// Test case for scalar RungeKutta4
TEST_F(ODETest, TestRK4Scal) {
    TestRK4Scal();
}

// Test case for vector Euler
TEST_F(ODETest, TestEulerVec) {
    TestEulerVec();
}

// Test case for vector Midpoint
TEST_F(ODETest, TestMidpointVec) {
    TestMidpointVec();
}

// Test case for vector RungeKutta4
TEST_F(ODETest, TestRK4Vec) {
    TestRK4Vec();
}
//
// Created by uki on 11/24/23.
//
#include <iostream>
#include <armadillo>
#include "stats.hpp"

using namespace std;
using namespace arma;

int main()
{
    mat A(4, 5, fill::randu);
    mat B(4, 5, fill::randu);

    cout << A*B.t() << mean(A) << endl;

    return 0;
}

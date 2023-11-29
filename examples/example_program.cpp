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
    mat A;
    field<std::string> header{2};
    header[0] = "Marital status";
    header[1] = "Application mode";
    bool res = A.load(csv_name("/home/chromeilion/Code/Uni/uni2023w/ap/ap2023/hw2/numoop/examples/dataset.csv", header));
    cout << res << endl;
    A.print();
    return 0;
}

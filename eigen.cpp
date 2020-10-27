#include <iostream>
#include <eigen3/Eigen/Dense>
#include <chrono>
#include <iomanip>

using namespace Eigen;
using namespace std;

int main() {

    auto t1 = chrono::high_resolution_clock::now();
    int n = 10000;
    MatrixXf a = MatrixXf::Random(n, n);
    MatrixXf b = MatrixXf::Random(n, n);
    MatrixXf c = MatrixXf::Random(n, n);
    a = a*1;
    b = b*1;
    c = c*1;

    auto t2 = chrono::high_resolution_clock::now();
    c = a*b;
    auto t3 = chrono::high_resolution_clock::now();
    auto durationAll = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    auto duration = chrono::duration_cast<chrono::microseconds>(t3-t2).count();
    cout << "(n=" << std::setw(10) << n << ", ";
    cout << "t=" << durationAll/1000.0 << ")\n";
    cout << "t=" << duration/1000.0 << ")\n";

}

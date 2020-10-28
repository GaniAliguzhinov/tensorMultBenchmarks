#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace Eigen;
using namespace std;

double timeProduct(int n) {

    MatrixXf a = MatrixXf::Random(n, n);
    MatrixXf b = MatrixXf::Random(n, n);
    auto t2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) {
        b = a*b;
    }
    auto t3 = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(t3-t2).count()/1000.0;
    return duration;
}
int main() {

    // auto t1 = chrono::high_resolution_clock::now();
    // int n = 10000;
    // MatrixXf a = MatrixXf::Random(n, n);
    // MatrixXf b = MatrixXf::Random(n, n);
    // MatrixXf c = MatrixXf::Random(n, n);
    // a = a*1;
    // b = b*1;
    // c = c*1;

    // auto t2 = chrono::high_resolution_clock::now();
    // c = a*b;
    // auto t3 = chrono::high_resolution_clock::now();
    // auto durationAll = chrono::duration_cast<chrono::microseconds>(t2-t1).count()/1000.0;
    // auto duration = chrono::duration_cast<chrono::microseconds>(t3-t2).count()/1000.0;
    // cout << "n = " << n << "\n";
    // cout << "Allocation time:\n\t";
    // cout << durationAll << " ms\n";
    // cout << "Product time:\n\t";
    // cout << duration << "ms\n";

    vector<int> sizes;
    vector<double> times;
    for (int i = 0; i < 100; ++i) {
        sizes.push_back(100 + i*10);
        times.push_back(timeProduct(100+i*10));
    }
    for (auto t : times)
        cout << t << " ";
    cout << endl;
}

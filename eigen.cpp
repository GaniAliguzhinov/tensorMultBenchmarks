#include <iostream>
#include <eigen3/Eigen/Dense>
#include <chrono>

using namespace Eigen;
using namespace std;

int main() {
    size_t n = 1000;
    MatrixXf a = MatrixXf::Random(n, n);
    MatrixXf b = MatrixXf::Random(n, n);
    MatrixXf c = MatrixXf::Random(n, n);
    a = a*1;
    b = b*1;
    c = c*1;

    auto t1 = chrono::high_resolution_clock::now();
    c = a*b;
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << "Elapsed:\t" << duration/1000000.0 << endl;

}


/*****************************************************************************
 * reduce.cpp     Blitz++ array reduction example
 *
 * This example illustrates the array reduction functions provided by
 * Blitz++.  These functions reduce an N dimensional array (or array
 * expression) to an N-1 dimensional array expression by summing, taking
 * the mean, etc.  These array reductions are currently provided: sum,
 * mean, min, max, minIndex, maxIndex, product, count, any and all.
 *****************************************************************************/

#include <blitz/array.h>
#include <iostream>
#include <blitz/timer.h>
#include <random/uniform.h>
using namespace blitz;
using namespace ranlib;

int main() {

    int n = 1000;
    Array<float, 2> A(n,n), B(n,n), C(n,n);
    Uniform<float> rand;
    rand.seed(23);
    A = rand.random();
    B = rand.random();

    firstIndex i;
    secondIndex j;
    thirdIndex k;

    Timer timer;
    timer.start();

    C = sum(A(i, k) * B(k, j), k);

    timer.stop();
    double seconds = timer.elapsed();

    std::cout << "seconds = " << seconds << std::endl;
}

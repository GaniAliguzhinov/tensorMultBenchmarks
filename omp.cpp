#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <omp.h>

using namespace std;

int main();


int main() {
    size_t n = 1000;

    float wtime;
    wtime = omp_get_wtime();
    float **a = new float *[n];
    float **b = new float *[n];
    float **c = new float *[n];

    for (size_t i = 0; i < n; ++i) {
        a[i] = new float[n];
        b[i] = new float[n];
        c[i] = new float[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
            c[i][j] = rand();
        }
    }

    int i, j, k;
    int thread_num;

    cout << "Allocated in \t" << omp_get_wtime() - wtime << " seconds\n";
    thread_num = omp_get_max_threads();

    cout << "threads:\t" << thread_num << "\n";
    wtime = omp_get_wtime();

    # pragma omp for
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            c[i][j] = 0.0;
            for (k = 0; k < n; ++k) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    wtime = omp_get_wtime() - wtime;
    cout << "Elapsed:\t" << wtime << "\n";
    return 0;
}


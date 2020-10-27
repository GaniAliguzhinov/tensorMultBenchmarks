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


    float *a = (float*)malloc(n*n*sizeof(float));
    float *b = (float*)malloc(n*n*sizeof(float));
    float *c = (float*)malloc(n*n*sizeof(float));

    cout << "n = " << n << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i*n+j] = rand();
            b[i*n+j] = rand();
            c[i*n+j] = 0.0;
        }
    }

    int i, j, k;
    int thread_num;

    cout << "Allocation time:\n\t" << 1000.0*(omp_get_wtime() - wtime) << " ms\n";
    thread_num = omp_get_max_threads();

    wtime = omp_get_wtime();

    # pragma omp for
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            c[i*n+j] = 0.0;
            for (k = 0; k < n; ++k) {
                c[i*n+j] = c[i*n+j] + a[i*n+k] * b[j*n+k];
            }
        }
    }
    wtime = omp_get_wtime() - wtime;
    cout << "Product time:\n\t" << 1000.0*wtime << " ms\n";
    return 0;
}

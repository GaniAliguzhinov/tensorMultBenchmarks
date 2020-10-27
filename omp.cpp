#include <iostream>
#include <cmath>
#include <ctime>
#include <omp.h>

using namespace std;

int main();


int main() {
    size_t n = 400;
    double a[n][n];
    double b[n][n];
    double c[n][n];
    int i, j, k;
    int thread_num;
    double wtime;


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


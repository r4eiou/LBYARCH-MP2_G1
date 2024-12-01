#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Declare the external assembly function
extern void sdotproduct(int n, double *vector1, double *vector2, double *result);

// C function to calculate dot product
double cdotproduct(int n, double *vector1, double *vector2) {
    double result = 0.0;
    int i; 
    for (i = 0; i < n; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

int main() {
    size_t sizes[] = {1 << 20, 1 << 24, 1 << 28}; // 2^20, 2^24, 2^28 
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int s, i, run;

    for (s = 0; s < num_sizes; ++s) {
        size_t n = sizes[s];
        printf("\nTesting vector size: %zu\n", n);

        // Allocate memory for the vectors
        double *vector1 = (double *)malloc(n * sizeof(double));
        double *vector2 = (double *)malloc(n * sizeof(double));
        double *result = (double *)malloc(n * sizeof(double));

        // Initialize vectors with random values
        for (i = 0; i < n; i++) {
            vector1[i] = (double)rand() / RAND_MAX;
            vector2[i] = (double)rand() / RAND_MAX;
        }

        // Time variables
        double asm_total_time = 0.0;
        double c_total_time = 0.0;
        double asm_time = 0.0;
        double c_time = 0.0;
        double sdot = 0.0;
        double c_sdot = 0.0;

        // Loop each kernel 20 times
        for (run = 0; run < 20; run++) {
            printf("Run %d: \n", run + 1);

            // Time the C execution
            clock_t start = clock();
            c_sdot = cdotproduct(n, vector1, vector2);
            clock_t end = clock();
            c_time = (double)(end - start) / CLOCKS_PER_SEC;
            c_total_time += c_time;
            printf("Dot product (C): \t%f\t ||\t", c_sdot);
            printf("Time (C): \t%f seconds\n", c_time);

            // Time the x86-64 execution
            start = clock();
            sdotproduct(n, vector1, vector2, result);
            end = clock();
            asm_time = (double)(end - start) / CLOCKS_PER_SEC;
            asm_total_time += asm_time;

            // Sum result array 
            sdot = 0.0;
            for (i = 0; i < n; i++) {
                sdot += result[i];
            }

            printf("Dot product (x86-64): \t%f\t ||\t", sdot);
            printf("Time (x86-64): \t%f seconds\n", asm_time);

            // Check correctness
            if (fabs(sdot - c_sdot) < 1e-5) {
                printf("The x86-64 kernel output is correct.\n");
            } else {
                printf("The x86-64 kernel output is incorrect.\n");
            }
        }

        // Compute averages
        double asm_avg_time = asm_total_time / 20;
        double c_avg_time = c_total_time / 20;

        // Print average results
        printf("\n");
        printf("Average time (x86-64):\t%f seconds\n", asm_avg_time);
        printf("Average time (C):\t%f seconds\n", c_avg_time);

        // Free memory
        free(vector1);
        free(vector2);
        free(result);
    }

    return 0;
}


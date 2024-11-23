#include <stdio.h>
#include <stdlib.h>

// Declare the external assembly function
extern void sdotproduct(int n, double *vector1, double *vector2, double *result);

// C function to calculate dot product (for sanity check)
double cdotproduct(int n, double *vector1, double *vector2) {
    double result;
	int i;
    for (i = 0; i < n; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

int main()
{
	// Variable declarations
	int n;
	int i;
	double sdot;
		// Allocate memory for the vectors
	double *vector1 = (double *)malloc(n * sizeof(double));
    double *vector2 = (double *)malloc(n * sizeof(double));
    double *result = (double *)malloc(n * sizeof(double));
	
    // Read the size of the vectors
    printf("Enter the size of the vectors: ");
    scanf("%d", &n);

    // Read vector1
    printf("Enter elements of vector1: ");
    for (i = 0; i < n; i++) {
        scanf("%lf", &vector1[i]);
    }

    // Read vector2
    printf("Enter elements of vector2: ");
    for (i = 0; i < n; i++) {
        scanf("%lf", &vector2[i]);
    }

    // Call the assembly function
    sdotproduct(n, vector1, vector2, result);

    // Print the result
    printf("Resultant vector: ");
    for (i = 0; i < n; i++) {
        printf("%lf ", result[i]);
    }
    printf("\n\n");
	
	// Compute the sum of all elements in the result vector (asm code)
    for (i = 0; i < n; i++) {
        sdot += result[i];
    }
	
	// Compute the sum of all elements in the result vector (c code)
	double c_sdot = cdotproduct(n, vector1, vector2);
	
	// Print the result/s
    printf("Dot product-x86-64:\t%lf\n", sdot);
	printf("Dot product-C:\t\t%lf\n", c_sdot);
	
	// Check correctness
    if (sdot == c_sdot) {
        printf("\nThe x86-64 kernel output is correct.\n");
    } else {
        printf("\nThe x86-64 kernel output is incorrect.\n");
    }

    return 0;
}

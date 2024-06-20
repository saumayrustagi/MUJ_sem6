#include <iostream>
#include <omp.h>

int main() {
    const int SIZE = 3;
    int matrixA[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrixB[SIZE][SIZE] = {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}};
    int resultMatrix[SIZE][SIZE] = {0};

#pragma omp parallel for
for (int i = 0; i < SIZE; ++i) {
	for (int j = 0; j < SIZE; ++j) {
		for (int k = 0; k < SIZE; ++k) {
			resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
		}
	}
}

    std::cout << "Resulting Matrix:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << resultMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

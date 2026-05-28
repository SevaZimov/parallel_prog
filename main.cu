#include <iostream>
#include <vector>
#include <fstream>
#include <cuda_runtime.h>

using namespace std;

__global__ void matrixMulKernel(
    double* A,
    double* B,
    double* C,
    int n
) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {

        double sum = 0.0;

        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }

        C[row * n + col] = sum;
    }
}

void readMatrix(
    const string& filename,
    vector<double>& matrix,
    int& n
) {
    ifstream file(filename);

    file >> n;

    matrix.resize(n * n);

    for (int i = 0; i < n * n; i++) {
        file >> matrix[i];
    }
}

int main() {

    int n1, n2;

    vector<double> A;
    vector<double> B;

    readMatrix("matrixA.txt", A, n1);
    readMatrix("matrixB.txt", B, n2);

    int n = n1;

    vector<double> C(n * n);

    double *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, n * n * sizeof(double));
    cudaMalloc(&d_B, n * n * sizeof(double));
    cudaMalloc(&d_C, n * n * sizeof(double));

    cudaMemcpy(
        d_A,
        A.data(),
        n * n * sizeof(double),
        cudaMemcpyHostToDevice
    );

    cudaMemcpy(
        d_B,
        B.data(),
        n * n * sizeof(double),
        cudaMemcpyHostToDevice
    );

    dim3 blockSize(16, 16);

    dim3 gridSize(
        (n + blockSize.x - 1) / blockSize.x,
        (n + blockSize.y - 1) / blockSize.y
    );

    cudaEvent_t start, stop;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    matrixMulKernel<<<gridSize, blockSize>>>(
        d_A,
        d_B,
        d_C,
        n
    );

    cudaEventRecord(stop);

    cudaEventSynchronize(stop);

    float milliseconds = 0;

    cudaEventElapsedTime(
        &milliseconds,
        start,
        stop
    );

    cudaMemcpy(
        C.data(),
        d_C,
        n * n * sizeof(double),
        cudaMemcpyDeviceToHost
    );

    cout << "CUDA execution time: "
         << milliseconds
         << " ms"
         << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
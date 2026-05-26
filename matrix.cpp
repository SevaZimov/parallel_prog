#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

vector<vector<double>> readMatrix(const string& filename, int& n) {
    ifstream file(filename);

    file >> n;

    vector<vector<double>> matrix(n, vector<double>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> matrix[i][j];

    return matrix;
}

void writeMatrix(const string& filename,
                 const vector<vector<double>>& matrix,
                 int n) {
    ofstream file(filename);

    file << n << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
}

vector<vector<double>> multiplyParallel(
    const vector<vector<double>>& A,
    const vector<vector<double>>& B,
    int n,
    int threads
) {
    vector<vector<double>> C(n, vector<double>(n, 0));

    omp_set_num_threads(threads);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    int n1, n2;

    auto A = readMatrix("matrixA.txt", n1);
    auto B = readMatrix("matrixB.txt", n2);

    if (n1 != n2) {
        cout << "Matrix sizes do not match!" << endl;
        return 1;
    }

    int n = n1;

    int threadCounts[] = {1, 2, 4, 8};

    long long operations = 2LL * n * n * n;

    for (int threads : threadCounts) {

        auto start = chrono::high_resolution_clock::now();

        auto C = multiplyParallel(A, B, n, threads);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> duration = end - start;

        cout << "Threads: " << threads << endl;

        cout << "Execution time: "
             << duration.count()
             << " ms" << endl;

        cout << "Count of operation = "
             << operations
             << endl;

        cout << "-------------------------" << endl;

        if (threads == 1) {
            writeMatrix("result.txt", C, n);
        }
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

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

vector<vector<double>> multiply(const vector<vector<double>>& A,
                                const vector<vector<double>>& B,
                                int n) {
    vector<vector<double>> C(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

void writeMatrix(const string& filename,
                 const vector<vector<double>>& M,
                 int n) {
    ofstream file(filename);

    file << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            file << M[i][j] << " ";
        file << endl;
    }
}

int main() {
    int n1, n2;

    auto A = readMatrix("matrixA.txt", n1);
    auto B = readMatrix("matrixB.txt", n2);

    if (n1 != n2) {
        cout << "Matrices must be same size!" << endl;
        return 1;
    }

    int n = n1;

    auto start = chrono::high_resolution_clock::now();

    auto C = multiply(A, B, n);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    writeMatrix("result.txt", C, n);

    cout << "Time: " << elapsed.count() << " seconds" << endl;
    cout << "Operations (N^3): " << n * n * n << endl;

    return 0;
}
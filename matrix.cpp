#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>

using namespace std;

void readMatrix(const string& filename,
                vector<double>& matrix,
                int& n) {

    ifstream file(filename);

    file >> n;

    matrix.resize(n * n);

    for (int i = 0; i < n * n; i++) {
        file >> matrix[i];
    }
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;

    vector<double> A;
    vector<double> B;
    vector<double> C;

    if (rank == 0) {

        int temp;

        readMatrix("matrixA.txt", A, n);
        readMatrix("matrixB.txt", B, temp);

        C.resize(n * n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        B.resize(n * n);
    }

    MPI_Bcast(B.data(),
              n * n,
              MPI_DOUBLE,
              0,
              MPI_COMM_WORLD);

    int rowsPerProcess = n / size;

    vector<double> localA(rowsPerProcess * n);
    vector<double> localC(rowsPerProcess * n, 0);

    MPI_Scatter(A.data(),
                rowsPerProcess * n,
                MPI_DOUBLE,
                localA.data(),
                rowsPerProcess * n,
                MPI_DOUBLE,
                0,
                MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    double start = MPI_Wtime();

    for (int i = 0; i < rowsPerProcess; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {

                localC[i * n + j] +=
                    localA[i * n + k] *
                    B[k * n + j];
            }
        }
    }

    double end = MPI_Wtime();

    MPI_Gather(localC.data(),
               rowsPerProcess * n,
               MPI_DOUBLE,
               C.data(),
               rowsPerProcess * n,
               MPI_DOUBLE,
               0,
               MPI_COMM_WORLD);

    if (rank == 0) {

        double duration =
            (end - start) * 1000.0;

        long long operations =
            2LL * n * n * n;

        cout << "Processes: "
             << size
             << endl;

        cout << "Execution time: "
             << duration
             << " ms"
             << endl;

        cout << "Count of operation = "
             << operations
             << endl;

        ifstream checkFile("results.csv");

        bool fileExists = checkFile.good();

        checkFile.close();

        ofstream csv("results.csv", ios::app);

        if (!fileExists) {
            csv << "MatrixSize,Processes,TimeMs,Operations\n";
        }

        csv << n << ","
            << size << ","
            << duration << ","
            << operations
            << endl;

        csv.close();
    }

    MPI_Finalize();

    return 0;
}
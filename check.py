import numpy as np

def read_matrix(filename):
    with open(filename) as f:
        n = int(f.readline())
        data = [list(map(float, f.readline().split())) for _ in range(n)]
    return np.array(data)

A = read_matrix("matrixA.txt")
B = read_matrix("matrixB.txt")
C_cpp = read_matrix("result.txt")

C_py = np.dot(A, B)

if np.allclose(C_cpp, C_py):
    print("Verification: OK")
else:
    print("Verification: FAILED")
    print("Python result:\n", C_py)
    print("C++ result:\n", C_cpp)
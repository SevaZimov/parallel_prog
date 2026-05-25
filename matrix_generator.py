import random

SIZE = 750

def generate_matrix(filename, size):
    with open(filename, 'w') as file:
        file.write(f"{size}\n")

        for _ in range(size):
            row = [str(random.randint(0, 9)) for _ in range(size)]
            file.write(" ".join(row) + "\n")

generate_matrix("matrixA.txt", SIZE)
generate_matrix("matrixB.txt", SIZE)

print("Matrices generated successfully.")
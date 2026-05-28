import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("cuda_results.csv")

plt.figure(figsize=(12, 7))

block_sizes = data["BlockSize"].unique()

for block in block_sizes:

    subset = data[data["BlockSize"] == block]

    plt.plot(
        subset["MatrixSize"],
        subset["TimeMs"],
        marker='o',
        label=block
    )

plt.xlabel("Размер матриц")
plt.ylabel("Время выполнения, мс")

plt.title("CUDA: зависимость времени выполнения от размера матриц")

plt.grid(True, linestyle='--', alpha=0.5)

plt.legend(title="Размер блока")

plt.tight_layout()

plt.savefig("cuda_graph.png", dpi=300)

plt.show()
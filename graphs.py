import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")

plt.figure(figsize=(12, 7))

processes = sorted(data["Processes"].unique())

for p in processes:

    subset = data[data["Processes"] == p]

    plt.plot(
        subset["MatrixSize"],
        subset["TimeMs"],
        marker='o',
        label=f'{p} процесс(ов)'
    )

plt.yscale('log')

plt.xlabel('Размер матриц n')
plt.ylabel('Время, ms')

plt.grid(True, which='both', linestyle='--', alpha=0.5)

plt.legend()

plt.tight_layout()

plt.savefig("graph.png", dpi=300)

plt.show()
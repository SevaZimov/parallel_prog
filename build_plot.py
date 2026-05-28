import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(
    "results.csv",
    header=None,
    names=[
        "MatrixSize",
        "Processes",
        "TimeMs",
        "Operations"
    ]
)

plt.figure(figsize=(12, 7))

processes = sorted(
    data["Processes"].unique()
)

for p in processes:

    subset = data[
        data["Processes"] == p
    ]

    plt.plot(
        subset["MatrixSize"],
        subset["TimeMs"] / 1000,
        marker='o',
        label=f'{p} процесс(ов)'
    )

plt.xlabel("Размер матриц")
plt.ylabel("Время выполнения, с")

plt.title(
    "MPI: зависимость времени выполнения "
    "от размера матриц"
)

plt.grid(
    True,
    linestyle='--',
    alpha=0.5
)

plt.legend()

plt.tight_layout()

plt.savefig(
    "mpi_graph.png",
    dpi=300
)

plt.show()
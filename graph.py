import matplotlib.pyplot as plt

matrix_sizes = [200, 400, 800, 1200, 1600, 2000]

times_1 =  [53.8726, 402.875, 5225.16, 26639.8, 24563.6, 143307]
times_2 =  [33.3801, 273.945, 2301.75, 12084.1, 11574.6, 60958.7]
times_4 =  [42.3895, 214.779, 2279.24, 9067.27, 8434.87, 49032.4]
times_8 =  [42.7121, 207.575, 2013.09, 7812.64, 7590.5, 45652.1]

plt.figure(figsize=(12, 7))

plt.plot(matrix_sizes, times_1, marker='o', label='1 поток(ов)')
plt.plot(matrix_sizes, times_2, marker='o', label='2 поток(ов)')
plt.plot(matrix_sizes, times_4, marker='o', label='4 поток(ов)')
plt.plot(matrix_sizes, times_8, marker='o', label='8 поток(ов)')


plt.yscale('log')

plt.xlabel('Размер матриц n')
plt.ylabel('Время, ms')

plt.grid(True, which='both', linestyle='--', alpha=0.5)

plt.legend()

plt.tight_layout()

plt.show()
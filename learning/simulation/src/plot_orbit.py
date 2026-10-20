import numpy as np
import matplotlib.pyplot as plt

points_matrix = np.loadtxt("points.csv", delimiter=",")

x_earth_list = []
y_earth_list = []
x_moon_list = []
y_moon_list = []

for i in range(len(points_matrix)):
    if i % 2 == 0:
        x_earth_list.append(points_matrix[i, 0])
        y_earth_list.append(points_matrix[i, 1])
    else:
        x_moon_list.append(points_matrix[i, 0])
        y_moon_list.append(points_matrix[i, 1])

plt.plot(x_earth_list, y_earth_list, label="Earth")
plt.plot(x_moon_list, y_moon_list, label="Moon")
plt.axis("equal")
plt.legend()
plt.savefig("orbita.png")

import numpy as np
import matplotlib.pyplot as plt

points_matrix = np.loadtxt("points.csv", delimiter=",")

x_earth_list = []
y_earth_list = []
x_moon_list = []
y_moon_list = []

for i in range(len(points_matrix)):
    if i % 2 == 0:
        x_earth_list.append(points_matrix[i, 0] / 1e3)
        y_earth_list.append(points_matrix[i, 1] / 1e3)
    else:
        x_moon_list.append(points_matrix[i, 0] / 1e3)
        y_moon_list.append(points_matrix[i, 1] / 1e3)

plt.figure(figsize=(10, 10))
plt.plot(x_earth_list, y_earth_list, label="Earth")
plt.plot(x_moon_list, y_moon_list, label="Moon")
plt.gca().set_aspect("equal")
plt.xlabel("x (km)")
plt.ylabel("y (km)")
plt.legend()
plt.savefig("orbita.png", dpi=150)

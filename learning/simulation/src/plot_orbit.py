import numpy as np
import matplotlib.pyplot as plt

AU = 149597870700 # One astronomical unit in meters.
points_matrix = np.loadtxt("points.csv", delimiter=",") / AU
nr_bodies = points_matrix.shape[1] // 2

plt.figure(figsize=(10, 10))

names = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter"]

for i in range(nr_bodies):
    body_x_coordinates_arr = points_matrix[:, 2 * i]
    body_y_coordinates_arr = points_matrix[:, 2 * i + 1]
    plt.plot(body_x_coordinates_arr, body_y_coordinates_arr, label=names[i])

plt.gca().set_aspect("equal")
plt.xlabel("x (AU)")
plt.ylabel("y (AU)")
plt.legend()
plt.savefig("orbit.png", dpi=150)

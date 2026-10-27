import numpy as np
import matplotlib.pyplot as plt

points_matrix = np.loadtxt("points.csv", delimiter=",") / 1e3 # Convert to km.

nr_bodies = points_matrix.shape[1] // 2

plt.figure(figsize=(10, 10))

for i in range(nr_bodies):
    body_x_coordinates_arr = points_matrix[:, 2 * i]
    body_y_coordinates_arr = points_matrix[:, 2 * i + 1]
    plt.plot(body_x_coordinates_arr, body_y_coordinates_arr, label=f"Body {i}")

plt.gca().set_aspect("equal")
plt.xlabel("x (km)")
plt.ylabel("y (km)")
plt.legend()
plt.savefig("orbita.png", dpi=150)

import numpy as np
import matplotlib.pyplot as plt

points_matrix = np.loadtxt("points.csv", delimiter=",") / 1e3 # Convert to km.

x_earth_list = points_matrix[:, 0]
y_earth_list = points_matrix[:, 1]
x_moon_list = points_matrix[:, 2]
y_moon_list = points_matrix[:, 3]

plt.figure(figsize=(10, 10))
plt.plot(x_earth_list, y_earth_list, label="Earth")
plt.plot(x_moon_list, y_moon_list, label="Moon")
plt.gca().set_aspect("equal")
plt.xlabel("x (km)")
plt.ylabel("y (km)")
plt.legend()
plt.savefig("orbita.png", dpi=150)

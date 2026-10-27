orbit.png: sim plot_orbit.py
	./sim && python3 plot_orbit.py && xdg-open orbit.png

sim: main.c planets.h planets.c csv_handler.h csv_handler.c
	gcc -Wall -Wextra -O3 main.c planets.c csv_handler.c -o sim -lm

clean:
	rm -f orbit.png points.csv orbit
	
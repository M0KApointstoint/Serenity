orbita.png: points.csv plot_orbit.py
	python3 plot_orbit.py && xdg-open orbita.png

points.csv: orbita
	./orbita | grep '(x, y)' | cut -d " " -f 5,6 | tr "()" " " | tr -d " " > points.csv

orbita: orbita.c
	gcc -Wall -Wextra -O3 orbita.c -o orbita -lm

clean:
	rm orbita.png points.csv orbita


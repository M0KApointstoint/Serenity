orbita.png: orbita plot_orbit.py
	./orbita && python3 plot_orbit.py && xdg-open orbita.png

orbita: orbita.c planets.h
	gcc -Wall -Wextra -O3 orbita.c planets.h -o orbita -lm

clean:
	rm -f orbita.png points.csv orbita
	
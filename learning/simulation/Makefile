CC = gcc
CFLAGS = -Wall -Wextra -O3

IMAGE = orbit.png
EXEC = sim

BUILD_DIR = ./build
SRC_DIR = ./src

$(IMAGE): $(BUILD_DIR)/$(EXEC) $(SRC_DIR)/plot_orbit.py
	$(BUILD_DIR)/$(EXEC) && python3 $(SRC_DIR)/plot_orbit.py && xdg-open $(BUILD_DIR)/$(IMAGE)

$(BUILD_DIR)/$(EXEC): $(SRC_DIR)
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/*.c -o $(BUILD_DIR)/$(EXEC) -lm

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

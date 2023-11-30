# Variables
BOARD := esp32:esp32:heltec_wifi_kit_32_V3
PORT := /dev/cu.usbserial-0001
PROJECT_DIR := /Users/c2k/ArduinoProjects/LEDARMv2/main
PROJECT_FILE := $(PROJECT_DIR)/main.ino
BUILD_DIR := $(PROJECT_DIR)/build

# Compilation settings
COMPILE_FLAGS := --fqbn $(BOARD) --verbose

# Default target
all: compile upload

# Compile
compile:
	arduino-cli compile $(COMPILE_FLAGS) $(PROJECT_FILE)

# Upload
upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(PROJECT_DIR) --verbose

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all compile upload clean

# Use -j to run multiple jobs in parallel (e.g., -j4 for 4 parallel jobs)
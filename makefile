include .env


# Variables
BOARD := esp32:esp32:heltec_wifi_kit_32_V3
PORT := /dev/cu.usbserial-0001
PROJECT_DIR := /Users/c2k/ArduinoProjects/Flux/main
CONFIG_DIR := $(PROJECT_DIR)/src/config
PROJECT_FILE := $(PROJECT_DIR)/main.ino
BUILD_DIR := $(PROJECT_DIR)/build

# Compilation settings
COMPILE_FLAGS := --fqbn $(BOARD) --verbose

# Default target
all: compile upload

# Compile
compile: copy
	arduino-cli compile $(COMPILE_FLAGS) $(PROJECT_FILE)

# Upload
upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(PROJECT_DIR) --verbose

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Monitor
monitor:
	arduino-cli monitor -p $(PORT)

# Copy configuration and main files based on CONFIG_TYPE
copy:
ifeq ($(PROJ), HOUSE)
	cp $(CONFIG_DIR)/houseConfig.h $(CONFIG_DIR)/config.h
	cp $(PROJECT_DIR)/houseMain.h $(PROJECT_DIR)/main.ino
else ifeq ($(PROJ), GAUNTLET)
	cp $(CONFIG_DIR)/gauntletConfig.h $(CONFIG_DIR)/config.h
	cp $(PROJECT_DIR)/gauntletMain.h $(PROJECT_DIR)/main.ino
else
	$(error PROJ is not set to HOUSE or GAUNTLET)
endif

.PHONY: all compile upload clean copy monitor pre-compile post-compile

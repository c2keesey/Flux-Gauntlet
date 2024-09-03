include .env

# Variables
BOARD := esp32:esp32:heltec_wifi_kit_32_V3
PORT := /dev/cu.usbserial-0001
CONFIG_DIR := $(DIR)/src/config
PROJECT_FILE := $(DIR)/main.ino
BUILD_DIR := $(DIR)/build

# Compilation settings
COMPILE_FLAGS := --fqbn $(BOARD) --verbose

# Default target
all: compile upload

# Compile
compile: copy
	arduino-cli compile $(COMPILE_FLAGS) $(PROJECT_FILE)

# Upload
upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(DIR) --verbose

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Monitor
monitor:
	arduino-cli monitor -p $(PORT)

# Copy configuration and main files based on PROJ
copy:
ifeq ($(PROJ), HOUSE)
	cp $(CONFIG_DIR)/h_Config.h $(CONFIG_DIR)/config.h
	cp $(DIR)/h_Main.h $(DIR)/main.ino
else ifeq ($(PROJ), GAUNTLET)
	cp $(CONFIG_DIR)/g_Config.h $(CONFIG_DIR)/config.h
	cp $(DIR)/g_Main.h $(DIR)/main.ino
else
	$(error PROJ is not set to HOUSE or GAUNTLET)
endif
ifeq ($(DEV), true)
	cp $(DIR)/test_Main.h $(DIR)/main.ino
endif

# New target for compile, upload, and monitor
am: all monitor

.PHONY: all compile upload clean copy monitor am
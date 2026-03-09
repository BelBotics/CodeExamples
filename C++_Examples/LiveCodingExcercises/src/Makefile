# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

# Output binary and object files
BUILD_DIR := ../build
TARGET := $(BUILD_DIR)/exampleProject
OBJ := $(BUILD_DIR)/main.o $(BUILD_DIR)/display.o $(BUILD_DIR)/excercise.o

# Linker libraries
LDLIBS := -lncurses

# Phony targets (not real files)
.PHONY: all clean

# Default target builds the executable
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDLIBS)

# Compile and keep intermediate files (.i/.ii/.s)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -save-temps=obj -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/display.o: display.cpp display.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -save-temps=obj -c display.cpp -o $(BUILD_DIR)/display.o

$(BUILD_DIR)/excercise.o: excercise.cpp excercise.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -save-temps=obj -c excercise.cpp -o $(BUILD_DIR)/excercise.o

# Remove build artifacts and intermediate files
clean:
	rm -rf $(BUILD_DIR)

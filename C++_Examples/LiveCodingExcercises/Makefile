# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

# Output binary and object files
TARGET := exampleProject
OBJ := main.o

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
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -save-temps=obj -c main.cpp -o main.o

# Remove build artifacts and intermediate files
clean:
	rm -f $(TARGET) $(OBJ) *.i *.ii *.s

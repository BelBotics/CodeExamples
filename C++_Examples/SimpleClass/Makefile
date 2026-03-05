CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET := simpleClass
SRC := simpleClass.cpp

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := virtual_func
SRC := virtual_func.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

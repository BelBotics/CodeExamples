include makefiles/common.mk

.PHONY: all clean run

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

run: all
	./$(BIN_DIR)/$(TARGET)

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

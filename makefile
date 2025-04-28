CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
BUILD_DIR := build
SRC_DIR := .
MKDIR_P := mkdir -p

# Исходные файлы
MAIN_SRCS := main.cpp interface.cpp errors.cpp
TEST_SRCS := tests.cpp interface.cpp errors.cpp

# Создаем папку build
$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

.PHONY: all clean run test

all: run test

clean:
	rm -rf $(BUILD_DIR)

# Правило для компиляции
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Основная программа
RUN_OBJ := $(addprefix $(BUILD_DIR)/,$(MAIN_SRCS:.cpp=.o))
RUN_TARGET := $(BUILD_DIR)/t2.exe

run: $(RUN_TARGET)

$(RUN_TARGET): $(RUN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Тестовая программа
TEST_OBJ := $(addprefix $(BUILD_DIR)/,$(TEST_SRCS:.cpp=.o))
TEST_TARGET := $(BUILD_DIR)/t1.exe

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
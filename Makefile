# -----------------------------------------
# Password Strength Analyzer - Makefile
# -----------------------------------------

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Source and build files
SRC := src/main.cpp src/PasswordAnalyzer.cpp
OBJ := $(SRC:.cpp=.o)

# Output executable name
TARGET := PasswordAnalyzer

# Default rule
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Compile each .cpp into a .o file
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Remove build files
clean:
	rm -f $(OBJ) $(TARGET)

# Remove everything including editor temp files
clean-all:
	rm -f $(OBJ) $(TARGET) *.tmp *.log

.PHONY: all clean clean-all run

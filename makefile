# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

# Target executable
TARGET = task-cli

# Source files
SRC = main.cpp

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule to remove compiled binary
clean:
	rm -f $(TARGET)


# Omer Farkash
# 211466362

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

# Executable name
TARGET = ex3.out

# Source files
SRCS = main.cpp Bounded_Buffer.cpp Unbounded_Buffer.cpp Co_Editor.cpp Dispatcher.cpp Producer.cpp Screen_Manager.cpp

# Object files (same as source files, but with .o extension)
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
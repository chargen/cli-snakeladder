# Flags
CPP_FLAGS := -O0 -g -Wall -Wextra -pedantic -Werror -std=c++11

# Commands
RM := rm -rf
MKDIR_P := mkdir -p

# Paths
CURR_DIR := $(notdir $(shell pwd))

# Files to compile
SRC_FILES := $(wildcard ./*.cpp)
OBJ := $(SRC_FILES:%.cpp=%.o)


# Target name
EXEC := $(CURR_DIR)

# Build .o first
%.o: %.cpp
	$(CXX) $(CPP_FLAGS) -o $@ -c $<

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CPP_FLAGS) -o $@ $^

# Clean executable and object files
clean:
	$(RM) $(wildcard ./*.o) $(EXEC)

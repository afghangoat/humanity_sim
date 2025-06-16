CXX = g++
CXXFLAGS = -O1 -std=c++17 -Wall -Wextra -MMD -MP -g -ggdb -DCPORTA -D_JPORTA_STAT
ifeq ($(W_COVERAGE),1)
	CXXFLAGS += --coverage -fprofile-arcs -ftest-coverage
endif

LDFLAGS =

ifeq ($(W_ASAN),1)
	CXXFLAGS+= -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-inline -fno-sanitize-recover=address
	LDFLAGS += -fsanitize=address
endif

TARGET = main

SRC = $(wildcard src/*.cpp) $(wildcard src/terrain_tiles/*.cpp) $(wildcard src/creatures/*.cpp) $(wildcard src/ui/*.cpp) $(wildcard src/creatures/humans/*.cpp) $(wildcard src/creatures/hostiles/*.cpp) $(wildcard src/world_object/*.cpp)

ifeq ($(W_MEMTRACE),1)
	CXXFLAGS += -DMEMTRACE
	SRC += $(wildcard src/external/*.cpp)
endif

ifeq ($(FAKE_SFML),1)
    SRC += $(wildcard src/fake_sfml/*.cpp)
    CXXFLAGS += -DFAKE_SFML
else
	LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d) # Dependency files

all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEP)

clean:
	rm -f $(TARGET) $(OBJ) $(DEP) *.gcno *.gcda *.gcov

cleancoverage:
	find . -type f \( -name '*.o' -o -name '*.d' -o -name '*.gcno' -o -name '*.gcda' -o -name '*.gcov' \) -delete

#make FAKE_SFML=1
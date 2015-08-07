#### PROJECT SETTINGS ####
# Default build type
TYPE = debug

# Defaults for variables
PROGRAM_NAME = gaff
CXX = g++

# Variables based on build type
COMPILE_FLAGS_EXTRA = -Wno-write-strings -Wno-unused-parameter -g

# Libraries
LIBS_EXTERN = libpng zlib
#### END PROJECT SETTINGS ####
#
#
#
#
#
#
#
#

NAME = build/$(TYPE)/$(PROGRAM_NAME)
LIBS = $(shell pkg-config --libs --cflags $(LIBS_EXTERN))
DEFS = 
COMPILE_FLAGS = -std=c++14 -Wall -Wextra $(COMPILE_FLAGS_EXTRA) $(DEFS)
INCLUDES = -I include -I libs/include
MAKEFLAGS = "-j $(shell grep -c ^processor /proc/cpuinfo)"

SOURCES = $(shell find src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
SOURCES_LIBS = $(shell find libs/src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

HEADERS = $(shell find include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
HEADERS_LIBS = $(shell find libs/include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

OBJECTS = $(subst .cpp,.o,$(subst src/,obj/, $(SOURCES)))
OBJECTS_LIBS = $(subst .cpp,.o,$(subst /src/,/obj/, $(SOURCES_LIBS)))

all: include/Standard.h.gch $(NAME)

$(NAME): $(OBJECTS_LIBS) $(OBJECTS) 
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -o $@ $^

$(OBJECTS) : obj/%.o : src/%.cpp ./Makefile include/Standard.h.gch
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $<

$(OBJECTS_LIBS) : libs/obj/%.o : libs/src/%.cpp ./Makefile
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $< -Wno-type-limits -Wno-missing-field-initializers

include/Standard.h.gch: $(HEADERS) $(HEADERS_LIBS) ./Makefile
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) include/Standard.h 

run:
	cd sandbox; ./../$(NAME)

debug:
	cd sandbox; gdb ../$(NAME) -ex run -ex bt -ex quit --silent

clean:
	rm -f build/debug/$(PROGRAM_NAME)
	rm -f build/release/$(PROGRAM_NAME)
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_LIBS)

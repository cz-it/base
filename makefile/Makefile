CC        = g++
CPPFLAGS  = -g -Wall
LINKFLAGS = 

OBJ_DIR = .obj

SRC_FILES   := $(wildcard *.cpp )
SRC_FILES 	+= $(wildcard eventdriver/*.cpp)
SRC_FILES 	+= $(wildcard eventdriver/poller/*.cpp)

INC_FILES   := -I./
INC_FILES   := -I../common/
INC_FILES	+= -I./eventdriver/
INC_FILES 	+= -I./eventdriver/poller/
INC_FILES	+= -I./utils

OBJS    := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))



define mkdirs
	mkdir -p $(dir $(1))



endef

server: dirs $(OBJS)
	$(CC) $(LINKFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: %.cpp
	$(call mkdirs,$@)
	$(CC) $(CPPFLAGS) $(INC_FILES)  -c $^ -o $@

dirs: 
	-if (test -d $(OBJ_DIR)) ; then pwd ; else mkdir -p $(OBJ_DIR); fi

clean:
	-rm *.o $(OBJ_DIR)/* -rf
	-rm server

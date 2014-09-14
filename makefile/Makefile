CC        = g++
CPPFLAGS  = -g -Wall
LINKFLAGS = 

OBJ_DIR = .obj
DIST_DIR = dist

SRC_FILES   := $(wildcard *.cpp )
SRC_FILES   += $(wildcard client/*.cpp)
SRC_FILES   += $(wildcard server/utils/*.cpp)

INC_FILES   := -I./
INC_FILES   := -I./common/
INC_FILES   += -I./server/
INC_FILES   += -I./server/utils/
INC_FILES   += -I./client/


OBJS    := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

define mkdirs
        mkdir -p $(dir $(1))
endef


.DEFAULT :　all
all:main
	@echo "[BUILD　MAIN]:"	
	
main: dirs $(OBJS)
        $(CC) $(LINKFLAGS) $(OBJS) -o $@ 

dist: main
        -cp main $(DIST_DIR)

$(OBJ_DIR)/%.o: %.cpp
        $(call mkdirs,$@)
        $(CC) $(CPPFLAGS) $(INC_FILES)  -c $^ -o $@

dirs: 
        -if (test -d $(OBJ_DIR)) ; then pwd ; else mkdir -p $(OBJ_DIR); fi
        -if (test -d $(DIST_DIR)) ; then pwd ; else mkdir -p $(DIST_DIR); fi

.PHONY : clean
clean:
        -rm *.o $(OBJ_DIR)/* -rf
        -rm server -rf
        -rm $(DIST_DIR) -rf

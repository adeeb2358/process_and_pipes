CC                  = g++
SRC_DIR             = ""
OBJ_DIR             = libs
MAIN_EXE            = final
SRC_FILES           = $(wildcard *.cpp)
OBJ_FILES           = $(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ_FILES_WITH_PATH = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
#CCFLAGS             = -Wwrite-strings

all:compile

compile:main
	
main:$(OBJ_FILES)
	@echo "building main" $^
	$(CC) $(CCFLAGS) -o $(MAIN_EXE)/$@ $(OBJ_FILES_WITH_PATH) 

$(OBJ_FILES):
	@echo "compiling" $*.cpp
	$(CC)  $(CCFLAGS) -c  $*.cpp -o $(OBJ_DIR)/$@
	
clean:
	@echo "cleaning program"
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(MAIN_EXE)/*
	$(RM) *.o$
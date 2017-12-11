CC                  = g++
SRC_DIR             = ""
OBJ_DIR             = libs
MAIN_EXE            = final
SRC_FILES           = $(wildcard *.cpp)
OBJ_FILES           = $(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ_FILES_WITH_PATH = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
MKDIR_P             = mkdir 
#CCFLAGS             = -Wwrite-strings

all:compile

compile:directory main

directory:
	$(MKDIR_P) $(OBJ_DIR) $(MAIN_EXE) 

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
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(MAIN_EXE)
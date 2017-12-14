CC                  = g++
SRC_DIR             = ""
OBJ_DIR             = libs
MAIN_EXE            = final
MAIN_EXE_NAME  		= main 
MAIN_EXE_FILE		= $(MAIN_EXE)/main
LOG_FILE  			= output.txt
REDIRECT_COMMAND 	= >>
SRC_FILES           = $(wildcard *.cpp)
OBJ_FILES           = $(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ_FILES_WITH_PATH = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
MKDIR_P             = mkdir -p
MAKE_OBJ_DIR        = if [ ! -d "$(OBJ_DIR)/" ]; then  $(MKDIR_P) $(OBJ_DIR); fi; 
MAKE_MAIN_EXE_DIR   = if [ ! -d "$(MAIN_EXE)/" ]; then $(MKDIR_P) $(MAIN_EXE); fi;
#CCFLAGS             = -Wwrite-strings

all:compile

compile:directory main

run:
	./$(MAIN_EXE_FILE)	

directory:
	$(RM) $(LOG_FILE)
	touch $(LOG_FILE) 
	$(MAKE_MAIN_EXE_DIR)
	$(MAKE_OBJ_DIR) 


main:build_objects build_main
	
build_objects:$(OBJ_FILES)

build_main:
	@echo "building main" $^ $(REDIRECT_COMMAND) $(LOG_FILE)
	$(CC) $(CCFLAGS) -o $(MAIN_EXE_FILE) $(OBJ_FILES_WITH_PATH)  $(REDIRECT_COMMAND) $(LOG_FILE)

$(OBJ_FILES):
	@echo "compiling" $*.cpp >> $(LOG_FILE)
	$(CC)  $(CCFLAGS) -c  $*.cpp -o $(OBJ_DIR)/$@  $(REDIRECT_COMMAND)  $(LOG_FILE)
	
clean:
	@echo "cleaning program"
	$(RM) -rf $(OBJ_FILES_WITH_PATH)
	$(RM) -rf $(MAIN_EXE_FILE)
	$(RM)  $(LOG_FILE)
	
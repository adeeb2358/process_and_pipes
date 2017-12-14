#include "commonHeader.h"
#include "pipes.h"

void pipe_function(){

	/*
		this program is equivalent to
		ls | sort -r
	*/

	int p[2];
	
	/*system call to create the pipe*/
	
	pipe(p);
	if(fork() == 0){
		
		/*
			child connect stdout to pipe
		*/
		
		dup2(p[1],1);
		close(p[0]);
		execlp("ls","ls",NULL);
	}
	
	/*
		parent connect stdin to pipe
	*/
	
	dup2(p[0],0);
	close(p[1]);
	execlp("sort","sort","-r",NULL);
	return;
}

int prompt_and_parse(char** up_stream,char **down_stream){
	char *one_line;
	size_t one_line_size = 100;
	down_stream[0]       = NULL;
	printf("> ");
	if(getline(&one_line,&one_line_size,stdin) == -1){
		return -1;
	}
	int compare_result = strcmp(one_line,"END");
	if(compare_result == 10){
		return -1;
	}
	printf("%s",one_line);
	return 1;
}  

void pipe_shell(){
	int pipe_descriptor[2];
	char *up_stream[20], *down_stream[20];
	while(prompt_and_parse(up_stream,down_stream) > 0){
						
	}
	return;
}

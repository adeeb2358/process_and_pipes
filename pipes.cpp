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
	char *one_line       = NULL;
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
	
	/*
		strtok initially take first piece
		subsequent calls passs NULL and
		get the subsequent data
	*/
	*up_stream++ = strtok(one_line," \t");
	while(*up_stream = strtok(NULL,"\t")){
		if(strcmp(*up_stream," |") == 0){
			*up_stream = NULL;
		}
	}
	
	/*one_piece = strtok(one_line," \t");
	printf("%s\n",one_piece);*/
	/*one_piece = strtok(one_line," \t");
	printf("%s\n",one_piece);
	one_area = strtok(NULL," \t");
	one_area = strtok(NULL," \t");
	one_area = strtok(NULL," \t");
	one_area = strtok(NULL," \t");*/
	
	/**u++  = strtok(one_line,"\t");
	while(*u = strtok(NULL,"\t")){
		if(strcmp(*u,"|") == 0){
			*u = NULL;
			while(*d++ = strtok(NULL,"\t")){
				return 1;
			}
		}
		u++;
	}*/
	
	return 1;
}  

void pipe_shell(){
	int pipe_descriptor[2];
	char *up_stream[20], *down_stream[20];
	while(prompt_and_parse(up_stream,down_stream) > 0){
							
	}
	return;
}

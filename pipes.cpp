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
	//printf("%d compare result \n",compare_result);
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
			while(*down_stream++ = strtok(NULL,"\t")){
				return 1;
			}
		}
		*up_stream ++;
	}
	
	return 1;
}  

void sanitize_string(char* good_string,char* one_string){
	char bad_chars[] = {'\n','$','\''};
	
	for(int i = 0,j = 0; i < 20; i++){
		if((one_string[i] != bad_chars[0]) && 
		  	(one_string[i] != bad_chars[1]) &&
			(one_string[i] != bad_chars[2])
			){
			
			good_string[j] = one_string[i];
			j++;
		}
	}
}

void pipe_shell(){
	int pipe_descriptor[2];
	char *up_stream[20], *down_stream[20];
	char *argument[2];
	argument[1] = NULL;
	argument[2] = NULL;
	
	while(1){
		int parse_result = prompt_and_parse(up_stream,down_stream);
		
		if(parse_result == -1){
			exit(0);
		}

		char good_command[20];
		sanitize_string(good_command,up_stream[0]);
		up_stream[0] = good_command;
		argument[0]  = good_command;
		
		if(down_stream[0] == NULL){
			/*only one command is given to the sample terminal*/
			if(fork() == 0){/*child process*/
				
				execvp(up_stream[0],argument);
				printf("%s :not found\n",good_command);
				exit(1);
			}else{
				wait(0);
			}
		}else{
			/*
				there are two commands pipe the result and display it
				we need to run fork() twice to run the downstream and upstream
				commands concurrently with a pipe between them,	
			*/
			pipe(pipe_descriptor);
			if(fork() == 0){/*upstream child*/
				/*
					connect stdout to upstream end of pipe
				*/
				dup2(pipe_descriptor[1],1);
				close(pipe_descriptor[0]);
				/*
					execute the upstream command
				*/
				execvp(up_stream[0],argument);
				printf("%s :not found\n",up_stream[0]);
				exit(1);
			}
			/*
				downstream child
			*/
			if(fork() == 0){
				/*
					execute the downstream command
					connect stdin to the downstream end of pipe
				*/
				dup2(pipe_descriptor[0],0);
				/*close the upstream end of the pipe*/
				close(pipe_descriptor[1]);
				char *argument[2];
				argument[1]  = NULL;
				argument[2]  = NULL;
				char good_command[20];
				sanitize_string(good_command,down_stream[0]);
				up_stream[0] = good_command;
				argument[0]  = good_command;
				execvp(down_stream[0],argument);
				printf("%s: not found\n",down_stream[0]);
				exit(1);
			}else{
				close(pipe_descriptor[0]);
				close(pipe_descriptor[1]);
				/*
				wait for both children to finish
				*/
				wait(0);
				wait(0);
			}
		}						
	}
	return;
}

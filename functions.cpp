#include "commonHeader.h"
#include "functions.h"

void fork_function(){
	if(fork()){
		printf("Parent came\n");
	}else{
		printf("child came\n");
	}
}

void fork_loop(){
	if(fork()){
		for(int i = 0;i < 100000; i++){
			printf("** PARENT %d\n", i);
		}
	}else{
		for(int i = 0;i < 100000; i++){
			printf("  **  CHILD %d\n",i);
		}
	}
}

void exec_examples(){
	const char *argv[] = {"ls","-a",0};
	const char *envp[] = {"EDITOR=vi","TZ=:EST",0};
	
	/*
		giving absolute path and inherited 
		environment
	*/
	
	//execl("/bin/ls","ls","-a",NULL);
	
	/*
		giving absolute path new environment and 
		list
	*/

	int result = 0;
	
	
	result = execle("/bin/ls","ls","-a",NULL,envp);
	std::cout <<"status code " <<result <<"\n";
	return;
}

void exit_status(){
	int status;
	if(fork()){
		/*
			parent 
		*/
		printf("parent waiting for child\n");
		wait(&status);
		/*
			if the child exited normally
		*/
		if(WIFEXITED(status)){
			printf("child exited normally,exit status= %d\n",WEXITSTATUS(status));
		}
		/*
			if the child exited ubnormally
		*/
		if(WIFSIGNALED(status)){
			printf("child terminated by signal %d\n",WTERMSIG(status));
		}

	}else{
		/*
			child
		*/
		printf("child running .. PID is %d\n",getpid());
		/*
			writing some data to an invalid address
			segev :- segmentation violtaion SEGEV
		*/
		*(int *)0 = 42;

		sleep(100);
		exit(3);
	}
	return;
}

void simple_shell(){
	
}
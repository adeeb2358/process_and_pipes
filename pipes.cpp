#include "commonHeader.h"
#include "pipes.h"

void pipe_function(){
	int p[2];
	/*system call to create the pipe*/
	pipe(p);
	return;
}
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

void myFunction(char **one_array,char **two_array){
	char one_line[80] = "adeeb \t sasi";
	std::cout << one_line;
	char *first_word;
	*one_array++ = strtok(one_line,"\t");
	*one_array--;
	std::cout<< one_array;
	return;
}

int main(){
	char *one_array[20];
	char *two_array[20];
	myFunction(one_array,two_array);
	return 0;
}
#ifndef PIPES_H
#define PIPES_H
int prompt_and_parse(char** upstream,char **down_stream);
void pipe_function();
void pipe_shell();
void sanitize_string(char* good_string,char* one_string);
#endif // PIPES_H

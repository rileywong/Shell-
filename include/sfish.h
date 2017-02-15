#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


void splitArray(char* cmd);
void printHelp();
void updatePrompt();
char* extractString(int lower, int upper);
void splitArray1(char* cmd, int start, int end);
int fileExist();
void addPid(int pid, int waitpid);
void printJobs();
void disownThis(int disown);
int ctrlB(int cnt, int key);
int ctrlG(int cnt, int key);
int ctrlH(int cnt, int key);
int ctrlP(int cnt, int key);
void incrPgid(int incr);
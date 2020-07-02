#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define MAXSIZE 100



int compareFiles(FILE *file1, FILE *file2);
void cd(char name[]);
float Judge(char name[]);
void ui();
int ls(char x[]);
void Text(char name[]);

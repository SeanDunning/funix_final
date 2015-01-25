#ifndef DIRECTORY_H
#define DIRECTORY_H


#include "permissions.h"

#define COMMAND_LENGTH 80
#define NUM_COMMANDS 5
#define SUB_DIR_COUNT 3

typedef struct Dir
{

  struct Dir *parentDir; //points back to parent directory node
  struct Dir *subDir[SUB_DIR_COUNT]; //points to array of subdirectories
  char *dirName;
  int subDirCount;
  int timeMod;
  struct Permissions *per; //contain permissions rwx and time?

}Directory;

void createDirectory(Directory *currentDirectory, int tempUmask,
                     const char* arguments[]);  
// creates root dir "/" with umask value, subsequent calls create new dir
void showPath(Directory *currentDirectory);  
// recursively print current directory
void mkdir(Directory *currentDirectory, const char* arguments[]);  
// calls createDirectory with current directory and other arguments
void ls(Directory *currentDirectory, int argCount, const char *arguments[]);  
// print current directory info, subdirectories and umask/time values
struct Dir *cd (Directory *currentDirectory, int numChildren,
                const char *arguments[]);  
// change current directory, move along linked list?


#endif



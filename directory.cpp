#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "directory.h"


void createDirectory(Directory *currentDirectory, int tempUmask, 
                     const char* arguments[]) 
 // creates new dir with umask value, subsequent calls create new dir,
 // check for 3 subdir already made
{
  if (currentDirectory -> subDirCount <= 2)
    {
      currentDirectory -> subDir[currentDirectory -> subDirCount] -> subDirCount
      = 0; // Init it to 0
      
     currentDirectory -> subDir[currentDirectory -> subDirCount] -> dirName =
     (char*)malloc ( strlen( arguments[1]) + 1 ); // Malloc the name of
     // subDirectory

      strcpy(currentDirectory -> subDir[currentDirectory -> subDirCount] ->
      dirName, arguments[1]); // Copy name read in as subDirectory name

      currentDirectory -> subDir[currentDirectory -> subDirCount] -> parentDir
      = currentDirectory;   
  
      createPermissions(currentDirectory -> subDir[currentDirectory ->
      subDirCount] -> per, tempUmask); // Fill in those permissions from umask
          
    } //subDirCount not exceed 3
}// createDirectory()
void showPath(Directory *currentDirectory)
// recursively print current directory 
// by pointing back to parent node until NULL
{
  if (strcmp(currentDirectory->dirName, "/") == 0)
    printf("%s", currentDirectory->dirName);

  else // if Directory name does not match with root "/"
  {
 
    showPath(currentDirectory -> parentDir);
 
    printf("%s/", currentDirectory -> dirName);
  }//prints currentDirectory name recursively

}// showPath()

void mkdir(Directory *currentDirectory, const char* arguments[])
{

   if (currentDirectory -> subDirCount <= 2) 
   // If subDirectories number less than 3
   {
     currentDirectory -> subDir[currentDirectory -> subDirCount] =  
(Directory*)malloc(sizeof(Directory)); // Malloc the subDirectory

//     currentDirectory -> subDir[currentDirectory -> subDirCount] -> dirName = 
//(char*)malloc ( strlen( arguments[1]) + 1 ); // Malloc the name of subDirectory

     currentDirectory -> subDir[currentDirectory -> subDirCount] -> subDirCount
 = (int)malloc(sizeof(int)); // Malloc new subDirCount
  
     currentDirectory -> subDir[currentDirectory -> subDirCount] -> per = 
(Permissions*)malloc(sizeof(Permissions)); // Malloc permissions for each SubDir


   } //making a new directory
//making a new directory when the current directory's subdirectory count<=3
   if (currentDirectory -> subDirCount > 2) 
   // If subDirectories number greater than 3
   {
     printf("mkdir: %s already contains the maximum number of directories\n",
 currentDirectory -> dirName);
   }// If subDirectories number greater than 3
}// mkdir()

void ls(Directory *currentDirectory, int argCount, const char *arguments[]) 
// print current directory info, subdirectories and umask/time values

{
  int tempSubDirCount = currentDirectory -> subDirCount - 1; 
// subDirCount - 1 is 3 subDir at max

  if (argCount == 0)
  {
    for (int i = 0; i <= tempSubDirCount; i++)
      printf("%s ", currentDirectory -> subDir[i] -> dirName); 
//Print subDir names in order
      printf("\n"); // Formatting
  } 	// if number of arguments is 0
  
  if (argCount == 1)
  {
    for (int i = 0; i <= tempSubDirCount; i++)
    {
     printPermissions(currentDirectory -> subDir[i] -> per);

      printf("%d %s\n", currentDirectory -> subDir[i] -> timeMod,
 currentDirectory -> subDir[i] -> dirName);

    }// terminates when i goes through each subDirectory (based on count)
  }// if there is 1 argument

}// ls()
struct Dir *cd(Directory *currentDirectory, int numChildren,
                const char *arguments[])
{

 if (strcmp("..", arguments[1]) == 0)
    {
      if (strcmp(currentDirectory -> parentDir -> dirName, "/") != 0)
        {
          currentDirectory = currentDirectory -> parentDir;

          return currentDirectory;
        } // if name of parent directory is not the same as "/" the root
      else if  (strcmp(currentDirectory -> parentDir -> //c
 dirName, "/") == 0)
      {
        currentDirectory = currentDirectory -> parentDir;

        return currentDirectory;
      }// else if it IS equal to 0 (the strings match)
    }// if the argument is '..' and there is not another argument after
  if ((numChildren >= 1) && (strcmp(currentDirectory -> subDir[0] -> dirName,
 arguments[1]) == 0))
    {
      currentDirectory = currentDirectory -> subDir[0];

      return currentDirectory;
    }// returns currentDirectory if number of children >= 1 

  if ((numChildren >= 2) && (strcmp(currentDirectory -> subDir[1] -> dirName,
 arguments[1]) == 0))
    {
      currentDirectory = currentDirectory -> subDir[1];

      return currentDirectory;
    }// if there is more than 2 children and the name of subDir 1 match.

  if ((numChildren == 3) && (strcmp(currentDirectory -> subDir[2] -> dirName,
 arguments[1]) == 0))
    {
      currentDirectory = currentDirectory -> subDir[2];

      return currentDirectory;
    }// Sets currentDirectory's current Directory to the last subDirectory 


  else// if function cannot find subdirectory path
  {
    printf("cd: %s: No such file or directory\n", arguments[1]);

    return currentDirectory;
  }//if Directory does not exist, print this

}// cd()




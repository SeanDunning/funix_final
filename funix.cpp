#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funix.h"
#include "directory.h"


void cd(Funix *funix, int argCount, const char *arguments[])// calls cd() with
// currentDirectory as one of its parameters
{

  if (argCount != 1)
    printf("usage: cd directoryName\n");
  else //if passed
  {
    int numChildren = funix -> currentDirectory -> subDirCount;
   
    funix->currentDirectory = cd(funix -> currentDirectory, numChildren,
    arguments);

  }//call cd in directory on else
} // cd()


int eXit(Funix *funix, int argCount, const char *arguments[])// checks "exit" 
//command, returns 0 on proper exit
{
  if (argCount > 0)
  {
    printf("\nusage: exit");
    return 1;
  }//usage error

  exit(0);
} // eXit()


void getCommand(Funix *funix, char *command) // calls writePrompt and reads in
// command
{
  writePrompt(funix);

  fgets(command, COMMAND_LENGTH, stdin); //read in command into command. 

  if (strlen(command)-1 > 0)

    if (command[strlen(command)-1] == '\n') //checks for newline
      command[strlen(command) -1] = '\0';   //delete newline
} // getCommand()


void init(Funix *funix) // creates currentDirectory, and sets umask and time
{

  funix -> currentDirectory = (Directory*)malloc(sizeof(Directory));
  funix -> currentDirectory -> subDirCount = (int)malloc(sizeof(int));
  funix -> currentDirectory -> parentDir = funix -> currentDirectory;
  funix -> currentDirectory -> subDirCount = 0;
  funix -> time = 0;
  funix -> umask = 0;
  funix -> currentDirectory -> dirName = (char*)malloc ( strlen("/") + 1); 
  strcpy (funix -> currentDirectory -> dirName, "/");
// strcpy(funix -> currentDirectory -> dirName, "/");
 // funix -> currentDirectory -> dirName = "/";

} // init()


void ls(Funix *funix, int argCount, const char *arguments[])  // calls ls()
// with currentDirectory as one of its parameters
{
  if (argCount > 1) // incorrect usage of ls, print usage
  {
    printf("usage: ls [-l]\n");
  }//usage

  if (argCount == 1) // long version ls, checks for usage of -l
  {
    if (strcmp(arguments[1], "-l") == 0)
      ls(funix -> currentDirectory, argCount, arguments);
    else //usage if not passed
      printf("usage: ls [-l]\n");
  }// check options on ls

  if (argCount == 0) // regular ls
    ls(funix -> currentDirectory, argCount, arguments);


} // ls()

void mkdir(Funix *funix, int argCount, const char *arguments[])
{
  if (argCount != 1) //Check correct usage of mkdir
  {
    printf("usage: mkdir directory_name\n");
  }//usage error
  else // passed usage
  {
    int tempUmask; // Value passed when making new directory
    int nameMatch = 1; // Variable that checks for duplicate directories
    tempUmask = funix -> umask; // Pass umask to directory -> then perm
    
     for (int i; i < funix -> currentDirectory -> subDirCount; i++) //check name
      {
        nameMatch = strcmp(funix -> currentDirectory -> subDir[i] -> dirName,
        arguments[1]); // compare subDir names vs new name
       
        if (nameMatch == 0) // 0 means name already exists
         {
            printf("mkdir: cannot create directory '%s': File exists\n",
            arguments[1]); //error
            break; //end search
         }//usage error
      }//compare subDir name with arguments[1]
   
      if (nameMatch != 0) // != 0 means no match found, create new directory
      {
        mkdir(funix -> currentDirectory, arguments);
        createDirectory(funix -> currentDirectory, tempUmask, arguments);
        funix -> currentDirectory -> subDir[funix -> currentDirectory ->
        subDirCount] -> timeMod = funix -> time; //Sets timeMod each new dir
        
        if (funix -> currentDirectory -> subDirCount < 3)
          funix -> currentDirectory -> subDirCount++; // Keep track cd's subdir
      }//no duplicate subDir
  }//successfully made new subDir
} // mkdir

int processCommand(Funix *funix, char *command) // returns 0 on proper exit
{
  const char space[2] = " "; // delim in strtok function
  const char *arguments[40]; // contains array of commands and options
  const char *commandList[] = {"cd", "mkdir", "umask", "ls", "exit"}; // List of
// legal commands
  int i = 0; // increment for array of strings
  int j = 0; // increment for position of command on commandList array

  arguments[0] = strtok(command, space); // parse main command into first array

  funix -> time++; // Time increases for each command, good or bad

  while(arguments[i] != NULL)
  {
     arguments[++i] = strtok(NULL, space); // parse options into rest of arrays
  }//strtok additional arguments

  int argCount = i - 1; // 0 = command, > 0 are options


  int switchCommands; 

  if (arguments[0] != NULL)
    {  
      do //compare first argument with legal commands
      {
        if (j <= 4)
        {
          switchCommands = strcmp(arguments[0], commandList[j]);
        } //run through all command list
       
        ++j;
       
        if (j == 6) // Reach end of comparison, break out of loop
          {
            j = 10;
            switchCommands = 0;
          } //nothing found, end loop

      } while (switchCommands != 0); //Value 0 means match was found

    } //check commands agasint list

  --j; // deincrement to return j to correct value

    switch(j) //j is number corresponding to commandList
    {
     case 0:

         cd (funix, argCount, arguments);
         break;

     case 1:
          mkdir(funix, argCount, arguments);
          break;

     case 2:
           umask(funix, argCount, arguments);
           break;

     case 3:
           ls(funix, argCount, arguments);
           break;

     case 4:
           eXit(funix, argCount, arguments);
           break;
     default:
           printf("%s: Command not found.\n", command);
	

    } //switch statement for command list

     return 1;


} // processCommand ()


void run(Funix *funix) // reads and processes commands in a loop until proper
// exit
{
  char command[COMMAND_LENGTH];
  init(funix);
  int i;
 
 do
  {
    getCommand(funix, command);
    
    if (strcmp(command, "\n"))
      {
        processCommand(funix, command);
      } //if command is only enter, try again
   
    i++;
  } while(i != 1000); // end on proper exit command


} // run()


void umask(Funix *funix, int argCount, const char *arguments[])  
// checks "umask" command and executes it if it is proper
{
  if (argCount == 1)
  {

    int temp = atoi(arguments[1]);

    if (temp > 7 || temp < 0)
      printf("umask: octal must be between 0 and 7\n");
    else // passed usage
      funix -> umask = temp;
  } // passed argcount on umask
  else //usage error
  {
    printf("usage: umask octal\n");
  } // usage

} // umask()


void writePrompt(Funix *funix) // shows path and '#'
{
  showPath(funix -> currentDirectory);
  printf(" # ");

} // writePrompt



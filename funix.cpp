#include <cstring>
#include <cstdlib>
#include <iostream>
#include "funix.h"
#include "directory.h"
#include <iomanip>


using namespace std;
const short imask = 0022; //p4::4 sets initial umask octal

Funix::Funix() : umask(0022)
// creates currentDirectory, and sets umask and time
{
  ifstream readFile("directories.txt");

  int umas;

  readFile >> umas;

  currentDirectory = new Directory("/", umask, NULL);
}  // Funix()
//bool Funix::operator==(const Funix &rhs) const
//{

//} // operator==

Funix::~Funix()
{
  const char *arguments[2] = {"cd", ".."};
  Directory *next = currentDirectory->cd(2, arguments);

  while(currentDirectory != next)
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments);
  }  // while currentDirectory not root

  delete currentDirectory;
}  // ~Funix())

int Funix::eXit(int argCount, const char *arguments[])
{
  // checks "exit" command, returns 0 on proper exit

  if (argCount > 1)
  {
    cout << "usage: exit\n";
    return 1;
  }  // if more than one argument

  ofstream dirFile("directories.txt");
  dirFile << *this;

  return 0;
}  // eXit()
ostream& operator<< (ostream& dirFile, Funix& rhs)
{
  const char *arguments[2] = {"cd", ".."};
  Directory *current = rhs.currentDirectory;
  Directory *next = rhs.currentDirectory->cd(2, arguments);

  while(current != next)
  {
    current = next;
    next = current->cd(2, arguments);

  }  // while currentDirectory not root
  dirFile << current->name;
  //dirFile << *current->modTime << " ";
  dirFile << current->subDirectoryCount << "\n";

    for (int i = 0; i < current->subDirectoryCount; i++)
        dirFile << *current->subDirectories[i];
    //dirFile.close();
return dirFile;
}
void Funix::getCommand(char *command)  // writes prompt and reads command
{
  writePrompt();
  cin.getline(command, COMMAND_LENGTH);
  time++;
}  // getCommand()

int Funix::processCommand(char *command)  // returns 0 on proper exit
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask", "chmod"};
  const char *arguments[MAX_ARGUMENTS];
  char *ptr;
  int argCount = 0, commandNum;
  ptr = strtok(command, " ");

  while (ptr)
  {
    arguments[argCount++] = ptr;
    ptr = strtok(NULL, " ");
  }  // while more arguments in the command line

  if (argCount > 0)
  {
    for (commandNum = 0; commandNum < NUM_COMMANDS; commandNum++)
    {
      if (strcmp(arguments[0], commands[commandNum]) == 0)
        break;
    }  // for each possible command

    switch (commandNum)
    {
      case 0: currentDirectory = currentDirectory->cd(argCount, arguments);
              break;
      case 1: return eXit(argCount, arguments);
      case 2: currentDirectory->ls(argCount, arguments); break;
      case 3: currentDirectory->mkdir(argCount, arguments, umask); break;
      case 4: setUmask(argCount, arguments); break;
      case 5: currentDirectory->chmod(argCount, arguments, umask); break;
      default: cout << arguments[0] << ": Command not found.\n";
    }  // switch on commandNum
  }  // if at least one argument

  return 1;
}  // processCommand()


void Funix::run()
// reads and processes commands until proper exit
{
  char command[COMMAND_LENGTH];
  getCommand(command);

  while (processCommand(command))
    getCommand(command);
}  // run()


void Funix::setUmask(int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{

  long x;
  if (argCount == 1)
  {
    cout << std::oct;
    cout << setfill('0') << setw(4) << umask << "\n";
    return;
  }  // if only one argument

  if ((argCount > 2))
  {
    cout << "umask: Too many arguments.\n";
    return;
  }  // if more than 1 argument (if argument[2] is not null)


  x = strtol(arguments[1], NULL, 8);


  if ( x < 00 || x > 0777 || arguments[1][0] < '0' || arguments[1][0] > '7' ||
                             arguments[1][1] < '0' || arguments[1][1] > '7' ||
                             arguments[1][2] < '0' || arguments[1][2] > '7' )
  {
    cout << "umask: Improper mask.\n";
    return;
  }// if x is not an octal value



  umask = x;
}  // umask()



void Funix::writePrompt() const  // shows path and '#'
{
  currentDirectory->showPath();
  cout << " # ";
}  // writePrompt()


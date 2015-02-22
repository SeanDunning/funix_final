#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"
#include <fstream>
#include <iostream>

using namespace std;

const int COMMAND_LENGTH = 80;
const int NUM_COMMANDS = 6;
const int MAX_ARGUMENTS = 40;

class Funix
{
  Directory *currentDirectory;
  int umask;
  int time;

  int eXit(int argCount, const char *arguments[]);
    // checks "exit" command, returns 0 on proper exit
  void getCommand(char *command);
    // writes prompt and reads command
  int processCommand(char *command);  // returns 0 on proper exit
  void setUmask(int argCount, const char *arguments[]);
    // checks "umask" command and executes it if it is proper
  void writePrompt() const;  // shows path and '#'
public:
  Funix();
  ~Funix();
  void run();
    // reads and processes commands in a loop until proper exit
    // creates currentDirectory, and sets umask and time
  friend ostream& operator<< (ostream& dirFile, Funix&);
  //friend bool Funix::operator==(const Funix &rhs) const;

};  // class Funix
#endif


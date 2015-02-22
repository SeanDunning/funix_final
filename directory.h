#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#include <iostream>

using namespace std;

const int MAX_DIRECTORIES = 3;

class Directory
{
  public:
  char *name;
  Time *modTime;
  Directory **subDirectories;
  int subDirectoryCount;
  Directory *parent;
  Permissions permissions;


    Directory(const char *nam, short umask,/* Time *tim,*/ Directory *paren);
    ~Directory();
    Directory* cd(int argCount, const char *arguments[]);
    void chmod(int argCount, const char *arguments[], short umask);
    void ls(int argCount, const char *arguments[]) const;
    void mkdir(int argCount, const char *arguments[], short umask);
    void showPath() const;
    friend ostream& operator<< (ostream& dirFile, Directory&);
    //friend bool Directory::operator==(const Funix &rhs) const;
};  // class Directory
#endif  // DIRECTORY_H


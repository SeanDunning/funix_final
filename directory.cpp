#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
using namespace std;

Directory::Directory(const char *nam, short umask, /*Time *tim, */Directory *paren)
  : modTime(), subDirectories(NULL), subDirectoryCount(0), parent(paren)
 {
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, umask);
  //modificationTime->theTim
  modTime = new Time(this->modTime);
 }  // Directory())
ostream& operator<< (ostream& dirFile, Directory& rhs)
{

  Directory *current = &rhs;


  dirFile << current->name;
  //dirFile << *current->modTime << " ";
  dirFile << current->subDirectoryCount << "\n";

  for (int i = 0; i < current->subDirectoryCount; i++)
  {
        dirFile << *current->subDirectories[i];

  }
}

Directory::~Directory()
{
  delete [] name;

  for (int i = 0; i < subDirectoryCount; i++)
    delete subDirectories[i];

  delete [] subDirectories;
}  // ~Directory())

Directory* Directory::cd(int argCount, const char *arguments[])
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)
  {
    if (parent)
      return parent;
    else  // this is root
      return this;
  }  // if cd ..

  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (strcmp(subDirectories[i]->name, arguments[1]) == 0)
    {
      if(subDirectories[i]->permissions.isPermitted(3))
        return subDirectories[i];
      else
      {
        cout << subDirectories[i]->name << ": Permission denied.\n";
        return this;
      }//else

    }//if

  }  // for each subdirectory

  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()


void Directory::chmod(int argCount, const char *arguments[], short umask)
{
  int x;
  int k;

  if (argCount == 2)
  {
     cout << "chmod: missing operand after vi'"<<arguments[1]<<"'\n"
          << "Try 'chmod --help' for more information\n";
     return;
  }//if there are less than 3 arguments (needs directory name)
  if (argCount < 2)
  {
     cout << "chmod: missing operand'\n"
          << "Try 'chmod --help' for more information\n";
     return;
  }//if there are less than 3 arguments (needs directory name)

  x = strtol(arguments[1], NULL, 8); //converts arguments into short

  if ( arguments[1][0] < '0' || arguments[1][0] > '7' ||
       arguments[1][1] < '0' || arguments[1][1] > '7' ||
       arguments[1][2] < '0' || arguments[1][2] > '7' ||
       arguments[1][3] != NULL) //checking between value of 0-0777
  {
     cout << "chmod: invalid mode: '"<< arguments[1] << "'\n"
          << "Try 'chmod --help' for more information\n";

  }//if argument[1] is an octal value
  else
  {
    for (int j = 2; j < argCount; j++)
    {
      k = 0;                                    // k is counting variable
      for(int i = 0; i < subDirectoryCount; i++)//first file should be at arguments[2]
      {
        if (strcmp(subDirectories[i]->name, arguments[j]) == 0)
         {
           subDirectories[i]->permissions.set(x, 00);
           subDirectories[i]->modTime->update(modTime);
           k = 1; //there should only be one subdirectory with same name
         }// if matching name in subdirectories
      } //for i < subDirectoryCount

      if (k == 0)
      {
         cout << "chmod: cannot access '"<< arguments[j]
              << "': No such file or directory\n";
      }// if no file
    }  //for  j < argCount
  }//else
  return;
}//chmod()




void Directory::ls(int argCount, const char *arguments[])const
{


  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]\n";
  else  // correct number of arguments
  {
      //isPermitted()
    if (permissions.isPermitted(1)) //if directory has permission
    {
      if (argCount == 1)  // simple ls
      {
        for (int i = 0; i < subDirectoryCount; i++)
          cout << subDirectories[i]->name << " ";

          cout << "\n";
      }  // if simple ls
      else  // must be ls -l
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          subDirectories[i]->permissions.print();
          subDirectories[i]->modTime->print();
          cout << " " << ' ' << subDirectories[i]->name << endl;
        }  // for each subdirectory
      }  // else is ls -l
    }// if (permissions exist)
    else
      cout << "ls: cannot open directory .: Permission denied\n";
  }  // else correct arguments
}  // ls()

//bool Directory::operator==(const Directory &rhs)

void Directory::mkdir(int argCount, const char *arguments[], short umask)
{
  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (strcmp(subDirectories[i]->name, arguments[1]) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
           << "': File exists\n";
      return;
    }  // if subdirectory already exists.
  }  // for each subdirectory

  if ((permissions.isPermitted(2)) || (!(parent)))
  {
    for (int j = 0; j < argCount - 1; j++)
    {
      Directory **subDirectoriesTemp = new Directory*[subDirectoryCount + 1];

      for (int i = 0; i < subDirectoryCount; i++)
        subDirectoriesTemp[i] = subDirectories[i];

      delete [] subDirectories;
      subDirectories = subDirectoriesTemp;
      subDirectories[subDirectoryCount] = new Directory(arguments[j+1], umask, this);
      subDirectoryCount++;
    }//for
  }//if
  else
  {
    cout << "mkdir: cannot create directory '" << arguments[argCount - 1] <<"': "
         << "Permission denied\n";
  }// else
    return;
}  // mkdir()


void Directory::showPath() const
{
  if (parent == NULL)
  {
    cout << "/";
    return;
  }  // at root

  parent->showPath();
  cout << name << "/";
}  // showPath())

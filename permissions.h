#ifndef PERMISSIONS_H
#define PERMISSIONS_H

typedef struct Permissions 
{
  short octal;
}Perm;

void createPermissions(Permissions *per, int tempUmask); // set rwx? umask?
void printPermissions(Permissions *per); // print rwx when prompted?

#endif



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "permissions.h"

void createPermissions(Permissions *per, int tempUmask)
{
  
  //per -> octal = (short*)malloc(sizeof(short));
  per -> octal = tempUmask;
  

}// createPermissions()

void printPermissions(Permissions *per)
{

  if (per -> octal == 0)
    printf("rwx ");

  if (per -> octal == 1)
    printf("rw- ");

  if (per -> octal == 2)
    printf("r-x ");

  if (per -> octal == 3)
    printf("r-- ");

  if (per -> octal == 4)
    printf("-wx ");

  if (per -> octal == 5)
    printf("-w- ");

  if (per -> octal == 6)
    printf("--x ");

  if (per -> octal == 7)
    printf("--- ");

}// printPermissions()



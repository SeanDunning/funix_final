#include <iostream>
#include "permissions.h"

using namespace std;

bool Permissions::isPermitted(int x)const
{
    if (x == 1)//testing reading permissions
    {
      if (permissions & 256 )
        return true; // has permission
    }//if

    else if (x == 2)
    {
      if (permissions & 128)//testing writing permissions
        return true; //permissions
    }//if


    else if (x == 3) //testing execute permissions
    {
      if (permissions & 64)
        return true;
    }//if
  else
  {
    return false;
  }
}//isPermitted()

void Permissions::set(short originalPermissions, short umask)
{
  permissions = originalPermissions & ~umask;
}  // set()

void Permissions::print() const
{


  if (permissions & 256) //Others permissions
    cout << "r";
  else  // no others read permissions
    cout << "-";

  if (permissions & 128)
    cout << "w";
  else  // no others write permissions
    cout << "-";

  if (permissions & 64)
    cout << "x";
  else  // no others execute permissions
    cout << "-";


  if (permissions & 32) //group permissions
    cout << "r";
  else  // no group read permissions
    cout << "-";

  if (permissions & 16)
    cout << "w";
  else  // no group write permissions
    cout << "-";

  if (permissions & 8)
    cout << "x";
  else  // no group execute permissions
    cout << "-";


  if (permissions & 4)
    cout << "r";
  else  // no read permissions
    cout << "-";

  if (permissions & 2)
    cout << "w";
  else  // no write permissions
    cout << "-";

  if (permissions & 1)
    cout << "x";
  else  // no execute permissions
    cout << "-";

}  // print()

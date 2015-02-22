#include <cstring>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Time.h"
using namespace std;

Time::Time(Time *modTime)
 {


  time_t tim;
  time(&tim);
  modificationTime = *localtime(&tim);



 }  // Time()
ostream& operator<< (ostream& dirFile, Time& rhs)
{
  //Time->modificationTime *modTime = &rhs;
  dirFile << " " << rhs.modificationTime.tm_mon ;
  dirFile << " " <<  rhs.modificationTime.tm_mday;
   dirFile << " " <<  rhs.modificationTime.tm_hour;
   dirFile << " " <<  rhs.modificationTime.tm_min;
}
void Time::update(Time *modTime)
{
  time_t tim;
  time(&tim);
  modificationTime = *localtime(&tim);
}
void Time::print()const
{
  cout << " " << modificationTime.tm_mon <<" ";

  switch(modificationTime.tm_mon)
  {
      case 0: cout << "Jan"; break;
      case 1: cout << "Feb"; break;
      case 2: cout << "Mar"; break;
      case 3: cout << "April"; break;
      case 4: cout << "May"; break;
      case 5: cout << "June"; break;
      case 6: cout << "July"; break;
      case 7: cout << "Aug"; break;
      case 8: cout << "Sep"; break;
      case 9: cout << "Oct"; break;
      case 10: cout << "Nov"; break;
      case 11: cout << "Dec"; break;
  }


  //cout << " " << modificationTime.tm_mon <<" " << modificationTime.tm_mday
     cout  <<" " << modificationTime.tm_hour<< ":" << setfill('0') << setw(2) << modificationTime.tm_min;
}

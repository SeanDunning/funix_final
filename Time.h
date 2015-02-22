#ifndef TIME_H
  #define TIME_H
#include <ctime>
#include <fstream>

using namespace std;
class Time
{

public:
  struct tm modificationTime;
  Time(Time *modTime );
  void update(Time *modTime);
  void print() const;
  friend ofstream& operator<< (ofstream& dirFile, Time&);
};  // class Time;
#endif  // TIME_H

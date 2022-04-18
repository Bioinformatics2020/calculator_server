#ifndef DATE_H
#define DATE_H

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstring>
#include "set.h"

class Date
{
private:
  SetDate &set;
  std::string tFormat;
  tm getTime(std::string &str);                  // string转tm
  void deff(tm &time1, tm &time2);               // tm1 tm2之差的绝对值，保存于time1
  int tmToDay(tm &time);                         //由tm求天
  int tmToSecond(tm &time);                      //由tm求秒
  void print1582_10_11_12(std::ostream &calOut); //输出1582年特殊的三个月(十天)到流
public:
  std::string sign();
  Date(SetDate &set);
  std::string getNow();                                                      //获取现在时间
  std::string diffTime(std::string &str1, std::string &str2);                //求日期间隔
  void put_cal(int year, std::ostream &calOut);                              //输出日历到流
  std::string changeTime(std::string &str1, std::string &str2, bool is_add); //日期加减天数
};

#endif // !DATE_H
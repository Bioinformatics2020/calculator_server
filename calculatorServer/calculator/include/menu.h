#ifndef MENU_H
#define MENU_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include "History.h"
#include "date.h"
#include "set.h"
#include "company.h"
#include "bigNumber.h"
#include "programmer.h"
#include "common.h"

using std::string;
using std::vector;

class userData
{
public:
  std::mutex m;
  std::condition_variable cv;
  std::istringstream userIn;
  std::ostringstream userOut;
  bool canIn = true;
  bool canOut = false;
  bool kill = false;
};

void menu(userData &data);

class user
{
private:
  bool in_cal = false;
  std::thread t;
  userData data;

public:
  int time;
  std::string input, output;
  ~user()
  {
    data.kill = true;
    data.cv.notify_all();
    t.join();
  }
  bool run();
};
#endif // !MENU_H
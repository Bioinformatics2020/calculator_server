#include "menu.h"
Set set;
History his(set);

bool user::run()
{
  if (!in_cal)
  {
    in_cal = true;
    t = std::thread(menu, std::ref(data));
  }
  else
  {
    std::unique_lock<std::mutex> L1(data.m);
    data.cv.wait(L1, [this]
                 { return this->data.canIn; });
    data.userIn = std::istringstream(input);
    data.canIn = false;
    data.cv.notify_all();
    L1.unlock();
  }
  std::unique_lock<std::mutex> L2(data.m);
  data.cv.wait(L2, [this]
               { return this->data.canOut; });
  std::string outPut = data.userOut.str();
  data.userOut.str("");
  if (outPut == "good bye\n")
  {
    output = outPut;
    t.join();
    return true;
  }
  while (!outPut.empty())
  {
    output = outPut;
    outPut = "";
    if (false)
    {
      t.join();
      return true;
    }
  }
  data.canOut = false;
  data.cv.notify_all();
  return false;
}

bool myGetOpt(userData &data, string &input, vector<string> &in)
{
  data.canOut = true;
  data.cv.notify_all();
  std::unique_lock<std::mutex> L1(data.m);
  data.cv.wait(L1, [&data]
               { return !data.canIn || data.kill; });
  if (data.kill)
    return false;
  // data.userIn.seekg(std::ios::end);
  getline(data.userIn, input);
  data.canIn = true;
  data.cv.notify_all();
  L1.unlock();
  if (input == "0")
    return false;
  int space = 0, space2;
  //取出输入内容
  int i = 0;
  while (i < 4)
  {
    space2 = input.find(' ', space);
    if (space2 == -1)
    {
      in.push_back(input.substr(space));
      break;
    }
    in.push_back(input.substr(space, space2 - space));
    space = space2 + 1;
    ++i;
  }
  return true;
}

void mainHelp(userData &data)
{
  std::ifstream fHelp("help.txt", std::ios::in);
  if (fHelp.is_open())
    data.userOut << fHelp.rdbuf() << '\n';
  else
    data.userOut << "help.txt is lost" << '\n';
}

void programmerMenu(userData &data)
{
  string his1 = "programmer";
  programmer a;
  do
  {
    string input, ans;
    data.userOut << "程序员计算器:>";
    vector<string> in;
    if (!myGetOpt(data, input, in))
      return;
    if (in.size() == 4 && in[0] == "more")
    {
      if (in[3] == "set")
      {
        ans = a.set(stoi(in[1]), stoi(in[2]));
      }
      else
        ans = a.conversion(stoi(in[1]), stoi(in[2]), in[3]);
    }
    else
    {
      try
      {
        ans = a.calculation(input);
      }
      catch (std::invalid_argument &err)
      {
        data.userOut << err.what() << '\n';
      }
    }
    data.userOut << ans << '\n';
    his.push(his1, input, ans);
  } while (true);
}

void commonMenu(userData &data)
{
  string his1 = "common";
  Common a(set);
  do
  {
    string input, ans;
    data.userOut << "科学计算器:>";
    vector<string> in;
    if (!myGetOpt(data, input, in))
      return;
    try
    {
      if (in.size() == 3)
      {
        if (in[0] == "more")
        {
          if (in[1] == "set")
            ; //统计模式
          else if (in[1].size() == 1 && in[1][0] >= 'A' && in[1][0] <= 'Z')
            ans = a.changePreset(in[1][0] - 'A', in[2]);
        }
        else if (in[0] == "batch")
          ans = a.batch(in[1], in[2]);
      }
      else if (in.size() == 1)
        ans = a.calculation(input);
      else
        throw std::invalid_argument("参数错误");
    }
    catch (std::invalid_argument &err)
    {
      data.userOut << err.what() << '\n';
      continue;
    }

    data.userOut << ans << '\n';
    his.push(his1, input, ans);
  } while (true);
}

void bigNumMenu(userData &data)
{
  string his1 = "bigNum";
  bigNumber a;
  do
  {
    string input, ans;
    data.userOut << "大数计算器:>";
    vector<string> in;
    if (!myGetOpt(data, input, in))
      return;
    try
    {
      ans = a.calculation(input);
    }
    catch (std::invalid_argument &err)
    {
      data.userOut << err.what() << '\n';
    }

    data.userOut << ans << '\n';
    his.push(his1, input, ans);
  } while (true);
}

void dateMenu(userData &data)
{
  string his1 = "date";
  Date a(set);
  do
  {
    string input, ans;
    data.userOut << "日期计算:>";
    vector<string> in;
    if (!myGetOpt(data, input, in))
      return;
    char mode = -1;
    if (in[0].size() == 1)
      mode = in[0][0];
    switch (mode)
    {
    case 'i':
      if (in.size() > 3 || in.size() < 2)
        data.userOut << "输入参数错误\n";
      else
      {
        if (in.size() == 2)
          in.push_back("");
        ans = a.diffTime(in[1], in[2]);
      }
      break;
    case 'v': // v 2022/4/9 + 1
      if (in.size() == 4)
      {
        if (in[2] == "+")
          ans = a.changeTime(in[1], in[3], true);
        else if (in[2] == "-")
          ans = a.changeTime(in[1], in[3], false);
        else
          data.userOut << "输入参数错误\n";
      }
      else
        data.userOut << "输入参数错误\n";
      break;
    case 'n':
      if (in.size() > 1)
        data.userOut << "输入参数错误\n";
      else
        ans = a.getNow();
      break;
    case 's':
      data.userOut << a.sign() << '\n';
      break;
    case 'c':
      if (in.size() != 2)
        data.userOut << "输入参数错误\n";
      try
      {
        int year = stol(in[1]); //字符串转整型，避免输入格式错误
        if (year <= 0)
        {
          data.userOut << "暂不支持公元前\n";
        }
        a.put_cal(year, data.userOut);
        ans = "日历已显示";
      }
      catch (const std::invalid_argument)
      {
        data.userOut << "年份输入错误\n";
      }
      break;
    default:
      data.userOut << "选项错误\n";
      continue;
    }
    data.userOut << ans << '\n';
    his.push(his1, input, ans);
  } while (true);
}

void companyMenu(userData &data)
{
  string his1("company");
  string (*funs[])(char, char, double) = {Company::dataLength, Company::angle, Company::volume, Company::mass, Company::length, Company::area, Company::time, Company::temperature, Company::energy, Company::speed, Company::power, Company::pressure};
  do
  {
    string input, ans;
    data.userOut << "单位换算:>";
    vector<string> in;
    if (!myGetOpt(data, input, in))
      return;
    bool is_err = false;
    char mode = -1;
    if (in[0].size() == 1)
      mode = in[0][0];
    if (mode >= 'a' && mode <= 'l' && in.size() == 4 && in[1].size() == 1 && in[2].size() == 1)
    {
      try
      {
        ans = funs[mode - 'a'](in[1][0], in[2][0], stod(in[3]));
      }
      catch (std::invalid_argument) //非法参数，stod错误或mode错误
      {
        is_err = true;
      }
    }
    else
      is_err = true;
    if (is_err)
    {
      data.userOut << "输入选项或参数错误\n";
      continue;
    }
    data.userOut << ans << '\n';
    his.push(his1, input, ans);
  } while (true);
}

void menu(userData &data)
{
  data.userOut << "欢迎来到多功能计算器2.0\n";
  string input; //直接读取字符串可以防止输出参数错误
  do
  { //功能选择
    data.userOut << "菜单:>";
    data.canOut = true;
    data.cv.notify_all();
    std::unique_lock<std::mutex> L1(data.m);
    data.cv.wait(L1, [&data]
                 { return !data.canIn || data.kill; });
    if (data.kill)
      return;
    data.userIn >> input;
    data.canIn = true;
    data.cv.notify_all();
    L1.unlock();
    //以下可以使用字典优化
    if (input == "help")
      mainHelp(data);
    else if (input == "exit" || input == "0")
      break;
    else if (input == "common")
      commonMenu(data);
    else if (input == "bigNum")
      bigNumMenu(data);
    else if (input == "programmer")
      programmerMenu(data);
    else if (input == "date")
      dateMenu(data);
    else if (input == "company")
      companyMenu(data);
    else
    {
      data.userOut << "选项错误\n";
      data.userIn.clear();
    }
  } while (true);
  data.userOut << "good bye\n";
  data.canOut = true;
  data.cv.notify_all();
}
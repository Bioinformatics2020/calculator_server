#include "date.h"

constexpr char mysign[] = "白羊座：03月21日 - 04月19日 金牛座：04月20日 - 05月20日\n双子座：05月21日 - 06月21日 巨蟹座：06月22日 - 07月22日\n狮子座：07月23日 - 08月22日 处女座：08月23日 - 09月22日\n天枰座：09月23日 - 10月23日 天蝎座：10月24日 - 11月22日\n射手座：11月23日 - 12月21日 摩羯座：12月22日 - 01月19日\n水瓶座：01月20日 - 02月18日 双鱼座：02月19日 - 03月20日\n";
std::vector<std::string>table = {
	"         1月                    2月                    3月        \n" ,
	"         4月                    5月                    6月        \n" ,
	"         7月                    8月                    9月        \n" ,
	"        10月                   11月                   12月        \n" ,
	"日 一 二 三 四 五 六   日 一 二 三 四 五 六   日 一 二 三 四 五 六\n" };
int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
std::vector<std::string>trunk_and_branch = { "甲","乙","丙","丁","戊","己","庚","辛","壬","癸",
"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" };

Date::Date(SetDate &set) :set(set)
{
	tFormat = set.set["dateFormat"] + " " + set.set["timeFormat"];
}

tm Date::getTime(std::string & str)
{
	tm time;
	memset(&time, 0, sizeof(tm));
	std::stringstream s(str);
	s >> std::get_time(&time, set.set["dateFormat"].c_str());
	return time;
}
void Date::deff(tm &time1, tm &time2)//tm1 tm2之差的绝对值，保存于time1
{
	time_t t = mktime(&time1) - mktime(&time2);
	if (t < 0)
		t *= -1;
	time1 = *std::localtime(&t);

}
int Date::tmToDay(tm &time)//由tm求天
{
	return (int)mktime(&time) / (60 * 60 * 24) + 1;
}

int Date::tmToSecond(tm &time)//由tm求秒
{
	return (int)mktime(&time);
}
void Date::print1582_10_11_12(std::ostream &calOut)//输出1582年特殊的三个月(十天)到流
{
	calOut << table[3] << table[4]
		<< "    1  2  3  4 15 16       1  2  3  4  5  6             1  2  3  4 \n"
		<< "17 18 19 20 21 22 23    7  8  9 10 11 12 13    5  6  7  8  9 10 11 \n"
		<< "24 25 26 27 28 29 30   14 15 16 17 18 19 20   12 13 14 15 16 17 18 \n"
		<< "31                     21 22 23 24 25 26 27   19 20 21 22 23 24 25 \n"
		<< "                       28 29 30               26 27 28 29 30 31    \n"
		<< "\n\n";
}
std::string Date::sign()
{
	return mysign;
}
std::string Date::getNow()//获取现在时间
{
	std::time_t rev = std::time(nullptr);
	char t[32];
	std::strftime(t, 32, tFormat.c_str(), std::localtime(&rev));
	return std::string(t);
}
std::string Date::diffTime(std::string &str1, std::string &str2)//求日期间隔
{
	tm t1, t2;
	t1 = getTime(str1);
	if (str2.empty())
	{
		std::time_t rev = std::time(nullptr);
		t2 = *std::localtime(&rev);
	}
	else
		t2 = getTime(str2);
	deff(t1, t2);
	return std::to_string(tmToDay(t1));
}

void Date::put_cal(int year, std::ostream &calOut)//输出日历到流
{
	int week;
	month[1] = 28;//默认第二月有28天
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		month[1] = 29;//闰年2月有29天

	//每多一个普通年，星期往后一天，365%7=1,星期0是星期7//因历史原因，1582年10月少10天，直接作为特例输出
	if (year <= 1582)//1年1月1日星期六 
		week = ((year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + 6) % 7;
	if (year >= 1583)//1583年1月1日星期六
		week = ((year - 1583) + (year - 1581) / 4 - (year - 1501) / 100 + (year - 1201) / 400 + 6) % 7;

	int month_week[12];
	for (int i = 0; i < 12; ++i)//确定每个月第一天
	{
		month_week[i] = 1 - week;
		week = (week + month[i]) % 7;
	}

	int trunk = (year % 10 + 10 - 3 - 1) % 10;
	int branch = (year % 12 + 12 - 3 - 1) % 12;

	calOut << '\n' << year << "年日历  " << trunk_and_branch[trunk] << trunk_and_branch[branch + 10] << "年\n";
	for (int i = 0; i < 4; ++i)//输出四季
	{
		calOut << table[i] << table[4];
		for (int j = 0; j < 6; ++j)//输出6行共三个月
		{
			for (int k = 0; k < 3; ++k)//输出三个星期共一行
			{
				for (int l = 0; l < 7; ++l)//输出一个星期
				{
					if (month_week[i * 3 + k] <= 0 || month_week[i * 3 + k] > month[i * 3 + k])
						calOut << "  ";
					else
					{
						calOut.width(2);
						calOut << month_week[i * 3 + k];
					}
					++month_week[i * 3 + k];
					calOut << ' ';
				}
				calOut << "  ";
			}
			calOut << "\n";
		}
		calOut << "\n";
		if (year == 1582 && i == 2)//1582年10 11 12月特殊处理
		{
			print1582_10_11_12(calOut);
			++i;
		}
	}
}
std::string Date::changeTime(std::string &str1, std::string &str2, bool is_add)//日期加减天数
{
	tm t1;
	time_t d1, d2;
	t1 = getTime(str1);
	d1 = mktime(&t1);
	if (d1 == -1)
		return "不支持该时间";
	d2 = std::stoi(str2) * 60 * 60 * 24;
	if (is_add)
		d1 += d2;
	else
	{
		d1 -= d2;
	}
	if (d1 < 0)
		return "1970年前";
	char t[32];
	std::strftime(t, 32, set.set["dateFormat"].c_str(), std::localtime(&d1));
	return std::string(t);
}
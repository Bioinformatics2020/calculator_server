#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include<string>
#include<vector>
#include"ToPostfix.h"

class myData
{
public:
	std::string num;
	int minus = 0;//0为正，1为负
	int point = 0;//小数位数
	myData() = default;
	myData(std::string str, int ok = 0);
	std::string to_str();
	void justify(myData &str);
	myData& operator+=(myData str);
	myData& operator-=(myData str);//使用了swap
	myData& operator*=(const myData &str);
	myData& operator/=(myData str);
	myData operator--(int)//后置减减
	{
		myData temp = (*this);
		myData a("1");
		(*this) -= a;
		return temp;
	}
	bool operator==(const char a)//只用到了a==0的情况
	{
		return (num.size() == 1 && num[0] == a) ? true : false;
	}
	bool operator!=(const char a)
	{
		return (num.size() == 1 && num[0] == a) ? false : true;
	}
	bool operator<(const myData &str)
	{
		return (num.size() - point == str.num.size() - str.point) ?
			(num.compare(str.num) < 0) : (num.size() - point < str.num.size() - str.point);
	}
};
myData operator*(const myData &num1, const int num2);

class bigNumber
{
public:
	std::string calculation(std::string &input);
private:

};

#endif // !BIGNUMBER_H
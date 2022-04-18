#ifndef PROGRAMMER_H
#define PROGRAMMER_H


#include<string>
#include"ToPostfix.h"

class programmer
{
public:
	int a = 10;
	int b = 10;
	std::string conversion(int a, int b, std::string number);//number a进制转b进制
	std::string calculation(std::string &input);
	std::string set(int a, int b);
};
#endif // !PROGRAMMER_H
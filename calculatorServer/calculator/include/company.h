#ifndef COMPANY_H
#define COMPANY_H

#include<string>
#include<sstream>
class Company
{
public:
	static std::string dataLength(char mode1, char mode2, double number);//数据长度
	static std::string angle(char mode1, char mode2, double number);//角度
	static std::string volume(char mode1, char mode2, double number);//容量/体积
	static std::string mass(char mode1, char mode2, double number);//质量
	static std::string length(char mode1, char mode2, double number);//长度
	static std::string area(char mode1, char mode2, double number);//面积
	static std::string time(char mode1, char mode2, double number);//时间
	static std::string temperature(char mode1, char mode2, double number);//温度
	static std::string energy(char mode1, char mode2, double number);//能量
	static std::string speed(char mode1, char mode2, double number);//速度
	static std::string power(char mode1, char mode2, double number);//功率
	static std::string pressure(char mode1, char mode2, double number);//压强
};

#endif
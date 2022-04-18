#ifndef COMMON_H
#define COMMON_H


#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>
#include"set.h"
#include"ToPostfix.h"

constexpr char PI[] = "3.141592653589793";
constexpr char E[]  = "2.718281828459045";
//a sqrt,b cbrt,c hypot,d loge,e log2,f log10,g sin,h cos,i tan,j arcsin,k arccos,l arctan,m p,n c
class Common
{
private:
	SetCommon &set;
	std::vector<std::string> preset;
	std::vector<std::string> funName = { "sqrt","cbrt","hypot","loge","log2","log10","sin","cos","tan","arcsin","arccos","arctan","p","c","abs","fac" };//a-p
	double proAns = 0;//preset[0]
	double myFun(std::string &input);//在此添加新函数，并在funName添加名称即可，若总数大于26需要改变Common与ToPostfix
	double funfactorial(int num);
	double funp(int a, int b);
public:
	Common(SetCommon &set);
	std::string calculation(std::string input);
	std::string batch(std::string fileNameIn, std::string fileNameOut);
	std::string changePreset(int index, std::string input);
};

#endif // !COMMON_H
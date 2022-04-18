#include "company.h"

constexpr double pi = 3.1415926535;
std::stringstream myCout;//输出流缓冲

std::string Company::dataLength(char mode1, char mode2, double number)//数据长度
{//标准为bit
	switch (mode1)
	{
	case 'k':
		number *= 1024;
	case 'j':
		number *= 1024;
	case 'i':
		number *= 1024;
	case 'h':
		number *= 1024;
	case 'g':
		number *= 1024;
	case 'f':
		number *= 1024;
	case 'e':
		number *= 1024;
	case 'd':
		number *= 1024; 
	case 'c':
		number *= 1024;
	case 'b':
		number *= 8;
	case 'a':
		;
		break;
	default:
		throw std::invalid_argument("mode1 error");
	}
	switch (mode2)
	{
	case 'k':
		number /= 1024;
	case 'j':
		number /= 1024;
	case 'i':
		number /= 1024;
	case 'h':
		number /= 1024;
	case 'g':
		number /= 1024;
	case 'f':
		number /= 1024;
	case 'e':
		number /= 1024;
	case 'd':
		number /= 1024;
	case 'c':
		number /= 1024;
	case 'b':
		number /= 8;
	case 'a':
		;
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::angle(char mode1, char mode2, double number)//角度
{//标准为度
	switch (mode1)
	{
	case 'a':
		number /= 60;
	case 'b':
		number /= 60;
	case 'c':
		break;
	case 'd':
		number *= pi / 180;
		break;
	case 'e':
		number *= 0.9;
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		break;
	case 'b':
		number *= 180 / pi;
		break;
	case 'c':
		number *= 10/9;
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::volume(char mode1, char mode2, double number)//容量/体积
{//标准为微升
	switch (mode1)
	{
	case 'a':
		number *= 1000;
	case 'b':
		number *= 1000;
	case 'c':
		number *= 1000;
	case 'd':
		break;
	case 'e':
		number *= 1.5;
	case 'f':
		number *= 1000 * 10;//公制茶匙转微升
		break;
	case 'g':
		number *= 42;
	case 'h':
		number *= 4;
	case 'i':
		number *= 2;
	case 'j':
		number *= 32;
	case 'k':
		number *= 3;
	case 'l':
		number *= 4.9289216 * 1000;//美制茶匙转微升
		break;
	case 'm':
		number *= 36;
	case 'n':
		number *= 4;
	case 'o':
		number *= 2;
	case 'p':
		number *= 32;
	case 'q':
		number *= 3;
	case 'r':
		number *= 5.9193906 * 1000;//英制茶匙转微升
		break;
	case 's':
		number *= 27;
	case 't':
		number *= 1728;
	case 'u':
		number *= 16.38706 * 1000;//立方英寸转微升
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 1000;
	case 'b':
		number /= 1000;
	case 'c':
		number /= 1000;
	case 'd':
		break;
	case 'e':
		number /= 1.5;
	case 'f':
		number /= (1000 * 10);//微升转公制茶匙
		break;
	case 'g':
		number /= 42;
	case 'h':
		number /= 4;
	case 'i':
		number /= 2;
	case 'j':
		number /= 32;
	case 'k':
		number /= 3;
	case 'l':
		number /= (4.9289216 * 1000);//微升转美制茶匙
		break;
	case 'm':
		number /= 36;
	case 'n':
		number /= 4;
	case 'o':
		number /= 2;
	case 'p':
		number /= 32;
	case 'q':
		number /= 3;
	case 'r':
		number /= (5.9193906 * 1000);//微升转英制茶匙
		break;
	case 's':
		number /= 27;
	case 't':
		number /= 1728;
	case 'u':
		number /= (16.38706 * 1000);//微升转立方英寸
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::mass(char mode1, char mode2, double number)//质量
{//标准为微克
	switch (mode1)
	{
	case 'a':
		number *= 1000;
	case 'b':
		number *= 1000;
	case 'c':
		number *= 1000;
	case 'd':
		number *= 1000;
	case 'e':
		break;//转微克
	case 'f':
		number *= 100;
	case 'g':
		number *= 10;
	case 'h':
		number *= 10;
	case 'i':
		number *= 5*1000*1000;//钱转微克
		break;
	case 'j':
		number *= 16;
	case 'k':
		number *= 28.349523*1000*1000;//盎司转微克
		break;
	case 'l':
		number *= 10;
	case 'm':
		number *= 0.02 * 1000 * 1000;//分(钻石)转微克
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 1000;
	case 'b':
		number /= 1000;
	case 'c':
		number /= 1000;
	case 'd':
		number /= 1000;
	case 'e':
		break;//微克
	case 'f':
		number /= 100;
	case 'g':
		number /= 10;
	case 'h':
		number /= 10;
	case 'i':
		number /= (5 * 1000 * 1000);//微克转钱
		break;
	case 'j':
		number /= 16;
	case 'k':
		number /= (28.349523 * 1000 * 1000);//微克转盎司
		break;
	case 'l':
		number /= 10;
	case 'm':
		number /= (0.02 * 1000 * 1000);//微克转分(钻石)
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::length(char mode1, char mode2, double number)//长度
{//标准为米
	switch (mode1)
	{
	case 'a':
		number /= 1000;
	case 'b':
		number /= 1000;
	case 'c':
		number /= 1000;
	case 'd':
		number /= 10;
	case 'e':
		number /= 10;
	case 'f':
		break;//米
	case 'g':
		number *= 1.852;
	case 'h':
		number *= 2;
	case 'i':
		number *= 150;
	case 'j':
		number *= 10;
	case 'k':
		number *= 10;
	case 'l':
		number *= 10;
	case 'm':
		number *= 10;
	case 'n':
		number *= 3/10/1000;//厘转米
		break;
	case 'o':
		number *= 1760;
	case 'p':
		number *= 3;
	case 'q':
		number *= 12;
	case 'r':
		number *= 0.0254;//英寸转米
		break;
	case 's':
		number *= 30856775814671916;//秒差距转米
		break;
	case 't':
		number *= 149597870700;//天文单位转米
		break;
	case 'u':
		number *= 9460730472580800;//光年转米
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number *= 1000;
	case 'b':
		number *= 1000;
	case 'c':
		number *= 1000;
	case 'd':
		number *= 10;
	case 'e':
		number *= 10;
	case 'f':
		break;//米
	case 'g':
		number /= 1.852;
	case 'h':
		number /= 2;
	case 'i':
		number /= 150;
	case 'j':
		number /= 10;
	case 'k':
		number /= 10;
	case 'l':
		number /= 10;
	case 'm':
		number /= 10;
	case 'n':
		number /= (3.0 / 10 / 1000);//厘转米
		break;
	case 'o':
		number /= 1760;
	case 'p':
		number /= 3;
	case 'q':
		number /= 12;
	case 'r':
		number /= 0.0254;//英寸转米
		break;
	case 's':
		number /= 30856775814671916;//秒差距转米
		break;
	case 't':
		number /= 149597870700;//天文单位转米
		break;
	case 'u':
		number /= 9460730472580800;//光年转米
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::area(char mode1, char mode2, double number)//面积
{//标准为平方毫米
	switch (mode1)
	{
	case 'a':
		number *= 100;
	case 'b':
		number *= 15;
	case 'c':
		number *= (2000/3);
	case 'd':
		number *= 10000;
	case 'e':
		number *= 100;
	case 'f':
		break;//平方毫米
	case 'g':
		number *= 640;
	case 'h':
		number *= 43560;
	case 'i':
		number *= 144;
	case 'j':
		number *= 645.16;//平方英寸转平方毫米
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 100;
	case 'b':
		number /= 15;
	case 'c':
		number /= (2000 / 3);
	case 'd':
		number /= 10000;
	case 'e':
		number /= 100;
	case 'f':
		break;//平方毫米
	case 'g':
		number /= 640;
	case 'h':
		number /= 43560;
	case 'i':
		number /= 144;
	case 'j':
		number /= 645.16;//平方毫米转平方英寸
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::time(char mode1, char mode2, double number)//时间
{//标准为秒
	switch (mode1)
	{
	case 'a':
		number *= 100;
	case 'b':
		number *= (365.25/7);
	case 'c':
		number *= 7;
	case 'd':
		number *= 24;
	case 'e':
		number *= 60;
	case 'f':
		number *= 60;
	case 'g':
		break;//秒
	case 'h':
		number *= 1000;
	case 'i':
		number *= 1000;
	case 'j':
		number /= 1000000000;
		break;//纳秒转秒
	case 'k':
		number *= 8;
	case 'l':
		number *= (15*60);
		break;//刻转秒
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 100;
	case 'b':
		number /= (365.25 / 7);
	case 'c':
		number /= 7;
	case 'd':
		number /= 24;
	case 'e':
		number /= 60;
	case 'f':
		number /= 60;
	case 'g':
		break;//秒
	case 'h':
		number /= 1000;
	case 'i':
		number /= 1000;
	case 'j':
		number *= 1000000000;
		break;//秒转纳秒
	case 'k':
		number /= 8;
	case 'l':
		number /= (15 * 60);
		break;//秒转刻
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::temperature(char mode1, char mode2, double number)//温度
{//标准为摄氏度
	switch (mode1)
	{
	case 'a':
		number = (number - 32) / 1.8;//华氏度转摄氏度
	case 'b':
		break;
	case 'c':
		number -= 273.15;//开尔文转摄氏度
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number = number * 1.8 + 32;//华氏度转摄氏度
	case 'b':
		break;
	case 'c':
		number += 273.15;//摄氏度转开尔文
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::energy(char mode1, char mode2, double number)//能量
{//标准为焦耳
	switch (mode1)
	{
	case 'a':
		number *= 3600000;
	case 'b':
		break;
	case 'c':
		number *= 4.1858518;
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 3600000;
	case 'b':
		break;
	case 'c':
		number /= 4.1858518;
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::speed(char mode1, char mode2, double number)//速度
{//标准为米每秒
	switch (mode1)
	{
	case 'a':
		number *= 340;
	case 'b':
		break;
	case 'c':
		number *= 1.852;
	case 'd':
		number /= 3.6;//公里每小时转米每秒
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 340;
	case 'b':
		break;
	case 'c':
		number /= 1.852;
	case 'd':
		number *= 3.6;//公里每小时转米每秒
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::power(char mode1, char mode2, double number)//功率
{//标准为瓦
	switch (mode1)
	{
	case 'a':
		number *= 1000;
	case 'b':
		break;
	case 'c':
		number *= 735.49875;//公制马力转瓦
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 1000;
	case 'b':
		break;
	case 'c':
		number /= 735.49875;//公制马力转瓦
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
std::string Company::pressure(char mode1, char mode2, double number)//压强
{//标准为千帕
	switch (mode1)
	{
	case 'a':
		number *= 1.01325;
	case 'b':
		number *= 100;
	case 'c':
		number *= 7.5;
	case 'd':
		break;
	default:
		throw std::invalid_argument("mode1 error");
		break;
	}
	switch (mode2)
	{
	case 'a':
		number /= 1.01325;
	case 'b':
		number /= 100;
	case 'c':
		number /= 7.5;
	case 'd':
		break;
	default:
		throw std::invalid_argument("mode2 error");
		break;
	}
	myCout.str("");
	myCout << number;
	return myCout.str();
}
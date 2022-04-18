#include "common.h"

Common::Common(SetCommon &set) :set(set)
{
	preset.resize(29);
	preset[1] = PI;
	preset[2] = E;
}

std::string Common::changePreset(int index, std::string input)
{
	if (index < 0 || index>25)
		throw std::invalid_argument("预设参数错误");
	preset[index + 3] = calculation(input);
	return "set OK";
}

std::string Common::batch(std::string fileNameIn, std::string fileNameOut)
{
	std::fstream in(fileNameIn, std::ios::in);
	if (!in.is_open())
		throw std::invalid_argument("无法打开输入文件");
	std::fstream out(fileNameOut, std::ios::out);
	if (!out.is_open())
		throw std::invalid_argument("无法打开输出文件");
	std::string input, output;
	while (in >> input)
	{
		try {
			output = calculation(input);
		}
		catch (std::invalid_argument &err)
		{
			output = err.what();
		}
		out << output << '\n';
	}
	return "batch OK";
}

double Common::funfactorial(int num)
{
	if (num == 0)
		return 1;
	else if (num < 0)
		throw std::invalid_argument("fun函数参数错误");
	double ans = 1;
	while (num)
		ans *= num--;
	return ans;
}

double Common::funp(int a, int b)
{
	return funfactorial(a) / funfactorial(a - b);
}

double Common::myFun(std::string & input)
{
	double ans;
	std::vector<double> num;
	int a = 2, b, i = 0;
	while (true)
	{
		b = input.find(',', a);
		if (b != - 1)//
		{
			num.push_back(std::stold(calculation(input.substr(a, b-a))));//12345
			a = b+1;
		}
		else
		{
			num.push_back(std::stold(calculation(input.substr(a, input.size()-1-a))));
			break;
		}
	}
	switch (input[0])
	{
	case 'a':
		if(num.size()!=1)
			throw std::invalid_argument("sqrt函数参数错误");
		ans = std::sqrt(num[0]);
		break;
	case 'b':
		if (num.size() != 1)
			throw std::invalid_argument("cbrt函数参数错误");
		ans = std::cbrt(num[0]);
		break;
	case 'c':
		if (num.size() != 2)
			throw std::invalid_argument("hypot函数参数错误");
		ans = std::hypot(num[0],num[1]);
		break;
	case 'd':
		if (num.size() != 1)
			throw std::invalid_argument("loge函数参数错误");
		ans = std::log(num[0]);
		break;
	case 'e':
		if (num.size() != 1)
			throw std::invalid_argument("log2函数参数错误");
		ans = std::log2(num[0]);
		break;
	case 'f':
		if (num.size() != 1)
			throw std::invalid_argument("log10函数参数错误");
		ans = std::log10(num[0]);
		break;
	case 'g':
		if (num.size() != 1)
			throw std::invalid_argument("sin函数参数错误");
		ans = std::sin(num[0]);
		break;
	case 'h':
		if (num.size() != 1)
			throw std::invalid_argument("cos函数参数错误");
		ans = std::cos(num[0]);
		break;
	case 'i':
		if (num.size() != 1)
			throw std::invalid_argument("tan函数参数错误");
		ans = std::tan(num[0]);
		break;
	case 'j':
		if (num.size() != 1)
			throw std::invalid_argument("arcsin函数参数错误");
		ans = std::asin(num[0]);
		break;
	case 'k':
		if (num.size() != 1)
			throw std::invalid_argument("arccos函数参数错误");
		ans = std::acos(num[0]);
		break;
	case 'l':
		if (num.size() != 1)
			throw std::invalid_argument("arctan函数参数错误");
		ans = std::atan(num[0]);
		break;
	case 'm':
		if (num.size() != 2)
			throw std::invalid_argument("p函数参数错误");
		ans = funfactorial(num[0]) / funfactorial(num[0] - num[1]);//排列
		break;
	case 'n':
		if (num.size() != 2 || num[0] < num[1] || num[1] <0)
			throw std::invalid_argument("c函数参数错误");
		ans = funfactorial(num[0]) / funfactorial(num[0] - num[1]) / funfactorial(num[1]);//组合
		break;
	case 'o':
		if (num.size() != 1)
			throw std::invalid_argument("c函数参数错误");
		ans = std::abs(num[0]);
		break;
	case 'p':
		if (num.size() != 1)
			throw std::invalid_argument("fun函数参数错误");
		ans = funfactorial(num[0]);
		break;
	default:
		throw std::invalid_argument("未定义函数");
		break;
	}
	return ans;
}

std::string Common::calculation(std::string input)
{
	std::string input_is_change;
	for (int i = 0; i < input.size(); )//预处理，确定预设值与函数
	{
		if (input[i] >= 'A' && input[i] <= 'Z')//处理预设值
		{
			input_is_change += preset[input[i] - 'A' + 3];
			++i;
		}
		else if (i + 2 < input.size() && input[i] == 'a' && input[i+1] == 'n'&& input[i+2] == 's')
		{
			input_is_change += preset[0];
			i += 3;
		}
		else if (i + 1 < input.size() && input[i] == 'p' && input[i+1] == 'i')
		{
			input_is_change += preset[1];
			i += 2;
		}
		else if (input[i] == 'e')
		{
			input_is_change += preset[2];
			++i;
		}
		else if(input[i] >= 'a' && input[i] <= 'z')//处理函数
		{
			int k = 0;
			for (int j = 0; j < funName.size(); ++j)//查找所有函数
			{
				int len = funName[j].size();
				if (i + len <= input.size())
				{
					k = 0;
					for (; k < len; ++k)
					{
						if (funName[j][k] != input[i + k])
							break;
					}
					if (k == len)
					{
						input_is_change += (j + 'a');//添加该函数所对应字母
						break;
					}
				}
			}
			if (k == 0)
				throw std::invalid_argument("函数名称错误");
			else
				i += k;
		}
		else
		{
			input_is_change += input[i];
			++i;
		}
	}
	
	ToPostfix p(input_is_change);
	std::vector<double> stackNum;
	for (auto i = p.postfix.begin(); i < p.postfix.end(); ++i)
	{
		long long a;
		if (i->symbol != 0)
		{
			if (stackNum.size() < 2)
				throw std::invalid_argument("无义的运算符");
			double tempNum(stackNum.back());
			stackNum.pop_back();
			switch (i->symbol)
			{
			case '+':
				stackNum.back() += tempNum;
				break;
			case '-':
				stackNum.back() -= tempNum;
				break;
			case '*':
				stackNum.back() *= tempNum;//预防溢出
				break;
			case '/':
				stackNum.back() /= tempNum;
				break;
			case '%':
				a = stackNum.back();
				a %= (long long)tempNum;
				stackNum.back() = a;
				break;
			case '^':
				stackNum.back() = std::pow(stackNum.back(),tempNum);
				break;
			default:
				throw std::invalid_argument("不支持的运算符");
				break;
			}
		}
		else
		{
			if(i->str[0]>='a'&&i->str[0] <= 'z')
				stackNum.push_back(myFun(i->str));
			else
				stackNum.push_back(std::stod(i->str));
		}
	}
	if (stackNum.size() != 1)
		throw std::invalid_argument("缺少运算符");
	std::ostringstream ss;
	ss << stackNum.back();
	preset[0] = ss.str();
	return ss.str();
}

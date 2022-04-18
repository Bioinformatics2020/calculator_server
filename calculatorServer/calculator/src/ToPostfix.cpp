#include "ToPostfix.h"

ToPostfix::ToPostfix(std::string input)
{
	//转后缀表达式
	std::vector<char> stackSymbol;
	int bracket = 0;//记录未成对左括号数
	for (auto i=input.begin(); i != input.end(); ++i)
	{
		//取出非双目运算符
		auto j = i;
		if (*j == '-') { ++j; }//负号特殊处理
		for (; j != input.end() &&(( *j>='0' && *j<='9')||*j=='.'); ++j) {};
		if (j != input.end() && *j >= 'a' && *j <= 'z')//需要将整个函数提取出来
		{
			int left = 1;//函数内左右括号相同
			j += 2;
			while (left && j != input.end())
			{
				if (*j == '(')
					++left;
				if (*j == ')')
					--left;
				++j;
			}
		}
		if (i + 1 == j && *i == '-')
			throw std::invalid_argument("未知的负号");
		if (i != j)//避免多个符号一起
		{
			postfix.push_back(PostfixNode(std::string(i, j)));
			i = j;
		}
		else if(*i == ')' && *(i-1) != ')')
		{
			throw std::invalid_argument("小括号错误");
		}

		//取出双目运算符
		if (i == input.end())break;
			//若优先级更高时，才需要入栈
		while (!stackSymbol.empty() && priority[*i] <= priority[stackSymbol.back()])
		{
			if (stackSymbol.back()!='(')//括号不必写入后缀表达式
			{
				postfix.push_back(PostfixNode(stackSymbol.back()));
				stackSymbol.pop_back();
			}
			else
			{	
				if (*i != ')')
					break;
				--bracket;
				stackSymbol.pop_back();
				break;//避免弹出多个左括号
			}
		}
		if(*i!=')')
			stackSymbol.push_back(*i);
		if (*i == '(')
			++bracket;
	}
	if (bracket)
		throw std::invalid_argument("括号未成对");
	while (!stackSymbol.empty())
	{
		postfix.push_back(PostfixNode(stackSymbol.back()));
		stackSymbol.pop_back();//这里不用避免弹出多个左括号
	}
}

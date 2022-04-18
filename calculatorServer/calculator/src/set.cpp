#include "set.h"

bool SetRoot::change(std::string str1, std::string str2, std::string mode)
{
	if (m[str1][str2].empty())//没有这一项
		return false;
	is_change = true;
	m[str1][str2] == mode;
	return true;
}

SetRoot::SetRoot()
{
	fSet.open(setName, std::ios::in);
	if (!fSet.is_open())
		throw std::logic_error("configuration file open error");
	std::string str1, str2, str3;
	while (fSet >> str1 >> str2 >> str3)
	{
		m[str1][str2] = str3;
	}
}

SetRoot::~SetRoot()
{
	if (is_change)
	{
		for (auto kk : m)
		{
			for (auto k : kk.second)
			{
				fSet << kk.first << ' ' << k.first << ' ' << k.second << '\n';
			}
		}
	}
}
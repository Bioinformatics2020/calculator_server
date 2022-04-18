#ifndef SET_H
#define SET_H
#include<unordered_map>
#include<vector>
#include<string>
#include<fstream>
#include<exception>

constexpr char setName[] = "mySet.set";

class SetRoot
{
private:
	std::fstream fSet;
	bool is_change = false;
protected:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m;
	bool change(std::string str1, std::string str2, std::string mode);
public:
	SetRoot();
	~SetRoot();
};

class SetDate :public virtual SetRoot
{
private:
	std::string str1 = "Date";
public:
	std::unordered_map<std::string, std::string>& set;

	SetDate() :set(m[str1]) { ; }
	bool setDateFormat(std::string mode){return change(str1, "dateFormat", mode);}
	bool setTimeFormat(std::string mode) { return change(str1, "timeFormat", mode); }
};

class SetHis :public virtual SetRoot
{
private:
	std::string str1 = "His";
public:
	std::unordered_map<std::string, std::string>& set;

	SetHis() :set(m[str1]) { 
		;
	}
	bool setDateFormat(std::string mode) { return change(str1, "dateFormat", mode); }
	bool setTimeFormat(std::string mode) { return change(str1, "timeFormat", mode); }
};

class SetCommon :public SetRoot
{
private:
	std::string str1 = "Common";
public:
	std::unordered_map<std::string, std::string>& set;
	SetCommon() :set(m[str1]) {
		;
	}
	
};

class Set :public SetDate, public SetHis,public SetCommon//包含所有set类
{
	;
};
#endif // !SET_H
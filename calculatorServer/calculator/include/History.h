#ifndef HISTORY_H
#define HISTORY_H

#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<string>
#include<ctime>
#include"set.h"
#include<fstream>

constexpr char fName[] = "history.log";

class History
{
private:
	bool needReWrite = false;
	bool is_read = false;
	int hisSize;
	std::string tFormat;
	std::fstream fHis;
	SetHis &set;
	std::vector<std::string> h;//历史记录

	void write(std::vector<std::string> &temp, int begin, bool is_app);
	void read();
public:
	History(SetHis &set);
	~History();
	const std::vector<std::string> & get();
	void push(std::string &function, std::string &input, std::string &ans);
};
#endif

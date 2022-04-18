#include "History.h"

void History::write(std::vector<std::string> &temp, int begin, bool is_app)
{
	fHis.close();
	if (is_app)
		fHis.open(fName, std::ios::app);
	else
		fHis.open(fName, std::ios::out);
	int end = temp.size();
	while (begin < end)
	{
		fHis << temp[begin++] << '\n';
	}
}

void History::read()
{
	std::vector<std::string> h0;//新的历史记录
	std::string line;
	while (getline(fHis, line))
	{
		h0.push_back(line);
	}
	is_read = true;
	h0.insert(h.end(), h.begin(), h.end());
	h.swap(h0);
}

History::History(SetHis &set) :set(set) {
	fHis.open(fName, std::ios::in);
	fHis.seekg(0, std::ios::end);
	hisSize = fHis.tellg();
	tFormat = set.set["dateFormat"] + " " + set.set["timeFormat"];
};

History::~History()
{
	if (hisSize >= stoi(set.set["sizeMax"]))
	{
		if (!is_read)
			read();
		write(h, h.size() / 2, false);
	}
	else if (needReWrite)
		write(h, 0, true);
	fHis.close();
}

const std::vector<std::string> & History::get()
{
	if (!is_read)
		read();
	return h;
}

void History::push(std::string &function, std::string &input, std::string &ans)
{
	std::time_t rev = std::time(nullptr);
	char t[32];
	std::strftime(t, 32, tFormat.c_str(), std::localtime(&rev));
	h.push_back(t);
	h.back() += " " + function + ":" + input + "=>" + ans;
	needReWrite = true;
}
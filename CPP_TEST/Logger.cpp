#include <iostream>
#include <vector>
#include <sstream>

using LogData = std::string;

class Logger {
public:
	Logger(){}
	friend class LogUnit;

	void print()
	{
		int i = 0;
		for (auto&& mitem : mLogData)
		{
			std::cout << i << " " << mitem << std::endl;
			i++;
		}
	}
private:
	std::vector<LogData> mLogData;
};

class LogUnit : public std::stringstream {
	Logger& log;
public :
	LogUnit(Logger& log) : log{log}{}
	void emit() {
		log.mLogData.emplace_back(std::move(this->str()));
		std::stringstream().swap(*this);
	}
	~LogUnit() {
		if (!this->str().empty()) emit();
	}
};

int main() {

	Logger log{};
	{
		LogUnit LogUnit{ log };

		LogUnit << "ABC" << std::endl;
		LogUnit.emit();

		LogUnit << "EFG" << " Hello~ "<< std::endl;
		LogUnit.emit();
	}

	log.print();


}
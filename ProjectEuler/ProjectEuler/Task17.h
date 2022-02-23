#pragma once
#include "TaskBase.h"

class Task17 : public TaskBase
{
public:
	Task17();
	~Task17();

	virtual void Run() override;

private:
	using numType = uint16;

	std::unordered_map<numType, std::string> mNumLiteralMap;

	const char * mHundredStr;
	const char * mThousandStr;

	const numType mMaxNum;

	void MakeLiteral(numType num, std::string & out);

	size_t CountLetter(const char* str);
};

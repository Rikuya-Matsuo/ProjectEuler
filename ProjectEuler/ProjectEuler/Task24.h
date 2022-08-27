#pragma once
#include "TaskBase.h"

class Task24 : public TaskBase
{
public:
	Task24();
	~Task24();

	void Run() override;

private:
	struct PermutationObject
	{
		std::string mStr;
		uint32 mScore;

		PermutationObject() {};
		PermutationObject(const char* str) : PermutationObject((std::string)str) {}
		PermutationObject(const std::string & str) { *this = str; }
		PermutationObject& operator=(const std::string & rhs);

		bool operator<(const PermutationObject& rhs) const { return this->mScore < rhs.mScore; }
		bool operator>(const PermutationObject& rhs) const { return this->mScore > rhs.mScore; }
		bool operator<=(const PermutationObject& rhs) const { return this->mScore <= rhs.mScore; }
		bool operator>=(const PermutationObject& rhs) const { return this->mScore >= rhs.mScore; }
	};

private:
	std::vector<PermutationObject> mPermutations;

	void makePermutationList(const std::string & sampleString);

	void makePermutationListImpl_threadBegin(const std::string & sampleString, std::vector<PermutationObject> & out, size_t index);
	void makePermutationListImpl(const std::string & sampleString, std::vector<PermutationObject> & out, std::list<size_t> & indexList);

	size_t calcLetterCombination(const std::string & sampleString) const;
};

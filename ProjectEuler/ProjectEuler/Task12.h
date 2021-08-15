#pragma once
#include "TaskBase.h"

class Task12 : public TaskBase
{
public:
	Task12();
	~Task12();

	void Run() override;

private:
	// i”Ô–Ú‚ÌOŠp”‚ğ‹‚ß‚é
	// OŠp”‚ÌŒö®‚ğ—p‚¢‚é
	size_t CalcTriangleNum(size_t i) { return (i * (i + 1)) / 2; }

	// –ñ”‚Ì”‚ğ‹‚ß‚é
	size_t CalcDivisorMass(size_t num);
};

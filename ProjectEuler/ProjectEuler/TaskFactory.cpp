#include "TaskFactory.h"
#include "TaskHeader.h"

TaskBase * TaskFactory::Create(uint16_t id)
{
	TaskBase * ret = nullptr;

	switch (id)
	{
	case 5:
		ret = new Task5();
		break;

	case 6:
		ret = new Task6();
		break;

	case 7:
		ret = new Task7();
		break;

	case 8:
		ret = new Task8();
		break;

	case 9:
		ret = new Task9();
		break;

	case 10:
		ret = new Task10();
		break;

	case 11:
		ret = new Task11();
		break;

	case 12:
		ret = new Task12();
		break;

	default:
		break;
	}

	return ret;
}

TaskFactory::TaskFactory()
{
}


TaskFactory::~TaskFactory()
{
}

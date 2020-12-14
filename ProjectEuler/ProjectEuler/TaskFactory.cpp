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

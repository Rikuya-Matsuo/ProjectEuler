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

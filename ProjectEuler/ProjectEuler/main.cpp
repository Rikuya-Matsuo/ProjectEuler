#include "TaskBase.h"
#include "TaskFactory.h"

int main(int argc, char ** argv)
{
	const uint16_t id = 7;
	TaskBase * task = TASK_FACTORY.Create(id);

	if (task)
	{
		task->Run();

		delete task;
	}

	return 0;
}

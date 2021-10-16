#include "TaskBase.h"
#include "TaskFactory.h"

int main(int argc, char ** argv)
{
	TaskBase * task = TASK_CREATE(13);

	if (task)
	{
		task->Run();

		delete task;
	}

	return 0;
}

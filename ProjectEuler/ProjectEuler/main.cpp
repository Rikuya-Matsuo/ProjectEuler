#include "TaskHeader.h"

#define TASK_ID 14

int main(int argc, char ** argv)
{
	TaskBase * task = TASK_CREATE(TASK_ID);

	if (task)
	{
		task->Run();

		delete task;
	}

	return 0;
}

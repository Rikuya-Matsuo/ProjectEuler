#include "TaskHeader.h"

#define TASK_ID 15

#define TO_STRING(x) #x
#define TO_STRING_AFTER_EXTEND(x) TO_STRING(x)

#define TASK_FILENAME_IMPL(id) Task##id##.h
#define TASK_FILENAME(id) TASK_FILENAME_IMPL(id)

#include TO_STRING_AFTER_EXTEND(TASK_FILENAME(TASK_ID))

int main(int argc, char ** argv)
{
	std::cout << "Current Task ID : " << TASK_ID << "\nStart run?(cancel : 0, run : natural number) : ";
	{
		size_t input;
		std::cin >> input;

		if (!input)
		{
			return 0;
		}
	}

	TaskBase * task = TASK_CREATE( TASK_ID );

	if (task)
	{
		task->Run();

		delete task;
	}

	return 0;
}

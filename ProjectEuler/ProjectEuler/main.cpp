#include "TaskHeader.h"

#define TASK_ID 15

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

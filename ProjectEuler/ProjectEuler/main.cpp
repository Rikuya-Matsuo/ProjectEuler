#include "TaskHeader.h"
#include "ProperDivisorManager.h"
#include "PrimeManager.h"

int main(int argc, char ** argv)
{
	// 起動タスク確認
	std::cout << "Current Task ID : " << TASK_ID << "\nStart run?(cancel : 0, run : natural number) : ";
	{
		size_t input;
		std::cin >> input;

		if (!input)
		{
			return 0;
		}
	}

	// タスククラス生成＆実行
	TaskBase * task = TASK_CREATE( TASK_ID );

	if (task)
	{
		task->Run();

		delete task;
	}

	// 各種ユーティリティマネージャのメモリ解放
	ProperDivisorManager::DeleteInstance();
	PrimeManager::DeleteInstance();

	return 0;
}

#pragma once

#define TASK_CREATE_IMPL(id) (new Task##id())
#define TASK_CREATE(id) TASK_CREATE_IMPL(id)

// タスクID。ここを変更して動かすタスクを変える。
#define TASK_ID 20

// タスクcppファイルのインクルード
#define TO_STRING_IMPL(x) #x
#define TO_STRING(x) TO_STRING_IMPL(x)

#define TASK_FILENAME_IMPL(id) Task##id##.h
#define TASK_FILENAME(id) TASK_FILENAME_IMPL(id)

#define INCLUDE_TASK_FILE TO_STRING(TASK_FILENAME(TASK_ID))

#include INCLUDE_TASK_FILE

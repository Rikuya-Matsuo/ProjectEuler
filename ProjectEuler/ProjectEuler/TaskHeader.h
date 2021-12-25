#pragma once

#define TASK_CREATE_IMPL(id) (new Task##id())
#define TASK_CREATE(id) TASK_CREATE_IMPL(id)

// タスクID。ここを変更して動かすタスクを変える。
#define TASK_ID 16

// タスクcppファイルのインクルード
#define TO_STRING(x) #x
#define TO_STRING_AFTER_EXTEND(x) TO_STRING(x)

#define TASK_FILENAME_IMPL(id) Task##id##.h
#define TASK_FILENAME(id) TASK_FILENAME_IMPL(id)

#include TO_STRING_AFTER_EXTEND(TASK_FILENAME(TASK_ID))

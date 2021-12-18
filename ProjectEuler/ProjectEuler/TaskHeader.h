#pragma once

#define TASK_CREATE_IMPL() new Task
#define TASK_CREATE(id) (TASK_CREATE_IMPL()id())

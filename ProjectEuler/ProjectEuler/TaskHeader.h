#pragma once

#define TASK_CREATE_IMPL(id) (new Task##id())
#define TASK_CREATE(id) TASK_CREATE_IMPL(id)

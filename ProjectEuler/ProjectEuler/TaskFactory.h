#pragma once
#include <cstdint>
#include "TaskHeader.h"

#define TASK_CREATE(id) (new Task##id())

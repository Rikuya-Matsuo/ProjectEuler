﻿#pragma once
#include "Task5.h"
#include "Task6.h"
#include "Task7.h"
#include "Task8.h"
#include "Task9.h"
#include "Task10.h"
#include "Task11.h"
#include "Task12.h"
#include "Task13.h"
#include "Task14.h"

#define TASK_CREATE_IMPL() new Task
#define TASK_CREATE(id) (TASK_CREATE_IMPL()id())

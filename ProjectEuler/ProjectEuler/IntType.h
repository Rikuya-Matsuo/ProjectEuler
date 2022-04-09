#pragma once
#include <cstdint>

#define USING_INT_TYPE(bitnum)\
using uint##bitnum = uint##bitnum##_t;\
using sint##bitnum = int##bitnum##_t

USING_INT_TYPE(8);
USING_INT_TYPE(16);
USING_INT_TYPE(32);

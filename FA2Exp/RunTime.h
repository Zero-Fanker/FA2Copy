#pragma once
#include <FA2PP.h>

class RunTime
{
public:


	using ptr_type = unsigned long;
	static void ResetMemoryContentAt(ptr_type addr, const void* content, size_t size, size_t offset = 0);









	RunTime();
	~RunTime();
};


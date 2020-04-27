#pragma once
#include "framework.h"

class ReaderWriterBin
{
public:
	void Write(const char* path, std::vector<int> offs);
	std::vector<int> Read(const char* path);
};
#pragma once

enum ArrayIndexResult
{
	AIR_Invalid = -1,
};

template<typename T>
void SafeDelete(T*& Ptr)
{
	if (Ptr != nullptr)
	{
		delete Ptr;
		Ptr = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& Ptr)
{
	if (Ptr != nullptr)
	{
		delete[] Ptr;
		Ptr = nullptr;
	}
}
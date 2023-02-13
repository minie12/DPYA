#pragma once

template<typename T>
class DPArray
{
public:
	DPArray()
		: MaxSize(2)
		, ArrayCount(0)
	{
		Arr = new T[MaxSize];
	}

	~DPArray()
	{
		delete[] Arr;
	}

	T& operator[] (int Index) const
	{
		if (!IsValidIndex(Index))
		{
			// Try
		}

		return Arr[Index];
	}

	inline void Add(const T& InData)
	{
		if (ArrayCount >= MaxSize)
		{
			// 배열 크기가 부족하면, 더 크게 생성하고 메모리 이동
			MaxSize = 2 * MaxSize;
			T* Temp = new T[MaxSize];
			for (unsigned int Index = 0; Index < ArrayCount; Index++)
			{
				Temp[Index] = Arr[Index];
			}
			delete[] Arr;
			Arr = Temp;
		}

		Arr[ArrayCount++] = InData;
	}

	int Find(const T& InData) const
	{
		for (unsigned int Index = 0; Index < ArrayCount; Index++)
		{
			if (Arr[Index] == InData)
				return Index;
		}

		return -1;
	}

	bool Contains(const T& InData) const
	{
		if (-1 != Find(InData))
			return true;

		return false;
	}

	void Insert(const T& InData, unsigned int InIndex)
	{
		if (!IsValidIndex(InIndex))
		{
			// NOT VALID
			return;
		}

		unsigned int Index = ArrayCount++;
		while (InIndex != Index)
		{
			Arr[Index] = Arr[Index - 1];
			Index--;
		}

		Arr[Index] = InData;
	}

	void Empty()
	{
		delete[] Arr;
		Arr = new T[MaxSize];
		ArrayCount = 0;
	}

	inline const T* Get() const { return Arr; }
	inline unsigned int Num() const { return ArrayCount; }
	inline bool IsEmpty() const { return 0 == ArrayCount; }
	inline bool IsValidIndex(unsigned int InIndex) const { return 0 <= InIndex && InIndex < ArrayCount; }

private:
	T* Arr;
	unsigned int MaxSize;
	unsigned int ArrayCount;
};
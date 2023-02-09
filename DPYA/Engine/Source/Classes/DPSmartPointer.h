#pragma once

#include "DPCore.h"

class RefCount
{
public:
	RefCount()
		: StrongCnt(1)
		, WeakCnt(0)
	{}

	inline void IncreaseStrong() { StrongCnt++; }
	inline void IncreaseWeak() { WeakCnt++; }

	bool DecreaseStrongAndCheck()
	{
		StrongCnt--;
		if (StrongCnt <= 0)
			return true;

		return false;
	}

	bool DestroyAll()
	{
		if (StrongCnt <= 0 && WeakCnt <= 0)
			return true;

		return false;
	}

	bool DecreaseWeakAndCheck()
	{
		WeakCnt--;
		if (StrongCnt <= 0 && WeakCnt <= 0)
			return true;

		return false;
	}

	inline bool IsExpired()
	{ 
		return StrongCnt <= 0;
	}

private:
	unsigned int StrongCnt;
	unsigned int WeakCnt;
};

template <typename T>
class DPSharedPtr
{
public:
	DPSharedPtr()
		: Ptr(nullptr)
		, Ref(nullptr)
	{ }
	
	~DPSharedPtr()
	{
		if (nullptr != Ref)
		{
			if (Ref->DecreaseStrongAndCheck())
			{
				SafeDelete(Ptr);
			}
			if (Ref->DestroyAll())
			{
				SafeDelete(Ref);
			}
		}
	}

	DPSharedPtr(const DPSharedPtr& InSPtr)
	{
		Ptr = InSPtr.Get();
		Ref = InSPtr.GetRef();
	}

	static DPSharedPtr MakeShareable(T* InPtr)
	{
		DPSharedPtr Temp;
		Temp.Ptr = InPtr;
 		Temp.Ref = new RefCount();

		return Temp;
	}

	DPSharedPtr& operator=(const DPSharedPtr& InSPtr)
	{
		Ptr = InSPtr.Get();
		Ref = InSPtr.GetRef();
		return *this;
	}

	inline T* operator->() { return Ptr; }
	inline T& operator*() { return *Ptr; }

	inline T* Get() const { return Ptr; }
	inline RefCount* GetRef() const { return Ref; }

private:
	T* Ptr;
	RefCount* Ref;
};
#pragma once

template<typename T>
class DPList
{
	struct Node
	{
		T Data;
		Node* Prev;
		Node* Next;

		Node(const T& InData)
			: Data(InData)
			, Prev(nullptr)
			, Next(nullptr)
		{ }
	};

public:
	DPList()
		: Root(nullptr)
		, Tail(nullptr)
		, ListCount(0)
	{}

	~DPList()
	{
		Node* Temp = Root;

		while (nullptr != Temp)
		{
			Node* NextTemp = Temp->Next;

			delete Temp;
			Temp = NextTemp;
		}
	}

	class iterator
	{
	public:
		iterator() : CurrentNode(nullptr) { }
		iterator(Node* InCurrent)
			: CurrentNode(InCurrent)
		{ }

		T operator*() const
		{
			return CurrentNode->Data;
		}

		iterator& operator++()
		{
			CurrentNode = CurrentNode->Next;
			return *this;
		}
		iterator& operator--()
		{
			CurrentNode = CurrentNode->Prev;
			return *this;
		}
		T& operator->() const
		{
			return CurrentNode->Data;
		}
		bool operator!=(const iterator& Other) const
		{
			return Other.CurrentNode != CurrentNode;
		}
		bool operator==(const iterator& Other) const
		{
			return Other.CurrentNode == CurrentNode;
		}

	private:
		Node* CurrentNode;
	};

	void PushBack(const T& InData)
	{
		Node* Temp = new Node(InData);

		if (nullptr == Root)
		{
			Root = Tail = Temp;
		}
		else
		{
			Tail->Next = Temp;
			Temp->Prev = Tail;

			Tail = Temp;
		}

		ListCount++;
	}

	void Clear()
	{
		Node* Temp = Root;
		while (nullptr != Temp)
		{
			Node* Del = Temp;
			Temp = Temp->Next;

			delete Del;
		}
	}

	iterator begin()
	{
		iterator Temp(Root);
		return Temp;
	}
	iterator end()
	{
		iterator Temp;
		return Temp;
	}
	inline T& Front() const { return Root->Data; }
	inline T& Back() const { return Tail->Data; }
	inline unsigned int Size() const { return ListCount; }
	inline bool IsEmpty() const { return ListCount <= 0; }

private:
	Node* Root;
	Node* Tail;
	unsigned int ListCount;
};
#pragma once

using std::cout;
using std::cin;
using std::endl;

template <typename T>
class StackNode
{
private:
	StackNode() : next_(NULL)
	{

	}
	~StackNode()
	{

	}

private:
	template <typename T>
	friend class StackClass;

private:
	T	data_;
	StackNode<T>* next_;
};

template <typename T>
class StackClass
{
public:
	StackClass()
	{
		begin_ = new Node;
		end_ = new Node;

		begin_->next_ = end_;

		size_ = 0;
	}
	~StackClass()
	{
		PNode node = begin_;
		while (node)
		{
			PNode next = node->next_;
			delete node;
			node = next;
		}
	}

private:
	typedef StackNode<T> Node;
	typedef StackNode<T>* PNode;

private:
	PNode begin_;
	PNode end_;
	int size_;

public:
	void Push(const T& data)
	{
		PNode node = new Node;
		node->data_ = data;

		PNode next = begin_->next_;

		node->next_ = next;
		begin_->next_ = node;

		++size_;
	}

	T Pop()
	{
		if (Empty())
			return 0;

		PNode next = begin_->next_;
		begin_->next_ = next->next_;

		T data = next->data_;

		delete next;

		--size_;

		return data;
	}

	T top()
	{
		if (Empty())
			return 0;

		return begin_->next_->data_;
	}

	bool Empty()
	{
		return size_ == 0;
	}
};


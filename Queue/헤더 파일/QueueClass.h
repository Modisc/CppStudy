#pragma once

using std::cout;
using std::cin;
using std::endl;

template <typename T>
class QueueNode
{
private:
	QueueNode() : next_(NULL), prev_(NULL)
	{

	}
	~QueueNode()
	{

	}

private:
	template <typename T>
	friend class QueueClass;

private:
	T	data_;
	QueueNode<T>* next_;
	QueueNode<T>* prev_;

};

template <typename T>
class QueueClass
{
public:
	QueueClass()
	{
		begin_ = new Node;
		end_ = new Node;

		begin_->next_ = end_;
		end_->prev_ = begin_;

		size_ = 0;

	}
	~QueueClass()
	{
		PNode node = begin_->next_;

		while (node)
		{
			PNode next = node->next_;
			delete node;
			node = next;
		}

		begin_->next_ = end_;
		end_->prev_ = begin_;

		size_ = 0;
	}

private:
	typedef QueueNode<T> Node;
	typedef QueueNode<T>* PNode;

private:
	PNode begin_;
	PNode end_;
	unsigned int size_;

public:
	void Push(const T& data)
	{
		PNode node = new Node;
		
		node->data_ = data;

		PNode prev = end_->prev_;

		prev->next_ = node;
		node->prev_ = prev;

		end_->prev_ = node;
		node->next_ = end_;

		++size_;
	}

	T Pop()
	{
		if (Empty())		return -1;

		PNode pop_node = begin_->next_;
		PNode next = pop_node->next_;
		
		begin_->next_ = next;
		next->prev_ = begin_;
		
		T data = pop_node->data_;

		delete pop_node;

		--size_;

		return data;

	}

	bool Empty()
	{
		return size_ == 0;
	}
};


template <typename T, int SIZE = 100>
class CircleQueue
{
public:
	CircleQueue()
	{
		size_ = 0;
		head_ = 0;
		tail_ = 0;
	}
	~CircleQueue()
	{

	}

private:
	T		 	 data_[SIZE];
	unsigned int size_;
	unsigned int head_;
	unsigned int tail_;

public:
	void Push(const T& data)
	{
		if (Full())	return;

		int idx = (tail_ + 1) % SIZE;

		data_[idx] = data;

		tail_ = idx;

		++size_;

	}

	T Pop()
	{
		if (Empty())		return -1;

		int idx = (head_ + 1) % SIZE;

		T data = data_[idx];
		
		head_ = idx;
		
		--size_;

		return data;
	}

	bool Full()
	{
		return size_ == SIZE;
	}

	bool Empty()
	{
		return size_ == 0;
	}
};



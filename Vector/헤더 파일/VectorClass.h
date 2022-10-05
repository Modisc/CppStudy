#pragma once

using std::cout;
using std::cin;
using std::endl;

template <typename T>
class VectorNode
{
private:
	VectorNode()
	{

	}
	~VectorNode()
	{

	}

private:
	template <typename T>
	friend class VectorClass;
	template <typename T>
	friend class VectorIterator;

private:
	T	data_;
	int index_;
};


template <typename T>
class VectorIterator
{
public:
	VectorIterator()
	{

	}
	~VectorIterator()
	{
		
	}

private:
	template <typename T>
	friend class VectorClass;

private:
	typedef VectorNode<T> Node;
	typedef VectorNode<T>* PNode;

private:
	PNode curr_node_;

public:
	bool operator ==(const VectorIterator<T>& iter)
	{
		return curr_node_ == iter.curr_node_;
	}

	bool operator !=(const VectorIterator<T>& iter)
	{
		return curr_node_ != iter.curr_node_;
	}

	bool operator <(const VectorIterator<T>& iter)
	{
		return curr_node_ < iter.curr_node_;
	}

	void operator ++()
	{
		//curr_node_->index_ = curr_node_->index_ + 1;
		curr_node_ = (curr_node_ + 1);
	}

	void operator --()
	{
		//curr_node_->index_ = curr_node_->index_ - 1;
		curr_node_ = (curr_node_ - 1);
	}

	T operator *()
	{
		//return curr_node_[curr_node_->index_].data_;
		return curr_node_->data_;
	}
	

};

template <typename T>
class VectorClass
{
public:
	VectorClass()
	{
		curr_size_ = 0;
		capacity_ = 2;

		array_ = new Node[capacity_ + 2]; // Begin, End ��� ���� 1���� �߰��ؼ� ��ü �뷮 + 2
	}
	// �����ڸ� ���ؼ��� Reserve �Լ��� ���� ������� ���� ������ �����ϵ��� ������.
	VectorClass(int size)
	{
		curr_size_ = 0;
		capacity_ = size;

		array_ = new Node[size + 2];
	}
	~VectorClass()
	{
		delete[] array_;
	}

private:
	typedef VectorNode<T> Node;
	typedef VectorNode<T>* PNode;

public:
	typedef VectorIterator<T> Iterator;

private:
	PNode array_;
	unsigned int curr_size_;
	unsigned int capacity_;

public:
	void PushBack(const T& data)
	{
		if (Full())
			resize(curr_size_ * 2);

		array_[curr_size_ + 1].data_ = data;
		// 1�� �ε����� �߰��ϱ�� ������ ���������� ù��° ���̹Ƿ�
		// 0�� �ε����� �νĽ�Ű�� ���� �ε��� ���� 0�� �־��� ����.
		array_[curr_size_ + 1].index_ = curr_size_;
		++curr_size_;
	}

	void resize(int size)
	{
		PNode arr = new Node[size + 2];
		
		// ������ 2�踸ŭ ������ ���� �Ҵ��ϰ� ������ �ִ�
		// ����� �����͸� ���� �Ҵ��� ������ �������ش�.
		// �迭�� 0�� �ε����� begin�� �ǹ��Ѵ�.
		// ���� �迭�� 1�� �ε������� ���� ����.
		memcpy(arr + 1, array_ + 1, sizeof(Node) * curr_size_);

		delete[] array_;

		array_ = arr;
		capacity_ = size;
	}

	void Clear()
	{
		delete[] array_;
		curr_size_ = 0;
		capacity_ = 2;
		array_ = new Node[capacity_ + 2];
	}

	bool Full()
	{
		return curr_size_ == capacity_;
	}

	bool Empty()
	{
		return curr_size_ == 0;
	}

	unsigned int GetSize() const
	{
		return curr_size_;
	}

	unsigned int GetCapacity() const
	{
		return capacity_;
	}

	T operator [](int idx)
	{
		return array_[idx + 1].data_;
	}

	void Reserve(int size)
	{
		delete[] array_;

		array_ = new Node[size + 2];

		capacity_ = size;
		curr_size_ = 0;
	}

	Iterator begin()
	{
		Iterator iter;
		iter.curr_node_ = &array_[1];
		return iter;
	}

	Iterator end()
	{
		Iterator iter;
		iter.curr_node_ = &array_[curr_size_ + 1];
		return iter;
	}

};


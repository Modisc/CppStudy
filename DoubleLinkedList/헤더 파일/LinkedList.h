#pragma once

template <typename T>
class ListNode
{
	// �����ڿ� �Ҹ��ڸ� private���� �ϰ� �Ǹ�
	// �ܺο��� ��ü ���� �� �Ҹ��� �Ұ����ϴ�.
	// �����ڴ� ��ü�� ������ �� �ڵ����� ȣ��Ǵ� �Լ��ε� private�� �ϸ�
	// ��ü�� �����ϸ鼭 ȣ��� ������ �Ұ����ϴ�. => ������ �Ұ����ϴ�.
	// �ܺο��� ListNode�� ������ �� ���� LinkedList Ŭ������ ���ؼ��� ���� �� �Ҹ��� �����ϵ��� ���� ��. �������� �ö󰣴�.
private:
	ListNode() : next_(NULL), prev_(NULL)
	{

	}
	~ListNode()
	{

	}

private:
	// friend : ģ���� ������ش�.
	// friend�� ������ Ŭ����(LinkedList)���� �� Ŭ����(ListNode)�� private�̳� protected�� ������ ����������.
	// �Ϲ� Ŭ������ friend class Ŭ������; �� ������ ������ ���ø� Ŭ������ ��� �Ʒ�ó�� template�� ������ �־�� �Ѵ�.
	template <typename T>
	friend class LinkedList;
	template <typename T>
	friend class ListIterator;
	template <typename T>
	friend class ListReverseIterator;

private:
	T	data_;
	ListNode<T>* next_;
	ListNode<T>* prev_;
};

// �ݺ��� Ŭ���� : ����Ʈ�� ��带 �ݺ��ؼ� ��ȸ�� �� �ִ� ����� �����ϴ� Ŭ����
template <typename T>
class ListIterator
{
public:
	ListIterator()
	{

	}
	~ListIterator()
	{

	}

private:
	template <typename T>
	friend class LinkedList;

private:
	typedef ListNode<T> Node;
	typedef ListNode<T>* PNode;

private:
	PNode curr_node_;

public:
	bool operator ==(const ListIterator<T>& iter)
	{
		return curr_node_ == iter.curr_node_;
	}
	
	bool operator !=(const ListIterator<T>& iter)
	{
		return curr_node_ != iter.curr_node_;
	}

	void operator ++()
	{
		curr_node_ = curr_node_->next_;
	}

	void operator --()
	{
		curr_node_ = curr_node_->prev_;
	}

	T operator *()
	{
		return curr_node_->data_;
	}
};

template <typename T>
class ListReverseIterator
{
public:
	ListReverseIterator()
	{

	}
	~ListReverseIterator()
	{

	}

private:
	template <typename T>
	friend class LinkedList;

private:
	typedef ListNode<T> Node;
	typedef ListNode<T>* PNode;

private:
	PNode curr_node_;

public:
	bool operator ==(const ListReverseIterator<T>& iter)
	{
		return curr_node_ == iter.curr_node_;
	}

	bool operator !=(const ListReverseIterator<T>& iter)
	{
		return curr_node_ != iter.curr_node_;
	}

	void operator ++()
	{
		curr_node_ = curr_node_->next_;
	}

	void operator --()
	{
		curr_node_ = curr_node_->prev_;
	}

	T operator *()
	{
		return curr_node_->data_;
	}
};

template <typename T>
class LinkedList
{
public:
	LinkedList()
	{
		begin_ = new Node;
		end_ = new Node;

		begin_->next_ = end_;
		end_->prev_ = begin_;
		size_ = 0;
	}
	~LinkedList()
	{
		clear();
		delete begin_;
		delete end_;
		size_ = 0;
	}

private:
	typedef ListNode<T> Node;
	typedef ListNode<T>* PNode;

public:
	typedef ListIterator<T> Iterator;
	typedef ListReverseIterator<T> ReverseIterator;

private:
	PNode		 begin_;
	PNode		 end_;
	unsigned int size_;

public:
	// const T& ������ �̳� T ������ �̳� �Ѵ� ���� ������ �ʴ´ٴ� ���� �Ȱ���. �׷��� ���� �鿡�� ���̰� ����.
	// ������� T ������ ���� �Ϲ� ������ �����ϸ� ����ü�� ���, ����ü�� ũ�Ⱑ 100����Ʈ��� �ϸ� 100����Ʈ�� ���� ��� ���簡 �ȴ�.
	// ������ ���۷����� ����ϸ� �ܼ��� �����ϴ� �� ���̹Ƿ� �޸� �Ҹ��� �ſ� ����. ��, �ξ� ������ ���� ����� �� �� �ִ�.
	// const�� ����� ������ �� �ȿ��� �Ű������� ���� �������� ���� ���̶�� ��Ÿ���� ���̴�.(������ + ������)
	// �ٸ� ����� �� �ڵ带 �� ���� �ְ�, ���߿� ���� �� �ڵ带 �ٽ� Ȯ���� �� �����ϱ� ���ϴ�.
	void insert_back(const T& data)
	{
		PNode node = new Node;
		node->data_ = data;

		// End�� ���� ��尡 ���� ������ ����̴�.
		PNode last = end_->prev_;
		
		last->next_ = node;
		node->prev_ = last;
		
		node->next_ = end_;
		end_->prev_ = node;

		++size_;
	}

	void insert_front(const T& data)
	{
		Node node = new Node;
		node->data_ = data;

		// Begin�� ���� ��尡 ���� ù��° ����̴�.
		PNode first = begin_->next_;

		begin_->next_ = node;
		node->prev_ = begin_;

		node->next_ = first;
		first->prev_ = node;

		++size_;
	}

	// ����Լ� �ڿ� const�� �ٿ��ָ� �� �Լ� ������ ��������� ���� ������ �� ����.
	unsigned int GetSize() const
	{
		return size_;
	}

	bool Empty() const
	{
		return size_ == 0;
	}

	void clear()
	{
		PNode node = begin_->next_;

		while (node != end_)
		{
			PNode next_node = node->next_;
			delete node;
			node = next_node;
		}

		begin_->next_ = end_;
		end_->prev_ = begin_;
		size_ = 0;
	}

	Iterator begin()
	{
		Iterator iter;
		iter.curr_node_ = begin_->next_;
		return iter;
	}

	Iterator end()
	{
		Iterator iter;
		iter.curr_node_ = end_;
		return iter;
	}

	ReverseIterator first()
	{
		ReverseIterator reiter;
		reiter.curr_node_ = begin_;
		return reiter;
	}

	ReverseIterator last()
	{
		ReverseIterator reiter;
		reiter.curr_node_ = end_->prev_;
		return reiter;
	}
};


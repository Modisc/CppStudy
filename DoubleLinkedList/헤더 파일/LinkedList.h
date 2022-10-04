#pragma once

template <typename T>
class ListNode
{
	// 생성자와 소멸자를 private으로 하게 되면
	// 외부에서 객체 생성 및 소멸이 불가능하다.
	// 생성자는 객체를 생성할 때 자동으로 호출되는 함수인데 private로 하면
	// 객체를 생성하면서 호출시 접근이 불가능하다. => 생성이 불가능하다.
	// 외부에선 ListNode를 생성할 수 없고 LinkedList 클래스를 통해서만 생성 및 소멸이 가능하도록 만들 것. 안전성이 올라간다.
private:
	ListNode() : next_(NULL), prev_(NULL)
	{

	}
	~ListNode()
	{

	}

private:
	// friend : 친구로 만들어준다.
	// friend로 지정된 클래스(LinkedList)에서 이 클래스(ListNode)의 private이나 protected에 접근이 가능해진다.
	// 일반 클래스는 friend class 클래스명; 만 적으면 되지만 템플릿 클래스의 경우 아래처럼 template을 지정해 주어야 한다.
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

// 반복자 클래스 : 리스트의 노드를 반복해서 순회할 수 있는 기능을 제공하는 클래스
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
	// const T& 변수명 이나 T 변수명 이나 둘다 값이 변하지 않는다는 점은 똑같다. 그러나 성능 면에서 차이가 난다.
	// 예를들어 T 변수명 으로 일반 변수를 선언하면 구조체의 경우, 구조체의 크기가 100바이트라고 하면 100바이트의 값이 모두 복사가 된다.
	// 하지만 레퍼런스를 사용하면 단순히 참조하는 것 뿐이므로 메모리 소모값이 매우 적다. 즉, 훨씬 빠르게 값을 끌어다 쓸 수 있다.
	// const를 사용한 이유는 이 안에서 매개변수의 값은 변경하지 않을 것이라고 나타내는 것이다.(안전성 + 가독성)
	// 다른 사람이 내 코드를 볼 수도 있고, 나중에 내가 내 코드를 다시 확인할 때 이해하기 편하다.
	void insert_back(const T& data)
	{
		PNode node = new Node;
		node->data_ = data;

		// End의 이전 노드가 가장 마지막 노드이다.
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

		// Begin의 다음 노드가 가장 첫번째 노드이다.
		PNode first = begin_->next_;

		begin_->next_ = node;
		node->prev_ = begin_;

		node->next_ = first;
		first->prev_ = node;

		++size_;
	}

	// 멤버함수 뒤에 const를 붙여주면 이 함수 내에서 멤버변수의 값을 변경할 수 없다.
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


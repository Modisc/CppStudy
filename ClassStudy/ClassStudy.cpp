#include <iostream>
#include <functional>

using std::cout;
using std::cin;
using std::endl;


/*
클래스, 상속, 다형성, 가상함수 등에 공부하기 위한 클래스입니다.
특별한 구현이 아닌 강의를 보면서 따라 작성하고 헷갈리는 부분을 바로바로 테스트 하기 위한 소스입니다.
*/

class Parent
{
public:
	Parent()
	{
		cout << "Parent 생성자 출력" << endl;
	}
	virtual ~Parent()
	{
		cout << "Parent 소멸자 출력" << endl;
	}
	
public:
	int pub_a_;
protected:
	int pro_b_;
private:
	int pri_c_;

public:
	virtual void Output()
	{
		cout << "Parent Output Func" << endl;
	}

	// 순수가상함수 : 가상함수 뒤에 = 0을 붙여주면 해당 가상함수는
	// 순수가상함수가 된다. 순수가상함수는 구현부분이 존재하지 않는다.
	// 순수가상함수를 가지고 있는 클래스를 추상클래스라고 부른다.
	virtual void OutputPure() = 0;
};

class Child1 : public Parent
{
public:
	Child1()
	{
		pro_b_ = 300;
		// pri_c_ = 400;  private 이어서 접근 불가.
		cout << "Child1 생성자 출력" << endl;
	}
	// ChildChild 클래스의 부모 클래스이므로.
	virtual ~Child1()
	{
		cout << "Child1 소멸자 출력" << endl;
	}

protected:
	int d_;

public:
	void Child1Output()
	{
		cout << "Child1 Child1Output Function" << endl;
	}

	void Output()
	{
		Parent::Output(); // 이렇게 해주면 자식이 부모의 Output함수 호출하는 것.
		cout << "Child1 Output Func" << endl;
	}

	void OutputPure()
	{

	}
};

class Child2 : private Parent
{
public:
	Child2()
	{
		pub_a_ = 1000;
		pro_b_ = 2000;
		// pri_c_ = 3000; private 이어서 접근 불가.
		cout << "Child2 생성자 출력" << endl;
	}
	~Child2()
	{
		cout << "Child2 소멸자 출력" << endl;
	}

public:
	int f_;

private:
	int d_;

public:
	virtual void OutputPure()
	{

	}
};

class ChildChild : public Child1
{
public:
	ChildChild()
	{
		d_ = 500;
		cout << "ChildChild 생성자 출력" << endl;
	}
	~ChildChild()
	{
		cout << "ChildChild 소멸자 출력" << endl;
	}

private:
	int e_;
};

int main()
{
//	Parent parent;
//	Child1 child10;
//	Child2 child2;
//	ChildChild childchild;
//
//	parent.pub_a_ = 100;
//	child1.pub_a_ = 200;
//	//child2.pub_a_ = 600; // Parent 클래스를 private으로 상속받기 때문에 접근할 수 없다.
//	child2.f_ = 700; // Parent 클래스와 무관한 child2 자체 멤버 변수들은 접근 제한자에 따라 접근할 수 있다.

//	 parent.Output(); // 가능
//	 child1.Output(); // 가능
	// child2.Output(); 불가능

	// Child1 클래스는 Parent 클래스를 상속받고 있다.
	// new Child1을 하게되면 Child1 객체 하나를 생성해주고
	// 그 메모리 주소를 반환한다.
	// 그러나 아래에서는 Parent* 타입 변수에 이 반환된 주소를 대입해주고 있다.
	// 부모 포인터 타입에 Child1 객체의 메모리 주소를 넣을 수 있는 이유는
	// 상속관계에 있기 때문이다. 자식 메모리 주소를 부모 포인터 타입으로
	// 형변환 한 것이다. 이런 형변환을 업캐스팅이라 한다.
	// 자식 -> 부모 타입 형변환 : 업캐스팅
	// 부모 -> 자식 타입 형변환 : 다운캐스팅
	Parent* parent1 = new Child1;
	// Parent* parent2 = new Child2; // private으로 상속받기 때문에 이렇게 하는게 불가능함.
	//Parent* parent3 = new ChildChild;
	
	// 다형성의 장점.
	// 이런식으로 부모 클래스 배열 하나로 자식 클래스 모두 관리할 수 있음.
	// 게임에서도 플레이어, 적 등의 다양한 클래스들의 부모 클래스가 같다면
	// 해당 부모 클래스 타입 하나로 플레이어, 적 모두 관리가 가능하다.
	// 관리상의 매우 큰 장점이다.
	/*Parent* parent_arr[2] = {};
	parent_arr[0] = new Child1;
	parent_arr[1] = new ChildChild;*/

	// 가상함수 사용법을 몰라서 테스트 겸 virtual 키워드를 부모 클래스의 함수에만 붙이고 자식 클래스엔 붙이지 않았음.
	// 이렇게 했을 때도 Child1의 Output이 출력됨. => parent1이 Child1 타입이기 때문에.
	// 만약 Child1 클래스에 Output이 재정의 되어있지 않다면 parent 클래스의 Output이 출력됐을 것임.
	// Child1 클래스의 Output함수 주석처리 하고 테스트해보자.
	parent1->Output();

	parent1->Parent::Output(); // 이렇게 호출하면 부모(Parent)의 Output 호출할 수 있음.

	// 이렇게 하면 당연히 parent 클래스의 Output이 출력됨
	// 현재 Parent 클래스는 순수가상함수를 멤버로 가지기 때문에 추상클래스다.
	// 따라서 객체를 가질 수 없다.
	/*Parent parent2;
	parent2.Output();*/

	// Parent 클래스의 순수가상함수를 Child2 클래스에서 재정의하지 않았기 때문에
	// 오류가 발생한다. ( Child2 클래스에 순수가상함수를 재정의 해주면 문제가 해결된다.)
	 Child2 child2;

	// 아래 두 클래스는 모두 Parent 클래스를 상속받고 있다.
	// 그러므로 Parent를 두 타입 모두 다운캐스팅 가능하다.
	// 그런데 여기서 parent 변수는 Child1로 할당한 객체이다.
	// 이 객체를 Child1 타입으로 다운캐스팅하게 되면
	// 이 객체를 사용할 때 문제가 발생할 수 있다.
	// 애초에 생성한 객체가 아닌 다른 타입으로 변환이 됐기 때문이다.
	// 다운캐스팅 사용시 주의.
	// Child1* child1 = (Child1*)parent1; // 다운캐스팅. 이건 가능
	// Child2* child2 = (Child2*)parent1; // 이건 위험할 수 있다.

	// Child 클래스에 있는 ChildOutput 함수에 접근할 수 없다.
	// 왜냐하면 Parent는 Parent 포인터 타입이기 때문에 자식의 멤버에
	// 접근이 불가능하기 때문이다. 만약 접근하고 싶다면
	// 형변환 해야한다. 매번 이렇게 형변환 하는 것은 매우 불합리하다.
	// 이런 문제 해결을 위해 가상함수 사용한다.
	//((Child1*)parent1)->Child1Output();

	// 현재 delete를 하게되면 Child 소멸자 -> Parent 소멸자가 호출되어야 하는데
	// 지금은 Parent 소멸자만 호출된다.
	// 왜냐하면 근본적으로 Parent는 Parent 포인터 타입이다.
	// 따라서 Child 소멸자가 호출될 수 없다.
	// 다형성으로 할당될 수는 있지만 근본적으로 Parent 포인터 타입이다.
	// 생성에선 new Child1 을 하므로 제대로 생성자가 호출되지만, 소멸자에선 이러한 문제가 발생한다.
	// 따라서 소멸자를 가상함수로 만들어준다.
	// 여기서 가상함수 테이블을 참조하면 parent는 child1 타입으로 변환되어 있으므로
	// child1 소멸자가 등록되어 있을 것이다. 따라서 child1 소멸자가 호출되고, 자동으로 부모 클래스인
	// parent 클래스 소멸자도 호출이 되는 것이다.
	
	delete parent1;
	
	// delete parent1 대신 parent1을 다운캐스팅한 child1의 소멸자를 호출한다면 parent 소멸자까지 정상적으로 호출된다.
	//delete child1;
	//delete parent3;

	// 위와 같이 다형성 사용시 소멸자에서 자식 클래스 소멸자가 제대로 호출되지 않는다는 문제점이 생긴다.
	// parent_arr 같이 배열에 다양한 타입의 자식 클래스를 각각 할당해놓을 경우 문제가 심각해진다.
	// 하나하나 캐스팅 해줘야 해결이 된다. 하지만 배열 숫자가 1000개를 넘을 정도로 많아진다면?
	/*for (int i = 0; i < 2; i++)
	{
		delete parent_arr[i];
	}*/

	return 0;
}
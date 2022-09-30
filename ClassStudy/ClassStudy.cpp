#include <iostream>
#include <functional>

using std::cout;
using std::cin;
using std::endl;


/*
Ŭ����, ���, ������, �����Լ� � �����ϱ� ���� Ŭ�����Դϴ�.
Ư���� ������ �ƴ� ���Ǹ� ���鼭 ���� �ۼ��ϰ� �򰥸��� �κ��� �ٷιٷ� �׽�Ʈ �ϱ� ���� �ҽ��Դϴ�.
*/

class Parent
{
public:
	Parent()
	{
		cout << "Parent ������ ���" << endl;
	}
	virtual ~Parent()
	{
		cout << "Parent �Ҹ��� ���" << endl;
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

	// ���������Լ� : �����Լ� �ڿ� = 0�� �ٿ��ָ� �ش� �����Լ���
	// ���������Լ��� �ȴ�. ���������Լ��� �����κ��� �������� �ʴ´�.
	// ���������Լ��� ������ �ִ� Ŭ������ �߻�Ŭ������� �θ���.
	virtual void OutputPure() = 0;
};

class Child1 : public Parent
{
public:
	Child1()
	{
		pro_b_ = 300;
		// pri_c_ = 400;  private �̾ ���� �Ұ�.
		cout << "Child1 ������ ���" << endl;
	}
	// ChildChild Ŭ������ �θ� Ŭ�����̹Ƿ�.
	virtual ~Child1()
	{
		cout << "Child1 �Ҹ��� ���" << endl;
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
		Parent::Output(); // �̷��� ���ָ� �ڽ��� �θ��� Output�Լ� ȣ���ϴ� ��.
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
		// pri_c_ = 3000; private �̾ ���� �Ұ�.
		cout << "Child2 ������ ���" << endl;
	}
	~Child2()
	{
		cout << "Child2 �Ҹ��� ���" << endl;
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
		cout << "ChildChild ������ ���" << endl;
	}
	~ChildChild()
	{
		cout << "ChildChild �Ҹ��� ���" << endl;
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
//	//child2.pub_a_ = 600; // Parent Ŭ������ private���� ��ӹޱ� ������ ������ �� ����.
//	child2.f_ = 700; // Parent Ŭ������ ������ child2 ��ü ��� �������� ���� �����ڿ� ���� ������ �� �ִ�.

//	 parent.Output(); // ����
//	 child1.Output(); // ����
	// child2.Output(); �Ұ���

	// Child1 Ŭ������ Parent Ŭ������ ��ӹް� �ִ�.
	// new Child1�� �ϰԵǸ� Child1 ��ü �ϳ��� �������ְ�
	// �� �޸� �ּҸ� ��ȯ�Ѵ�.
	// �׷��� �Ʒ������� Parent* Ÿ�� ������ �� ��ȯ�� �ּҸ� �������ְ� �ִ�.
	// �θ� ������ Ÿ�Կ� Child1 ��ü�� �޸� �ּҸ� ���� �� �ִ� ������
	// ��Ӱ��迡 �ֱ� �����̴�. �ڽ� �޸� �ּҸ� �θ� ������ Ÿ������
	// ����ȯ �� ���̴�. �̷� ����ȯ�� ��ĳ�����̶� �Ѵ�.
	// �ڽ� -> �θ� Ÿ�� ����ȯ : ��ĳ����
	// �θ� -> �ڽ� Ÿ�� ����ȯ : �ٿ�ĳ����
	Parent* parent1 = new Child1;
	// Parent* parent2 = new Child2; // private���� ��ӹޱ� ������ �̷��� �ϴ°� �Ұ�����.
	//Parent* parent3 = new ChildChild;
	
	// �������� ����.
	// �̷������� �θ� Ŭ���� �迭 �ϳ��� �ڽ� Ŭ���� ��� ������ �� ����.
	// ���ӿ����� �÷��̾�, �� ���� �پ��� Ŭ�������� �θ� Ŭ������ ���ٸ�
	// �ش� �θ� Ŭ���� Ÿ�� �ϳ��� �÷��̾�, �� ��� ������ �����ϴ�.
	// �������� �ſ� ū �����̴�.
	/*Parent* parent_arr[2] = {};
	parent_arr[0] = new Child1;
	parent_arr[1] = new ChildChild;*/

	// �����Լ� ������ ���� �׽�Ʈ �� virtual Ű���带 �θ� Ŭ������ �Լ����� ���̰� �ڽ� Ŭ������ ������ �ʾ���.
	// �̷��� ���� ���� Child1�� Output�� ��µ�. => parent1�� Child1 Ÿ���̱� ������.
	// ���� Child1 Ŭ������ Output�� ������ �Ǿ����� �ʴٸ� parent Ŭ������ Output�� ��µ��� ����.
	// Child1 Ŭ������ Output�Լ� �ּ�ó�� �ϰ� �׽�Ʈ�غ���.
	parent1->Output();

	parent1->Parent::Output(); // �̷��� ȣ���ϸ� �θ�(Parent)�� Output ȣ���� �� ����.

	// �̷��� �ϸ� �翬�� parent Ŭ������ Output�� ��µ�
	// ���� Parent Ŭ������ ���������Լ��� ����� ������ ������ �߻�Ŭ������.
	// ���� ��ü�� ���� �� ����.
	/*Parent parent2;
	parent2.Output();*/

	// Parent Ŭ������ ���������Լ��� Child2 Ŭ�������� ���������� �ʾұ� ������
	// ������ �߻��Ѵ�. ( Child2 Ŭ������ ���������Լ��� ������ ���ָ� ������ �ذ�ȴ�.)
	 Child2 child2;

	// �Ʒ� �� Ŭ������ ��� Parent Ŭ������ ��ӹް� �ִ�.
	// �׷��Ƿ� Parent�� �� Ÿ�� ��� �ٿ�ĳ���� �����ϴ�.
	// �׷��� ���⼭ parent ������ Child1�� �Ҵ��� ��ü�̴�.
	// �� ��ü�� Child1 Ÿ������ �ٿ�ĳ�����ϰ� �Ǹ�
	// �� ��ü�� ����� �� ������ �߻��� �� �ִ�.
	// ���ʿ� ������ ��ü�� �ƴ� �ٸ� Ÿ������ ��ȯ�� �Ʊ� �����̴�.
	// �ٿ�ĳ���� ���� ����.
	// Child1* child1 = (Child1*)parent1; // �ٿ�ĳ����. �̰� ����
	// Child2* child2 = (Child2*)parent1; // �̰� ������ �� �ִ�.

	// Child Ŭ������ �ִ� ChildOutput �Լ��� ������ �� ����.
	// �ֳ��ϸ� Parent�� Parent ������ Ÿ���̱� ������ �ڽ��� �����
	// ������ �Ұ����ϱ� �����̴�. ���� �����ϰ� �ʹٸ�
	// ����ȯ �ؾ��Ѵ�. �Ź� �̷��� ����ȯ �ϴ� ���� �ſ� ���ո��ϴ�.
	// �̷� ���� �ذ��� ���� �����Լ� ����Ѵ�.
	//((Child1*)parent1)->Child1Output();

	// ���� delete�� �ϰԵǸ� Child �Ҹ��� -> Parent �Ҹ��ڰ� ȣ��Ǿ�� �ϴµ�
	// ������ Parent �Ҹ��ڸ� ȣ��ȴ�.
	// �ֳ��ϸ� �ٺ������� Parent�� Parent ������ Ÿ���̴�.
	// ���� Child �Ҹ��ڰ� ȣ��� �� ����.
	// ���������� �Ҵ�� ���� ������ �ٺ������� Parent ������ Ÿ���̴�.
	// �������� new Child1 �� �ϹǷ� ����� �����ڰ� ȣ�������, �Ҹ��ڿ��� �̷��� ������ �߻��Ѵ�.
	// ���� �Ҹ��ڸ� �����Լ��� ������ش�.
	// ���⼭ �����Լ� ���̺��� �����ϸ� parent�� child1 Ÿ������ ��ȯ�Ǿ� �����Ƿ�
	// child1 �Ҹ��ڰ� ��ϵǾ� ���� ���̴�. ���� child1 �Ҹ��ڰ� ȣ��ǰ�, �ڵ����� �θ� Ŭ������
	// parent Ŭ���� �Ҹ��ڵ� ȣ���� �Ǵ� ���̴�.
	
	delete parent1;
	
	// delete parent1 ��� parent1�� �ٿ�ĳ������ child1�� �Ҹ��ڸ� ȣ���Ѵٸ� parent �Ҹ��ڱ��� ���������� ȣ��ȴ�.
	//delete child1;
	//delete parent3;

	// ���� ���� ������ ���� �Ҹ��ڿ��� �ڽ� Ŭ���� �Ҹ��ڰ� ����� ȣ����� �ʴ´ٴ� �������� �����.
	// parent_arr ���� �迭�� �پ��� Ÿ���� �ڽ� Ŭ������ ���� �Ҵ��س��� ��� ������ �ɰ�������.
	// �ϳ��ϳ� ĳ���� ����� �ذ��� �ȴ�. ������ �迭 ���ڰ� 1000���� ���� ������ �������ٸ�?
	/*for (int i = 0; i < 2; i++)
	{
		delete parent_arr[i];
	}*/

	return 0;
}
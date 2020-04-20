#include<iostream>
using namespace std;

class A
{
	int a;
public:
	A(int ia) :a(ia)
	{

	}
	virtual void show()
	{
		std::cout << a<<"\n";
	}
};

class B :public A
{
	int b;
public:
	B(int ib) :A(0)
	{
		b = ib;
	}
	virtual void show()
	{
		std::cout << b << "\n";
	}
};

class C :public A
{
	int c;
public:
	C(int ic) :A(0)
	{
		c = ic;
	}
	virtual void show()
	{
		std::cout << c << "\n";
	}
};


int main()
{
	A* p1 = new A(5);

	A* p3;

	B* p2 = new B(6);

	p1->show();

	std::cout << "\n";

	p1 = p2;

	p1->show();


	C* p4 = new C(7);

	p1 = p4; //Here C's Object has pointer of the A

	p1->show();

	//Error as we tried to cast C into B's pointer
	if (p2 = dynamic_cast<B*>(p1))
	{
		std::cout << "sucess !!\n";
	}
	else
	{
		std::cout << "Fail !!\n";
	}

	//Here C's pointer is cast into A's pointer and then A's pointer casted into A's another
	//pointer
	//sucess as we tried to cast C into A's pointer
	if (p3 = dynamic_cast<A*>(p1))
	{
		std::cout << "sucess !!\n";
	}
	else
	{
		std::cout << "Fail !!\n";
	}


}
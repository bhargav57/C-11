#include<iostream>

using namespace std;
class b
{
	int a[10];
};

class b1 : public b
{

};

class b2 : public b
{

};

class derived : public b1, public b2
{

};

class A
{
public:
	int* p;
	A(int i)
	{
		p = new int(i);
	}
	~A()
	{
		delete p;
	}
	void pv()
	{
		std::cout << "the value is" << *p;
	}
};

void myFunc(A x)
{
	std::cout << "i am in myfunc \n";
}

class twod
{
	int dim1;
	int dim2;
public:
	twod() { dim1 = 5; dim2 = 6; }
	virtual void operator<<(ostream& rhs);
	
};
void twod::operator<<(ostream& rhs)
{
	rhs << this->dim1 << this->dim2 << "\n";
}


class threed :public twod
{
	int dim3;
public:
	threed() { dim3 = 7; }
	virtual void operator<<(ostream& rhs);
};

void threed::operator<<(ostream& rhs)
{
	twod::operator<<(rhs);
	rhs << this->dim3<<"\n";
}

int main()
{
	derived d;
	std::cout << sizeof(b)<<"\n";
	std::cout << sizeof(b1) << "\n";
	std::cout << sizeof(b2) << "\n";
	std::cout << sizeof(derived) << "\n";
	
	//std::cout << 25u - 50;
	/*A b = 20;
	myFunc(b);
	b.pv();*/

	/*int a, * pa, &ra;
	pa = &a;
	ra = a;
	cout << "a=" << a << "*pa" << *pa << "ra" << ra;*/

	//twod obj1;
	//obj1 << cout;

	//threed obj2;
	//obj2 << cout;
}
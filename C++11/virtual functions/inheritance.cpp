#include<iostream>
#include<vector>
using namespace std;

class A
{
	virtual void f2()
	{
		cout << "from base\n";
	}
	
public:
	void f1()
	{
		f2();
	}
};

class B : public A
{
	int _a;
public:
	void f2()
	{
		cout << "from derived\n";
		_a = 10;
		cout << "vaue of _a" << _a;
	}
};




int main()
{
	
	B d;
	d.f1();

	A b;
	b.f1();
}
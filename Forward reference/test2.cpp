#include<iostream>
#include<vector>
using namespace std;

class myKlass
{
	int i;
	float f;
public:
	myKlass(int ii,float ff):i(ii),f(ff)
	{
		std::cout << "Paramterized constructor\n";
	}
	myKlass(const myKlass& o)
	{
		std::cout << "Copy constructor\n";
		this->i = o.i;
		this->f = o.f;
	}
	myKlass(myKlass&& o)
	{
		std::cout << "Move constructor\n";
		this->i = o.i;
		this->f = o.f;
	}
	~myKlass()
	{
		std::cout << "Destructor\n";
	}
};

void fun(int a, int b)
{
	std::cout << a << " " << b;
}



int geta()
{
	int a = 5;
	return a;
}

int getb()
{
	int b = 6;
	return b;
}
template<typename T1, typename T2>
void wrapper(T1 e1, T2 e2)
{
	fun(e1, e2);
}


int main()
{
	std::vector<myKlass> v;
	//v.push_back(myKlass(2, 3.14f));

	std::cout << "\n\n\n";
	v.emplace_back(2, 3.14f);
	int a = 5, b = 6;
	wrapper<int,int>(5, 5);


	return 0;
}
#include<iostream>
using namespace std;

class A
{
	int size;
	int* p;
public:
	A() = default;
	A(const A& o)
	{
		int* k;
		size = o.size;
		p = new int[size];
		k = p;
		int* j = o.p;
		std::cout << "copy const\n";
		for (int i = 0; i < size; i++)
		{
			*k = *j;
			k++;
			j++;
		}
	}
	void operator=(const A& o)
	{
		int* k;
		this->size = o.size;
		this->p = new int[size];
		k = this->p;
		int* j = o.p;
		std::cout << "copy assignemnt operator\n";
		for (int i = 0; i < size; i++)
		{
			*k = *j;
			k++;
			j++;
		}
	}
	A(A&& obj)
	{
		std::cout << "move const\n";
		size = obj.size;
		p = obj.p;
		obj.p = nullptr;
	}
	void operator=(A&& o) noexcept
	{
		std::cout << "move assignemnt\n";
		this->size = o.size;
		this->p = o.p;
		o.p = nullptr;
	}
	void set(int ts)
	{
		int* k;
		size = ts;
		p = new int[size];
		k = p;
		for (int i = 0; i < size; i++)
		{
			*k = i;
			k++;
		}
	}
	void print()
	{
		int* k;
		k = p;
		for (int i = 0; i < size; i++)
		{
			std::cout << *k;
			k++;
		}
		std::cout << "\n";
	}

};

A getObj()
{
	A obj;
	obj.set(6);
	return obj;
}



int main()
{
	A o;
	o.set(5);
	o.print();

	std::cout << "second obj\n";
	A o1 = o;
	o1.print();

	std::cout << "third obj\n";
	A o2 = getObj();
	o2.print();

	A o4;
	o4.set(4);
	o4.print();

	o4 = o;
	std::cout << "after\n";
	o4.print();

	A o5;
	std::cout << "Object 5\n";
	o5 = getObj();

	/* this code call the move constructor 
	A o5 = move(o)
	*/
	
	/* this code calle move assignemnt 
	A o5;
    o5 = move(o);
	*/

	o5.print();
}
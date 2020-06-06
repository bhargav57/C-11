#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class A
{
	int a;
public:
	A(int _a):a(_a)
	{
		
	}
	void operator()(A &b)
	{
		b.a = b.a * b.a;
		//std::cout << a << "\n";
	}
	void print()
	{
		std::cout << a << "\n";
	}
};
template<typename T>
vector<T> createVector(int count)
{
	vector<T> vec;
	for (int i = 0; i < count; i++)
	{
		T obj(i);
		vec.emplace_back(obj);
	}
	return vec;
}

int main()
{
	vector<A> Avect = createVector<A>(6);
	for (A &e : Avect)
	{
		e.print();
	}
	int val = 5;

	for_each(begin(Avect), end(Avect),A(val));
	std::cout << "After \n";

	for (A& e : Avect)
	{
		e.print();
	}
}
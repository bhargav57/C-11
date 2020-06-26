#include<iostream>
#include<memory>
#include<thread>
using namespace std;

class d
{
	int x;
public:
	d(int _x) :x(_x)
	{

	}
	~d()
	{
		std::cout << "dest\n";
	}
	int getX()
	{
		return x;
	}
};

void fun(std::shared_ptr<d> p)
{
	std::cout << p.use_count() << "\n";
}

int main()
{
	std::shared_ptr<d> sp(new d(8));
	std::cout << sp.use_count() << "\n";

	std::shared_ptr<d> sp1 = sp;
	std::cout << sp.use_count() << "\n";

	thread t1(fun, sp);
	thread t2(fun, sp);
	thread t3(fun, sp);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
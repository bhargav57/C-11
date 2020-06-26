#include<iostream>
using namespace std;

class myInt
{
public:
	explicit myInt(int* p = nullptr)
	{
		data = p;
	}
	~myInt()
	{
		delete data;
	}
	int& operator*()
	{
		return *data;
	}
private:
	int* data;
};


int main()
{
	int* p = new int(10);

	myInt myint =  myInt(p);

	cout << *myint;

	return 0;
}
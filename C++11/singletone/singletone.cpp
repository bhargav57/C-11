#include<iostream>
#include<string>
#include<vector>
#include<array>
using namespace std;

class singletone
{
	static singletone* obj;
	int v;
	singletone(int inv = 0)
	{
		v = inv;
	}
public:
	static singletone* getObj()
	{
		if (obj == nullptr)
		{
			obj = new singletone();
		}
		return obj;
	}
	void setValue(int val)
	{
		v = val;
	}
	int getValue()
	{
		return v;
	}
};

singletone* singletone::obj = nullptr;

int main()
{
	singletone* p1 = singletone::getObj();
	p1->setValue(50);
	std::cout << p1->getValue();
	singletone* p2 = singletone::getObj();
	std::cout << p2->getValue();
	singletone* p3 = singletone::getObj();
	std::cout << p3->getValue();
	return 0;
}
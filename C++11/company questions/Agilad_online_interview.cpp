#include<iostream>
#include<memory>
#include<thread>
using namespace std;
//What is the oupput of the program

class Example;
class Test
{
public:
	class Temp
	{
	public:
		int Interesting(Example& a);
	};

};
class Example
{
	int number;
	int friend Test::Temp::Interesting(Example& a);
public:
	Example(int m = 23) :number(m++)
	{

	}
	void dis()
	{
		cout << number << "\n";
	}
};
int Test::Temp::Interesting(Example& E)
{
	return E.number += --E.number;
}

int main()
{
	Test::Temp* Try = new Test::Temp;
	Example E(8);
	Try->Interesting(E);
	E.dis();

	return 0;
}
#include<iostream>
#include<vector>
using namespace std;

class A
{
	
public:
	string a;
	//explicit A(string ia)
	A(string ia)
	{
		a = ia;
	}
	void show()
	{
		std::cout << a<<"\n";
	}
};




int main()
{
	vector<string> v{"a","b"};

	for (A e : v)
	{
		std::cout << e.a;
	}

}
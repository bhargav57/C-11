#include<iostream>
#include<vector>
#include<array>
#include<thread>
#include<mutex>
using namespace std;

class base
{
	int i, j;
public:
	void setij(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
	void show()
	{
		std::cout << i << " " << j<<" ";
	}
};
// when abse are inherited at that time private data member of base are also part of the private data member of the derived
//see the sizeof derived
class derived :public base
{
	int k; //i,j are also giveb to this derived but that are not same as base's i and j;
public:
	void setk(int i,int j,int k)
	{
		base::setij(i, j);
		this->k = k;

	}
	void showk()
	{
		base::show();
		std::cout << k;
	}
};
int main()
{
	base b;
	b.setij(5, 6);
	derived d;
	d.setk(7,8,9);

	

	d.showk();
	b.show();

	std::cout << "\n";
	std::cout << "size of base =" << sizeof(base);

	std::cout << "\n";
	std::cout << "size of derived =" << sizeof(derived);

	return 0;
}
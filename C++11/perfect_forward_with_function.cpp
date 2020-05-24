#include<iostream>
#include<vector>
#include <utility>
using namespace std;

class myClass
{
	int m_i;
	float m_f;
public:
	myClass()
	{
		std::cout << "default constructor\n";
	}
	myClass(int ii, float ff) :m_i(ii), m_f(ff)
	{
		std::cout << "parameterised constructor\n";
	}
	myClass(const myClass& o)
	{
		std::cout << "copy constructor\n";
		this->m_i = o.m_i;
		this->m_f = o.m_f;
	}
	myClass(myClass&& o)noexcept
	{
		std::cout << "move constructor\n";
		this->m_i = o.m_i;
		this->m_f = o.m_f;
	}
	
	
};

void fun(int&& ii, float&& ff)
{
	std::cout << "R-value\n";
}
void fun(int& ii, float& ff)
{
	std::cout << "normal value\n";
}


template<typename ... Args>
void funTemplate(Args&& ... args)
{
	std::cout << "Template function is called\n";
	fun(std::forward<Args>(args)...);
}

//template <typename ... Args>
//void funTemplate(Args&& ... args) {
//	std::cout << "Template function is called\n";
//	 fun(std::forward<Args>(args)...);
//}



int main()
{
	vector<myClass> myvec;
	vector<myClass> myvec2;

	/* This call creates a temporary r-value object */
	/* but create a temporary object it calls a parameterised constructor */
	/* Then it will reclaim the temporary and delete temporary by calling 
	the move constructor */
	myvec2.push_back(myClass(1, 2.f));

	/* This call does not create a temporary object but it pass argument as a r-value */
	/* Then it creates a direct object at its place with parameterised constructor */
	/* emplace back used perfect forwarding inside the code */
	myvec.emplace_back(2, 2.f);
	
	
	int a1 = 5;
	float b = 6;
	
    /* This is an exmple of the perfeact forwarding with function */
	funTemplate(5, 6.f);
	funTemplate(a1, b);
}
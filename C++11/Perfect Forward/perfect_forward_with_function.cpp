#include<iostream>
#include<vector>
#include <utility>
using namespace std;
/* Where is the problem

void fun(int ii, float ff)
{
	std::cout << "normal value\n";
}

the above function accepts the both r-value as well as l-values kind of the arguments.
fun(5, 6.f);
fun(a1, b);

however, the below one accepts only the l-value referecnes
void fun(int& ii, float& ff)
{
	std::cout << "normal value\n";
}

fun(5, 6.f);  //This one is not working with the ablve fun(ref) fucntions
fun(a1, b);

so we need a new kinf of overloaded function which accepts the r value references too!!!
void fun(int&& ii, float&& ff)
{
	std::cout << "R-value\n";
}
void fun(int& ii, float& ff)
{
	std::cout << "normal value\n";
}

now add now const reference, then it would make things more complicated 
like this
const int b1 = 7;

and call like this
fun(b1, b); ---> "void fun(int& ii, float& ff)" would gives an compile time error.
we need one more function to overload this situaation
void fun(const int& ii, float& ff)
{
	std::cout << "const normal value\n";
}

now some one calls the same function with second argument as a constant,
up to how many combinations we have to go....its a tedious job and to mitigate that situation and make appropriate call we have to introduce
a new concepts call perfect farwarding with veradic templates argument

r-value can be passed to the l-vlaue reference accepting functions but it need a const argument
like for r value reference

fun(5, 6.f); 

we need below function
void fun(const int& ii, const float& ff)
{
	std::cout << "const normal value [ l-values+ r-values ]\n";
}
 
R-value is basically constant reference, please read below description for the detail like why r-vlaue reference is const lavalue refernece

1st answer:
An r-value is a temporary evanescent object, that can be read but is about to be destroyed. It is also a value that cannot stay on the left-hand side of an assignment (how could you make sense of assigning values to such a ghost?)

C++ has a very specific way to deal with this kind of entities. If you could pass an r-value by (non-const) reference, you could also be able to assign to it from inside the function. Therefore the rule that if r-values are to be passed by reference, this has to be a const reference.

This is not the whole truth though, because you have, indeed, r-value references (denoted with &&). So, you can, in the end, manipulate a temporary object, but you have to make an explicit statement that you really want to do so, using r-value references.

second answer
It gets back to the definition of literal. A literal is a constant; e.g.the value of the number 5 will not change, ever, though a variable may change from being assigned the value of 5 to another value. Passing a literal by reference implies that the function may modify it, which is something you can't do to a literal, by definition, which is why the language requires that you modify it with const. I don't think C++ could modify literals even if it let you try, but it still enforces this convention to remind the programmer that a literal value cannot be modified.

Please see below code which will work with all type of variables as well as the arguments
*/

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
	std::cout << "normal value[ l-values+ r-values ]\n";
}
void fun(const int& ii, float& ff)
{
	std::cout << "const normal value [ l-values+ r-values ]\n";
}


//template<typename ... Args>
//void funTemplate(Args&& ... args)
//{
//	std::cout << "Template function is called\n";
//	fun(std::forward<Args>(args)...);
//}

template <typename ... Args>
void funTemplate(Args&& ... args) {
	std::cout << "Template function is called\n";
	 fun(std::forward<Args>(args)...);
}



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
	const int b1 = 7;

	/* This is an exmple of the perfeact forwarding with function */
	funTemplate(5, 6.f);
	funTemplate(a1, b);
	funTemplate(b1, b);
}
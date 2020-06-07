#include<iostream>
#include <new>
using namespace std;

int callConstructor();

class data
{
	int *p;
	int size;
public:
	data(int t_size)
	{
		size = t_size;
		try
		{
			p = new int[size];
			int *k =p;
			for(int j = 0; j< t_size; j++)
			{
				*k = j;
				k++;
			}
		}
		catch(bad_alloc xa)
		{
			std::cout<<"bad allocation\n";
		}
	}

	data(const data &obj)
	{
		size = obj.size;
		int *k;
		int *m;
        std::cout<<"Copy Constructor is called \n";

		try
		{
			p = new int[size];
			k = obj.p;
			m = p;
		}
		catch(bad_alloc ba)
		{
			std::cout<<"copy const bad allocation\n";
		}

		for(int j=0; j< size; j++)
		{
			*m++ = *k++;
		}
	}
	data(data &&obj):size(obj.size),p(obj.p)
	{
	    std::cout<<"Move Constructor is called \n";
		obj.size = 0;
		obj.p = nullptr;
	}
	void show()
	{
		int *k = p;
		for(int j=0; j< size; j++)
		{
			std::cout<< *k<<" ";
			k++;
		}
		std::cout<<"\n";
	}
};

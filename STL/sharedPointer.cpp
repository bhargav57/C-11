#include<iostream>
#include <new>
#include <fstream>
#include<memory>
using namespace std;

class data
{
	int *p;
	int size;
public:
	data(int t_size)
	{
		std::cout<<"construcotr is called\n";
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
	~data()
	{
		std::cout<<"destructor is called\n";
		delete p;
	}
	data(const data &obj)
	{
		size = obj.size;
		int *k;
		int *m;
		
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


void generateResource()
{
	//data res(6);
	//return res; // this return value will invoke the move constructor
	std::shared_ptr<data> p(new data(8));
	std::cout<<p.use_count();
	std::shared_ptr<data> p2 = p;
	std::cout<<p.use_count();
	p2->show();
	p->show();

	std::shared_ptr<data> p3 = std::make_shared<data>(9); //make shared is a preffered way as it is faster then the new.
	std::cout<<p3.use_count();
	std::shared_ptr<data> p4 = p3;
	std::cout<<p4.use_count()<<" "<<p3.use_count()<<"\n";
	p3->show();
}
 



int main()
{
	
	generateResource();

	return 0;
}
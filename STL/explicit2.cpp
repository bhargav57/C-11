#include<iostream>
#include <new>
#include <fstream>
#include<memory>
using namespace std;

class entity
{
	int data;
public:
	entity()
	{
	}
	entity(int i)
	//explicit entity(int i)
	{
		data = i;
	}
	int getData()
	{
		return data;
	}
};

void getObj(entity obj)
{
	std::cout<< obj.getData()<<"\n";;
}

/* here getObj() take int = 5 argument as a input and convert imlicitely into the entity object by calling implicit constructor that is entity(int i)*/
/* it is able to convert int into entity object, however sometime in a code, we want an extra pre causion to convert things explicit. Means we do not want to */
/* convert integer argument in to entity but we want entity in to entity so we used word explicit in front of the constructor, uncomment the below code and comment the non-explicit code */
/* you can see the difference of the implicit and explicit cnstructor*/
int main()
{
    getObj(5);
	//entity obj(6);
	//getObj(obj);
	return 0;
}

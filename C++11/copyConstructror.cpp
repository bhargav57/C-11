#include "copyConstructor.h"


data generateResource()
{
	data res(6);
	return res; // this return value will invoke the move constructor
}


int callConstructor()
{
	data obj1(6);
	obj1.show();
	data obj2 = std::move(generateResource());
	obj2.show();
	return 0;
}

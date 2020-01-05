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

	/* this will call the copy constructor */
	data obj3 = obj1;
	obj3.show();

	/* this will call the move constructor */
	data obj2 = std::move(generateResource());
	obj2.show();
	return 0;
}

#include<iostream>
#include<vector>
#include<array>
#include<thread>
#include<mutex>
#include <future>
using namespace std;

typedef void (*t_fun)(int a);

void open_primary(int a)
{
	std::cout << "Primary\n";
}
void open_secondary(int a)
{
	std::cout << "Secondary\n";
}
void open_mutual(int a)
{
	std::cout << "Open Mutual\n";
}
void close(int a)
{
	std::cout << "Close\n";
}
void read(int a)
{
	std::cout << "ReadEvent\n";
}
void upload(int a)
{
	std::cout << "UploadEvent\n";
}

t_fun arryOfReqest[] = {
						&open_primary , 
						&open_secondary ,
						&open_mutual 
						};

t_fun arryOfReqest1[] = {
						&close ,
						&read ,
						&upload 
						};

typedef  t_fun* t_fun_ptr;

t_fun_ptr arr2[] = { arryOfReqest ,arryOfReqest1 };

int main()
{
	int reqNo = 1;
	arryOfReqest[reqNo](6);

	reqNo = 2;
	arryOfReqest[reqNo](6);


	reqNo = 3;
	arryOfReqest[reqNo](6);

	arr2[0][0](7);

	return 0;
}
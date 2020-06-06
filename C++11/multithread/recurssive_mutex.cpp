#include<iostream>
#include<mutex>
#include<chrono>
using namespace std;

std::recursive_mutex m;
int cnt = 0;
void recurefun(int threadnum, int val)
{
	if (val < 0)
		return;

	m.lock();
	std::cout << "thread = " << threadnum << "counter ="<<++cnt<<"\n";
	--val;
	recurefun(threadnum,val);
	m.unlock();
}

int main()
{
	std::thread t1(recurefun, 1, 10);
	std::thread t2(recurefun, 2, 10);

	t1.join();
	t2.join();

	return 0;
}
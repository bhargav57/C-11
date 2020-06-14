#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

/*
1. lock gaurd is a lightweight
2. it will acquire the lock on scope basis
3. one it start the lock it ends the lock when the scope is finished
4. normally the scope ends at the end of the fucniton
5. in between scope end one can use { } brackets
6. do not have a control to end the scope just like unlock function
7. cannot copy the mutex
*/


std::mutex m1;
int buffer = 0;

void task(std::string t_name, int loopfor)
{
	std::lock_guard<mutex> lock(m1);
	for (int i = 0; i < loopfor; i++)
	{
		std::cout << t_name << " " << ++buffer<<"\n";
	}
}

int main()
{
	std::thread t1(task,"T0", 10);
	std::thread t2(task,"T1", 10);

	t1.join();
	t2.join();

	return 0;
}
#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
using namespace std;


int counter = 0;
std::mutex m;
int var1 = 0, var2 = 0;

void countmore(int i)
{
	for (int i = 0; i < 10000000; i++)
	{
		if (m.try_lock())
		{
			if (i == 1)
			{
				++var1;
			}
			else
			{
				++var2;
			}
			++counter;
			m.unlock();
		}
	}
}

int main()
{
	std::thread t1(countmore,1);
	std::thread t2(countmore,2);

	t1.join();
	t2.join();


	std::cout << counter << "\n";
	std::cout << var1 << " " << var2;

	return 0;
}
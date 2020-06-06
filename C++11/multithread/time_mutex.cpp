#include<iostream>
#include<mutex>
#include<chrono>
using namespace std;

int myAmount = 0;
std::timed_mutex m;

void increment(int i)
{
	if (m.try_lock_for(std::chrono::seconds(1)))
	{
		++myAmount;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Thread " << i <<" Entered \n";
		m.unlock();
	}
	else
	{
		std::cout << "Thread " << i <<" could not entered\n";
	}
}

int main()
{
	std::thread t1(increment, 1);
	std::thread t2(increment, 2);

	t1.join();
	t2.join();


	std::cout <<"My amount =" <<myAmount << "\n";
	return 0;
}
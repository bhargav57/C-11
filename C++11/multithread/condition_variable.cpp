#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
int balance = 0;

void addMoney(int bal)
{
	std::lock_guard<mutex> lg(m);
	balance += bal;
	std::cout << "Balance credited = " << balance << "\n";
	cv.notify_one();
}

void withdrawMoney(int amt)
{
	std::unique_lock<mutex> ul(m);
	cv.wait(ul, [] {return (balance != 0) ? true : false; });
	if (balance >= amt)
	{
		balance -= amt;
		std::cout << "Balance withdrw = " << balance << "\n";
	}
	else
	{
		std::cout << "insufficent Balance = " << balance << "\n";
	}
	std::cout << "Available balance is = " << balance << "\n";
}

int main()
{
	std::thread t1(addMoney,500);
	std::thread t2(withdrawMoney,400);

	t1.join();
	t2.join();

	return 0;
}
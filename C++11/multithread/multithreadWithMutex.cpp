#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<vector>
using namespace std;
using namespace std::chrono;


int addMoney = 0;
std::mutex m;

void addMoneyFun()
{
	m.lock();
	addMoney++;
	m.unlock();
}

int main()
{

	auto startTime = std::chrono::high_resolution_clock::now();
	
	std::thread t1(addMoneyFun);

	std::thread t2(addMoneyFun);

	
	std::vector<std::thread> threadVect;

	for (int i=0;i<10000;i++)
	{
		threadVect.push_back(std::thread(addMoneyFun));
	}

	if(t1.joinable())
	{
		t1.join();
	}
	
	if (t2.joinable())
	{
		t2.join();
	}

	auto endtime = std::chrono::high_resolution_clock::now();

	auto duration = duration_cast<milliseconds> (endtime - startTime);

	std::cout << duration.count() / 1000;

	for (auto& th : threadVect) th.join();

	std::cout << "the ammount is " << addMoney<<"\n";

	return 0;

}
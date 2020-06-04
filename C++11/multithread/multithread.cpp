#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end) noexcept
{
	for (ull i = start; i <= end; i++)
	{
		if ((i & 1) == 0)
		{
			evenSum += i;
		}
	}
}


void findOdd(ull start, ull end) noexcept
{
	for (ull i = start; i <= end; i++)
	{
		if ((i & 1) == 1)
		{
			oddSum += i;
		}
	}
}


int main()
{
	ull start = 0, end = 1900000000;
	

	auto startTime = high_resolution_clock::now();

	std::thread t1(findEven, start, end);
	std::thread t2(findOdd, start, end);

	t1.join();
	t2.join();

	auto endtime = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds> (endtime - startTime);

	std::cout << duration.count() / 1000;

	return 0;

}
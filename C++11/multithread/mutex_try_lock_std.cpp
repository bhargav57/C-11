#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
using namespace std;

int x = 0, y = 0;
std::mutex m1, m2;

void dosomething(int seconds)
{
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void incrementXorY(int& XorY, std::mutex& m, const char* desc)
{
	for (int i = 0; i < 5; ++i)
	{
		m.lock();
		++XorY;
		std::cout << desc << XorY << "\n";
		m.unlock();
		dosomething(1);
	}
}

void consumeXY()
{
	int useCount = 5;
	int xplusY = 0;

	while (1)
	{
		int result = std::try_lock(m1, m2);
		if (result == -1)
		{
			if (x != 0 && y != 0)
			{
				--useCount;
				xplusY += x + y;
				x = 0;
				y = 0;
				std::cout << "XplusY is =" << xplusY << "\n";
				std::cout << "useCount is =" << useCount << "\n";
			}
			m1.unlock();
			m2.unlock();
			if (useCount == 0)
			{
				break;
			}
		}
		
	}
}


int main()
{
	std::thread t1(incrementXorY, std::ref(x), std::ref(m1), "X");
	std::thread t2(incrementXorY, std::ref(y), std::ref(m2), "Y");
	std::thread t3(consumeXY);


	t1.join();
	t2.join();
	t3.join();

	return 0;
}
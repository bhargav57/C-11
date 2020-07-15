#include<iostream>
#include<vector>
#include<array>
#include<thread>
#include<mutex>
using namespace std;

vector<int> paircount;
std::mutex m;

bool keycalc(int a, int b, int key)
{
	return (a + b) % key == 0 ? true : false;
}


void fun(vector<int> atemp, vector<int> btemp, int val)
{
	int asize = atemp.size();
	int bsize = btemp.size();

	int cnt = 0;
	for (int i = 0; i < asize; ++i)
	{
		for (int j = 0; j < bsize; ++j)
		{
			if (keycalc(atemp[i], btemp[j], val))
			{
				cnt++;
			}
		}
	}
	
	m.lock();
	if (cnt != 0)
	{
		paircount.push_back(cnt);
	}
	m.unlock();
	
}

vector<int> calc(vector<int> a, vector<int> b, vector<vector<int>> query)
{
	int asize = a.size();
	int bsize = b.size();

	int qsize = query.size();

	vector<int> temp = query[0];
	int val = temp[0];
	thread t1(fun, a, b, val);

	for (int k = 1; k < query.size(); k++)
	{
		temp = query[k];
		if (temp[0] == 0)
		{
			int idx = temp[1];
			b[idx] = temp[2];
		}

		temp = query[k+1];
		int val = temp[0];
		thread t2(fun, a, b, val);
		t1.join();
		t2.join();
	}

	return paircount;
}



int main()
{
	/*vector<int> a{ 1,2,3 };
	vector<int> b{ 3,4 };
	vector<vector<int>> query{ {1,5} ,{0,0,1} ,{1,5} };*/

	vector<int> a{ 1,2,2 };
	vector<int> b{ 2,3 };
	vector<vector<int>> query{ {1,4} ,{0,0,3} ,{1,5} };

	calc(a, b, query);
	return 0;
}
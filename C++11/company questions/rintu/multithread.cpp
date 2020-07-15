#include<iostream>
#include<vector>
#include<array>
#include<thread>
#include<mutex>
#include <future>
using namespace std;

vector<int> paircount;
std::mutex m;

struct sepratedData
{
	vector<vector<int>> Adata;
	vector<vector<int>> Bdata;
	vector<int> Fval;
};

sepratedData goloabalData;

bool keycalc(int a, int b, int key)
{
	return (a + b) % key == 0 ? true : false;
}


void fun(vector<int> atemp, vector<int> btemp, int val, int tcount)
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

	if (m.try_lock())
	{
		if (cnt != 0)
		{
			paircount[tcount] = cnt;
		}
		m.unlock();
	}

}

vector<int> calc(vector<int> a, vector<int> b, vector<vector<int>> query)
{
	int asize = a.size();
	int bsize = b.size();

	int qsize = query.size();

	paircount.resize((qsize + 1) / 2, 0);

	for (int i = 0; i < qsize; i = i + 2)
	{


		if (i % 2 == 0)
		{

			if (i == 0)
			{
				vector<int> tempQuery = query[0];
				int FValueData = tempQuery[1];
				goloabalData.Adata.push_back(a);
				goloabalData.Bdata.push_back(b);
				goloabalData.Fval.push_back(FValueData);
			}
			else
			{
				vector<int> tempQuery = query[i - 1];
				if (tempQuery[i - 1] == 0)
				{
					goloabalData.Adata.push_back(a);
					vector<int> tempB = b;
					tempB[tempQuery[1]] = tempQuery[2];
					goloabalData.Bdata.push_back(tempB);
					goloabalData.Fval.push_back(query[i][1]);
				}
			}
		}
	}


	/*thread t0(fun, goloabalData.Adata[0], goloabalData.Bdata[0], goloabalData.Fval[0], 0);
	thread t1(fun, goloabalData.Adata[1], goloabalData.Bdata[1], goloabalData.Fval[1], 1);

	t0.join();
	t1.join();*/
	int dSize = goloabalData.Adata.size();
 	std::vector<thread> t;
	int cnt = 0;

	for (int cnt = 0; cnt < dSize; cnt++)
	{

		t.push_back(std::thread(fun, goloabalData.Adata[cnt], goloabalData.Bdata[cnt], goloabalData.Fval[cnt], cnt));
		//t[cnt].join();
	}

	/*for (int cnt = 0; cnt < t.size(); cnt++)
	{
		t[cnt].join();
	}*/

	for (std::thread& th : t)
	{
		// If thread Object is Joinable then Join that thread.
		if (th.joinable())
			th.join();
	}

	return paircount;
}



int main()
{
	/*vector<int> a{ 1,2,3 };
	vector<int> b{ 3,4 };
	vector<vector<int>> query{ {1,5} ,{0,0,1} ,{1,5} };*/

	/*vector<int> a{ 1,2,2 };
	vector<int> b{ 2,3 };
	vector<vector<int>> query{ {1,4} ,{0,0,3} ,{1,5} };*/

	vector<int> a{ 1,0,1 };
	vector<int> b{ 2,0,2 };
	vector<vector<int>> query{{1,0}};

	vector<int> res = calc(a, b, query);

	for (const auto& e : res)
	{
		std::cout << e << " ";
	}


	return 0;
}
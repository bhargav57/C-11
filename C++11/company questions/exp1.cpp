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


void fun(vector<int> a, vector<int> b, int val)
{
	int asize = a.size();
	int bsize = b.size();

	int cnt = 0;
	for (int i = 0; i < asize; ++i)
	{
		for (int j = 0; j < bsize; ++j)
		{
			if (keycalc(a[i], b[j], val))
			{
				cnt++;
			}
		}
	}
	
	m.lock();
	paircount.push_back(cnt);
	m.unlock();
	
}

vector<int> calc(vector<int> a, vector<int> b, vector<vector<int>> query)
{
	int asize = a.size();
	int bsize = b.size();

	vector<int> temp = query[0];
	vector<int> temp1 = query[1];
	vector<int> temp2 = query[2];
	vector<int> b1 = b;

	if (temp[0] == 1)
	{
		int val = temp[1];
		int rval = 0;
		fun(a, b, val);	
	}

	

	if (temp1[0] == 0)
	{
		int idx = temp1[1];
		b1[idx] = temp1[2];
	}

	
	if (temp2[0] == 1)
	{
		int val = temp2[1];
		int rval = 0;
		fun( a, b1, val);
	}
	

	//for(int k = 0; k < query.size(); k++)
	//{
	//	vector<int> temp = query[k];
	//	int cnt = 0;
	//	if (temp[0] == 0)
	//	{
	//		int idx = temp[1];
	//		b[idx] = temp[2];
	//	}
	//	else if (temp[0] == 1)
	//	{
	//		/*for (int i = 0; i < asize; ++i)
	//		{
	//			for (int j = 0; j < bsize; ++j)
	//			{
	//				if (keycalc(a[i], b[j], temp[1]))
	//				{
	//					cnt++;
	//				}
	//			}
	//		}*/

	//		
	//		paircount.push_back(cnt);
	//	}
	//	
	//}

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
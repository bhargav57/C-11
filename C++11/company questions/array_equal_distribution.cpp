#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;



int main()
{
	//int arr[] ={ 1,2,3,3,18,19};
	int arr[] = { 1,1,1,1,1,1,1,15,20 };
	const int n = sizeof(arr) / sizeof(arr[0]);

	int setSize = n;
	int smsize = n / 2;
	int set1[n];
	int set2[n];

	int pos1 = 0;
	int pos2 = 0;

	int i = n - 1;

	int sum1 = 0;
	int sum2 = 0;
	for(i = n - 1; i>=0 ; i--)
	{
		if (sum1 < sum2)
		{
			set1[pos1] = arr[i];
			pos1++;
			sum1 += arr[i];
		}
		else
		{
			set2[pos2] = arr[i];
			pos2++;
			sum2 += arr[i];
		}
	}

	while (i >= 0)
	{
		if (pos1 < setSize)
			set1[pos1++] = arr[i];
		else
			set2[pos2++] = arr[i];
		i--;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << set1[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << set2[i] << " ";
	}
	
}
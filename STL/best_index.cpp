#include <array>
#include <iostream>
#include <vector>
#include <list>
#include <numeric>

using namespace std;



class data
{
public:
	list<vector<vector<int>>> inputData;
	int sum;
};
int main()
{
	int size;
	cin>>size;
 
	int arr[size]; // Define an array of four integers
    
	// Get inputs for the array elements
	for (int ti=0;ti<size; ti++) {
    	cin >> arr[ti];
	}
	/*int size = 10;
	int arr[] = {2, 1, 3, 9, 2, 4, -10 ,-9 ,1 ,3};*/

	data obj1;
	obj1.sum = 0;
	//int size = 5;
	//int arr[] = {1, 3, 1, 2, 5};
	int vecSize;
	int tempsum=0;


	for(int k=0; k<size; k++)
	{
		int idx=k;
		size = size;
		vector<vector<int>> outerV;
		vecSize =0;
		tempsum = 0;
		bool ex = false;
		for(int j=0; (j<size && !ex);j++)
		{
			vector<int> v;
			
			for(int i=0;(i<j && idx<size);i++)
			{
				v.push_back(arr[idx++]);
			}
			if(v.size() !=0)
			{
				if(v.size() <= vecSize)
				{
					ex = true;
				}
				else
				{
					tempsum +=  std::accumulate(v.begin(),v.end(),0);
					outerV.push_back(v);
					vecSize = v.size();
				}
			}				
		}
		//if(!ex)
		{
			if(tempsum > obj1.sum)
			{
				obj1.sum = tempsum;
				obj1.inputData.push_back(outerV);
			}
		}
	}


	std::cout<< obj1.sum;

	return 0;
}
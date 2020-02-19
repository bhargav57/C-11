#include<iostream>
#include <vector>
#include<algorithm> 
using namespace std;

void prime(int j,vector<int>& v)
{
    
	for(int i=2; i<j; i++)
	{
	
		auto f = std::all_of(v.begin(),v.end(),[=](int x){return i%x!=0;});
		if(f)
		{
			v.push_back(i);
		}
	}
	
	for(const auto& ele:v)
	{
	    std::cout<<ele<<" ";
	}
	/*vector<int>::iterator itr = v.begin();
	while(itr != v.end())
	{

		std::cout<<*itr<<" ";
		itr++;
	}*/
		
}

int main()
{
    int num;
    cin >> num;
    
    vector<int> plist;
	plist.push_back(2);
    prime(num,plist);
}
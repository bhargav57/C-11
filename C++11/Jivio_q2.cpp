#include<iostream>
#include <array>
#include<vector>
#include<algorithm>
#include<map>
#include<set>

using namespace std;

bool findcommon(std::string first, std::string second)
{
	std::string tstring = first + second;
	int length = tstring.size();
	std::set<char> tempSet;
	int cnt = 0;
	while (cnt < length)
	{
		char c = tstring[cnt];
		tempSet.insert(c);
		cnt++;
	}
	if (length == tempSet.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}


int solution(vector<string>& A) {
	// write your code in C++14 (g++ 6.2.0)
	std::multimap<int, string, std::greater<int>> finalstring;
	int retVaue = 0;
	for (std::string& ele : A)
	{
		int length = ele.size();
		std::set<char> tempSet;
		int cnt = 0;
		while (cnt < length)
		{
			char c = ele[cnt];
			tempSet.insert(c);
			cnt++;
		}
		if (length == tempSet.size())
		{
			finalstring.insert(std::pair<int, string>(length, ele));
		}

	}
	if (finalstring.size() > 0)
	{
		
		std::multimap<int, string, std::greater<int>>::iterator it = finalstring.begin();
		int cnt = 0;
		int firstsize = finalstring.size()-1;

		while (it != finalstring.end())
		{
			pair<int, string> tempPairFir = *it;
			it++;
			pair<int, string> tempPairSec = *it;
			if (findcommon(tempPairFir.second, tempPairSec.second))
			{
				tempPairFir.first + tempPairSec.first;
				std::multimap<int, string, std::greater<int>>::iterator it2 = finalstring.find(tempPairFir.first);
				finalstring.erase(it2);
				it2 = finalstring.find(tempPairSec.first);
				finalstring.erase(it2);

				//std::multimap<int, string, std::greater<int>>::iterator it2

				finalstring.insert(std::pair<int, string>(tempPairFir.first + tempPairSec.first, 
					tempPairFir.second+ tempPairSec.second));

				it = finalstring.begin();
			}
			cnt++;
			if (cnt == firstsize)
			{
				break;
			}
		}


		it = finalstring.begin();
		pair<int, string> fin = *it;
		return fin.first;
	}
	else
	{
		return retVaue;
	}
}

int main()
{
	
	std::vector<std::string> input = { "pototo","kayak","banana","racecar" };
	//std::vector<std::string> input = { "co","dil","ity"};
	//std::vector<std::string> input = { "eva","jqw","tny" ,"jan"};
	int size = solution(input);
	return 0;
}
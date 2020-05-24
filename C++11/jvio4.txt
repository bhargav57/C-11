#include<iostream>
#include<utility>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

class comparePair
{
	static int maxcount;
public:
	comparePair() 
	{
		maxcount = 1;
	}
	void operator()(std::pair<float, int> pair)
	{
		if (pair.second > maxcount)
		{
			maxcount = pair.second;
		}
	}
	static int getCount()
	{
		return maxcount;
	}
};
int comparePair::maxcount;

int solution(vector<int>& X, vector<int>& Y)
{
	int finalCount = 1;
	map<float, int> evaluatedList;
	set<float> keys;
	int idx = 0;
	for (const auto& e : X)
	{
		int tempY = Y.at(idx);
		float fval = ((float)e )/( (float)tempY);

		std::set<float>::iterator it;
		it = keys.find(fval);
		if (it != keys.end())
		{
			map<float, int>::iterator mapItr = evaluatedList.begin();
			while (mapItr != evaluatedList.end())
			{
				std::pair<float, int> tempPair = *mapItr;
				if (tempPair.first == fval)
				{
					evaluatedList.erase(mapItr);					
					int cntVal = tempPair.second++;
					cntVal++;
					evaluatedList.insert(std::make_pair(fval, cntVal));
					break;
				}
				mapItr++;
			}
		}
		else
		{
			evaluatedList.insert(std::make_pair(fval, 1));
			keys.insert(fval);
		}

		//
		idx++;
	}

	/*int maxValue = 1;
	{
		map<float, int>::iterator mapItr = evaluatedList.begin();
		while (mapItr != evaluatedList.end())
		{
			std::pair<float, int> tempPair = *mapItr;
			if (tempPair.second > maxValue)
			{
				maxValue = tempPair.second;
			}
			mapItr++;
		}

		finalCount = maxValue;
	}*/

	std::for_each(begin(evaluatedList), end(evaluatedList), comparePair());
	finalCount = comparePair::getCount();
	return finalCount;
}

void result(int original, int expected)
{
	if (original == expected)
		std::cout << "pass \n";
	else
		std::cout << "fail \n";
}
int main()
{
	vector<int> x = { 1,2,3,4,0 };
	vector<int> y = { 2,3,6,8,4 };

	int count = solution(x, y);

	result(count, 3);

	vector<int> x1 = { 3,4,4 };
	vector<int> y1 = {5,4,3};

	result(solution(x1,y1), 1);


	vector<int> x2 = { 4,4,7,1,2 };
	vector<int> y2 = { 4,4,8,1,2 };

	result(solution(x2, y2), 4);

	vector<int> x3 = { 1,2,3,1,2 };
	vector<int> y3 = { 2,4,6,5,10 };

	result(solution(x3, y3), 3);

}
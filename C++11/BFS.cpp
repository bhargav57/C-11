#include<iostream>
#include <array>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;

class attributeVertex
{
public:
	int distance;
};

class vertex
{
	
public:
	int ownNumber;
	vector<int> adjVertes;
	bool visited;
	vector<attributeVertex> addVertexAttribute;
	vertex(int iOwnNumber, vector<int> iadjVertexes) :ownNumber(iOwnNumber), adjVertes(iadjVertexes), visited(false)
	{

	}
	
	vertex operator=(const vertex v)
	{
		this->ownNumber = v.ownNumber;
		this->adjVertes = v.adjVertes;
		this->addVertexAttribute = v.addVertexAttribute;
		return *this;
	}
};


int main()
{
	vertex v1(1, {2});
	vertex v2(2, {1,3,4,5});
	vertex v3(3, {2,4,5});
	vertex v4(4, {1,2,3,5});
	vertex v5(5, {1,2,3,4});
	
	

	v1.adjVertes.push_back(2);
	attributeVertex v1atr;
	v1atr.distance = 5;

	v1.addVertexAttribute.push_back(v1atr);
	
	std::vector<vertex*> graph = { &v1,&v2,&v3,&v4,&v5 };

	std::vector<vertex*>::iterator itr = graph.begin();

	deque<vertex*> internalQueue;

	internalQueue.push_back(&v1);

	while (!internalQueue.empty())
	{
		vertex* tempV = internalQueue.front();
		
		if (tempV->visited != true)
		{
			std::cout << tempV->ownNumber << "\n";
			tempV->visited = true;

			vector<int> adjV = tempV->adjVertes;

			std::vector<int>::iterator itr = adjV.begin();

			while (itr != adjV.end())
			{
				int tempVertextNumber = *itr;
				vertex* tempQueueVertex = graph.at(tempVertextNumber-1);
				int getVertexNum = tempQueueVertex->ownNumber;
				internalQueue.push_back(tempQueueVertex);
				++itr;
			}
		}
		internalQueue.pop_front();
	}

}
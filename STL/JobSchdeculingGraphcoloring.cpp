#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<std::string> col{ "red","green", "blue", "white", "pink", "nocolor" };
class job
{
public:
	job() = default;
	
	int s;
	int e;
	job(int is, int ie) :s(is), e(ie)
	{

	}
};


class vertex
{
	std::string  col;
	int number;
	vector<int> adjucentVertex;
	job ownjob;
public:
	vertex()
	{
		number = -1;
		col = "nocolor";
	}
	void setVertex(std::initializer_list<int> data)
	{
		for (const auto& ele : data)
		{
			adjucentVertex.push_back(ele);
		}
	}
	void addVertex(int data)
	{
		adjucentVertex.push_back(data);
	}
	void setOwnVertex(int data)
	{
		number = data;
	}
	std::string getcolor()
	{
		return col;
	}
	void setcolor(std::string icolor)
	{
		col = icolor;
	}
	vector<int> getAdj()
	{
		return adjucentVertex;
	}
	int getwonJobNumber()
	{
		return number;
	}
	void setJob(job ijob)
	{
		ownjob = ijob;
	}
	job getJob()
	{
		return ownjob;
	}
};

bool isoverlapping(job j1, job j2)
{
	bool res = true;
	
	if ((j1.s == j2.s) && 
		(j1.e == j2.e))
	{
		res &= false;
	}
	else if( (j2.s >= j1.s) && 
		     (j2.s < j1.e))
	{
		res &= false;
	}
	else if ((j2.e > j1.s) &&
		(j2.e <= j1.e))
	{
		res &= false;
	}
	return res;
}

int main()
{
	job j1(1,3),j2(2,3), j3(3,4), j4(2,4), j5(5,7), j6(3,5), j7(1,2),j8(1,7),j9(1,7),j10(1,7);

	vector<job> jobV = { j1,j2,j3,j4,j5,j6,j7,j8,j8,j10 };
	
	int jobsize = jobV.size();
	vector<vertex> graph;
	for (int i = 0; i < jobsize; i++)
	{
		vertex v;
		v.setOwnVertex(i+1);
		v.setJob(jobV.at(i));
		for (int j = 0; j < jobsize; j++)
		{
			if (j != i)
			{
				bool res = isoverlapping(jobV.at(i), jobV.at(j));
				if (!res)
				{
					v.addVertex(j+1);
				}
			}
		}
		graph.push_back(v);
	}

	for (vertex& ele : graph)
	{
		std::string elecolor = ele.getcolor();
		if (elecolor.compare("nocolor")==0 )
		{
			for (int i = 0; i < col.size(); i++)
			{
				std::string tempcol = col.at(i);
				vector<int> adjVertex = std::move(ele.getAdj());
				bool f = true;
				for (const auto& t: adjVertex)
				{
					vertex tempele = graph.at(t-1);
					std::string tempadjcolor = tempele.getcolor();
					if (tempcol.compare(tempadjcolor) == 0)
					{
						f = false;
						break;
					}
				}
				if (f == true)
				{
					ele.setcolor(tempcol);
					break;
				}
			}
		}
	}
	
	for (vertex& d : graph)
	{
		job temJob = d.getJob();
		std::cout<<"Job "<<d.getwonJobNumber() <<" is at room = " <<d.getcolor()<<" beetween " << temJob.s<<" and "<<temJob.e<<"\n";
	}

	return 0;
}
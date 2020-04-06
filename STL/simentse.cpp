#include<iostream>
#include<vector>
#include <cmath>
using namespace std;


bool is2power(int l)
{
	float a = log2(l);
	float around = round(a);
	float dif = around - a;
	if (dif == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	int l,a,r, b, res;
	l = 60;
	r = 1200;
	int one;

	while (l <= r)
	{
		bool islowerPowerof2 = is2power(l);
		if (islowerPowerof2)
		{
			int next = l + 1;
			while (next <= r)
			{
				bool isHighpower2 = is2power(next);
				if (isHighpower2)
				{
					res = l ^ next;
					if (res)
					{
						std::cout << res << "\n";
					}
				}
				next++;
			}
		}

		l++;
		
	}

	std::cout << "End\n";
	
}
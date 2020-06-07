#include<iostream>
#include <array>
#include<vector>
#include<algorithm>
#include<deque>
#define MAX 10000
using namespace std;

class stack
{
	int data[32];
	int top;
public:
	stack() :top(-1)
	{

	}
	void push(int val)
	{
		data[++top] = val;
	}
	int pop()
	{
		return data[top--];
	}
	bool isEmpty()
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int getsize()
	{
		return top+1;
	}
};

void dectobin(unsigned int n, int* data,int* size)
{
	int* p;
	int count = 0;
	p = data;
	if (n > 0 && n < 2147483647)
	{
		int max = 0;
		while (n>0)
		{
			*data = n % 2;
			n = n / 2;
			count++;
			data++;
			
		}
	}
	*size = count;
}

int size(unsigned int number)
{
	int arr[32];
	int size = 0;

	dectobin(number, arr, &size);
	stack o;
	int c = 0;
	int start = 0;
	int length = 0;
	while (c < size)
	{
		int bit = arr[c];
		if (bit == 0)
		{
			if(start == 1)
			{
				o.push(bit);
			}
			
		}
		else
		{
			if (bit == 1)
			{
				start = 1;
				if (o.getsize() > 0)
				{
					start = 0;
				}
				if (o.getsize() > length)
				{
					length = o.getsize();
					start = 1;
				}

				while (!o.isEmpty())
				{
					o.pop();
				}
			}
		}
		c++;
	}
	return length;
}
int main()
{
	int l = size(2013364227);
	
	/*l = size(529);
	l = size(20);
	l = size(15);
	l = size(32);*/

	return 0;
}
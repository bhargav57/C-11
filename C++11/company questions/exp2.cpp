#include<iostream>
#include<string>
#include<vector>
#include<array>
using namespace std;


class convert
{
public:
	void operator()(char& c)
	{
		c = std::toupper(c);
	}
};
class backtrace {
public:
	std::pair<int, int> lastcol;
	char sign;
	backtrace() = default;
	backtrace(std::pair<int, int> inputPair, char inputSign = 'x') :lastcol(inputPair), sign(inputSign)
	{

	}
};
string sayYesOrNo(string a, string b)
{

	int s1 = a.size();
	int s2 = b.size();

	if (s1 > s2)
	{
		std::string temp = a;
		a = b;
		b = temp;
	}


	int maxi = s1 > s2 ? s1 : s2;
	int mini = s1 < s2 ? s1 : s2;

	for_each(begin(a), end(a), convert());

	for_each(begin(b), end(b), convert());


	vector<int> temp(maxi + 1, 0);
	vector<vector<int>> v(mini + 1, temp);

	vector<backtrace> tempBackTrace(maxi + 1);
	vector<vector<backtrace>> backTraceVector(mini + 1, tempBackTrace);

	vector<char> finalString;
	int i, j;

	for (i = 0; i < 1; ++i)
	{
		for (j = 1; j <= maxi; j++)
		{
			if (i == 0)
			{
				std::pair<int, int> tempPair = std::make_pair(i, j - 1);
				backtrace tempObj(tempPair, 'L');
				backTraceVector[i][j] = tempObj;
			}
		}
	}

	for (i = 1; i < mini; ++i)
	{
		for (j = 0; j <= 1; j++)
		{
			if (j == 0)
			{
				std::pair<int, int> tempPair = std::make_pair(i - 1, j);
				backtrace tempObj(tempPair, 'U');
				backTraceVector[i][j] = tempObj;
			}
		}
	}

	for (i = 1; i <= mini; i++)
	{

		for (j = 1; j <= maxi; j++)
		{
			char achar = a[i - 1];
			char bchar = b[j - 1];
			if (a[i - 1] == b[j - 1])
			{
				v[i][j] = 1 + v[i - 1][j - 1];
				std::pair<int, int> tempPair = std::make_pair(i - 1, j - 1);
				backtrace tempObj(tempPair, 'D');
				backTraceVector[i][j] = tempObj;
			}
			else
			{
				v[i][j] = v[i - 1][j] > v[i][j - 1] ? v[i - 1][j] : v[i][j - 1];

				if (v[i - 1][j] > v[i][j - 1])
				{
					std::pair<int, int> tempPair = std::make_pair(i - 1, j);
					backtrace tempObj(tempPair, 'U');
					backTraceVector[i][j] = tempObj;
				}
				else
				{
					std::pair<int, int> tempPair = std::make_pair(i, j - 1);
					backtrace tempObj(tempPair, 'L');
					backTraceVector[i][j] = tempObj;
				}


			}
			//std::cout << "[" << i << "]" << "[" << j << "]" << v[i][j] << " ";
		}
		//std::cout << "\n";
	}

	i = mini;
	j = maxi;

	while (i != 0 || j != 0)
	{
		backtrace obj = backTraceVector[i][j];
		if (obj.sign == 'D')
		{
			finalString.push_back(b[j - 1]);
			i = obj.lastcol.first;
			j = obj.lastcol.second;
		}
		else
		{
			if (obj.sign == 'L')
			{
				j = obj.lastcol.second;
			}
			else if (obj.sign == 'U')
			{
				i = obj.lastcol.first;
			}
		}
	}

	/*for (const char& ele : finalString)
	{
		std::cout << ele << " ";
	}*/

	std::vector<char>::const_reverse_iterator rItr = finalString.crbegin();
	while (rItr != finalString.crend())
	{
		std::cout << *rItr << " ";
		rItr++;
	}


	char last = finalString[0];
	

	rItr = finalString.crbegin();
	char first = *rItr;


	std::size_t found = b.find(first);




	string ans = mini == finalString.size() ? "YES" : "NO";
	return ans;

}

int main()
{
	string flag;
	string a, b;
	/*a = "abcd";
	b = "bc";

	flag = geyYesOrNo(a, b) ? "YES" : "NO";
	std::cout << flag <<"\n";*/

	/*a = "ABCDGH";
	b = "AEDFHR";

	flag = geyYesOrNo(a, b) ? "YES" : "NO";
	std::cout << flag << "\n";*/

	//a = "AGGTAB";
	//b = "GXTXAYB";

	//flag = geyYesOrNo(a, b) ? "YES" : "NO";
	//std::cout << flag << "\n";

	/*a = "dabcd";
	b = "abc";

	flag = geyYesOrNo(a, b) ? "YES" : "NO";
	std::cout << flag << "\n";*/

	/*a = "beFgH";
	b = "EFG";

	flag = geyYesOrNo(a, b) ? "YES" : "NO";
	std::cout << flag << "\n";*/

	a = "MBQEVZPBjcbswirgrmkkfvfvcpiukuxlnxkkenqp";
	b = "MBQEVZP";


	vector<string> data{ 
		"BFZZVHdQYHQEMNEFFRFJTQmNWHFVXRXlGTFNBqWQmyOWYWSTDSTMJRYHjBNTEWADLgHVgGIRGKFQSeCXNFNaIFAXOiQORUDROaNoJPXWZXIAABZKSZYFTDDTRGZXVZZNWNRHMvSTGEQCYAJSFvbqivjuqvuzafvwwifnrlcxgbjmigkms",
		"BFZZVHQYHQEMNEFFRFJTQNWHFVXRXGTFNBWQOWYWSTDSTMJRYHBNTEWADLHVGIRGKFQSCXNFNIFAXOQORUDRONJPXWZXIAABZKSZYFTDDTRGZXVZZNWNRHMSTGEQCYAJSF",
		"AQIUQVIPJDKYNEBPXFGVHCMFGvURORPRSTYQYJZCYJDNFRPRYTMZIsNDOJAOAGAEFRCDKUJBhdkedalbwoxxnoyowoxpdlelovibyiwat",
		"AQIUQVIPJDKYNEBPXFGVHCMFGURORPRSTYQYJZC",
		};
	for (int i = 0 ;i < data.size(); i += 2)
	{
		/*flag = sayYesOrNo(data[i], data[i+1]) ? "YES" : "NO";*/
		std::cout << sayYesOrNo(data[i], data[i + 1]) << "\n";
	}
    /*flag = geyYesOrNo(a, b) ? "YES" : "NO";
	std::cout << flag;*/
	
	return 0;
}
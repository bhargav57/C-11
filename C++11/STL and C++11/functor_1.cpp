#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



struct containnuts
{
	string data;
	containnuts(string indata):data(indata){}
	bool operator()(string d)
	{	
		return d.compare(data) == 0? true:false;
	}
};


int main()
{
    std::string s = "Hello my name is Bhargav Patel\n";

    vector<char> capital;
    std::transform(begin(s), end(s), begin(s), [&](char c)
    {
        if (isupper(c))
        {
            capital.push_back(c);
            return tolower(c);
        }
        else
            return tolower(c);
    });

    std::replace_if(begin(s), end(s), 
    [](const char& c) 
    {
    return iswspace(c)?true:false; 
    }, '*');

    //replace_if(begin(s), end(s), [](const char& c) {return iswspace(c) ? true : false; }, '*');


	std::cout << s;
	

    //functor code
	vector<string> nuts{ "lemon","apple","walnut","orange" };

    /*
    Here containnuts is a struct/class has an operator() implemented which takes the string argument
    here in the code this find_if fucntion is iterating one by one collection object.
    in this case nuts is a collection/vector of string objects
    so in any operator overloading fucntion, the left side object which call the operator() fucntion.
    in below case, string objects call the operator and that string object which we need to compare that we have to pass as an argument
    here we want to comate the "almond" with all nuts collection so we pass that as an() argument and the vector of the string calls that operator.
    */
	auto found{std::find_if(begin(nuts),end(nuts),containnuts("almond"))};

}
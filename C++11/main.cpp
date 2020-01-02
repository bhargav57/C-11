#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


/* This function uses the std::generate() method to generate the data*/
void test_std_generate()
{
    std::cout<<"This is a test for the std::generate()\n";
    vector<int> v(10);

    std::generate(begin(v),end(v),[](){return (rand()/10);}); /* use of the lambda function*/

    for(auto a:v)
    {
        std::cout<<a<<"\n";
    }
}

int main()
{
    test_std_generate();
}

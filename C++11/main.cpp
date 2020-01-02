#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
    vector<int> v(10);
    std::generate(begin(v),end(v),[](){return rand();});

    for(auto a:v)
    {
        std::cout<<a<<"\n";
    }
}

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T>
void printData(T& data)
{
        for(auto it= begin(data); it != end(data); ++it)
        {
                cout <<*it;
        }

        for(auto a: data)
        {
                cout<<a<<"\n";
        }
}

int main()
{
        vector<int> v{1,2,3,4,5,6};

        for(auto it=begin(v);it != end(v); ++it)
        {
                *it *= 10;
        }

        copy(begin(v),end(v),ostream_iterator<int>(cout," "));

        cout<<"\n";
        for(auto it=std::prev(end(v)); it >= begin(v); --it)
        {
                *it -=5;
        }

        for_each(begin(v),end(v),[](int i){cout<<i<<" ";});

        printData<vector<int>>(v);
        return 0;
}
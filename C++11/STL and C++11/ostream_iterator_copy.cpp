#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

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

        return 0;
}
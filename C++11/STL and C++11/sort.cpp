#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> v{5,3,4,7,8,1,2,80};
    
    auto greater = [](const auto& a, const auto& b)
    {
        return a < b;
    };
    
    
    std::sort(begin(v),end(v),greater);
    
    
    copy(begin(v),end(v),ostream_iterator<int>(cout," "));

    return 0;
}
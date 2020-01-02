#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* This is a print utility function which takes the constant reference of the vector of integer*/
void printVector(const vector<int> &v)
{
    for(auto a:v)
    {
        std::cout<<a<<" ";
    }
    std::cout<<"\n";
}

/* This is a utility function which generates the vector of integer */
vector<int> generateVectorData()
{
     vector<int> v(10);
     std::generate(begin(v),end(v),[](){return (rand()/10);}); /* use of the lambda function*/
     return v;
}



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

/* This function uses the std::sort() method to sort the data*/
void test_std_sort()
{
    std::cout<<"This is a test for the std::sort()\n";
    vector<int> v(20);
    std::generate(begin(v),end(v),[](){return rand()/100;});

    std::cout<<"data before sorting\n";
    for(auto a:v)
    {
        std::cout<<a<<" ";
    }
    std::cout<<"\n";

    std::sort(begin(v),end(v));

    std::cout<<"data after sorting\n";
    for(auto a:v)
    {
        std::cout<<a<<" ";
    }
    std::cout<<"\n";


}

/* This function uses the std::reverse() method to sort the data*/
void test_reverse()
{
    vector<int> v(10);
    v = std::move(generateVectorData()); /* use of the move sementic */
    std::cout<<"Original data\n";
    printVector(v);
    std::reverse(begin(v),end(v));
    std::cout<<"reverse data\n";
    printVector(v);
}


/* This function uses the std::max_element() method to sort the data*/
void test_max_and_min_element()
{
    vector<int> v(10);
    v = std::move(generateVectorData());
    std::cout<<"Original data\n";
    printVector(v);
    std::cout<<"Maximum element = "<<*max_element(begin(v),end(v))<<"\n";

    std::cout<<"Minimum Element = "<<*min_element(begin(v),end(v))<<"\n";

    std::cout<<"Accumulated sum = "<<std::accumulate(begin(v),end(v),0);
}
int main()
{
    test_std_generate();
    test_std_sort();
    test_reverse();
    test_max_and_min_element();
}

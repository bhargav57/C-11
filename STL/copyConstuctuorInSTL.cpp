#include<iostream>
#include<vector>
#include<algorithm>
#include<new>
using namespace std;

class data
{
    int *p;
    int datasize;
public:
    data(int tsize):p(nullptr),datasize(tsize)
    {
        try
        {
            p =  new int[datasize];
            if( p != nullptr)
            {
                int *k;
                k = p;
                for(int j=0; j< datasize; j++)
                {
                    *k = j;
                    k++;
                }
            }
        }
        catch(bad_alloc ex)
        {
            std::cout<<"allocation error\n";
        }
    }

    data(const data &obj)
    {
        std::cout<<"Copy constructor \n";
        datasize = obj.datasize;

        try
        {
            p =  new int[datasize];
            if( p != nullptr)
            {
                int *k,*m;
                k = p;
                m = obj.p;
                for(int j=0; j< datasize; j++)
                {
                    *k = *m;
                    k++;
                    m++;
                }
            }
        }
        catch(bad_alloc ex)
        {
            std::cout<<"allocation error\n";
        }
    }
    data(data &&obj)
    {
        std::cout<<"Move constructor \n";
        datasize = obj.datasize;
        p = obj.p;
        obj.p = nullptr;
    }
    void show() const
    {
        int *k = p;
        for(int j=0; j< datasize; j++)
        {
            std::cout<<*(k++)<<"\n";
        }
    }
};

data getObj()
{
    data obj(8);
    return obj;
}

int main()
{
//    data obj(6);
//    obj.show();
//
//    data obj2 = obj;
//    obj2.show();
//
//    data obj3 =  std::move(getObj());
//    obj3.show();

    data o1(4), o2(5), o3(6);
    std::cout<<"Vector is created\n";
    vector<data> datvec;

    datvec.push_back(o1);
    datvec.push_back(o2);
    datvec.push_back(o3);

    std::cout<<"Before fore loop\n";
    for(auto a: datvec)
    {
        a.show();
    }

}


/* Description of the output */
/* Creating a vector as well as pushing the vector for dara type called the copy constructor. */

/* When it is iterating in the for loop, auto a is the local copy and not an actual copy that menas it calls the copy constructir too. That is very expensive if the vecotor and deep copy is involved , too avoid this deep copy pass the actual copy */

/* 
for(auto &a: datavec)
{
    a.show();
}
here passing the reference we can save the deep copy and significantly save the performance, however the problem is if the a.show modifies the data it has an impact on the orignial vector datavec too. To avoid inside modification pass the data like

for(const auto &a: datavec)
{
    a.show();
}

*/
/*
Vector is created
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Before fore loop
Copy constructor 
0
1
2
3
Copy constructor 
0
1
2
3
4
Copy constructor 
0
1
2
3
4
5
*/


/* the new output after const use 
Vector is created
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Copy constructor 
Before fore loop
0
1
2
3
0
1
2
3
4
0
1
2
3
4
5

*/
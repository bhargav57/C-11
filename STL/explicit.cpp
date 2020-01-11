#include<iostream>
#include<vector>
#include<algorithm>
#include<new>
using namespace std;
 /* The following code does not compile, becuase the constuructor has explicit type */
 /* Class c has datay type string in the construcor which acepts the string while creating an objects */
 /* here in for loop it calles for the local copy and call the constructor of the c class */
 /* however, as the constuructor is an explicit it expect the c class object instead of string data*/
 /* here, vs is a vector of string which gives individual string data to form a object but explicit constructor does not allows to do that*/
 /* this is added to avoid the mistake */
 /* if the vector is vector of c class then explicit constructor do not throws an error */
 /* see code below after this example */
 /* */
class c
{
    std::string d;
public:
    explicit c(std::string s):d(s)
    {

    }
    void show()
    {

        std::cout<<d;
    }
};

int main()
{

    vector<std::string> vs {"abc","bcd","mc","mk"};

    for(c ele:vs)
    {
        ele.show();
    }
}

/* This code does not throws an error as it has an explict constructor but in for loop */
/* it creates and temporary objects form the c class's vector */
/* hence compiler does not throws any error */
/**/
/**/


#include<iostream>
#include<vector>
#include<algorithm>
#include<new>
using namespace std;

class c
{
    std::string d;
public:
    explicit c(std::string s):d(s)
    {
        std::cout<<"Consturctor called \n";
    }
    void show()
    {

        std::cout<<d;
    }
};

int main()
{

    vector<std::string> vs {"abc","bcd","mc","mk"};
    c o1("ABC");
    c o2("BCD");
    c o3("MC");
    c o4("MK");

    vector<c> cVS;
    cVS.push_back(o1);
    cVS.push_back(o2);
    cVS.push_back(o3);
    cVS.push_back(o4);

    std::cout<<"Before the for loop\n";
    for(c& ele:cVS)
    {
        ele.show();
        std::cout<<"\n";
    }
}

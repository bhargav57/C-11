#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class student
{
        public:
                string fn,ln;
                int id;
        student():id(0){}
        student(int iid,string ifn,string iln):id(iid),fn(ifn),ln(iln){}
};
int main()
{
        vector<int> vec1(1,2);
        vector<int> vec2{1,2};


        cout<<std::boolalpha;

        bool e = equal(begin(vec1),end(vec1),begin(vec1));
        cout<<e<<"\n";

        vector<student> class1;
        vector<student> class2;

        class1.push_back({1,"bhargav","patel"});
        class1.push_back({2,"Priyanka","patel"});
        class1.push_back({3,"Dia","patel"});

        class2.push_back({1,"Kashyap","patel"});
        class2.push_back({2,"Hetusha","patel"});
        class2.push_back({3,"Hetaksh","patel"});


        std::function<bool(const student&, const student&)> id_only =
                [](const student& s1,const student& s2){
                        return s1.id == s2.id;
                };
        e = equal(begin(class1),end(class1), begin(class1),id_only);

        cout<< e <<"\n";

        std::function<bool(const student&,const student&)> all_data =
                [](const student& s1, const student&s2){
                        return s1.id == s2.id &&
                               s1.fn == s2.fn &&
                               s1.ln == s2.ln;
                };

        e = equal(begin(class1), end(class1), begin(class2), end(class2), all_data);

        cout<<e<<"\n";
        return 0;
}
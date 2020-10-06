#include<iostream>
using namespace std;

//some struct
struct Some {
    int x;
};

void useless(std::shared_ptr<Some> p) {//use count return 2 if pass by value
//void useless(std::shared_ptr<Some>& p) { //use count return 1 if pass by referece
    //Change the underlying object
    p->x = 20;
    std::cout << p.use_count()<<"\n";
}

void main() {

    //Create/initialize shared_ptr<Some>
    auto one = std::shared_ptr<Some>(new Some());
    //Another shared_ptr<Some> pointing nowhere 
    std::shared_ptr<Some> two;

    //Change the underlying object
    one->x = 10;
    //Read through shared_ptr
    std::cout << "x: " << one->x << "\n"; //x: 10

    //Pass to a function by value. This increases the ref count.
    useless(one);

    //Underlying object is changed
    std::cout << "x: " << one->x << "\n"; //x: 20

    //Assign to another shared_ptr
    two = one;

    //'one' and 'two' are pointing to the same object
    std::cout << std::boolalpha << (one.get() == two.get()) << "\n"; //true

    /*  On Return:
    1. 'one' and 'two' are destroyed
    2.  Ref count reaches zero
    3. 'Some' is destroyed */
}
#include<iostream>
#include<utility>
#include<vector>
using namespace std;

class foo
{
	int mi;
	float mf;
	bool mb;
	vector<int> mv;
public:
	foo() = default;
	
	foo(const foo& o)
	{
		std::cout << "copy constructor\n";
		this->mi = o.mi;
		this->mf = o.mf;
		this->mb = o.mb;
		this->mv = o.mv;
	}
	foo(foo&& o)
	{
		std::cout << "Move constructor\n";
		this->mi = std::move(o.mi);
		this->mf = std::move(o.mf);
		this->mb = std::move(o.mb);
		this->mv = std::move(o.mv);
	}
	foo(int ii, float ff, bool bb, vector<int> const& vv)
		:mi(ii),
		mf(ff),
		mb(bb),
		mv(vv)
	{
		std::cout << "normal constructor\n";
	}
	foo(int ii, float ff, bool bb, vector<int>&& vv)
		:mi(ii),
		mf(ff),
		mb(bb),
		mv(std::move(vv))
	{
		std::cout << "move overloaded constructor\n";
	}
	~foo()
	{
		std::cout << "destructor\n";
	}
};

class bar
{
	vector<foo> v;
public:
	template<typename ... Args>
	void addFoo(Args&& ... args)
	{
		v.emplace_back(forward<Args>(args)...);
	}
};
foo getObj()
{
	std::vector<int> v = { 1,2,3,4,5,6 };
	foo f(1, true, 1.2, v);
	return f;
}
int main()
{
	std::vector<int> v ={ 1,2,3,4,5,6 };
	std::vector<int> v1 = { 1,2,3,4,5,6 };

	/*std::vector<foo> f;

	foo f1 = { 1,2.f,true,v };*/
	//f.push_back(f1);

	//f.emplace_back(move(f1));

	bar b;
	b.addFoo(getObj());
	return 0;
}
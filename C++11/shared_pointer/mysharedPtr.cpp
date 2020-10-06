#include<iostream>
using namespace std;

class Counter
{
	unsigned int m_counter;
public:
	Counter() :m_counter(0)
	{

	}
	Counter(const Counter& obj) = delete;
	Counter& operator=(const Counter& c) = delete;
	~Counter()
	{

	}
	void reset()
	{
		m_counter = 0;
	}
	unsigned int get()
	{
		return m_counter;
	}
	void operator++()
	{
		m_counter++;
	}
	void operator++(int)
	{
		m_counter++;
	}
	void operator--()
	{
		m_counter--;
	}
	void operator--(int)
	{
		m_counter--;
	}
};

template<typename T>
class Shared_ptr 
{
	Counter* m_counter;
	T* m_ptr;
public:
	explicit Shared_ptr(T* ptr = nullptr)
	{
		m_ptr = ptr;
		m_counter = new Counter();
		if(m_ptr)
		{
			(*m_counter)++;
		}
	}

	~Shared_ptr()
	{
		(*m_counter)--;
		if (m_counter->get() == 0)
		{
			delete m_counter;
			delete m_ptr;
		}
	}

	Shared_ptr(const Shared_ptr<T>& obj)
	{
		this->m_ptr = obj.m_ptr;
		this->m_counter = obj.m_counter;
		(*m_counter)++;
	}
	T* get()
	{
		return m_ptr;
	}
	T& operator*()
	{
		return &m_ptr;
	}
	T* operator->()
	{
		return m_ptr;
	}
	unsigned int use_count()
	{
		return m_counter->get();
	}
};

int main()
{
	int* p = new int(50);

	Shared_ptr<int> sp1(p);

	std::cout<<sp1.use_count()<<"\n";

	Shared_ptr<int> sp2 = sp1;

	std::cout << sp2.use_count() << "\n";
}
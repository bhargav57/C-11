#include<iostream>
#include<new>
#include<algorithm>
#include<vector>
#include<initializer_list>
using namespace std;

template<typename T>
class node
{
public:
	T _data;
	node* _next;
	node* _prev;
};

template<typename T = int>
class deq
{
	node<T> *_head;
	node<T>* _tail;
	int _size;
public:
	deq();

	/* copy constructor */
	deq(const deq& obj);
	/* Move constructor */
	deq(deq&& obj);

	/* consturcutor with specific number*/
	deq(int elemNumber);

	/* consturcutor with specific number*/
	deq(int elemNumber,T data);

	/* Initalizer list constructor, does not work with VS2010 but checked with the codeblocks */
	/* deq(std::initializer_list<T> data); */

	node<T>* createNode(T data);
	
	void push_front(T data);
	void push_back(T data);
	void show();
	
	

	/* destructor*/
	~deq();
	
	class iterator
	{
		typedef iterator selfType;
		typedef node<T>* pointer;
		typedef node<T>& reference;
		typedef node<T> nodObj;
		pointer _ptr;
	public:
		selfType(pointer ptr):_ptr(ptr)
		{
		}
		
		selfType operator++(int junk)
		{
			//this->_ptr = this->_ptr->_next;
			_ptr = this->_ptr->_next;
			return *this;
		}
		selfType operator++()
		{
			this->_ptr = this->_ptr->_next;
			return *this;
		}
		bool operator!=(selfType rhs)
		{
			return this->_ptr != rhs._ptr;
		}
		bool operator==(selfType rhs)
		{
			return this->_ptr == rhs._ptr;
		}
		T operator*()
		{
			return this->_ptr->_data;
		}
	};

	iterator begin()
	{
		return iterator(_head);
	}

	iterator end()
	{
		if( _tail != nullptr)
		{
			return iterator(_tail->_next);
		}
		else
		{
			return nullptr;
		}
	}

	class const_iterator
	{
		typedef const_iterator selfType;
		typedef node<T>* pointer;

		pointer _ptr;
	public:
		const_iterator(pointer ptr):_ptr(ptr){}
		selfType operator++(int junk)
		{
			this->_ptr = this->_ptr->_next;
			return *this;
		}
		const T& operator*()
		{
			return this->_ptr->_data;
		}
		bool operator!=(selfType rhs)
		{
			return this->_ptr != rhs._ptr;
		}
		bool operator==(selfType rhs)
		{
			return this->_ptr == rhs._ptr;
		}
	};
	const const_iterator cbegin()
	{
		return const_iterator(_head);
	}

	const const_iterator cend()
	{
		if( _tail != nullptr)
		{
			return const_iterator(_tail->_next);
		}
		else
		{
			return nullptr;
		}
	}

	T& operator[](int idx)
	{
		node<T> *temp = _head;
		if(idx <= _size)
		{
			while( idx > 0 )
			{
				temp = temp->_next;
				idx--;
			}
			return temp->_data;
		}
		else
		{
			std::cout<<"[dequeue size] Requesting data out of size";
		}
	}

	deq<T>& operator=(deq<T>&& rhs)
	{
		_head = rhs._head;
		_tail = rhs._tail;
		_size = rhs._size;

		rhs._head = nullptr;
		rhs._tail = nullptr;
		rhs._size = 0;
		return this;
	}

	

	/* Dequeue manipulating methods */
	bool empty();
	void pop_front();
	void pop_back();
	int size();
	T& front();
	T& back();
	void swap(deq<T>& rhs);
};



template<typename T>
deq<T>::deq():_head(nullptr),_tail(nullptr),_size(0)
{
}

template<typename T>
deq<T>::deq(const deq& obj)
{
	_head = nullptr;
	_tail = nullptr;
	_size = obj._size;

	std::cout<<"Copy constructor\n";
	node<T>* temp = obj._head;
	while( temp != nullptr)
	{
		if(_head == nullptr)
		{
			node<T>* temp2 = new node<T>();
			temp2->_data   = temp->_data;
			_head = temp2;
			_tail = _head;
			
		}
		else
		{
			node<T>* temp2 = new node<T>();
			temp2->_data   = temp->_data;
			_tail->_next  = temp2;
			temp2->_prev  = _tail;
			_tail = temp2;
			
		}

		temp = temp->_next;
	}
}

template<typename T>
deq<T>::deq(deq&& obj)
{
	std::cout<<"Move constructor\n";
	_head = obj._head;
	_tail = obj._tail;
	_size = obj._size;

	obj._head = nullptr;
	obj._tail = nullptr;
}

/* Initalizer list constructor, does not work with VS2010 but checked with the codeblocks */
//template<typename T>
//deq<T>::deq(std::initializer_list<T> list)
//{
//	
//	_head = nullptr;
//	_tail = nullptr;
//
//	for(auto ele:list)
//	{
//		if( _head == nullptr)
//		{
//			_head = createNode(ele);
//			_tail = _head;
//          _size++;
//		}
//		else
//		{
//			/* insert a new node at front and link the previous and next node to it*/
//			node<T>* temp = createNode(ele);
//			temp->_next  = _head;
//			_head->_prev = temp;
//			_head		 = temp;
//          _size++;
//		}
//	}
//}

template<typename T>
node<T>* deq<T>::createNode(T data)
{
	node<T>* temp;
	try
	{
		temp = new node<T>();
		if( temp != nullptr)
		{
			temp->_data = data;
		}
		else
		{
			std::cout<<"Memory allocation error\n";
		}
	}
	catch(bad_alloc e)
	{
		std::cout<<"Memory allocation error\n";
	}
	return temp;
}
template<typename T>
void deq<T>::push_front(T data)
{
	if( _head == nullptr)
	{
		_head = createNode(data);
		_tail = _head;
		_size++;
	}
	else
	{
		/* insert a new node at front and link the previous and next node to it*/
		node<T>* temp = createNode(data);
		temp->_next  = _head;
		_head->_prev = temp;
		_head		 = temp;
		_size++;
	}
	
}

template<typename T>
void deq<T>::push_back(T data)
{
	if( _tail == nullptr)
	{
		_tail = createNode(data);
		_head = _tail;
		_size++;
	}
	else
	{
		node<T>* _temp = createNode(data);
		_tail->_next   = _temp;
		_temp->_prev   = _tail;
		_tail		   = _temp;
		_size++;
	}
}

template<typename T>
void deq<T>::show()
{
	const node<T>* temp = _head;
	while( temp != nullptr)
	{
		std::cout<<temp->_data<<" ";
		temp = temp->_next;
	}
	std::cout<<"\n";
}






template<typename T>
deq<T>::deq(int elemNumber)
{
	_head = nullptr;
	_tail = nullptr;

	while(elemNumber >0)
	{
		if( _head == nullptr)
		{
			_head = createNode(0);
			_tail = _head;
			_size++;
		}
		else
		{
			/* insert a new node at front and link the previous and next node to it*/
			node<T>* temp = createNode(0);
			temp->_next  = _head;
			_head->_prev = temp;
			_head		 = temp;
			_size++;
		}
		elemNumber--;
	}
}

/* consturcutor with specific number*/
template<typename T>
deq<T>::deq(int elemNumber,T data)
{
	_head = nullptr;
	_tail = nullptr;

	while(elemNumber >0)
	{
		if( _head == nullptr)
		{
			_head = createNode(data);
			_tail = _head;
			_size++;
		}
		else
		{
			/* insert a new node at front and link the previous and next node to it*/
			node<T>* temp = createNode(data);
			temp->_next  = _head;
			_head->_prev = temp;
			_head		 = temp;
			_size++;
		}
		elemNumber--;
	}
}

template<typename T>
deq<T>::~deq()
{
	node<T>* temp = _head;
	while( temp!= nullptr)
	{
		node<T>* temp2 = temp;
		temp = temp->_next;
		delete[] temp2;
	}
	_head = nullptr;
	_tail = nullptr;
}

template<typename T>
bool deq<T>::empty()
{
	return ( _head == nullptr?1:0) &&
		     ( _tail == nullptr?1:0);
}

template<typename T>
void deq<T>::pop_front()
{
	node<T>* temp = _head;
	_head = _head->_next;
	delete[] temp;
	_size--;
	temp = nullptr;
	if(_head != nullptr)
	{
		_head->_prev = nullptr;
	}
	else
	{
		_tail = nullptr;
	}
}
template<typename T>
void deq<T>::pop_back()
{
	node<T>* temp = _tail;
	_tail = _tail->_prev;
	delete[] temp;
	_size--;
	temp = nullptr;

	if( _tail != nullptr)
	{
		_tail->_next = nullptr;
	}
	else
	{
		_head = nullptr;
	}
}

template<typename T>
int deq<T>::size()
{
	return _size;
}

template<typename T>
T& deq<T>::front()
{
	node<T> *temp = _head;
	return temp->_data;
}

template<typename T>
T& deq<T>::back()
{
	node<T> *temp = _tail;
	return temp->_data;
}

template<typename T>
void deq<T>::swap(deq<T>& rhs)
{
	node<T>* tempTail, *tempHead;
	int tempSize;
	tempHead = rhs._head;
	tempTail = rhs._tail;
	tempSize = rhs._size;

	rhs._head = this->_head;
	rhs._tail = this->_tail;
	rhs._size = this->_size;

	this->_head = tempHead;
	this->_tail = tempTail;
	this->_size = tempSize;
}

/* TDD */
void compare()
{
	vector<int> v;
	deq<int> obj;

	for(int i=0;i<100;i++)
	{
		v.push_back(i);
		obj.push_back(i);
	}

	int ret= true;
	vector<int>::iterator itr = v.begin();
	deq<int>::iterator decItr = obj.begin();

	while( itr != v.end() && decItr != obj.end() )
	{
		int vecData = *itr;
		int deqData = *decItr;
		std::cout<<vecData<<" "<<deqData<<"\n";
		if (vecData != deqData)
		{
			ret = false;
			break;
		}
		decItr++;
		itr++;
	}

	std::cout<<"return value"<<ret<<"\n";
	if(!ret)
	{
		std::cout<<"not same\n";
	}
	else
	{
		std::cout<<"same\n";
	}
}

template<typename T>
deq<T> getObj()
{
	deq<int> tempObj;
	tempObj.push_back(6);
	tempObj.push_back(61);
	tempObj.push_back(62);
	return tempObj;
}

/* */
int main()
{
	/*deq<int> obj1;
	obj1.push_front(5);
	obj1.push_front(6);
	obj1.push_front(7);
	obj1.push_front(8);
	obj1.push_front(9);
	obj1.push_back(4);*/

	//int j = obj1[20];

	/*obj1.pop_front();
	obj1.pop_front();*/
	//obj1.pop_front();

	/*obj1.pop_back();
	obj1.pop_back();
	obj1.pop_back();*/

	/*obj1.front() = 99;
	
	obj1.back() = 505;
	std::cout<<obj1.empty()<<"\n";
	std::cout<<"size ="<<obj1.size()<<"\n";*/
	//compare();
	/*obj1.push_front(5);
	obj1.push_front(6);
	obj1.push_front(7);

	obj1.push_back(4);
	obj1.push_back(3);
	obj1.push_back(2);
	obj1.push_back(1);*/

	//obj1.show();

	/*deq<int>::iterator itr = obj1.begin();
	while(itr != obj1.end())
	{
		std::cout<<*itr<<" ";
		itr = itr++;
	}*/

	/*deq<int>::const_iterator itr = obj1.cbegin();
	while( itr != obj1.cend())
	{
		std::cout<<*itr<<" ";
		itr++;
	}*/

	deq<char> objS;
	deq<char> objs2;

	objS.push_back('A');
	objS.push_back('D');
	objS.push_front('a');
	objS.push_front('x');


	objs2.push_back('k');
	objs2.push_back('l');
	objs2.push_back('m');

	objS.swap(objs2);

	deq<char>::const_iterator itr = objS.cbegin();
	while( itr != objS.cend())
	{
		char data = *itr;
		cout<<data<<" ";
		itr++;
	}

	
	/*deq<int> obj2(obj1);
	deq<int>::iterator itr = obj2.begin();
	while(itr != obj2.end())
	{
		std::cout<<*itr<<" ";
		itr = itr++;
	}*/

	/*deq<int> obj3 = getObj<int>();
	deq<int>::iterator itr = obj3.begin();
	while(itr != obj3.end())
	{
		std::cout<<*itr<<" ";
		itr = itr++;
	}*/
	return 0;
}
# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack <T> values;
    stack <T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};


template <class T> 
bool StackExt<T>::empty() const
{
	return values.empty();
}


template <class T> 
T& StackExt<T>::top()
{
    return values.top();
}


template <class T> 
void StackExt<T>::pop()
{
    if(values.top() == min.top()) min.pop();
    values.pop();
}


template <class T> 
void StackExt<T>::push(const T & val)
{
    values.push(val);
    if(min.empty() || min.top() >= val) min.push(val);
}

template <class T>
T& StackExt<T>::findMin()
{
    return min.top();
}


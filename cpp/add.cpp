#include <iostream>

using namespace std;

template<int F,int ...nums>
struct Add{
	static const int value = F + Add<nums...>::value;
};


template<int F>
struct Add<F>{
	static const int value = F ;
};

template<class T,int ...nums>
struct _array;

template<class T,int F,int ...nums>
struct _array<T,F,nums...>{
	typedef typename _array<T,nums...>::type next_type;
	typedef next_type type[F];
};

template<class T,int F>
struct _array<T,F>{
	typedef T next_type;
	typedef next_type type[F];
};

template<class T>
struct _array<T>{
	typedef T next_type;
	typedef next_type type;
};

int main(){
	cout << Add<1,2,3>::value << endl;
	typedef int arr[10][3];
	cout << is_same<arr,_array<int,10,3>::type >::value << endl;
	cout << is_same<int,_array<int>::type >::value << endl;
}

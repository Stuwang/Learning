#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

template<class T,int ...nums>
struct _array;

template<class T,int F,int ...nums>
struct _array<T,F,nums...>{
	typedef typename _array<T,nums...>::type next_type;
	typedef next_type type[F];
};

template<class T>
struct _array<T>{
	typedef T next_type;
	typedef next_type type;
};

template<class T,int ...nums>
struct my_array;

template<class T,int F,int ...nums>
struct my_array<T,F,nums...>{
	typedef typename _array<T,nums...>::type help_type;
	typedef help_type* type;
};

int main(){
	typedef typename my_array<int,10,10>::type int_array2;
	int_array2 p = static_cast< int_array2 >( malloc(sizeof(int)*10*10) );
	assert(p);
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			p[i][j] = i+j;
		}
	}
	
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%3d",p[i][j]);
		}
		printf("\n");
	}
	free(p);
}

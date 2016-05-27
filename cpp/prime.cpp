#include <cstdio>

using namespace std;

template<int i,int j>
struct _mod{
	static const int value =  i % j && _mod<i,j-1>::value;
};

template<int i>
struct _mod<i,2>{
	static const int value = ( i % 2 );
};

// sushu 1

template<int i>
struct sushu{
	static const int num = i;
	static const int value = _mod<i,i-1>::value;
};

template<>
struct sushu<2>{
	static const int num = 2;
	static const int value = 1;
};

template<int N>
void coutsushu(){
	coutsushu<N-1>();
	if(sushu<N>::value)
		 printf("%d ",sushu<N>::num );
};

template<>
void coutsushu<2>(){
	printf("2 ");
}

// sushu 2
template<int i>
struct sushu2: public sushu2<i-1>{
	typedef sushu2<i-1> base;

	const static int num = i;
	static const int value = _mod<i,i-1>::value;

	sushu2(){
		if(sushu2<i>::value)
			printf("%d ",sushu2<i>::num );
	};
};

template<>
struct sushu2<2>{
	static const int num = 2;
	static const int value = 1;
	sushu2(){
		printf("2 ");
	};
};



int main(){
	// coutsushu<1000>();
	sushu2<100> _;
};

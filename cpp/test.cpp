/*************************************************************************
    > File Name: test.cpp
    > Author: ma6174
    > Mail: 799086345@qq.com 
    > Created Time: 三  4/20 16:53:22 2016
 ************************************************************************/
#include <iostream>

using namespace std;

// can't use as this !!!
template<class T,int ...num>
struct test{
	using type = T[num]... ;
};

int main(){
	cout << is_same<int[10][10],test<int,10,10>::type >::value << endl;	
}

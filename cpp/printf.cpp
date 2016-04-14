// a printf use template
#include<iostream>
using namespace std;

template<class T>
int printf(const T& t){
	cout << t;
	return 1;
};

template<class T,class ...Arg>
int printf(const T&t,const Arg& ...arg){
	cout << t;
	return 1+ printf(arg...);
};

int main(){
	printf('a','\n');
}

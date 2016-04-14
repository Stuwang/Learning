/*************************************************************************
    > File Name: test3.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年12月17日 星期四 23时00分57秒
 ************************************************************************/

#include<iostream>
#include<type_traits>
using namespace std;

void f(const char *){
	cout << "const char *" << endl;
};

template<class T>
void f(T&){
	cout << "T&" << endl;
	cout << is_same<T,char[4]>::value << endl;
	cout << is_same<T,char(&)[4]>::value << endl;
	cout << is_same<T,char*>::value << endl;
};

void g(const char *,const char *){
	cout << "pointer" << endl;
};

template<class T>
void g(T,T){
	cout << "T" << endl;
	cout << is_same<T,char(&)[4]>::value << endl;
	cout << is_same<T,char*>::value << endl;
}
/*
void test(int a[]){
	cout << "[]" << endl;
}
void test(int *){
	cout << "*" << endl;
}

void test(int *&){
	cout << "*&" << endl;
}
*/

typedef int int_[3];
void test(int(&a)[3]){
	cout << "&" << endl;
	cout << is_same<decltype(a),int(&)[3]>::value << endl;
}

void int_test(int *a){
	a++;
}

void int_test(int const * a){
}


int main(){
	char a[]="123";
	char b[]="123";
	g(a,b);
	cout << "fffff" << endl;
	f(a);

	int ai[3];
	test(ai);

	cout << "fuck " << is_same<char*,int[]>::value << endl;

}

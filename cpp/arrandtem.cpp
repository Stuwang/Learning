/*************************************************************************
    > File Name: test33.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年12月18日 星期五 00时04分53秒
 ************************************************************************/

#include<iostream>
using namespace std;

void f(int (&a)[3]){
};

void t(const char *){
	cout << "**" << endl;
}

// this can't compile ok
// 
// void t(char (&)[]){
// 	cout << "&&" << endl;
// }

int main(){
	char a[3];
	t(a);
}

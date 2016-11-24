#include <iostream>
#include <type_traits>

using namespace std;

template<int N>
void test(char(&arr)[N]){
	cout << "array" << std::endl;
}

template<class T>
void test(T){
	static_assert(std::is_same<T,char*>::value,"ÕâÀïÊÇÎªÁË¼ì²é");
	cout << "pointer" << std::endl;
}

void test_pointer(char **){
	cout << "char**" << endl;
}

template<int N> 
void test_pointer(char (*)[N]){
	cout << "char(*)[N]" << endl;
}

template<class T>
void wrapper(T &data){
	test(data);
	test_pointer(&data);
}

int main(){
	char *p1 = "aaaa";
	char p2[32] = {"aaa"};
	wrapper(p1);
	wrapper(p2);
}

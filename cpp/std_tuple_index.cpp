#include <iostream>
#include <utility>

using namespace std;


void Test(index_sequence<>) {
};


template<size_t Head, size_t... indexs>
void Test(index_sequence<Head, indexs...>){
	std::cout << Head << " ";
	Test(index_sequence<indexs...>());
};

int main(){
	Test(make_index_sequence<3>());
}

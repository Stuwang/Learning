#include <iostream>
#include <utility>

using namespace std;


// first one
template<size_t ...index >
struct IndexTuple {};

template<size_t Num, size_t  ... Other>
struct IndexTuple_helper
	:  IndexTuple_helper < Num - 1, Num - 1, Other... >
{

};

template<size_t  ...Other>
struct IndexTuple_helper<0, Other...>
{
	typedef IndexTuple<Other...> type;
};

template<size_t Num>
using MakeIndex = typename IndexTuple_helper<Num>::type;

// // get from gun stl
// // but in face, the IndexTuple's next is ...
// template<size_t ... indexs>
// struct IndexTuple {
// 	typedef IndexTuple<indexs..., sizeof(indexs...)> next;
// };

// template<size_t N>
// struct BuildTuple {
// 	typedef typename BuildTuple < N - 1 >::type::next type;
// };

// template<>
// struct BuildTuple<0>
// {
// 	typedef IndexTuple<> type;
// };

// template<size_t N>
// using MakeIndex = typename BuildTuple<N>::type;

void Test(IndexTuple<>) {
};


template<size_t Head, size_t... indexs>
void Test(IndexTuple<Head, indexs...>){
	std::cout << Head << " ";
	Test(IndexTuple<indexs...>());
};

int main()
{
	Test(MakeIndex<100>());
	return 0;
}


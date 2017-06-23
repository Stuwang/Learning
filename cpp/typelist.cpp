#include <type_traits>
#include <iostream>

using namespace std;


template<typename ...>
struct TypeList {};

namespace Internel {

// size_t
// using Size;
template<typename ...>
struct Size;

template<typename ...Args>
struct Size<TypeList<Args...>> {
	static const size_t Value = sizeof...(Args);
};

// using Empty;
template<typename ...>
struct Empty;

template<typename ...Args>
struct Empty<TypeList<Args...>> {
	static const bool Value = ( 0 == Size<TypeList<Args...>>::Value);
};

template<typename ...>
struct _HeadType ;

template<typename T, typename ...Args>
struct _HeadType<TypeList<T, Args...>> {
	typedef T ValueType;
};

template<typename _TypeList>
using Front = typename _HeadType<_TypeList>::ValueType;

// // type
// using Back;
template<typename ...Args>
struct _Back {
	static_assert(sizeof...(Args) >= 1, "");
};

template<typename T, typename ...Args>
struct _Back<T, Args...> : _Back<Args...> {};

template<typename T>
struct _Back<T> {
	typedef T ValueType;
};

template<typename ...Args>
struct _BackProxy;

template<typename ...Args>
struct _BackProxy<TypeList<Args...>> : _Back<Args...> {};

template<typename _TypeList>
using Back = typename _BackProxy<_TypeList>::ValueType;


// PushBack;
template<typename...Args>
struct _PushBack;

template<typename T, typename...Args>
struct _PushBack<T, TypeList<Args...>> {
	typedef TypeList<Args..., T> ValueType;
};

template<typename T, typename _TypeList>
using PushBack = typename _PushBack<T, _TypeList>::ValueType;

// popback


// PushFront;
template<typename...Args>
struct _PushFront;

template<typename T, typename...Args>
struct _PushFront<T, TypeList<Args...>> {
	typedef TypeList<T, Args...> ValueType;
};

template<typename T, typename _TypeList>
using PushFront = typename _PushFront<T, _TypeList>::ValueType;

// PopFront;
template<typename...Args>
struct _PopFront;

template<typename T, typename...Args>
struct _PopFront<TypeList<T, Args...>> {
	static_assert(1 <= sizeof...(Args), "");
	typedef TypeList<Args...> ValueType;
};

template<typename _TypeList>
using PopFront = typename _PopFront<_TypeList>::ValueType;

// using Contect;
template<typename ...>
struct _Contect;

template<typename ...Args1, typename ...Args2>
struct _Contect<TypeList<Args1...>, TypeList<Args2...>> {
	typedef TypeList<Args1..., Args2...> ValueType;
};

template<typename T1, typename T2>
using Connect = typename _Contect<T1, T2>::ValueType;

// using At;
template<int index, typename ...Args>
struct _At {
	static_assert(sizeof...(Args) > index , "");
};

template<int index, typename T, typename ...Args>
struct _At<index, T, Args ...> : _At < index - 1, Args... > {};

template<typename T, typename ...Args>
struct _At < 0, T, Args... > {
	typedef T ValueType;
};

template<typename T>
struct _At < 0, T> {
	typedef T ValueType;
};

template<int index, typename ...Args>
struct _AtProxy;

template<int index, typename ...Args>
struct _AtProxy<index, TypeList<Args...>> : _At<index, Args...> {};

template<int index, typename T>
using At = typename _AtProxy<index, T>::ValueType;

// FirstN
template<int N, typename T, typename ...Args>
struct _FirstN;

template<int N, typename ...Args1, typename T, typename ...Args2>
struct _FirstN<N, TypeList<Args1...>, TypeList<T, Args2...>>:
	        _FirstN < N - 1, TypeList<Args1..., T>, TypeList<Args2...> > {};

template<typename ...Args1, typename T, typename ...Args2>
struct _FirstN<0, TypeList<Args1...>, TypeList<T, Args2...>> {
	typedef TypeList<Args1...> ValueType;
};

template<typename ...Args>
struct _FirstN<0, TypeList<Args...>, TypeList<>> {
	typedef TypeList<Args...> ValueType;
};

template<int N, typename T>
struct _FirstNProxy;

template<int N, typename ...Args>
struct _FirstNProxy<N, TypeList<Args...>>: _FirstN<N, TypeList<>, TypeList<Args...>> {};

template<int N, typename T>
using FirstN = typename _FirstNProxy<N, T>::ValueType;

template<int N, typename Args>
struct _LastN;

template <int N, typename T, typename...Args>
struct _LastN<N, TypeList<T, Args...>>
	                                    : _LastN < N - 1, TypeList<Args... >> {};

template<typename T, typename ...Args>
struct _LastN<0, TypeList<T, Args...>> {
	typedef TypeList<T, Args...> ValueType;
};

template<>
struct _LastN<0, TypeList<>> {
	typedef TypeList<> ValueType;
};

template<int N, typename ...Args>
struct _LastNProxy;

template<int N, typename ...Args>
struct _LastNProxy<N, TypeList<Args...>> : _LastN<N, TypeList<Args...>> {};

template<int N, typename Args>
using LastN = typename _LastNProxy<N, Args>::ValueType;


template<int N, typename T, typename List>
struct _Insert {
	typedef FirstN<N, List> Head;
	typedef LastN<N, List> Tail;
	typedef Connect<PushBack<T, Head>, Tail> ValueType;
};

template<int N, typename T, typename List>
using Insert = typename _Insert<N, T, List>::ValueType;

template<int N, typename List>
struct _Erase {
	typedef FirstN <N, List > Head;
	typedef LastN <N, List > Tail;
	typedef Connect<Head, PopFront<Tail> > ValueType;
};

template<int N, typename List>
using Erase = typename _Erase<N, List>::ValueType;

template<typename ...List>
struct _PopBack;

template<typename ...List>
struct _PopBack<TypeList<List...>> {
	typedef FirstN < sizeof...(List) - 1, TypeList<List... >> ValueType;
};


template<typename List>
using PopBack = typename _PopBack < List >::ValueType;

void Test() {
	typedef TypeList<int, char> typelist;

	static_assert(2 == Size<typelist>::Value, "");
	static_assert(!Empty<typelist>::Value, "");

	static_assert(std::is_same<Front<typelist>, int>::value, "");
	static_assert(std::is_same <
	              Back<TypeList<int, char>>,
	              char >::value, "");
	static_assert(std::is_same <
	              PushBack<double, TypeList<int, char>>,
	              TypeList<int, char, double >
	              >::value, "");

	static_assert(std::is_same <
	              PushFront<double, TypeList<int, char>>,
	              TypeList<double, int, char>
	              >::value, "");

	static_assert(std::is_same <
	              PopFront<TypeList<int, char>>,
	              TypeList<char>
	              >::value, "");

	static_assert(std::is_same <
	              Connect <TypeList<int>, TypeList<char>>,
	              TypeList<int, char>
	              >::value, "");

	static_assert(std::is_same <
	              At <0, TypeList<int, char, float, double>>,
	              int
	              >::value, "");
	// error
	// static_assert(std::is_same <
	//               At <4, TypeList<int, char, float, double>>,
	//               int
	//               >::value, "");
	static_assert(std::is_same <
	              At <3, TypeList<int, char, float, double>>,
	              double
	              >::value, "");

	static_assert(std::is_same <
	              FirstN <0, TypeList<int, char, float, double>>,
	              TypeList<>
	              >::value, "");

	static_assert(std::is_same <
	              FirstN <1, TypeList<int, char, float, double>>,
	              TypeList<int>
	              >::value, "");
	static_assert(std::is_same <
	              FirstN <4, TypeList<int, char, float, double>>,
	              TypeList<int, char, float, double>
	              >::value, "");

	// static_assert(std::is_same <
	//               LastN <0, TypeList<>>, TypeList<>
	//               >::value, "");
	static_assert(std::is_same <
	              LastN<0, TypeList<>>, TypeList<>
	              >::value, "");

	static_assert(std::is_same <
	              Insert<0, int, TypeList<>>, TypeList<int>
	              >::value, "");

	static_assert(std::is_same <
	              Erase<0, TypeList<int, char>>, TypeList<char>
	              >::value, "");

	static_assert(std::is_same <
	              PopBack<TypeList<int, char>>, TypeList<int>
	              >::value, "");


}


namespace GoogleChrome {
// Packs a list of types to hold them in a single type.
template <typename... Types>
struct TypeList {};

// Used for DropTypeListItem implementation.
template <size_t n, typename List>
struct DropTypeListItemImpl;

// Do not use enable_if and SFINAE here to avoid MSVC2013 compile failure.
template <size_t n, typename T, typename... List>
struct DropTypeListItemImpl<n, TypeList<T, List...>>
	        : DropTypeListItemImpl < n - 1, TypeList<List... >> {};

template <typename T, typename... List>
struct DropTypeListItemImpl<0, TypeList<T, List...>> {
	using Type = TypeList<T, List...>;
};

template <>
struct DropTypeListItemImpl<0, TypeList<>> {
	using Type = TypeList<>;
};

// A type-level function that drops |n| list item from given TypeList.
template <size_t n, typename List>
using DropTypeListItem = typename DropTypeListItemImpl<n, List>::Type;

// Used for TakeTypeListItem implementation.
template <size_t n, typename List, typename... Accum>
struct TakeTypeListItemImpl;

// Do not use enable_if and SFINAE here to avoid MSVC2013 compile failure.
template <size_t n, typename T, typename... List, typename... Accum>
struct TakeTypeListItemImpl<n, TypeList<T, List...>, Accum...>
	: TakeTypeListItemImpl < n - 1, TypeList<List...>, Accum..., T > {};

template <typename T, typename... List, typename... Accum>
struct TakeTypeListItemImpl<0, TypeList<T, List...>, Accum...> {
	using Type = TypeList<Accum...>;
};

template <typename... Accum>
struct TakeTypeListItemImpl<0, TypeList<>, Accum...> {
	using Type = TypeList<Accum...>;
};


template<int n, class T>
using Take = typename TakeTypeListItemImpl<n, T>::Type;

// A type-level function that takes first |n| list item from given TypeList.
// E.g. TakeTypeListItem<3, TypeList<A, B, C, D>> is evaluated to
// TypeList<A, B, C>.
template <size_t n, typename List>
using TakeTypeListItem = typename TakeTypeListItemImpl<n, List>::Type;

// Used for ConcatTypeLists implementation.
template <typename List1, typename List2>
struct ConcatTypeListsImpl;

template <typename... Types1, typename... Types2>
struct ConcatTypeListsImpl<TypeList<Types1...>, TypeList<Types2...>> {
	using Type = TypeList<Types1..., Types2...>;
};

void test() {
	static_assert(std::is_same <
	              Take<1, TypeList<char>>, TypeList<char>
	              >::value, "");

	static_assert(std::is_same <
	              DropTypeListItem<0, TypeList<>>, TypeList<>
	              >::value, "");
}


}

}

int main() {

}

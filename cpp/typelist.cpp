#include <type_traits>
#include <functional>

using namespace std;

template<typename ...>
struct TypeList {};

// Size
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
struct _Front ;

template<typename T, typename ...Args>
struct _Front<TypeList<T, Args...>> {
	typedef T ValueType;
};

template<typename _TypeList>
using Front = typename _Front<_TypeList>::ValueType;

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
	static_assert(0 <= sizeof...(Args), "");
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
struct _TakeN;

template<int N, typename ...Args1, typename T, typename ...Args2>
struct _TakeN<N, TypeList<Args1...>, TypeList<T, Args2...>>:
	        _TakeN < N - 1, TypeList<Args1..., T>, TypeList<Args2...> > {};

template<typename ...Args1, typename T, typename ...Args2>
struct _TakeN<0, TypeList<Args1...>, TypeList<T, Args2...>> {
	typedef TypeList<Args1...> ValueType;
};

template<typename ...Args>
struct _TakeN<0, TypeList<Args...>, TypeList<>> {
	typedef TypeList<Args...> ValueType;
};

template<int N, typename T>
struct _TakeNProxy;

template<int N, typename ...Args>
struct _TakeNProxy<N, TypeList<Args...>>: _TakeN<N, TypeList<>, TypeList<Args...>> {};

template<int N, typename T>
using TakeN = typename _TakeNProxy<N, T>::ValueType;

template<int N, typename Args>
struct _DropN;

template <int N, typename T, typename...Args>
struct _DropN<N, TypeList<T, Args...>>
	                                    : _DropN < N - 1, TypeList<Args... >> {};

template<typename T, typename ...Args>
struct _DropN<0, TypeList<T, Args...>> {
	typedef TypeList<T, Args...> ValueType;
};

template<>
struct _DropN<0, TypeList<>> {
	typedef TypeList<> ValueType;
};

template<int N, typename ...Args>
struct _DropNProxy;

template<int N, typename ...Args>
struct _DropNProxy<N, TypeList<Args...>> : _DropN<N, TypeList<Args...>> {};

template<int N, typename Args>
using DropN = typename _DropNProxy<N, Args>::ValueType;


template<int N, typename T, typename List>
struct _Insert {
	typedef TakeN<N, List> Head;
	typedef DropN<N, List> Tail;
	typedef Connect<PushBack<T, Head>, Tail> ValueType;
};

template<int N, typename T, typename List>
using Insert = typename _Insert<N, T, List>::ValueType;

template<int N, typename List>
struct _Erase {
	typedef TakeN <N, List > Head;
	typedef DropN <N, List > Tail;
	typedef Connect<Head, PopFront<Tail> > ValueType;
};

template<int N, typename List>
using Erase = typename _Erase<N, List>::ValueType;

template<typename ...List>
struct _PopBack;

template<typename ...List>
struct _PopBack<TypeList<List...>> {
	typedef TakeN < sizeof...(List) - 1, TypeList<List... >> ValueType;
};


template<typename List>
using PopBack = typename _PopBack < List >::ValueType;

void Test() {
	typedef TypeList<int, char> typelist;

	// Size
	static_assert(2 == Size<TypeList<int, char>>::Value, "");
	static_assert(0 == Size<TypeList<>>::Value, "");
	// Empty
	static_assert(!Empty<TypeList<int, char>>::Value, "");
	static_assert(Empty<TypeList<>>::Value, "");

	// Front
	static_assert(std::is_same<Front<TypeList<int, char>>, int>::value, "");
	static_assert(std::is_same<Front<TypeList<int>>, int>::value, "");

	// Back
	static_assert(std::is_same <
	              Back<TypeList<int, char>>,
	              char >::value, "");
	static_assert(std::is_same <
	              Back<TypeList<char>>,
	              char >::value, "");

	// At
	static_assert(std::is_same <
	              At <0, TypeList<int, char, float, double>>,
	              int
	              >::value, "");
	static_assert(std::is_same <
	              At <3, TypeList<int, char, float, double>>,
	              double
	              >::value, "");

	// PushBack
	static_assert(std::is_same <
	              PushBack<double, TypeList<int, char>>,
	              TypeList<int, char, double >
	              >::value, "");

	// PushFront
	static_assert(std::is_same <
	              PushFront<double, TypeList<int, char>>,
	              TypeList<double, int, char>
	              >::value, "");

	// PopFront
	static_assert(std::is_same <
	              PopFront<TypeList<int, char>>,
	              TypeList<char>
	              >::value, "");
	static_assert(std::is_same <
	              PopFront<TypeList<int>>,
	              TypeList<>
	              >::value, "");

	// PopBack
	static_assert(std::is_same <
	              PopBack<TypeList<int, char>>, TypeList<int>
	              >::value, "");
	static_assert(std::is_same <
	              PopBack<TypeList<int>>, TypeList<>
	              >::value, "");

	// Connect
	static_assert(std::is_same <
	              Connect <TypeList<int>, TypeList<char>>,
	              TypeList<int, char>
	              >::value, "");

	// TakeN
	static_assert(std::is_same <
	              TakeN <0, TypeList<int, char, float, double>>,
	              TypeList<>
	              >::value, "");

	static_assert(std::is_same <
	              TakeN <1, TypeList<int, char, float, double>>,
	              TypeList<int>
	              >::value, "");
	static_assert(std::is_same <
	              TakeN <4, TypeList<int, char, float, double>>,
	              TypeList<int, char, float, double>
	              >::value, "");

	// DropN
	static_assert(std::is_same <
	              DropN<0, TypeList<int>>, TypeList<int>
	              >::value, "");
	static_assert(std::is_same <
	              DropN<0, TypeList<>>, TypeList<>
	              >::value, "");
	static_assert(std::is_same <
	              DropN<2, TypeList<int, char>>, TypeList<>
	              >::value, "");


	// Insert
	static_assert(std::is_same <
	              Insert<0, int, TypeList<>>, TypeList<int>
	              >::value, "");
	static_assert(std::is_same <
	              Insert<1, int, TypeList<char>>, TypeList<char, int>
	              >::value, "");
	static_assert(std::is_same <
	              Insert<1, int, TypeList<char, double>>, TypeList<char, int, double>
	              >::value, "");

	// Erase
	static_assert(std::is_same <
	              Erase<0, TypeList<int, char>>, TypeList<char>
	              >::value, "");
	static_assert(std::is_same <
	              Erase<1, TypeList<int, char>>, TypeList<int>
	              >::value, "");
}

int main() {

}

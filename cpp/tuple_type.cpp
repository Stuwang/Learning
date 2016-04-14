// type tuple
#include <iostream>
#include <type_traits>
using namespace std;

template <class T1, class T2 = void, class T3 = void, class T4 = void>
struct my_typle {
  public:
	typedef my_typle<T2, T3, T4, void> next_type;
	typedef T1 value_type;
	static const int value = next_type::value + 1;
};

template <>
struct my_typle<void, void, void, void> {
	typedef my_typle<void, void, void, void> next_type;
	typedef void value_type;
	static const int value = 0;
};

template <typename C, int i>
struct get_type {
	typedef typename get_type<typename C::next_type, i - 1>::node_type node_type;
	typedef typename node_type::value_type value_type;
};

template <typename C>
struct get_type<C, 0> {
	typedef C node_type;
	typedef typename node_type::value_type value_type;
};

template <class C, class T, int i>
struct find_i {
	static const int value =
		is_same<typename C::value_type, T>::value ? C::value : find_i<typename C::next_type, T, i - 1>::value;
};

template <class C, class T>
struct find_i<C, T, -1> {
	static int const value = -1;
};

template <class C, class T>
struct find_it {
	static const int value = find_i<C, T, C::value>::value >= 0 ? C::value - find_i<C, T, C::value>::value : -1;
};

/*
template <class C, class T, int i>
struct find_i {
	typedef typename get_type<C, i>::value_type get_type;
	static int const value = is_same<get_type, T>::value ? i : find_i<C, T, i - 1>::value;
};

template <class C, class T>
struct find_i<C, T, -1> {
	static int const value = -1;
};

template <class C, class T>
struct find_it {
	static const int value = find_i<C, T, C::value>::value;
};
*/

int main() {
	typedef my_typle<int, char, int> my;
	// cout << is_same<get_type<my, 0>::value_type, int*>::value << endl;
	cout << find_it<my, int*>::value << endl;
}

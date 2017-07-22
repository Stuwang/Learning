#include <iostream>
#include <type_traits>

template<class ...>
struct Inner_Void_t {
	using type = void;
};

template<class ...Args>
using void_t = typename Inner_Void_t<Args...>::type;

struct A {
	int value;
};

struct B {
	int value_;
};

template<class T, typename = void>
struct HaseValue : public std::false_type {};

template<class T>
struct HaseValue<T, void_t<decltype(std::declval<T>().value)> >
: public std::true_type {};

int main() {
	std::cout << "A " << HaseValue<A>::value << std::endl;
	std::cout << "B " << HaseValue<B>::value << std::endl;
}
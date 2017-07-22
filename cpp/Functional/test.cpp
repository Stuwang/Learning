#include <iostream>

#include "invoke.h"
#include "functional.h"

namespace test {

template<class T, T value_>
struct integral_constant {
	typedef T type;
	constexpr static type value = value_;
};

template<class ...T>
struct voider {
	typedef void type;
};

template<class ...T>
using void_t = typename voider<T...>::type;

template<class T>
struct is_member_pointer: public std::false_type {};

template<typename C, typename Type>
struct is_member_pointer<Type C::*>: public std::true_type {};

template<class T>
struct is_member_function: public std::false_type {};

template<typename C, typename Type, typename...Params>
struct is_member_function<Type (C::*)(Params...)>: public std::true_type {};

// template<typename>
// struct is_member_pointer;

// template<class T>
// struct __is_member_pointer_helper
// 	: public std::false_type { };

// template<typename _Tp, typename _Cp>
// struct __is_member_pointer_helper<_Tp _Cp::*>
// 	: public std::true_type { };

// /// is_member_pointer
// template<typename _Tp>
// struct is_member_pointer
// : public std::integral_constant<bool, (__is_member_pointer_helper<
//                                        typename std::remove_cv<_Tp>::type>::value)>
//   { };

}

struct TestType {
	int a;
	int get() {return 0;};
};

int main(int argc, char const *argv[])
{

	int a;

	std::cout <<
	          test::is_member_function<decltype(&TestType::a)>::value
	          << std::endl;
	std::cout <<
	          test::is_member_function<decltype(&TestType::get)>::value
	          << std::endl;


	std::cout <<
	          test::is_member_pointer<decltype(a)>::value
	          << std::endl;

	test::test_invoke();
	return 0;
}
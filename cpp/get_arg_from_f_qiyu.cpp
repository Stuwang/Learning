#include <type_traits>
#include <iostream>
#include <tuple>
#include <functional>


//member function
#define TIMAX_FUNCTION_TRAITS(...)\
template <typename ReturnType, typename ClassType, typename... Args>\
struct function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : function_traits<ReturnType(Args...)>{};


//普通函数
//函数指针
//function/lambda
//成员函数
//函数对象

//转换为std::function和函数指针
template<typename T>
struct function_traits;

//普通函数
template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
public:
	enum { arity = sizeof...(Args) };
	typedef Ret function_type(Args...);
	typedef Ret return_type;
	using stl_function_type = std::function<function_type>;
	typedef Ret(*pointer)(Args...);

	using result_type = return_type;

	template<size_t I>
	struct arg
	{
		// static_assert(I < arity, "index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
	};

	typedef std::tuple<std::remove_cv<std::remove_reference<Args>>...> tuple_type;
};

//函数指针
template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};

//std::function
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};

TIMAX_FUNCTION_TRAITS()
TIMAX_FUNCTION_TRAITS(const)
TIMAX_FUNCTION_TRAITS(volatile)
TIMAX_FUNCTION_TRAITS(const volatile)

//函数对象
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

// template <typename Function>
// typename function_traits<Function>::stl_function_type to_function(const Function& lambda)
// {
// 	return static_cast<typename function_traits<Function>::stl_function_type>(lambda);
// }

// template <typename Function>
// typename function_traits<Function>::stl_function_type to_function(Function&& lambda)
// {
// 	return static_cast<typename function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));
// }

// template <typename Function>
// typename function_traits<Function>::pointer to_function_pointer(const Function& lambda)
// {
// 	return static_cast<typename function_traits<Function>::pointer>(lambda);
// }



void test_lambda() {
	auto lambda = [](int i) { return long(i * 10); };

	typedef function_traits<decltype(lambda)> traits;

	static_assert(std::is_same<long, traits::result_type>::value, "err");
	static_assert(std::is_same<int, traits::arg<0>::type>::value, "err");

	// std::cout << traits::value << std::endl;

};

int Test_jelper_(char, long);
void test_row_function() {
	typedef function_traits<decltype(Test_jelper_)> traits;
	static_assert(std::is_same<int, traits::result_type>::value, "err");
	static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
	static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

	// std::cout << traits::value << std::endl;
};

struct testClass {
	int test(char, long);
	int const_test(char, long)const;
	char data_;
};

void test_class_member_fun() {
	typedef function_traits<decltype(&testClass::test)> traits;
	static_assert(std::is_same<int, traits::result_type>::value, "err");
	static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
	static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

	// std::cout << traits::value << std::endl;
};

void test_const_class_member_fun() {
	typedef function_traits<decltype(&testClass::const_test)> traits;
	static_assert(std::is_same<int, traits::result_type>::value, "err");
	static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
	static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

	// std::cout << traits::value << std::endl;
};

void test_functional() {
	std::function<int(char, long)> fun;

	typedef function_traits<decltype(fun)> traits;
	static_assert(std::is_same<int, traits::result_type>::value, "err");
	static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
	static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

	// std::cout << traits::value << std::endl;
};

struct Test_Operator {
	int operator()(char, long) {
		return 1;
	}
};

void test_operator() {
	Test_Operator t;

	typedef function_traits<decltype(t)> traits;
	static_assert(std::is_same<int, traits::result_type>::value, "err");
	static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
	static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

	// std::cout << traits::value << stdnt main()
};

int main()
{
	test_lambda();
	test_row_function();
	test_class_member_fun();
	test_const_class_member_fun();
	test_functional();
	test_operator();
	return 0;
}


/**
*
* how to get the arg type and return type of all ?.here
*
* https://github.com/topcpporg/rest_rpc/blob/master/rest_rpc/base/function_traits.hpp
* http://stackoverflow.com/questions/7943525/
*    is-it-possible-to-figure-out-the-parameter-type-and-return-type-of-a-lambda
*
*/

#include <type_traits>
#include <iostream>
#include <tuple>
#include <functional>

template <typename T>
struct function_traits
: public function_traits<decltype(&T::operator())>
  {
      static constexpr char* value =
          "in fact lambda is a const member function and a class";
  };
// For generic types, directly use the result of the signature of its 'operator()'


template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...)>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };

    static constexpr char* value = "const member function";
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...)const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };

    static constexpr char* value = "member function";
};

template <typename ReturnType, typename... Args>
struct function_traits<ReturnType(Args...)>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };

    static constexpr char* value = "function";
};


void test_lambda() {
    auto lambda = [](int i) { return long(i * 10); };

    typedef function_traits<decltype(lambda)> traits;

    static_assert(std::is_same<long, traits::result_type>::value, "err");
    static_assert(std::is_same<int, traits::arg<0>::type>::value, "err");

    std::cout << traits::value << std::endl;

};

int Test_jelper_(char, long);
void test_row_function() {
    typedef function_traits<decltype(Test_jelper_)> traits;
    static_assert(std::is_same<int, traits::result_type>::value, "err");
    static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
    static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

    std::cout << traits::value << std::endl;
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

    std::cout << traits::value << std::endl;
};

void test_const_class_member_fun() {
    typedef function_traits<decltype(&testClass::const_test)> traits;
    static_assert(std::is_same<int, traits::result_type>::value, "err");
    static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
    static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

    std::cout << traits::value << std::endl;
};

void test_functional() {
    std::function<int(char, long)> fun;

    typedef function_traits<decltype(fun)> traits;
    static_assert(std::is_same<int, traits::result_type>::value, "err");
    static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
    static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

    std::cout << traits::value << std::endl;
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

    std::cout << traits::value << std::endl;
}

// void test_bind() {
//     auto fun = std::bind(&Test_jelper_, std::placeholders::_1, std::placeholders::_2);

//     typedef function_traits<decltype(fun)> traits;
//     static_assert(std::is_same<int, traits::result_type>::value, "err");
//     static_assert(std::is_same<char, traits::arg<0>::type>::value, "err");
//     static_assert(std::is_same<long, traits::arg<1>::type>::value, "err");

//     std::cout << traits::value << std::endl;
// }

// test code below:
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


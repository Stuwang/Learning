#include <iostream>

#include "Bind.h"

void test_placeholder(){
    std::cout << qy::IsPlaceHolder<decltype(qy::_1)>::value << std::endl;
}

void test_select(){
    using namespace qy;
    std::tuple<qy::PlaceHolder<1>,int> bounds{qy::_1,1};
    int data = 12;
    std::tuple<int&> args{data};
    decltype(auto) i = qy::Select<0>(bounds,args);
    i = 13;
    std::cout << data << std::endl;
}

struct A{
    int operator()(int a){
        return a;
    }

    int call(int a) const {return a+2;}

    int getData(){return data;}

    int data;
};

template<typename>
    struct __is_member_function_pointer_helper
    : public std::false_type { };

  template<typename _Tp, typename _Cp>
    struct __is_member_function_pointer_helper<_Tp _Cp::*>
    : public std::integral_constant<bool, std::is_function<_Tp>::value> {
        typedef _Tp return_type;
        typedef _Cp class_type;
    };

void test_callbale_type(){
    static_assert(std::is_member_function_pointer<decltype(&A::operator())>::value );
    static_assert(std::is_member_function_pointer<decltype(&A::call)>::value );
    // static_assert(std::is_member_function_pointer<decltype(&A::data)>::value );
    static_assert(__is_member_function_pointer_helper<decltype(&A::operator())>::value);
    static_assert(std::is_same<
    typename __is_member_function_pointer_helper<decltype(&A::operator())>::class_type,
    A>::value
    );
    static_assert(std::is_same<
    typename __is_member_function_pointer_helper<decltype(&A::call)>::return_type,
    int(int)const>::value
    );
}

void test_invoke(){
    using namespace qy;
    A a;
    a.data = 23;
    int i = 1;
}

struct CallObject{
    void operator()(){
        std::cout << "this is a object call" << std::endl;
    }
};

void test_bind(){
    using namespace qy;
    A a;
    a.data = 23;
    int i = 1;
    std::cout << "====================" << std::endl;
    std::cout << Bind(&A::operator(),a,_1)(11) << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << Bind(&A::call,a,_1)(11) << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << Bind(&A::getData,_1)(a) << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << Bind(&A::getData,_1)(&a) << std::endl;
    std::cout << "====================" << std::endl;

    CallObject o;
    Bind(o)();

    Bind(Bind(o))();
}

int main(){
    test_bind();
}
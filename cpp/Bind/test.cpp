#include <iostream>
#include <type_traits>
#include <tuple>

struct A{
    int operator()(int a){
        return a;
    }

    int call(int a){
        return a;
    }

    int call_const(int a)const{
        return a;
    }

    int data;
};

template<class T>
struct MemFn;

template<class T,class R,class ... Args>
struct MemFn<R(T::*)(Args...)>{
    using return_type = R;
    using class_type = T;

    using ArgsTuple = std::tuple<Args...>;
    template<int i>
    using arg = typename std::tuple_element<i,ArgsTuple>::type;

    static constexpr bool is_function = true;
};

template<class T,class R>
struct MemFn<R T::*>{
    using return_type = R;
    using class_type = T;

    static constexpr bool is_function = false;
};

int main(){
    int A::* a =  &A::data;
    int (A::*f)(int)const = &A::call_const;
    auto c = &A::call_const;
    static_assert(std::is_same<decltype(c),int (A::* )(int)const>::value);

    using MemberType = MemFn<int A::*>;
    static_assert(std::is_same<A,MemberType::class_type>::value );
    static_assert(std::is_same<int,MemberType::return_type>::value );

    using MemberFunction = MemFn<int (A::*)(int)>;
    static_assert(std::is_same<int,MemberFunction::arg<0> >::value );
}

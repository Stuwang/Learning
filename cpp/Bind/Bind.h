#include <type_traits>
#include <tuple>
#include <functional>

namespace qy {

template <size_t i>
struct PlaceHolder {};

PlaceHolder<1> _1;
PlaceHolder<2> _2;
PlaceHolder<3> _3;
PlaceHolder<4> _4;
PlaceHolder<5> _5;
PlaceHolder<6> _6;
PlaceHolder<7> _7;
PlaceHolder<8> _8;
PlaceHolder<9> _9;

template<class T>
struct IsPlaceHolder : public std::false_type{};

template<int i>
struct IsPlaceHolder<PlaceHolder<i>> : public std::true_type{};

// 参数选择相关
template<class T,class ...Args>
decltype(auto) SeletOne(T&& t,std::tuple<Args...>& args){
    return t;
}

template<size_t i,class ...Args>
decltype(auto) SeletOne(PlaceHolder<i>,std::tuple<Args...>& args){
    return std::get<i - 1>(args);
}

template<size_t i,class ...BoundArgs,class ...Args>
decltype(auto) Select(std::tuple<BoundArgs...>& bound_args,std::tuple<Args...>& args){
    return SeletOne(std::get<i>(bound_args),args);
}

// invoke 相关
// pure function

template<class T>
struct InvokeHelper : public InvokeHelper<decltype(&T::operator())>{};

template<class R,class ...Args>
struct InvokeHelper<R(*)(Args...)>{

    static decltype(auto) Invoke(R(*p_funtion)(Args...),Args&&... args){
        return std::forward<p_funtion>(std::forward<Args&&>(args)...);
    }
};
// member pointer
template<class R,class T>
struct InvokeHelper<R T::*>{

    static decltype(auto) Invoke(R T::* f,T t){
        return (std::forward<T&&>(t)).*f;
    }

    static decltype(auto) Invoke(R T::* f,T* t){
        return (std::forward<T&&>(*t)).*f;
    }
};

// member function
template<class R,class T,class ...Args>
struct InvokeHelper<R (T::*)(Args...)>{

    static decltype(auto) Invoke(R (T::* f)(Args...),T t,Args... args){
        return ((std::forward<T&&>(t)).*f)(std::forward<Args&&>(args)...);
    }

    static decltype(auto) Invoke(R (T::* f)(Args...),T* t,Args&&... args){
        return ((std::forward<T&&>(*t)).*f)(std::forward<Args&&>(args)...);
    }
};

// this is function invoke
// function invoke
template<class R,class ...Args>
decltype(auto) Invoke(R(*p_funtion)(Args...) ,Args&&... args){
    return std::forward<p_funtion>(std::forward<Args&&>(args)...);
}



// member pointer
template<class R,class T>
decltype(auto) Invoke(R T::* f,T t){
    return (std::forward<T&&>(t)).*f;
}

template<class R,class T>
decltype(auto) Invoke(R T::* f,T* t){
    return (std::forward<T&&>(*t)).*f;
}

// member function
#define MEMBER_FUNCTION_INVOKE(modifier)\
template<class R,class T,class ...Args>\
decltype(auto) Invoke(R (T::* f)(Args...)modifier,T t,Args... args){\
    return ((std::forward<T&&>(t)).*f)(std::forward<Args&&>(args)...);\
}\
template<class R,class T,class ...Args>\
decltype(auto) Invoke(R (T::* f)(Args...)modifier,T* t,Args&&... args){\
    return ((std::forward<T&&>(*t)).*f)(std::forward<Args&&>(args)...);\
}

MEMBER_FUNCTION_INVOKE()
MEMBER_FUNCTION_INVOKE(const)
MEMBER_FUNCTION_INVOKE(volatile)
MEMBER_FUNCTION_INVOKE(const volatile)
#undef MEMBER_FUNCTION_INVOKE

template<class T,class ...Args>
decltype(auto) Invoke(T&& t,Args&&... args){
    return (std::forward<T&&>(t))(std::forward<Args&&>(args)...);
}

template<class F,class ...BoundArgs>
class _Bind{
public:
    template<class ...Args>
    decltype(auto) operator()(Args... args){
        return BindInvoke(bounds_,
            std::forward_as_tuple(args...),
            std::make_index_sequence<std::tuple_size<BoundTuple>::value>());
    }

    template<class ...Args,size_t ...indexs>
    decltype(auto) BindInvoke(std::tuple<BoundArgs...>& bounds,std::tuple<Args...>&& args,
        const std::index_sequence<indexs...>& ){
// #define USE_CLASS_INVOKE
#ifdef USE_CLASS_INVOKE
        typedef InvokeHelper<F> InvokeType;
        return InvokeType::Invoke(f_,Select<indexs>(bounds_,args)...);
#else
        return Invoke(f_,Select<indexs>(bounds_,args)...);
#endif
    };

    _Bind(F f,BoundArgs... args):
        f_(f),bounds_(std::forward_as_tuple(args...))
    {}

private:
    F f_;
    using BoundTuple = std::tuple<BoundArgs...>;
    std::tuple<BoundArgs...> bounds_;
};

template<class F,class ...Args>
_Bind<F,Args...> Bind(F f,Args... args){
    typedef _Bind<F,Args...> ReturnType;
    return ReturnType(f,args...);
}

} // end namespace qy

#ifndef INVOKE_H__
#define INVOKE_H__

#include <type_traits>
#include <functional>

// namespace internal {

// template<typename C, typename M>
// C GetClassFromPointerToMember(M C::*);

// template<typename FunctionT, typename ObjectPointerT, typename ...ParamsT>
// constexpr decltype(auto) CheckObjectPointer(const std::false_type&, FunctionT&& pFunction, ObjectPointerT&& object, ParamsT&&...params) {
// 	return ((*std::forward<ObjectPointerT>(object)).*pFunction)(
// 	           std::forward<ParamsT>(params)...);
// }

// template<typename FunctionT, typename ObjectPointerT, typename ...ParamsT>
// constexpr decltype(auto) CheckObjectPointer(const std::true_type&, FunctionT&& pFunction, ObjectPointerT&& object, ParamsT && ...params) {
// 	return (std::forward<ObjectPointerT>(object).*pFunction)(
// 	           std::forward<ParamsT>(params)...);
// };


// template<typename FunctionT, typename ...ParamsT>
// constexpr decltype(auto) CheckMemberPointer(const std::false_type&, FunctionT& pFunction, ParamsT && ...params) {
// 	return (std::forward<FunctionT>(pFunction))(
// 	           std::forward<ParamsT>(params)...);
// };


// template<typename FunctionT, typename ObjectT, typename ...ParamsT>
// constexpr decltype(auto) CheckMemberPointer(const std::true_type&, FunctionT&& pFunction, ObjectT&& object, ParamsT && ...params) {
// 	typedef typename std::decay<ObjectT>::type ObjType;
// 	typedef typename std::is_base_of<decltype(GetClassFromPointerToMember<>(pFunction)), ObjType>::type is_basetype;
// 	return CheckObjectPointer<FunctionT, ObjectT, ParamsT...>(is_basetype(),
// 	        std::forward<ObjectT>(object),
// 	        std::forward<FunctionT>(pFunction),
// 	        std::forward<ParamsT>(params)...);
// };


// } // namespace internal

// template<class FunctionT, class ...ParamsT>
// constexpr decltype(auto) Invoke(FunctionT&& function, ParamsT&& ...params) {
// 	typedef std::is_member_pointer<FunctionT> IsMemType;
// 	return internal::CheckMemberPointer<FunctionT, ParamsT...>
// 	       (IsMemType(),
// 	        std::forward<FunctionT>(function),
// 	        std::forward<ParamsT>(params)...);
// }

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */

namespace i_stl {

template<typename _Functor, typename... _Args>
inline typename std::enable_if <
(!std::is_member_pointer<_Functor>::value
 & & !std::is_function<_Functor>::value
 & & !std::is_function<typename std::remove_pointer<_Functor>::type>::value),
 typename std::result_of < _Functor&(_Args&&...) >::type
 >::type Invoke(_Functor& __f, _Args&&... __args)
{
	return __f(std::forward<_Args>(__args)...);
}

template<typename _Functor, typename... _Args>
inline typename std::enable_if <
(std::is_member_pointer<_Functor>::value
 & & !std::is_function<_Functor>::value
 & & !std::is_function<typename std::remove_pointer<_Functor>::type>::value),
 typename std::result_of < _Functor(_Args&&...) >::type
 >::type Invoke(_Functor& __f, _Args&&... __args)
{
	return std::mem_fn(__f)(std::forward<_Args>(__args)...);
}

// To pick up function references (that will become function pointers)
template<typename _Functor, typename... _Args>
inline
typename std::enable_if <
(std::is_pointer<_Functor>::value
 && std::is_function<typename std::remove_pointer<_Functor>::type>::value),
 typename std::result_of < _Functor(_Args&&...) >::type
 >::type Invoke(_Functor __f, _Args&&... __args)
{
	return __f(std::forward<_Args>(__args)...);
}

}

namespace test {

struct Type {
	int get() {
		std::cout << __FUNCTION__ << std::endl;
		return 0;
	}
};

int get_static_function(int v) {
	std::cout << __FUNCTION__ << std::endl;
	return 1;
}

void test_invoke() {
	using i_stl::Invoke;

	static_assert(
	    std::is_member_pointer<decltype(get_static_function)>::value == false, "");
	Invoke(&get_static_function, 1);
	Type t;

	static_assert(!std::is_function<decltype(&Type::get)>::value, "");
	static_assert(!std::is_function<typename std::remove_pointer <
	              decltype(&Type::get) >::type>::value, "");
	static_assert(std::is_member_pointer<decltype(&Type::get)>::value, "");

	static_assert(
	    std::is_same <
	    typename std::result_of<decltype(&Type::get)(Type*)>::type,
	    int >::value, "");

	// Invoke(&Type::get, &t);
}

}


#endif
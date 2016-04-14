// 网上大牛的一个typle 实现

#include <iostream>
using namespace std;

// 元容器
template <typename T0 = void, typename T1 = void, typename T2 = void,
		  typename T3 = void>
class meta_container {
  public:
	typedef T0 type;
	typedef meta_container<T1, T2, T3, void> next_node; // 参数移位了
	static const int size = next_node::size + 1; // 非 null_type 模板参数个数
};
template <> // 特例，递归终止
class meta_container<void, void, void, void> {
  public:
	typedef void type;
	static const int size = 0;
};

// 访问元容器中的数据
template <typename C, unsigned i> class get {
  public:
	static_assert(i < C::size,
				  "get<C,i>: index exceed num"); // C++11 引入静态断言
	typedef typename get<C, i - 1>::c_type::next_node c_type;
	typedef typename c_type::type ret_type;
};
template <typename C> class get<C, 0> {
  public:
	static_assert(0 < C::size,
				  "get<C,i>: index exceed num"); // C++11 引入静态断言
	typedef C c_type;
	typedef typename c_type::type ret_type;
};

// 在元容器中查找某个类型，找到返回索引，找不到返回 -1
template <typename T1, typename T2> class same_type {
  public:
	enum {
		ret = false
	};
};
template <typename T> class same_type<T, T> {
  public:
	enum {
		ret = true
	};
};

template <bool c, typename Then, typename Else> class IF_ {};
template <typename Then, typename Else> class IF_<true, Then, Else> {
  public:
	typedef Then reType;
};
template <typename Then, typename Else> class IF_<false, Then, Else> {
  public:
	typedef Else reType;
};
template <int i> class number {
  public:
	static const int ret = i;
};
template <typename C, typename T, int i> class find_i {
  public:
	typedef typename get<C, i>::ret_type get_type;
	static const int ret = IF_<same_type<get_type, T>::ret, number<i>,
							   find_i<C, T, i - 1> >::reType::ret;
};
template <typename C, typename T> class find_i<C, T, -1> {
  public:
	static const int ret = -1;
};

template <typename C, typename T> class find_it {
  public:
	static const int ret = find_i<C, T, C::size - 1>::ret;
};

int main() {
	typedef meta_container<int, int, const int> mc;
	int a = 9999;
	get<mc, 1>::ret_type aref = a;
	// std::cout << mc::size << '\n';
	// std::cout << aref << '\n';
	std::cout << find_it<mc, int>::ret << '\n';
    std::cout << find_it<mc, float>::ret << '\n';
}

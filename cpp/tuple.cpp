// 自己实现的tuple 学习用

#include <iostream>
using namespace std;

struct Null_Type {};

template <class T1, class T2 = Null_Type, class T3 = Null_Type, class T4 = Null_Type>
class my_typle {
  public:
	typedef my_typle<T2, T3, T4, Null_Type> next_type;
	typedef T1 data_type;

	static const int num = next_type::num + 1;
	data_type data;
	next_type next;
	my_typle() {};
	my_typle(const T1& t1, const T2& t2 = T2(), const T3& t3 = T3(), const T4& t4 = T4())
		: data(t1), next(t2, t3, t4) {};
};

template <class T1>
class my_typle<T1, Null_Type, Null_Type, Null_Type> {
  public:
	typedef T1 data_type;

	static const int num = 1;
	data_type data;
	my_typle() {};
	my_typle(const T1& t1, const Null_Type& t2 = Null_Type(),
			 const Null_Type& t3 = Null_Type(), const Null_Type& t4 = Null_Type())
		: data(t1) {};
};

// template <int i, class T1 = Null_Type, class T2 = Null_Type, class T3 = Null_Type, class T4 = Null_Type>
// class shift {
//   public:
// 	typedef my_typle<T1, T2, T3, T4> node_type;
// 	typedef typename node_type::data_type data_type;

// 	typedef my_typle<T2, T3, T4, Null_Type> return_type;
// 	static return_type& get_node(my_typle<T1, T2, T3, T4>& tuple) {
// 		return shift<i - 1, T2, T3, T4, Null_Type>::get_node(tuple.next);
// 	}
// };
// template <class T1, class T2, class T3, class T4>
// class shift<0, T1, T2, T3, T4> {
//   public:
// 	typedef my_typle<T1, T2, T3, T4> node_type;
// 	typedef typename node_type::data_type data_type;

// 	static node_type& get_node(my_typle<T1, T2, T3, T4>& tuple) {
// 		return tuple;
// 	}
// };

template <int i, class T1, class T2, class T3, class T4>
class shift {
  public:
	typedef typename shift<i - 1, T1, T2, T3, T4>::node_type::next_type node_type;
	typedef typename node_type::data_type data_type;

	static node_type& get_node(my_typle<T1, T2, T3, T4>& tuple) {
		return shift<i - 1, T1, T2, T3, T4>::get_node(tuple).next;
	}
};
template <class T1, class T2, class T3, class T4>
class shift<0, T1, T2, T3, T4> {
  public:
	typedef my_typle<T1, T2, T3, T4> node_type;
	typedef typename node_type::data_type data_type;

	static node_type& get_node(my_typle<T1, T2, T3, T4>& tuple) {
		return tuple;
	}
};

template <int i, class T1, class T2, class T3, class T4>
typename shift<i, T1, T2, T3, T4>::data_type& get(my_typle<T1, T2, T3, T4>& tuple) {
	return shift<i, T1, T2, T3, T4>::get_node(tuple).data;
};

int main() {
	my_typle<int, char, double> a(12, 'a', 1.3);
	cout << a.num << endl;
	cout << get<1>(a) << endl;
}

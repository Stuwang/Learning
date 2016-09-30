#include <string>
#include <tuple>
#include <type_traits>
#include <iostream>

using namespace std;

/// pop front 
template<class...>
struct tuple_pop_front;

template<class T,class...Arg>
struct tuple_pop_front<tuple<T,Arg...>>{
  typedef tuple<Arg...> value_type;
};

///  this is error !!!
template<class... >
struct tuple_pop_back;

template<class ...Arg,class T>
struct tuple_pop_back<tuple<Arg...,T>>{
  typedef tuple<Arg...> value_type;
};

///
template<class ...>
struct tuple_push_front;

template<class T, class ...Arg>
struct tuple_push_front<tuple<Arg...>,T>{
  typedef tuple<T, Arg...> value_type;
};

////
template<class ... >
struct tuple_push_back;

template<class T,class...Args>
struct tuple_push_back<tuple<Args...>,T>{
  typedef tuple<Args..., T> value_type;
};

int main()
{

  typedef tuple<int, double, string> all;
  typedef tuple<int, double> back;
  typedef tuple<double, string> front;

  using type = tuple_pop_front<all>::value_type;
  cout << std::is_same<front, type >::value << endl;

//  std::cin.get();
  return 0;
}

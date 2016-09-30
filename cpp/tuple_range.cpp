#include <iostream>
#include <tuple>

using namespace std;

template<int ...Index>
struct TupleIndex { };

template<int N, int ...Index>
struct MakeTupleIndex : MakeTupleIndex<N - 1,N -1 ,Index...> { };


template<int ... Index>
struct MakeTupleIndex <0, Index ...>{
  typedef TupleIndex<Index...> type;
};


void Print(){
};

template<class T,class...Args>
void Print(const T& data,const Args&...args){
  cout << data << endl;
  Print(args...);
}

template<int ...index,class Tuple>
void PrintTupleHelper(const TupleIndex<index...>& Index,const Tuple& data){
  Print(std::get<index>(data)...);
};

template<class ...Args>
void PrintTuple(const tuple<Args...>& data){
	typedef tuple<Args...> Tuple;
	typedef typename MakeTupleIndex<std::tuple_size<Tuple>::value>::type value_type;
	PrintTupleHelper(value_type(),data);
}

void TestPrintTuple(){
  std::tuple<int, int, string> a { 1, 2, "aaaa" };
  PrintTuple(a);
}

int main(){
	TestPrintTuple();
}

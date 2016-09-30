// my future, promise
// only trival data, and no exception
#include <iostream>
#include <utility>
#include <chrono>

#include "MyFuture.h"
// template<class T>
// Future<T> Async();

using namespace std;
using namespace pp;

int main() {
	Promise<int> p;
	Future<int> f = p.GetFuture();

	thread t{[&]() {
		this_thread::sleep_for(chrono::milliseconds(1000));
		std::cout << "set value " << std::endl;
		p.SetValue(20);
	}};

	std::cout << "get " << f.Get() << std::endl;
	t.join();
}
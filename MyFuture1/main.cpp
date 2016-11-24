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

void TEST_MYFUTURE() {
	Promise<int> p;
	Future<int> f = p.GetFuture();

	thread t{[&]() {
		assert(p.Valid());
		auto p2 = std::move(p);
		assert(!p.Valid());
		assert(p2.Valid());
		Promise<int> p3{std::move(p2)};
		assert(!p2.Valid());
		// this_thread::sleep_for(chrono::milliseconds(1000));
		std::cout << "set value " << std::endl;
		p3.SetValue(20);
	}};
	assert(f.Valid());
	auto f2 = std::move(f);
	assert(!f.Valid());
	assert(f2.Valid());
	Future<int> f3{std::move(f2)};
	assert(!f2.Valid());
	std::cout << "get " << f3.Get() << std::endl;
	t.join();
}

void TEST_VOID_MYFUTURE() {
	Promise<void> p;
	Future<void> f = p.GetFuture();

	thread t{[&]() {
		assert(p.Valid());
		auto p2 = std::move(p);
		assert(!p.Valid());
		assert(p2.Valid());
		Promise<void> p3{std::move(p2)};
		assert(!p2.Valid());
		// this_thread::sleep_for(chrono::milliseconds(1000));
		std::cout << "set value " << std::endl;
		p3.SetValue();
	}};
	assert(f.Valid());
	auto f2 = std::move(f);
	assert(!f.Valid());
	assert(f2.Valid());
	Future<void> f3{std::move(f2)};
	assert(!f2.Valid());
	f3.Get();
	std::cout << "get ok" << std::endl;
	t.join();
}

int fuck() {
	cout << "hahhaha " << endl;
	return 20;
}

void TEST_ASYNC() {
	std::function<int()> fun = fuck;
	auto f = Async(fuck);
	std::cout << "get " << f.Get() << std::endl;

	auto f2 = Async([]() {
		cout << "hahhaha -------- " << endl;
		return 20;
	});
	std::cout << "get " << f2.Get() << std::endl;
};

int main() {
	TEST_MYFUTURE();
	TEST_VOID_MYFUTURE();
	TEST_ASYNC();
}
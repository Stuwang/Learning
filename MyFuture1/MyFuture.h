#ifndef MYFUTURE_H
#define MYFUTURE_H

#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <cassert>
#include <cstddef>
#include <utility>

namespace pp {

namespace Detail {
enum class State : int {
	start,
	setted,
	getted,
};

template<class T>
struct Storgedata {
	Storgedata()
		: state_(State::start)
		, data_() {};
	~Storgedata() {
		Assert();
	}

	void Assert() {
		assert(state_ != State::start);
	};

	bool wait(int timeout) {
		assert(false);
		return true;
	};

	void wait() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (state_ == State::start) {
			cond_.wait(lock);
		}
	};

	T Get() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (state_ == State::start) {
			cond_.wait(lock);
		}
		state_ = State::getted;
		return data_;
	};

	void Set(T data) {
		std::unique_lock<std::mutex> lock(mutex_);
		data_ = data;
		state_ = State::setted;
		cond_.notify_one();
	};

	Storgedata(const Storgedata&);
	Storgedata(Storgedata&&);
	Storgedata& operator=(Storgedata&&) = delete;
	Storgedata& operator=(const Storgedata&) = delete;

	std::mutex mutex_;
	std::condition_variable cond_;
	State state_;
	T data_;
};

template<>
struct Storgedata<void> {
	Storgedata()
		: state_(State::start) {};
	~Storgedata() {
		Assert();
	}

	void Assert() {
		assert(state_ != State::start);
	};

	bool wait(int timeout) {
		assert(false);
		return true;
	};

	void wait() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (state_ == State::start) {
			cond_.wait(lock);
		}
	};

	void Get() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (state_ == State::start) {
			cond_.wait(lock);
		}
		state_ = State::getted;
	};

	void Set() {
		std::unique_lock<std::mutex> lock(mutex_);
		state_ = State::setted;
		cond_.notify_one();
	};

	Storgedata(const Storgedata&);
	Storgedata(Storgedata&&);
	Storgedata& operator=(Storgedata&&) = delete;
	Storgedata& operator=(const Storgedata&) = delete;

	std::mutex mutex_;
	std::condition_variable cond_;
	State state_;
};
};

template<class T>
class Future {
public:
	using DateType = Detail::Storgedata<T>;
	Future(): data_(nullptr) {};
	explicit Future(DateType* p): data_(p) {assert(data_);};
	~Future() {delete data_;};
	Future(const Future&) = delete;
	Future& operator=(const Future&) = delete;
	Future(Future&&m): data_(m.data_) {
		m.data_ = nullptr;
	};

	Future& operator=(Future&&m) {
		Future().Swap(*this);
		this->Swap(m);
		return *this;
	};

	T Get() {
		return data_->Get();
	};

	bool Valid()const {return nullptr != data_;};
	void Wait()const {return data_->wait();};
	void Swap(Future& f) {
		std::swap(data_, f.data_);
	}
	// bool WaitFor(int timeout);
private:
	DateType *data_;
};

template<>
class Future<void> {
public:
	using DateType = Detail::Storgedata<void>;
	Future(): data_(nullptr) {};
	explicit Future(DateType* p): data_(p) {assert(data_);};
	~Future() {delete data_;};
	Future(const Future&) = delete;
	Future& operator=(const Future&) = delete;
	Future(Future&&m): data_(m.data_) {
		m.data_ = nullptr;
	};

	Future& operator=(Future&&m) {
		Future().Swap(*this);
		this->Swap(m);
		return *this;
	};

	void Get() {
		return data_->Get();
	};

	bool Valid()const {return nullptr != data_;};
	void Wait()const {return data_->wait();};
	void Swap(Future& f) {
		std::swap(data_, f.data_);
	}
	// bool WaitFor(int timeout);
private:
	DateType *data_;
};

template<class T>
class Promise {
public:
	using DateType = typename Detail::Storgedata<T>;

	Promise(const Promise&) = delete;
	Promise& operator=(const Promise& m) = delete;

	Promise()
		: data_(new DateType()) {};


	Promise(Promise&& m)
		: data_(m.data_) {m.data_ = nullptr;};

	Promise& operator=(Promise&&m) {
		Promise().Swap(*this);
		this->Swap(m);
		return *this;
	};

	~Promise() {
		if (data_) {
			data_->Assert();
		}
	};

	void SetValue(const T& data) {
		data_->Set(data);
	};

	// void SetValue(T& data) {

	// };

	// void SetValue(T&& data) {

	// };

	Future<T> GetFuture() {
		assert(Valid());
		return Future<T> {data_};
	};

	void Swap(Promise& p) {
		std::swap(data_, p.data_);
	};

	bool Valid()const {return nullptr != data_;}

private:
	DateType *data_;
};

template<>
class Promise<void> {
public:
	using DateType = typename Detail::Storgedata<void>;

	Promise(const Promise&) = delete;
	Promise& operator=(const Promise& m) = delete;

	Promise()
		: data_(new DateType()) {};


	Promise(Promise&& m)
		: data_(m.data_) {m.data_ = nullptr;};

	Promise& operator=(Promise&&m) {
		Promise().Swap(*this);
		this->Swap(m);
		return *this;
	};

	~Promise() {
		if (data_) {
			data_->Assert();
		}
	};

	void SetValue() {
		data_->Set();
	};

	// void SetValue(T& data) {

	// };

	// void SetValue(T&& data) {

	// };

	Future<void> GetFuture() {
		assert(Valid());
		return Future<void> {data_};
	};

	void Swap(Promise& p) {
		std::swap(data_, p.data_);
	};

	bool Valid()const {return nullptr != data_;}

private:
	DateType *data_;
};

}// namespace pp

#endif
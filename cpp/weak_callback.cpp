// #include <iostream>
#include <functional>
#include <memory>
#include <cstdio>

// template<class Self,class Func,class ...Args>
// std::function<> WeakCall()



// A barely usable WeakCallback
//
// FIXME: support std::shared_ptr as well, maybe using template template parameters
template<typename CLASS, typename... ARGS>
class WeakCallback
{
public:

	WeakCallback(const std::weak_ptr<CLASS>& object,
	             const std::function<void (CLASS*, ARGS...)>& function)
		: object_(object), function_(function)
	{
	}

	// Default dtor, copy ctor and assignment are okay

	void operator()(ARGS&&... args) const
	{
		std::shared_ptr<CLASS> ptr(object_.lock());
		if (ptr)
		{
			function_(ptr.get(), std::forward<ARGS>(args)...);
		}
		else
		{
			// LOG_TRACE << "expired";
			// std::cout << "expired" << std::endl;
			printf("expired\n");
		}
	}

private:

	std::weak_ptr<CLASS> object_;
	std::function<void (CLASS*, ARGS...)> function_;
};

template<typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS>& object,
        void (CLASS::*function)(ARGS...))
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

template<typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS>& object,
        void (CLASS::*function)(ARGS...) const)
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

template<typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::weak_ptr<CLASS>& object,
        void (CLASS::*function)(ARGS...))
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

/**
 * @brief      Makes a weak callback.
 *
 * @param[in]  object     The object
 * @param[in]  <unnamed>  { parameter_description }
 *
 * @tparam     CLASS      { description }
 * @tparam     ARGS       { description }
 *
 * @return     { description_of_the_return_value }
 */
template<typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::weak_ptr<CLASS>& object,
        void (CLASS::*function)(ARGS...) const)
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

//

class Executer {
public:
	void Run(const std::function<void()>& task) {
		task();
	};
};

class Call : public std::enable_shared_from_this<Call> {
public:
	// void Start(Executer * e);

	void Print() {
		// std::cout << "print " << std::endl;
		printf("print\n");
	};
	void WeakPrint() {
		// std::cout << "weak print " << std::endl;
		printf("weak print\n");
	};
	~Call() {
		// std::cout << "destructer " << std::endl;
		printf("destructor\n");
	}
};

int main() {
	Executer executer;
	std::weak_ptr<Call> w_ptr;
	{
		// auto ptr = std::make_shared<Call>(new Call());
		w_ptr = std::make_shared<Call>();
		// w_ptr
	}
	// executer.Run([w_ptr]() {
	// 	auto p = w_ptr.lock();
	// 	if (p) {
	// 		p->WeakPrint();
	// 	} else {
	// 		std::cout << "no object " << std::endl;
	// 	}
	// });

	executer.Run(makeWeakCallback(w_ptr, &Call::Print));

}

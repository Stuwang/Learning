#include <iostream>
#include <string>

void Push(std::string& out, int i) {
	char data[32] = {0};
	snprintf(data, 32, "%d", i);
	out += " ";
	out += data;
};

void Push(std::string& out, const std::string& i) {
	out += " ";
	out += i;
};

void Push(std::string& out, double i) {
	char data[32] = {0};
	snprintf(data, 32, "%f", i);
	out += " ";
	out += data;
};

template<class First, class ...Args>
void Push(std::string& out, const First& f, const Args&... args) {
	Push(out, f);
	Push(out, args...);
}

template<class ...Args>
std::string PushData(const Args& ... args){
	std::string ret;
	Push(ret,args...);
	return ret;
}

#define SERA(...) 					\
std::string Sera()const {			\
	std::string ret;				\
	Push(ret, __VA_ARGS__);			\
	return ret;						\
};

struct TestStruct {
	int i;
	std::string str;
	double d;
	SERA(i, str, d);
};

int main() {
	TestStruct s;
	s.i = 12;
	s.str = "hahahha";
	s.d = 1.111;

	std::string out = s.Sera();
	std::cout << out << std::endl;
}
#include <iostream>

using namespace std;

class Ia{
public:
	virtual void foo() = 0;
};

class A:virtual  public Ia{
public:
	virtual void foo(){
		cout << "A" << endl;
	};
};

class Ib{
public:
	virtual void foo() = 0;	
};

class B:virtual public Ia{
public:
	virtual void foo(){
		cout << "B" << endl;
	};
};

class All: public A,public B{
public:
	virtual void foo(){
		cout << "fuck" << endl;
	};
};

int main(){
	All * all = new All();
	Ia * a = (all);
	a->foo();
}
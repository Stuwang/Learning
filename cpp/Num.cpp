#include <iostream>

namespace fly {

static int gcd(int a, int b) {

	if (a == 0 || b == 0) {
		return 0;
	}

	if (a < b) {
		std::swap(a, b);
	}
	while (a % b) {
		int tmp  = a;
		a = b;
		b = tmp % b;
	}
	return b;
}

class Num {
public:
	Num()
		: num(0)
		, fenzi(0)
		, fenmu(1)
	{

	};

	Num(int a, int b, int c)
		: num(a)
		, fenzi(b)
		, fenmu(c)
	{

	};

	Num(int a)
		: num(a)
		, fenzi(0)
		, fenmu(1)
	{

	};

	Num(double a);

	void shift() {
		num += fenzi / fenmu;
		fenzi %= fenmu;
		int get = gcd(fenzi, fenmu);

		if (get) {
			fenzi /= get;
			fenmu /= get;
		}

		if (fenmu < 0) {
			fenmu = -fenmu;
			fenzi = - fenzi;
		}

		if (num > 0 && fenmu * fenzi < 0 ) {
			num--;
			fenzi += fenmu;
			shift();
		} else if (num < 0 && fenmu * fenzi > 0 ) {
			num++;
			fenzi -= fenmu;
			shift();
		}
	}

	Num operator-() const {
		Num ret ;
		ret.num = -num;
		ret.fenzi = -fenzi;
		ret.fenmu = fenmu;
		ret.shift();
		return ret;
	}

	friend Num operator+(const Num& n1, const Num& n2) {
		Num ret;
		ret.num = n1.num + n2.num;
		ret.fenzi = n1.fenzi * n2.fenmu + n2.fenzi * n1.fenmu;
		ret.fenmu = n1.fenmu * n2.fenmu;
		ret.shift();
		return ret;
	};
	friend Num operator-(const Num& n1, const Num& n2) {
		return n1 + (-n2);
	};
	friend Num operator*(const Num& n1, const Num& n2) {
		Num ret;
		ret.num = n1.num * n2.num;
		ret.fenzi = (ret.num) * n1.fenmu * n2.fenmu + n1.fenzi * n2.fenzi;
		ret.fenmu = n1.fenmu * n2.fenmu;
		ret.shift();
		return ret;
	};
	// friend Num operator/(const Num& n1,const Num& n2);

	Num Up() const{
		Num ret;
		if (*this > 0 && fenzi != 0 ) {
			ret = Num(num + 1, 0, 1);
		} else {
			ret = Num(num, 0, 1);
		}
		return ret;
	};
	Num Down()const {
		if (*this < 0 && fenzi != 0 ) {
			return Num(num - 1, 0, 1);
		}
		return Num(num, 0, 1);
	};

	Num ssheru() {

	};

	friend bool operator == (Num n1, Num n2) {
		n1.shift();
		n2.shift();
		return n1.num == n2.num && n1.fenzi	== n2.fenzi && n1.fenmu == n2.fenmu;
	}

	friend bool operator < (Num n1, Num n2) {
		n1.shift();
		n2.shift();

		if ( n1.num < n2.num ) {
			return true;
		} else if (n1.num == n2.num) {
			return n1.fenzi * n2.fenmu < n2.fenzi * n1.fenmu;
		} else {
			return false;
		}
	}

	///
	friend bool operator <= (const Num& n1, const Num& n2) {
		return (n1 < n2 || n1 == n2);
	}

	friend bool operator > (const Num& n1, const Num& n2) {
		return !(n1 > n2) && !(n1 == n2);
	}

	friend bool operator >= (const Num& n1, const Num& n2) {
		return !(n1 < n2);
	}

	friend bool operator != (const Num& n1, const Num& n2) {
		return !(n1 == n2);
	}

	friend std::ostream& operator<<(std::ostream& self, const fly::Num& num) {
		self << num.num;
		if (num.fenzi) {
			self << "+" << num.fenzi << "/" << num.fenmu;
		}
		return self;
	}


private:
	int num;
	int fenzi;
	int fenmu;
};

};

int main() {
	fly::Num a(1, 1, 2);
	fly::Num b(1, 1, 2);
	std::cout << a << "  " << -a << " " << (a - b) << std::endl;
	std::cout << a + 1 << std::endl;
	std::cout << a - 1 << std::endl;
	std::cout << a - 2 << std::endl;
	std::cout << "Num " << fly::Num(0, -1, 2) << std::endl;
	std::cout << fly::Num(0, -1, 2)*fly::Num(0, 1, 2)  << std::endl;

	fly::Num n1 = a.Up();
	std::cout <<  n1 << std::endl;
	std::cout << fly::Num(0, -1, 2).Down()  << std::endl;
}

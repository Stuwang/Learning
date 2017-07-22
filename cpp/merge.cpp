#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

template<class PushBackIter, class ConstIter>
void my_merge(PushBackIter result,
              ConstIter start_1, ConstIter end_1,
              ConstIter start_2, ConstIter end_2)
{
	while (start_1 != end_1 && start_2 != end_2 ) {
		if (*start_1 < *start_2) {
			*result++ = *start_1++;
		} else {
			*result++ = *start_2++;
		}
	}

	while (start_1 != end_1) {
		*result++ = *start_1++;
	}

	while (start_2 != end_2) {
		*result++ = *start_2++;
	}
};

int main() {
	int a[] = {2, 4, 6, 8, 10};
	int b[] = {1, 3, 5, 7, 9};
	int result[10];
	my_merge(result, begin(a), end(a), begin(b), end(b));
	std::copy(begin(result), end(result), ostream_iterator<int>(std::cout, " "));
	std::cout << endl;
}
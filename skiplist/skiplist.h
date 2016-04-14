#include <cstdlib>
#include <cassert>

namespace yuan {

template<class T>
struct Cmpare {
	bool operator ()(const T& t1, const T& t2) const
	{
		return t1 < t2;
	};
};

template<class KeyT, class ValueT, class Comp = Cmpare<KeyT> >
class skiplist {
public:
	struct Node;
	struct Iterator;

	typedef Iterator iterator;
public:
	skiplist(Comp cmp_): cmp(cmp_), head(NewNode( 0, 0, MAX_HEIGHT ) )
	{
		for (int i = 0; i < MAX_HEIGHT; i++) {
			head->SetNext(i, NULL);
		}
		srand((int)time(0));
	}

	skiplist(): cmp(Comp() ), head(NewNode( 0, 0, MAX_HEIGHT ) )
	{
		for (int i = 0; i < MAX_HEIGHT; i++) {
			head->SetNext(i, NULL);
		};
		srand((int)time(0));
	}

	Iterator begin() { return Iterator( head->Next(0) );};
	Iterator end() { return Iterator(); };
public:
	int RandomHeight();
	Node * NewNode(const KeyT& key , const ValueT& value , int height);
	Node * FindLessThan(const KeyT& key);
	Node * FindGreaterOrEqual(const KeyT& key, Node** prev);
	Node * FindLast();
	void Insert(const KeyT& key, const ValueT& value);
// private:
	Comp cmp;
	Node * head;
	const static int MAX_HEIGHT = 15;
	static const unsigned int kBranching = 4;
};

template<class KeyT, class ValueT, class Comp  >
struct skiplist<KeyT, ValueT, Comp >::Node
{
	const KeyT key;
	ValueT value;
	int height;
	Node* next[1];

	Node(const KeyT& key_, const ValueT& value_)
		: key(key_),
		  value(value_)
	{	};

	Node * Next(int level) { return next[level];};
	void SetNext(int level, Node* p) { next[level] = p ;};
};

template<class KeyT, class ValueT, class Comp  >
struct skiplist<KeyT, ValueT, Comp >::Iterator {
	Node * ptr;
	Iterator(): ptr(NULL) {};
	Iterator(Node * p ): ptr(p) {};
	Iterator & operator++() { ptr = ptr->Next(0); return *this ;};
	Iterator operator++(int) {Iterator a = *this; ++*this ; return a; };
	const KeyT & key() const {return ptr->key;};
	const ValueT & value() const {return ptr->value;};
	bool operator==(const Iterator & l) { return ptr = l.ptr ; };
	bool operator!=(const Iterator & l) { return ptr != l.ptr ; };
};

template<class KeyT, class ValueT, class Comp   >
int
skiplist<KeyT, ValueT, Comp >::RandomHeight()
{
	int height = 1;
	while (height < MAX_HEIGHT && ((rand() % kBranching) == 0)) {
		height++;
	}
	assert(height > 0);
	assert(height <= MAX_HEIGHT);
	return height;
}


template<class KeyT, class ValueT, class Comp   >
struct skiplist<KeyT, ValueT, Comp >::Node *
skiplist<KeyT, ValueT, Comp >::NewNode(const KeyT& key , const ValueT& value , int height)
{
	Node * p = static_cast<Node*>(
	               malloc(sizeof(Node) + (height - 1) * sizeof(Node*)) );
	return new (p) Node(key, value);
};

template<class KeyT, class ValueT, class Comp >
typename skiplist<KeyT, ValueT, Comp >::Node *
skiplist<KeyT, ValueT, Comp >::FindLessThan(const KeyT& key)
{
	Node * p = head;
	int level = MAX_HEIGHT - 1 ;
	while (true) {
		Node * next = p->Next(level);
		if ( next == NULL  || !cmp(next->key, key)) {
			if (level == 0) {
				return p;
			} else {
				level--;
			}
		} else {
			p = next;
		}
	}
};

template<class KeyT, class ValueT, class Comp >
typename skiplist<KeyT, ValueT, Comp >::Node *
skiplist<KeyT, ValueT, Comp >::FindGreaterOrEqual(const KeyT& key, Node** prev)
{
	Node * p = head;
	int level = MAX_HEIGHT - 1 ;
	while (true) {
		Node * next = p->Next(level);
		if ( next && !cmp(key, next->key) ) {
			p = next;
		} else {
			if (prev) prev[level] = p;
			if (level == 0) {
				return next;
			} else {
				level--;
			}
		}
	}
};

template<class KeyT, class ValueT, class Comp >
typename skiplist<KeyT, ValueT, Comp >::Node *
skiplist<KeyT, ValueT, Comp >::FindLast()
{
	Node * p = head;
	int level = MAX_HEIGHT - 1 ;
	while (true) {
		Node * next = p->Next(level);
		if (next != NULL ) {
			p = next;
		} else {
			if (level == 0 ) {
				return p;
			} else {
				level -- ;
			}
		}
	}
};

template<class KeyT, class ValueT, class Comp >
void
skiplist<KeyT, ValueT, Comp >::Insert(const KeyT& key, const ValueT& value)
{
	Node * prev[MAX_HEIGHT];
	Node * p = FindGreaterOrEqual(key, prev);

	int height = RandomHeight();
	// std::cout << "height " << height << std::endl;
	for (int i = height ; i < MAX_HEIGHT ; i++ ) {
		prev[i] = head;
	}

	p = NewNode(key, value, height );
	p->height = height ;
	for (int i = 0; i < height; i++) {
		p ->SetNext(i, prev[i]->Next(i));
		prev[i]->SetNext(i, p);
	}
};

};

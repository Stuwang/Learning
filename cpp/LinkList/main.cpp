#include <iostream>
#include <vector>

#include "LinkList.h"

using namespace util;

struct Node : public LinkNode <Node>{
	int value;

	Node() 
		: LinkNode<Node>(this)
	{

	}

	void Init() {
		data = this;
	}

	~Node() {
		this->Remove();
	}

};

void TestLinkList() {
	typedef LinkList<Node> NodeList;
	typedef LinkNode <Node>* NodeIterator;

	NodeList list;

	std::vector<Node> n(10);
	for (int i = 0;i < 10;i++) {
		n[i].value = i;
		n[i].Init();
		n[i].AddTail(&list);
	}

	for (NodeIterator i = list.root_.next; i != &list.root_;i = i->next) {
		std::cout << i->Data()->value << std::endl;
	}
}

int main() {
	TestLinkList();
	std::cin.get();
}
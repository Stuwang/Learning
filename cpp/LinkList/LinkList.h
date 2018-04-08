#pragma once

#include <cassert>

namespace util {

template<class T>
struct LinkList;

template<class T>
struct LinkNode{
	typedef LinkNode<T> SelfType;
	typedef LinkList<T> LinkType;

	SelfType* prev;
	SelfType* next;
	LinkType* continer;
	T* data;
public:
	LinkNode() {
		prev = next = nullptr;
		continer = nullptr;
		data = nullptr;
	}

	LinkNode(T* data) {
		prev = next = nullptr;
		continer = nullptr;
		data = nullptr; 
	}

	void Remove() {
		assert(continer);
		continer->Remove(this);
	};

	void AddHead(LinkType* c) {
		this->continer = c;
		c->AddInHead(this);
	};

	void AddTail(LinkType* c) {
		this->continer = c;
		c->AddInTail(this);
	}

	LinkType* GetContiner() {
		return continer;
	}

	T* Data() {
		return data;
	}
};

template<class T>
struct LinkList{
public:
	typedef LinkNode<T> NodeType;

	static void connect(NodeType* p, NodeType* n) {
		p->next = n;
		n->prev = p;
	}

	LinkList() {
		root_.continer = NULL;
		connect(&root_, &root_);
	};

	~LinkList() {
		assert(Empty());
	};

	void AddInHead(NodeType* node) {
		assert(this == node->GetContiner());

		auto n = root_.next;
		connect(&root_, node);
		connect(node, n);
	}

	void AddInTail(NodeType* node) {
		assert(this == node->GetContiner());
		auto p = root_.prev;
		connect(p, node);
		connect(node, &root_);
	}

	void Remove(NodeType* node) {
		assert(this == node->GetContiner());
		connect(node->prev, node->next);
		node->prev = nullptr;
		node->next = nullptr;
	}

	bool Empty()const {
		return root_.next == &root_ &&
			root_.prev == &root_;
	}

//private:
	// head 's prev and tail 's next 
	//   is mot use, so we use one
	NodeType root_;
};

}
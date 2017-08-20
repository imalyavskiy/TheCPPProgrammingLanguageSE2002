// 13_Templates_num_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class T> class List
{
	struct Link
	{
		Link* pre = nullptr;
		Link* suc = nullptr;

		T val;

		Link(Link* p, Link* s, const T& v)
			: pre(p)
			, suc(s) 
			, val(v)
		{
			if (p) 
				p->suc = this;
			if (s)
				s->pre = this;
		}
	};

	Link* head = nullptr;
	Link* tail = nullptr;

public:

	~List()
	{
		Link* h = head;
		head = tail = nullptr;

		while(h)
		{
			Link* p = h;
			h = p->suc;
			delete p;
		}
	}

	List(const T& t)
		: head(new Link(nullptr, nullptr, t))
		, tail(head)
	{ }

	void prepend(const T& t)
	{
		if(tail == head && tail == nullptr)
			tail = head = new Link(nullptr, nullptr, t);
		else
			head = new Link(nullptr, head, t);
	}

	void append(const T& t)
	{
		if (tail == head && tail == nullptr)
			tail = head = new Link(nullptr, nullptr, t);
		else
			tail = new Link(tail, nullptr, t);
	}

	bool find(const T& t)
	{
		Link* p = head;
		while(p)
		{
			if (p->val == t)
				return true;
			p = p->suc;
		}
		return false;
	}
};

int main()
{
	List<std::string> list(std::string("third"));

	list.prepend(std::string("second"));
	list.append(std::string("fourth"));
	list.prepend(std::string("first"));
	list.append(std::string("fifth"));

	list.find(std::string("third"));

    return 0;
}


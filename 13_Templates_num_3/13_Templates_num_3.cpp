// (*2.5) Напишите интрузивные и неинтрузивные двучсвязные списки. Какие дополнительные 
// операции нужно реализовать по сравнению с теми, которые вы сочли нужными ввести для 
// односвязных списков?

// 13_Templates_num_2.cpp : Defines the entry point for the console application.

#include "stdafx.h"
template <class T>
struct IntrusiveLink
{
	IntrusiveLink* suc = nullptr;
	IntrusiveLink* pre = nullptr;

	T val;

	IntrusiveLink(const T& val, IntrusiveLink* p, IntrusiveLink* s)
		: val(val)
		, pre(p)
		, suc(s)
	{
		if (pre)
			pre->suc = this;
		if (suc)
			suc->pre = this;
	}

	virtual std::string asText();
};

template <>
std::string IntrusiveLink<std::string>::asText()
{
	return val;
}

template <>
std::string IntrusiveLink<std::wstring>::asText()
{
	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	return converter.to_bytes(val);
}

struct ExtrusiveLink
{
	ExtrusiveLink* suc = nullptr;
	ExtrusiveLink* pre = nullptr;

	ExtrusiveLink(ExtrusiveLink* p, ExtrusiveLink* s)
		: pre(p)
		, suc(s)
	{
		if (pre)
			pre->suc = this;
		if (suc)
			suc->pre = this;
	}

	virtual std::string asText() = 0;
};

template <class T>
struct SubLink : ExtrusiveLink
{
	T val;

	SubLink(const T& v, SubLink* p, SubLink* s)
		: ExtrusiveLink(p, s)
		, val(v)
	{
	}

	std::string asText();
};

template <class T>
std::string SubLink<T>::asText()
{
	return std::to_string(val);
}

template <>
std::string SubLink<std::string>::asText()
{
	return val;
}

template <>
std::string SubLink<std::wstring>::asText()
{
	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	return converter.to_bytes(val);
}


template <class T> class List
{
public:

	T* head = nullptr;

	~List()
	{
		T* h = head;
		head = nullptr;

		while (h)
		{
			T* p = h;
			h = p->suc;
			delete p;
		}
	}

	List(T* t = nullptr)
		: head(t)
	{ }

	void add(T* t)
	{
		if (head)
			t->suc = head;
		head = t;
	}

	bool find(const T& t)
	{
		T* p = head;
		while (p)
		{
			if (p->val == t)
				return true;
			p = p->suc;
		}
		return false;
	}

	void print()
	{
		T* p = head;
		while (p)
		{
			std::cout << p->asText() << std::endl;
			p = p->suc;
		}
	}
};

int main()
{
	{
		typedef IntrusiveLink<std::string> string_link;
		typedef List<string_link> string_list;

		string_list list;

		list.add(new string_link(std::string("first")));
		list.add(new string_link(std::string("second")));
		list.add(new string_link(std::string("third")));
		list.add(new string_link(std::string("fourth")));
		list.add(new string_link(std::string("fifth")));

		list.print();
	}
	
	std::cout << std::endl;

	{
		typedef List<ExtrusiveLink> any_list;

		any_list list;

		list.add(new SubLink<std::string>(std::string("first")));
		list.add(new SubLink<std::wstring>(std::wstring(L"second")));
		list.add(new SubLink<int>(int(1)));
		list.add(new SubLink<double>(double(2.0)));

		list.print();
	}

    return 0;
}


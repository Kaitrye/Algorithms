#ifndef STACK_
#define STACK_
#include <iostream>

struct Node
{
	int data_;
	Node* next_;
	int max_;
	int min_;
};

class Stack
{
	Node* begin_;
	int count_;

public:
	Stack ()
	{
		begin_ = nullptr;
		count_ = 0;
	}

	void push (int x)
	{
		Node* tmp = new Node;
		tmp->data_ = x;
		tmp->next_ = begin_;

		if (begin_ != nullptr)
		{
			tmp->max_ = std::max (x, begin_->max_);
			tmp->min_ = std::min (x, begin_->min_);
		} else
		{
			tmp->max_ = x;
			tmp->min_ = x;
		}

		begin_ = tmp;
		++count_;
	}

	int pop ()
	{
		Node* tmp = begin_;
		begin_ = begin_->next_;

		int res = tmp->data_;
		delete tmp;

		--count_;
		return res;
	}

	int top () const
	{
		return begin_->data_;
	}

	int max () const
	{
		return begin_->max_;
	}

	int min () const
	{
		return begin_->min_;
	}

	bool is_empty () const
	{
		return begin_ == nullptr;
	}

	int size () const
	{
		return count_;
	}

	~Stack ()
	{
		while (begin_ != nullptr)
		{
			pop ();
		}
	}
};

#endif //STACK_

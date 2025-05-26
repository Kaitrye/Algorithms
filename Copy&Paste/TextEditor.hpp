#ifndef TEXT_EDITOR
#define TEXT_EDITOR
#include <iostream>
#include <fstream>
#include <cstring>

struct Node
{
	char data_[1000];
	Node* next_;
	Node* prev_;
};

class TextEditor
{
	Node* begin_;
	Node* end_;

	bool on_shift; // нажатие клавиши Shift.
	Node* cur_; // строка, на которой находится курсор.
	int cnt_sel; // количество выделенных строк.
	int cnt_buf; // количество сохраненных в буфер строк.
	Node* select[2]; // конец и начало выделенного блока.
	Node* buf[2]; // конец и начало блока, сохраненного в буфер.

	void insert (const char* str)
	{
		Node* tmp = new Node ();
		strncpy (tmp->data_, str, 1000);
		tmp->next_ = end_->next_;
		end_->next_->prev_ = tmp;

		tmp->prev_ = end_;
		end_->next_ = tmp;

		end_ = tmp;
	}

public:
	TextEditor ()
	{
		on_shift = false;
		cur_ = select[0] = select[1] = buf[0] = buf[1] = nullptr;
		cnt_sel = cnt_buf = 0;

		// добавляем метки конца и начала списка.
		Node* del = new Node ();
		strncpy (del->data_, "", 1000);
		del->prev_ = nullptr;
		begin_ = end_ = del;

		del = new Node ();
		strncpy (del->data_, "", 1000);
		del->prev_ = begin_;
		del->next_ = nullptr;

		end_->next_ = del;
	}

	void load (char* filename)
	{
		std::ifstream inFile (filename);
		if (!inFile.is_open ())
		{
			throw -1;
		}

		char str[1000];
		while (inFile.peek () != EOF)
		{
			inFile.getline (str, 1000);
			insert (str);
		}

		insert (""); // добавляем последнюю пустую строку.

		cur_ = begin_->next_;

		inFile.close ();
	}

	void save (char* filename) const
	{
		std::ofstream outFile (filename);
		if (!outFile.is_open ())
		{
			throw -2;
		}

		Node* tmp = begin_->next_;
		while (tmp != end_)
		{
			outFile << tmp->data_ << std::endl;
			tmp = tmp->next_;
		}

		outFile.close ();
	}

	void shift ()
	{
		on_shift = true;
		select[0] = cur_;
	}

	void erase ()
	{
		Node* tmp;
		while (buf[0] != nullptr)
		{
			tmp = buf[0];
			buf[0] = buf[0]->next_;
			delete tmp;
		}
		buf[0] = buf[1] = nullptr;

		if (cnt_sel > 0)
		{
			buf[0] = select[0];
			buf[1] = select[1]->prev_;

			select[0]->prev_->next_ = select[1];
			select[1]->prev_ = select[0]->prev_;

			buf[1]->next_ = nullptr;
			buf[0]->prev_ = nullptr;

			cnt_buf = cnt_sel;
		} else if (cnt_sel < 0)
		{
			buf[0] = select[1];
			buf[1] = select[0]->prev_;

			select[1]->prev_->next_ = select[0];
			select[0]->prev_ = select[1]->prev_;

			buf[1]->next_ = nullptr;
			buf[0]->prev_ = nullptr;

			cur_ = select[0];
			cnt_buf = -cnt_sel;
		} else if (cur_ != end_)
		{
			buf[0] = buf[1] = cur_;

			cur_->prev_->next_ = cur_->next_;
			cur_->next_->prev_ = cur_->prev_;

			cur_ = cur_->next_;
			buf[1]->next_ = nullptr;
			buf[0]->prev_ = nullptr;

			cnt_buf = 1;
		}

		cnt_sel = 0;
		select[0] = select[1] = nullptr;
		on_shift = false;
	}

	void paste ()
	{
		if (cnt_buf > 0)
		{
			if (cnt_sel == 0)
			{
				Node* begin = cur_->prev_;
				Node* end = cur_;

				Node* tmp = buf[0];
				while (tmp != nullptr)
				{
					Node* copy = new Node ();
					strncpy (copy->data_, tmp->data_, 1000);

					begin->next_ = copy;
					copy->prev_ = begin;
					begin = copy;

					copy->next_ = end;
					end->prev_ = copy;

					tmp = tmp->next_;
				}
			} else if (cnt_sel > 0)
			{
				Node* begin = select[0]->prev_;
				Node* end = select[1];

				Node* tmp = buf[0];
				while (tmp != nullptr)
				{
					Node* copy = new Node ();
					strncpy (copy->data_, tmp->data_, 1000);

					begin->next_ = copy;
					copy->prev_ = begin;
					begin = copy;

					copy->next_ = end;
					end->prev_ = copy;

					tmp = tmp->next_;
				}

				tmp = select[0];
				while (select[0] != select[1])
				{
					select[0] = tmp->next_;
					delete tmp;
					tmp = select[0];
				}
			} else if (cnt_sel < 0)
			{
				Node* begin = select[1]->prev_;
				Node* end = select[0];

				Node* tmp = buf[0];
				while (tmp != nullptr)
				{
					Node* copy = new Node ();
					strncpy (copy->data_, tmp->data_, 1000);

					begin->next_ = copy;
					copy->prev_ = begin;
					begin = copy;

					copy->next_ = end;
					end->prev_ = copy;

					tmp = tmp->next_;
				}

				while (select[1] != select[0])
				{
					tmp = select[1];
					select[1] = select[1]->next_;
					delete tmp;
				}
			}
		}

		cnt_sel = 0;
		select[0] = select[1] = nullptr;
		on_shift = false;
	}

	void operator--()
	{
		if (cur_ != end_)
		{
			if (on_shift)
			{
				++cnt_sel;
			}
			cur_ = cur_->next_;
			select[1] = cur_;
		}
	}

	void operator++()
	{
		if (cur_ != begin_->next_)
		{
			if (on_shift)
			{
				--cnt_sel;
			}
			cur_ = cur_->prev_;
			select[1] = cur_;
		}
	}

	~TextEditor ()
	{
		Node* tmp;
		while (begin_ != nullptr)
		{
			tmp = begin_;
			begin_ = begin_->next_;
			delete tmp;
		}

		while (buf[0] != nullptr)
		{
			tmp = buf[0];
			buf[0] = buf[0]->next_;
			delete tmp;
		}
	}
};

#endif // TEXT_EDITOR

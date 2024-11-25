/* Citation and Sources...
Final Project Milestone 1
Module: Utils
Filename: Utils.h
Version 1.0
Author	Tianwen Wang
Revision History
-----------------------------------------------------------
Date      Reason
2024/06/15  Preliminary release

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */


#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN 256

#include <cstring>
#include <iomanip>
#include <iostream>
#include "Book.h"

using namespace std;
namespace seneca
{
	// Default constructor
	Book::Book() : Publication(), m_author{ nullptr }
	{
		;
	}

	// Rule of the three
	Book::Book(const Book& nBook)
	{
		m_author = nullptr;
		*this = nBook;
	}

	Book& Book::operator=(const Book& nBook)
	{
		if (this != &nBook)
		{
			(Publication&)*this = nBook;

			delete[] m_author;
			m_author = nullptr;

			if (nBook.m_author)
			{
				m_author = new char[strlen(nBook.m_author) + 1];
				strcpy(m_author, nBook.m_author);
			}
		}

		return *this;
	}

	Book::~Book()
	{
		delete[] m_author;
		m_author = nullptr;
	}

	// Core methods
	char Book::type() const
	{
		return 'B';
	}

	std::ostream& Book::write(std::ostream& os) const
	{
		Publication::write(os);

		if (conIO(os))
		{
			os << ' ';
			if (strlen(m_author) <= SENECA_AUTHOR_WIDTH)
			{
				os << setw(SENECA_AUTHOR_WIDTH) << setfill(' ') << left << m_author;
			}
			else
			{
				for (int i = 0; i < SENECA_AUTHOR_WIDTH; ++i)
				{
					os << m_author[i];
				}
			}
			os << " |";
		}
		else
		{
			os << '\t' << m_author;
		}

		return os;
	}

	std::istream& Book::read(std::istream& is)
	{
		char author[MAX_NAME_LEN + 1]{ 0 };

		Publication::read(is);

		// Free the memory
		delete[] m_author;
		m_author = nullptr;

		if (conIO(is))
		{
			is.ignore();
			cout << "Author: ";
			is.get(author, MAX_NAME_LEN + 1, '\n');
		}
		else
		{
			is.ignore(1, '\t');
			is.get(author, MAX_NAME_LEN + 1, '\n');
		}

		if (!is.fail())
		{
			m_author = new char[strlen(author) + 1];
			strcpy(m_author, author);
		}

		return is;
	}

	void Book::set(int member_id)
	{
		Publication::set(member_id);
		resetDate();
	}

	Book::operator bool() const
	{
		return Publication::operator bool() && m_author && m_author[0] != '\0';
	}
}

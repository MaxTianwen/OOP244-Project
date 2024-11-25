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


#ifndef BOOK_H_
#define BOOK_H_

#include "Publication.h"

namespace seneca
{
	class Book : public Publication
	{
		char* m_author;
	
	public:
		// Default Constructor
		Book();

		// Rule of the three
		Book(const Book&);
		Book& operator=(const Book&);
		virtual ~Book();

		// Core Methods
		char type() const override;
		std::ostream& write(std::ostream& os) const override;
		std::istream& read(std::istream& is) override;
		void set(int member_id) override;
		operator bool() const override;
	};
}

#endif // !BOOK_H_


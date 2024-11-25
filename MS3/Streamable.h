/* Citation and Sources...
Final Project Milestone 3
Module: Date
Filename: Date.h
Version 1.0
Author	Tianwen Wang
Revision History
-----------------------------------------------------------
Date      Reason
2024/07/16  First Version

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */

#ifndef STREAMABLE_H_
#define STREAMABLE_H_

#include <iostream>

namespace seneca
{
	class Streamable
	{
	public:
		/* Core functions */
		// Streamable pure virtual functions
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual bool conIO(std::ios& ios) const = 0;
		virtual operator bool() const = 0;

		// Destructor
		virtual ~Streamable() {};
	};

	/* Global helper functions */
	std::ostream& operator<<(std::ostream& os, const Streamable& obj);
	std::istream& operator>>(std::istream& is, Streamable& obj);
}

#endif // !STREAMABLE_H_


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


#include "Streamable.h"

namespace seneca
{
	/* Global helper functions */
	std::ostream& operator<<(std::ostream& os, const Streamable& obj)
	{
		if (obj)
		{
			obj.write(os);
		}
		return os;
	}

	std::istream& operator>>(std::istream& is, Streamable& obj)
	{
		obj.read(is);
		return is;
	}
}
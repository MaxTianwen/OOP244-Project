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

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LEN 255

#include <cstring>
#include "Publication.h"

using namespace std;

namespace seneca
{
	/* Constructor */
	Publication::Publication()
	{
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
	}


	/* Modifiers */
	// Sets the membership attribute to either zero or a five-digit integer
	void Publication::set(int member_id)
	{
		m_membership = 0;
		if (member_id >= 10000 && member_id <= 99999)
		{
			m_membership = member_id;
		}
	}

	// Sets the **libRef** attribute value
	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	// Sets the date to the current date of the system
	void Publication::resetDate()
	{
		m_date = Date();
	}
	
	/* Queries */
	// Returns the character 'P' to identify this object as a "Publication object"
	char Publication::type() const
	{
		return 'P';
	}

	//Returns true is the publication is checkout (membership is non-zero)
	bool Publication::onLoan() const
	{
		return m_membership;
	}

	// Returns the date attribute
	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	// Returns true if the argument title appears anywhere in the title of the 
	// publication. Otherwise, it returns false; (use strstr() function in <cstring>)
	bool Publication::operator==(const char* title) const
	{
		bool hasTitle{ false };
		if (title && strstr(m_title, title))
		{
			hasTitle = true;
		}

		return hasTitle;
	}

	// Returns the title attribute
	Publication::operator const char* () const
	{
		return m_title;
	}

	// Returns the libRef attirbute
	int Publication::getRef() const
	{
		return m_libRef;
	}


	/* Overrided pure virtual functions from Class: Streamable*/
	std::ostream& Publication::write(std::ostream& os) const
	{
		if (conIO(os))
		{
			// shelfId
			os << "| " << m_shelfId << " | ";
			
			// Title
			os.width(SENECA_TITLE_WIDTH);
			os.fill('.');
			os.setf(ios::left);
			os << m_title << " | ";
			os.fill(' ');
			os.unsetf(ios::left);

			// Membership
			if (m_membership)
			{
				os << m_membership;
			}
			else
			{
				os << " N/A ";
			}
			os << " | ";

			// Date
			os << m_date << " |";
		}
		else
		{
			os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title
				<< '\t' << m_membership << '\t' << m_date;
		}

		return os;
	}

	std::istream& Publication::read(std::istream& is)
	{
		char title[MAX_STRING_LEN + 1];
		char shelfId[SENECA_SHELF_ID_LEN + 1];
		int membership{ 0 };
		int libRef{ -1 };
		Date date;

		// Reset all attributes
		delete[] m_title;
		m_title = nullptr;
		m_membership = 0;
		m_libRef = -1;
		m_shelfId[0] = '\0';

		// Read the attributes
		if (conIO(is))
		{
			cout << "Shelf No: ";
			is.getline(shelfId, SENECA_SHELF_ID_LEN + 1);

			if (strlen(shelfId) != SENECA_SHELF_ID_LEN)
			{
				// Manually set the istream to a fail state
				is.setstate(ios::failbit);
			}

			cout << "Title: ";
			cin.getline(title, MAX_STRING_LEN + 1, '\n');

			cout << "Date: ";
			is >> date;
		}
		else
		{
			is >> libRef;
			is.ignore();
			is.getline(shelfId, SENECA_SHELF_ID_LEN + 1, '\t');
			is.getline(title, MAX_STRING_LEN + 1, '\t');
			is >> membership;
			is.ignore();
			is >> date;
		}

		// Check if the date is valid and do the following things
		if (!date)
		{
			is.setstate(ios::failbit);
		}

		if (!is.fail())
		{
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			strcpy(m_shelfId, shelfId);
			m_membership = membership;
			m_libRef = libRef;
			m_date = date;
		}

		return is;
	}

	bool Publication::conIO(ios& io) const
	{
		return (&io == &std::cin || &io == &std::cout);
	}

	Publication::operator bool() const
	{
		return (m_title && m_shelfId && m_title[0] != '\0' && m_shelfId[0] != '\0');
	}


	/* The rule of the three */
	Publication::Publication(const Publication& rPub)
	{
		m_title = nullptr;
		*this = rPub;
	}

	Publication& Publication::operator=(const Publication& rPub)
	{
		if (this != &rPub)
		{
			delete[] m_title;
			m_title = nullptr;
			if (rPub.m_title)
			{
				m_title = new char[strlen(rPub.m_title) + 1];
				strcpy(m_title, rPub.m_title);
			}

			m_membership = rPub.m_membership;
			m_libRef = rPub.m_libRef;
			m_date = rPub.m_date;
			if (rPub.m_shelfId)
			{
				strcpy(m_shelfId, rPub.m_shelfId);
			}
			else
			{
				m_shelfId[0] = '\0';
			}
		}

		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
		m_title = nullptr;
	}
}

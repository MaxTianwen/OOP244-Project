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

#ifndef PUBLICATION_H_
#define PUBLICATION_H_

#define MAX_TITLE_LENGTH 255

#include "Date.h"
#include "Lib.h"
#include "Streamable.h"

namespace seneca
{
	class Publication : public Streamable
	{
		char* m_title;
		char m_shelfId[SENECA_SHELF_ID_LEN + 1];
		int m_membership;
		int m_libRef;
		Date m_date;

	public:
		/* Constructor */
		Publication();

		/* Modifiers */
		// Sets the membership attribute to either zero or a five-digit integer
		virtual void set(int member_id);
		// Sets the **libRef** attribute value
		void setRef(int value);
		// Sets the date to the current date of the system
		void resetDate();

		/* Queries */
		//Returns the character 'P' to identify this object as a "Publication object"
		virtual char type() const;
		//Returns true is the publication is checkout (membership is non-zero)
		bool onLoan() const;
		//Returns the date attribute
		Date checkoutDate() const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		bool operator==(const char* title) const;
		//Returns the title attribute
		operator const char* () const;
		//Returns the libRef attirbute
		int getRef() const;

		/* Overrided pure virtual functions from Class: Streamable*/
		std::ostream& write(std::ostream& os) const override;
		std::istream& read(std::istream& is) override;
		bool conIO(std::ios& io) const override;
		operator bool() const override;

		/* The rule of the three */
		Publication(const Publication& rPub);
		Publication& operator=(const Publication& rPub);
		~Publication();
	};
}

#endif // !PUBLICATION_H_


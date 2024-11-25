/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
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

#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__

#include <iostream>

namespace seneca
{
	const int MAX_MENU_ITEMS = 20;

	class Menu;

	class MenuItem
	{
		char* name;

		// Constructors, destructors, and operators
		MenuItem(const char*);
		MenuItem(const MenuItem&) = delete;
		~MenuItem();
		MenuItem& operator=(const MenuItem&) = delete;

		// Type conversions
		operator bool() const;
		operator const char* () const;

		// Other methods
		void display(std::ostream&) const;

		// Friend class
		friend class Menu;
	};

	class Menu
	{
		// Attributes
		MenuItem title;
		MenuItem* items[MAX_MENU_ITEMS];
		int numOfItems;

	public:
		// Constructor and Destructor
		Menu();
		Menu(const char*);
		~Menu();

		// Other methods
		std::ostream& displayTitle(std::ostream&) const;
		std::ostream& displayMenu(std::ostream&) const;
		int run() const;

		// Operators
		int operator~() const;
		Menu& operator<<(const char*);
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		const char* operator[](int) const;

		// Rule of three
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
	};

	/* Global overloaded operators */
	std::ostream& operator<<(std::ostream&, const Menu&);
}

#endif
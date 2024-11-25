/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Tianwen Wang
Revision History
-----------------------------------------------------------
Date      Reason
2024/06/24  Preliminary release

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca
{
	/******************/
	/* MenuItem Class */
	/******************/
	// Constructors and Destructors
	MenuItem::MenuItem(const char* content = nullptr)
	{
		// Check if the CString exists
		if (content && content[0] != '\0')
		{
			name = new char[strlen(content) + 1];
			strcpy(name, content);
		}
		else
		{
			// Set the pointer to an empty state
			name = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] name;
		name = nullptr;
	}


	// Type conversions
	MenuItem::operator bool() const
	{
		return name && name[0] != '\0';
	}

	MenuItem::operator const char* () const
	{
		return name;
	}

	// Other methods
	void MenuItem::display(std::ostream& os) const
	{
		if (name && name[0] != '\0')
		{
			os << name;
		}
	}


	/******************/
	/*   Menu Class   */
	/******************/
	// Constructors and Destructors
	Menu::Menu()
	{
		title.name = nullptr;
		// Initialize every element in the items array to nullptr
		for (int i = 0; i < MAX_MENU_ITEMS; ++i)
		{
			items[i] = nullptr;
		}
		numOfItems = 0;
	}

	Menu::Menu(const char* content)
	{
		// Check if the string argument is null or empty
		if (content && content[0] != '\0')
		{
			title.name = new char[strlen(content) + 1];
			strcpy(title.name, content);
		}
		else
		{
			title.name = nullptr;
		}

		// Initialize every element in the items array to nullptr
		for (int i = 0; i < MAX_MENU_ITEMS; ++i)
		{
			items[i] = nullptr;
		}
		numOfItems = 0;
	}

	Menu::~Menu()
	{
		// Deallocate memory for title
		delete[] title.name;
		title.name = nullptr;

		for (int i = 0; i < numOfItems; ++i)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}


	// Methods
	std::ostream& Menu::displayTitle(std::ostream& os) const
	{
		if (title.name && title.name[0] != '\0')
		{
			os << title.name;
		}

		return os;
	}

	std::ostream& Menu::displayMenu(std::ostream& os) const
	{
		// Display Menu title
		if (title.name && title.name[0] != '\0')
		{
			os << title.name << endl;
		}

		// Display Menu items
		for (int i = 0; i < numOfItems; ++i)
		{
			cout.width(2);
			cout.fill(' ');
			os << i + 1 << "- " << items[i]->name << endl;
		}

		// Display Menu footer
		cout.width(2);
		cout.fill(' ');
		os << 0 << "- " << "Exit" << endl;
		os << "> ";

		return os;
	}

	int Menu::run() const
	{
		int num;

		displayMenu(std::cout);
		// Ask for user input and validate the input number
		num = inputItemNum(numOfItems);

		return num;
	}


	// Operators
	int Menu::operator~() const
	{
		return run();
	}

	Menu& Menu::operator<<(const char* content)
	{
		// Check if items array is full
		if (numOfItems < MAX_MENU_ITEMS)
		{
			// Dynamically allocate memory for the new MenuItem
			items[numOfItems] = new MenuItem(content);
			numOfItems++;
		}

		return *this;
	}

	Menu::operator int() const
	{
		return numOfItems;
	}

	Menu::operator unsigned int() const
	{
		return numOfItems;
	}

	Menu::operator bool() const
	{
		return (numOfItems >= 1);
	}

	const char* Menu::operator[](int index) const
	{
		int num = 0;

		if (index < numOfItems)
		{
			num = index;
		}

		return items[num]->name;
	}


	/************************/
	/*   Global Functions   */
	/************************/
	std::ostream& operator<<(std::ostream& os, const Menu& menu)
	{
		return menu.displayTitle(os);
	}
}


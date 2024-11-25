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

#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"

namespace seneca 
{
	class LibApp 
	{
		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;

		bool confirm(const char* message);

		// Simple output functions
		void load();
		void save();
		void search();
		void returnPub();

		void newPublication();
		void removePublication();
		void checkOutPub();

	public:
		// Constructor
		LibApp();

		// Main driver method
		void run();
	};
}

#endif // !SENECA_LIBAPP_H




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

#define MAX_FILENAME_LEN 256
#define BOOK 1
#define PUBLICATION 2
#define DAILY_PENALTY 0.5

#define ALL 0
#define ONLY_ON_LOAN 1
#define NOT_ON_LOAN 2

#include "Lib.h"
#include "Menu.h"
#include "Publication.h"

namespace seneca 
{
	class LibApp 
	{
		int m_nolp;	// Number of loaded publications
		int m_llrn;	// Last library reference number
		bool m_changed;
		char m_filename[MAX_FILENAME_LEN + 1]{ 0 };
		Publication* m_ppa[SENECA_LIBRARY_CAPACITY]{ nullptr };	// Publication pointer array

		Menu m_pTypeMenu;
		Menu m_mainMenu;
		Menu m_exitMenu;

		void load();
		void save();
		bool confirm(const char* message);
		int search(int mode = ALL);

		Publication* getPub(int libRef);
		void newPublication();
		void removePublication();
		void checkOutPub();
		void returnPub();

	public:
		// Constructor and destructor
		LibApp(const char* filename);
		~LibApp();

		// Main driver method
		void run();
	};
}

#endif // !SENECA_LIBAPP_H




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

#include <iostream>
#include "LibApp.h"

using namespace std;

namespace seneca 
{
	bool LibApp::confirm(const char* message)
	{
		bool menuReturn{ false };

		// Instantiate a Menu in this function and initialize it with the message argument and add
		// "yes" as a single menu item to the Menu
		Menu newMenu(message);
		newMenu << "Yes";

		// If the run method of Menu returns 1, returns true; otherwise returns false
		if (newMenu.run() == 1)
		{
			menuReturn = true;
		}

		return menuReturn;
	}


	// Simple output functions
	void LibApp::load()
	{
		cout << "Loading Data" << endl;
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}

	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl;
		m_changed = true;
	}

	void LibApp::newPublication()
	{
		cout << "Adding new publication to library" << endl;

		if (confirm("Add this publication to library?"))
		{
			m_changed = true;
			cout << "Publication adeed" << endl;
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();

		if (confirm("Remove this publication from the library?"))
		{
			m_changed = true;
			cout << "Publication removed" << endl;
		}
	}

	void LibApp::checkOutPub()
	{
		search();
		if (confirm("Check out publication?"))
		{
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
	}

	/******************/
	/* Public Methods */
	/******************/
	// Constructor
	LibApp::LibApp() : 
		m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_mainMenu << "Add New Publication"
				   << "Remove Publication"
				   << "Checkout publication from library"
				   << "Return publication to library";

		m_exitMenu << "Save changes and exit"
				   << "Cancel and go back to the main menu";

		load();
	}


	// Main driver method
	void LibApp::run()
	{
		int selection;
		bool terminate{ false };
		
		do {
			selection = m_mainMenu.run();
			// Check the user input and call the corresponding method
			switch (selection)
			{
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				if (m_changed)
				{
					selection = m_exitMenu.run();
					switch (selection)
					{
					case 1:
						save();
						terminate = true;
						break;
					case 2:
						break;
					case 0:
						if (confirm("This will discard all the changes are you sure?") == 1)
						{
							terminate = true;
						}
						break;
					}
				}
				else
				{
					terminate = true;
				}
				break;
			default:
				cout << "Invalid selection! Please try again." << endl;
				break;
			}
			cout << endl;
		} while (!terminate);

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}
}

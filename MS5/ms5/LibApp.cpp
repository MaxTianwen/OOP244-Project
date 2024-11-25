/* Citation and Sources...
Final Project Milestone 5
Module: LibApp
Filename: LibApp.cpp
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


#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include "Book.h"
#include "LibApp.h"
#include "PublicationSelector.h"

using namespace std;
namespace seneca 
{
	bool LibApp::confirm(const char* message)
	{
		// Instantiate a Menu in this function and initialize it with the message argument and add
		// "yes" as a single menu item to the Menu
		Menu newMenu(message);
		newMenu << "Yes";

		return (newMenu.run() == 1);
	}


	// Simple output functions
	void LibApp::load()
	{
		char type{};

		cout << "Loading Data" << endl;
		// Read a publication or a book
		ifstream fin(m_filename);
		if (fin.is_open())
		{
			Publication* newPub{ nullptr };
			while (fin >> type)
			{
				fin.ignore();	// Ignore the space after the type letter
				if (type == 'P')
				{
					newPub = new Publication;
				}
				else if (type == 'B')
				{
					newPub = new Book;
				}

				if (newPub)
				{
					fin >> *newPub;
					m_ppa[m_nolp] = newPub;
					++m_nolp;
					m_llrn = newPub->getRef();
				}
			}
		}
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
		// Go through all the publications or books in the ppa array
		ofstream fout;
		fout.open(m_filename);

		if (fout.is_open())
		{
			for (int i = 0; i < m_nolp; ++i)
			{
				if (m_ppa[i] && m_ppa[i]->getRef())
				{
					fout << *m_ppa[i] << endl;
				}
			}
		}
	}

	Publication* LibApp::getPub(int libRef)
	{
		int i{};
		Publication* pubAddress{ nullptr };

		// Traverse the publication array and look for a match reference number
		for (i = 0; i < m_nolp && !pubAddress; ++i)
		{
			if (m_ppa[i]->getRef() == libRef)
			{
				pubAddress = m_ppa[i];
			}
		}

		return pubAddress;
	}

	int LibApp::search(int mode)
	{
		int i{};
		int	userSel{}, refNum{};
		char type{};
		char title[MAX_TITLE_LENGTH + 1]{};
		PublicationSelector selector("Select one of the following found matches:");

		// Show the publication type menu and get the search input from user
		// Check the selected publication type
		userSel = m_pTypeMenu.run();
		if (userSel == BOOK)
		{
			type = 'B';
		}
		else if (userSel == PUBLICATION)
		{
			type = 'P';
		}
		else
		{
			cout << "Aborted!" << endl;
		}

		if (type)
		{
			cout << "Publication Title: ";
			cin.ignore();
			cin.getline(title, MAX_TITLE_LENGTH + 1);

			// Traverse all the elements and return the search result based on the search mode
			// Search all
			for (i = 0; i < m_nolp; ++i)
			{
				if (m_ppa[i]->getRef() && m_ppa[i]->type() == type &&
					strstr(*m_ppa[i], title))
				{
					if (!mode || (mode == ONLY_ON_LOAN && m_ppa[i]->onLoan()) ||
						(mode == NOT_ON_LOAN && !(m_ppa[i]->onLoan())))
					{
						selector << m_ppa[i];
					}
				}
			}

			// Check if matches were found
			if (selector)
			{
				selector.sort();
				refNum = selector.run();
				if (!refNum)
				{
					cout << "Aborted!" << endl;
				}
			}
			else
			{
				cout << "No matches found!" << endl;
			}
		}

		return refNum;
	}

	void LibApp::newPublication()
	{
		int type{};
		Publication* newPub{ nullptr };

		// Check if the array reaches its maximum capability
		if (m_nolp == SENECA_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			// Get type input from user
			type = m_pTypeMenu.run();
			if (type)
			{
				// Instantiate a pointer dynamically
				if (type == BOOK)
				{
					newPub = new Book;
				}
				else if (type == PUBLICATION)
				{
					newPub = new Publication;
				}

				// Read the object and check if the it is valid
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> *newPub;
				if (cin.fail())
				{
					// Flush the buffer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Aborted!" << endl;
					delete newPub;
					newPub = nullptr;
				}
				else
				{
					// Confirm to add the new Publication to the array
					if (confirm("Add this publication to the library?"))
					{
						if (*newPub)
						{
							// Set the reference number
							++m_llrn;
							newPub->setRef(m_llrn);

							// Add the object to the end of the array and update the NOLP
							m_ppa[m_nolp] = newPub;
							++m_nolp;

							// Set the changed flag and display the result
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else
						{
							// If the object is invalid, deallocate the memory
							cout << "Failed to add publication!" << endl;
							delete newPub;
							newPub = nullptr;
						}
					}
					else
					{
						cout << "Aborted!" << endl;
						delete newPub;
						newPub = nullptr;
					}
				}
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
	}

	void LibApp::removePublication()
	{
		int refNum{};
		Publication* pub{ nullptr };

		cout << "Removing publication from the library" << endl;

		// Get the publication by invoking the getPub() method
		refNum = search(ALL);
		if (refNum)
		{
			pub = getPub(refNum);
			cout << *pub << endl;

			if (confirm("Remove this publication from the library?"))
			{
				// Set the removed publication to 0
				pub->setRef(0);
				// Change the flag and display the removal message
				m_changed = true;
				cout << "Publication removed" << endl;
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
	}

	void LibApp::checkOutPub()
	{
		int refNum{}, membership{};
		bool valid{ false };
		Publication* pub{ nullptr };

		cout << "Checkout publication from the library" << endl;
		// Search for available publications only
		refNum = search(NOT_ON_LOAN);

		if (refNum)
		{
			pub = getPub(refNum);
			cout << *pub << endl;
			if (confirm("Check out publication?"))
			{
				// Set the membership number of the selected publication
				// Get a valid membership number from user input
				cout << "Enter Membership number: ";
				while (!valid)
				{
					cin >> membership;
					if (!cin.fail() && membership >= 10000 && membership <= 99999)
					{
						valid = true;
					}
					else
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid membership number, try again: ";
					}
				}

				// Update the attributes of the publication
				pub->set(membership);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
	}

	void LibApp::returnPub()
	{
		int refNum{}, daysOnLoan{};
		double penalty{};
		Publication* pub{ nullptr };

		cout << "Return publication to the library" << endl;
		// Search for "on loan" items only
		refNum = search(ONLY_ON_LOAN);

		// Find the selected publication and check the loan status
		if (refNum)
		{
			pub = getPub(refNum);
			cout << *pub << endl;
			if (confirm("Return Publication?"))
			{
				// Check if the item is > 15 days on loan
				daysOnLoan = Date() - pub->checkoutDate();
				if (daysOnLoan > SENECA_MAX_LOAN_DAYS)
				{
					// Display the penalty
					penalty = DAILY_PENALTY * (daysOnLoan - SENECA_MAX_LOAN_DAYS);
					cout << "Please pay $" << fixed << setprecision(2) << penalty
						<< " penalty for being " << daysOnLoan - SENECA_MAX_LOAN_DAYS 
						<< " days late!" << endl;

				}
				// Set the membership and changed attribute
				pub->set(0);
				m_changed = true;

				cout << "Publication returned" << endl;
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
	}


	/******************/
	/* Public Methods */
	/******************/
	// Constructor
	LibApp::LibApp(const char* filename) :
		m_nolp{ 0 }, m_llrn{ 0 }, m_changed{ false },
		m_pTypeMenu{ "Choose the type of publication:" },
		m_mainMenu{ "Seneca Library Application" },
		m_exitMenu{ "Changes have been made to the data, what would you like to do?" }
	{
		// Validate the filename argument
		if (filename && filename[0] != '\0')
		{
			if (strlen(filename) <= MAX_FILENAME_LEN)
			{
				strcpy(m_filename, filename);
			}
			else
			{
				for (int i = 0; i < MAX_FILENAME_LEN; ++i)
				{
					m_filename[i] = filename[i];
				}
				m_filename[MAX_FILENAME_LEN] = '\0';
			}
		}

		// Initialize menus
		m_mainMenu << "Add New Publication"
				   << "Remove Publication"
				   << "Checkout publication from library"
				   << "Return publication to library";

		m_exitMenu << "Save changes and exit"
				   << "Cancel and go back to the main menu";

		m_pTypeMenu << "Book"
					<< "Publication";

		// Load data
		load();
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < m_nolp; ++i)
		{
			delete m_ppa[i];
			m_ppa[i] = nullptr;
		}
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
					break;
			}
			cout << endl;
		} while (!terminate);

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}
}

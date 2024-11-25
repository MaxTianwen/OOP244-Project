/* Citation and Sources...
Final Project Milestone 1
Module: Utils
Filename: Utils.cpp
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

#include <iostream>
#include <limits>
#include "Utils.h"

using namespace std;

namespace seneca 
{
	// Get a integer from user and validate the number to ensure it is between 
	// 0 and the number of the menu items
	int inputItemNum(int numOfItems)
	{
		int num{};
		bool valid{ true };

		do {
			cin >> num;
			if (cin.fail() || num < 0 || num > numOfItems)
			{
				valid = false;
				cout << "Invalid Selection, try again: ";

				// Clear input buffer and reset the cin flag
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				valid = true;
			}
		} while (!valid);

		return num;
	}

}
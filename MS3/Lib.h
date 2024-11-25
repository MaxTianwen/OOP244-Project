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


#ifndef LIB_H_
#define LIB_H_

namespace seneca
{
    // maximum number of day a publication can be borrowed with no penalty
    const int SENECA_MAX_LOAN_DAYS = 15;
    // The width in which the title of a publication should be printed on the console
    const int SENECA_TITLE_WIDTH = 30;
    // The width in which the author name of a book should be printed on the console
    const int SENECA_AUTHOR_WIDTH = 15;
    // The width in which the shelf id of a publication should be printed on the console
    const int SENECA_SHELF_ID_LEN = 4;
    // Maximum number of publications the library can hold.
    const int SENECA_LIBRARY_CAPACITY = 5000;
}

#endif // !LIB_H_
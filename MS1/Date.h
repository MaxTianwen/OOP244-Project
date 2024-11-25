/* Citation and Sources...
Final Project Milestone 1
Module: Date
Filename: Date.h
Version 1.0
Author	Tianwen Wang
Revision History
-----------------------------------------------------------
Date      Reason
2024/06/15  Preliminary release
2024/06/16  First Version
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */

#ifndef SENECA_DATE_H__
#define SENECA_DATE_H__

#include <iostream>

namespace seneca 
{
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int  DAY_ERROR = 4;
    const char DATE_ERROR[5][16] = 
    {
        "No Error",
        "cin Failed",
        "Bad Year Value",
        "Bad Month Value",
        "Bad Day Value"
    };
    const int  MIN_YEAR = 1500;

    class Date 
    {
    private:
        int m_year;
        int m_mon;
        int m_day;
        int m_ErrorCode;
        int m_CUR_YEAR;
        int daysSince0001_1_1() const; // returns number of days passed since the date 0001/1/1
        bool validate();             /* validates the date setting the error code and then returning the result 
                                    true, if valid, and false if invalid.*/
        void errCode(int);           // sets the error code
        int systemYear() const;       // returns the current system year
        bool bad() const;             // return true if the Date is in an erroneous state
        int mdays() const;            // returns the number of days in current month
        void setToToday();           // sets the date to the current date (system date)

    public:
        Date();                      // creates a date with current date
        Date(int year, int mon, int day); /* create a date with assigned values
                                            then validates the date and sets the 
                                            error code accordingly */
        int errCode() const;         // returns the error code or zero if date is valid
        const char* dateStatus() const;  // returns a string corresponding the current status of the date
        int currentYear() const;         // returns the m_CUR_YEAR value;

        /* Helper functions: get */
        // Return the days passed by calling the "daySince0001_1_1()" function
        int getDays() const;


        /* Type Conversion Operators */
        operator bool() const;


        /* Class Overloaded Operators */
        bool operator>=(const Date& rDate) const;
        bool operator<=(const Date& rDate) const;
        bool operator<(const Date& rDate) const;
        bool operator>(const Date& rDate) const;


        /* Read and write class functions */
        std::istream& read(std::istream&);
        std::ostream& write(std::ostream&) const;
    };

    /* Global overloaded operator functions */
    int operator-(const Date& lDate, const Date& rDate);
    bool operator==(const Date& lDate, const Date& rDate);
    bool operator!=(const Date& lDate, const Date& rDate);


    /* Global input and output stream functions */
    std::istream& operator>>(std::istream& is, Date& RO);
    std::ostream& operator<<(std::ostream& os, const Date& RO);
}

#endif
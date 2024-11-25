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



#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <iostream>
#include <ctime>

#include "Date.h"

using namespace std;

namespace seneca 
{
    // Global variables
    bool seneca_test = false;
    int seneca_year = 2024;
    int seneca_mon = 12;
    int seneca_day = 25;

    bool Date::validate() 
    {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) 
        {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12) 
        {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays()) 
        {
            errCode(DAY_ERROR);
        }
        return !bad();
    }

    int Date::mdays() const 
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && 
                (m_year % 100 != 0)) || (m_year % 400 == 0));
    }

    int Date::systemYear() const 
    {
        int theYear = seneca_year;
        if (!seneca_test) {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            theYear = lt.tm_year + 1900;
        }

        return theYear;
    }

    void Date::setToToday() 
    {
        if (seneca_test) {
            m_day = seneca_day;
            m_mon = seneca_mon;
            m_year = seneca_year;
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            m_day = lt.tm_mday;
            m_mon = lt.tm_mon + 1;
            m_year = lt.tm_year + 1900;
        }
        errCode(NO_ERROR);
    }

    int Date::daysSince0001_1_1()
        const 
    { 
        // Rata Die day since 0001/01/01 
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3) {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }

    Date::Date() :m_CUR_YEAR(systemYear()) 
    {
        setToToday();
    }

    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) 
    {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }

    const char* Date::dateStatus() const 
    {
        return DATE_ERROR[errCode()];
    }

    int Date::currentYear() const 
    {
        return m_CUR_YEAR;
    }

    void Date::errCode(int readErrorCode) 
    {
        m_ErrorCode = readErrorCode;
    }

    int Date::errCode() const 
    {
        return m_ErrorCode;
    }

    bool Date::bad() const 
    {
        return m_ErrorCode != 0;
    }

    // Read a date from the console and return the istram object
    std::istream& Date::read(std::istream& is)
    {
        // Create temporary variables to hold input values
        int year, mon, day;

        // Set the errorCode to 0 (no error)
        errCode(NO_ERROR);
        // Read the year, month, and day from the input stream
        is >> year;
        is.ignore();
        is >> mon;
        is.ignore();
        is >> day;

        // Check if istream succefully read the input date
        if (is.fail())
        {
            errCode(CIN_FAILED);
        }
        else
        {
            // Create an anonymous Date with the input properties object and assign 
            // it to the current object
            *this = Date(year, mon, day);
            validate();
        }

        // Reset the error flag on istream and clear the buffer

        return is;
    }

    std::ostream& Date::write(std::ostream& os) const
    {
        if (bad())
        {
            cout << dateStatus();
        }
        else
        {
            // Print the year
            os << m_year << "/";

            // Print the month in the following format
            os.width(2);
            os.setf(ios::right);
            os.fill('0');
            os << m_mon << "/";

            // Print the day in the following format
            os.width(2);
            os.setf(ios::right);
            os << m_day;

            // Reset the padding
            os.unsetf(ios::right);
            os.fill();
        }

        return os;
    }

    /* Get functions */
    // Return the days passed by calling the "daySince0001_1_1()" function
    int Date::getDays() const
    {
        return daysSince0001_1_1();
    }


    /* Type Conversion Operators */
    // bool
    Date::operator bool() const
    {
        return !bad();
    }


    /* Class Overloaded Operators */
    // >=
    bool Date::operator>=(const Date& rDate) const
    {
        return daysSince0001_1_1() >= rDate.daysSince0001_1_1();
    }

    // <=
    bool Date::operator<=(const Date& rDate) const
    {
        return daysSince0001_1_1() <= rDate.daysSince0001_1_1();
    }

    // <
    bool Date::operator<(const Date& rDate) const
    {
        return daysSince0001_1_1() < rDate.daysSince0001_1_1();
    }

    // >
    bool Date::operator>(const Date& rDate) const
    {
        return daysSince0001_1_1() > rDate.daysSince0001_1_1();
    }


    /* Global overloaded operator functions */
    // ==
    bool operator==(const Date& lDate, const Date& rDate)
    {
        return lDate.getDays() == rDate.getDays();
    }

    // !=
    bool operator!=(const Date& lDate, const Date& rDate)
    {
        return lDate.getDays() != rDate.getDays();
    }

    // -
    int operator-(const Date& lDate, const Date& rDate)
    {
        return lDate.getDays() - rDate.getDays();
    }


    /* Global input and output stream functions */
    // Input
    istream& operator>>(istream& is, Date& RO) 
    {
        return RO.read(is);
    }

    // Output
    ostream& operator<<(ostream& os, const Date& RO) 
    {
        return RO.write(os);
    }
}

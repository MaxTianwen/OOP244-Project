/*/////////////////////////////////////////////////////////////////////////
                            Milestone - #2
Full Name  : Yuhaochen Li
Student ID#: 103475232
Email      : yli734@myseneca.ca
Date       : 2024/7/9

Authenticity Declaration:

I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include "LibApp.h"
#include "Utils.h"
#include "PublicationSelector.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

namespace seneca {

    LibApp::LibApp(const char* filename): m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_pubTypeMenu("Choose the type of publication:") {

        strcpy(m_fileName, filename);
        m_NOLP = 0;
        m_LLRN = 0;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_pubTypeMenu << "Book" << "Publication";
        load();
    }
    bool LibApp::confirm(const char* message) {
        Menu confirmMenu(message);
        confirmMenu << "Yes";
        return confirmMenu.run() == 1;
    }
    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream file(m_fileName);
        char type;
        while (file >> type) {
            Publication* pub = nullptr;
            if (type == 'B') {
                pub = new Book();
            }
            else if (type == 'P') {
                pub = new Publication();
            }
            if (pub) {
                pub->read(file);
                if (file) {
                    m_PPA[m_NOLP++] = pub;
                    m_LLRN = pub->getRef();
                } 
                else delete pub;
            }
        }
    }
    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream file(m_fileName);
        for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() != 0) {
                file << *m_PPA[i] << endl;
            }
        }
    }
    int LibApp::search(int mode) {
        PublicationSelector ps("Select one of the following found matches:");
        char pubType = m_pubTypeMenu.run() == 1 ? 'B' : 'P';
        if (pubType == '0') {
            cout << "Aborted!" << endl;
            return 0;
        }

        cout << "Publication Title: ";
        char title[256];
        cin.ignore();
        cin.getline(title, 256);

        for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() != 0 && m_PPA[i]->type() == pubType && strstr(*m_PPA[i], title)) {
                if (mode == 1 || (mode == 2 && m_PPA[i]->onLoan()) || (mode == 3 && !m_PPA[i]->onLoan())) {
                    ps << m_PPA[i];
                }
            }
        }
        if (ps) {
            ps.sort();
            return ps.run();
        }
        else {
            cout << "No matches found!";
            return 0;
        }
    }
    void LibApp::returnPub() {
        //search();
        cout << "Return publication to the library" << endl;
        int ref = search(2);
        if (ref == 0) return;
        Publication* pub = getPub(ref);
        cout << *pub << endl;
        if (confirm("Return Publication?")) {
            Date current;
            int days = current - pub->checkoutDate();
            if (days > SENECA_MAX_LOAN_DAYS) {
                cout << "Please pay $" << (days - SENECA_MAX_LOAN_DAYS) * 0.5 <<
                    " penalty for being " << days - SENECA_MAX_LOAN_DAYS <<
                    " days late!" << endl;
            }
            pub->set(0);
            m_changed = true;
            cout << "Publication returned" << endl;
        }
        else cout << "Aborted!" << endl;
    }
    void LibApp::newPublication() {
        if (m_NOLP >= SENECA_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else {
            cout << "Adding new publication to the library" << endl;
            int pubType = m_pubTypeMenu.run();
            if (pubType != 0) {
                Publication* pub = (pubType == 1) ? static_cast<Publication*>(new Book()) : new Publication();
                cin.ignore(1000, '\n');
                cin >> *pub;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Aborted!" << endl;
                    delete pub;
                    return;
                }
                if (confirm("Add this publication to the library?")) {
                    if (*pub) {
                        pub->setRef(++m_LLRN);
                        m_PPA[m_NOLP++] = pub;
                        m_changed = true;
                        cout << "Publication added" << endl;
                    }
                    else {
                        cout << "Failed to add publication!" << endl;
                        delete pub;
                    }
                }
                else {
                    cout << "Aborted!" << endl;
                    delete pub;
                }
            }
            else cout << "Aborted!" << endl;
        }
    }
    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int ref = search(1);
        if (ref == 0) return;
        Publication* pub = getPub(ref);
        cout << *pub << endl;
        if (confirm("Remove this publication from the library?")) {
            pub->setRef(0);
            m_changed = true;
            cout << "Publication removed" << endl;
        }
        else  cout << "Aborted!" << endl;
    }
    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int ref = search(3);
        if (ref == 0) return;
        Publication* pub = getPub(ref);
        cout << *pub << endl;
        if (confirm("Check out publication?")) {
            int membership;
            cout << "Enter Membership number: ";
            do {
                cin >> membership;
                if (cin.fail() || membership < 10000 || membership > 99999) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid membership number, try again: ";
                }
            } while (membership < 10000 || membership > 99999);
            pub->set(membership);
            m_changed = true;
            cout << "Publication checked out" << endl;
        }
        else cout << "Aborted!" << endl;
    }
    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_NOLP; ++i) {
            if (m_PPA[i]->getRef() == libRef) {
                return m_PPA[i];
            }
        }
        return nullptr;
    }
    void LibApp::run() {
        bool flag = true;
        while (flag) {
            switch (m_mainMenu.run()) {
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
                if (!m_changed) {
                    flag = false;
                }
                else {
                    switch (m_exitMenu.run()) {
                        case 1:
                            save();
                            flag = false;
                            break;
                        case 2:
                            break;
                        case 0:
                            if (confirm("This will discard all the changes are you sure?")) {
                                flag = false;
                            }
                            break;
                    }
                }
                break;
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }
}
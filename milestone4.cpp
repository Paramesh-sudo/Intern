// ============================================================
// Milestone 4: Small In-Memory Contact Book (C++)
// ============================================================
// What this program does:
//   1. Shows a menu: Add / List / Find / Exit
//   2. Add  : saves a fictional name and phone number
//   3. List : shows all contacts (or a message if there are none)
//   4. Find : searches by EXACT name (or says "no match")
//
// Contacts are kept in memory only (a vector), so they are
// gone when the program ends. Phone numbers are stored as
// STRINGS (not numbers) because they can start with 0 or +.
// All names and numbers in this program are FICTIONAL.
//
// Compile: g++ -std=c++17 main.cpp -o contacts
// Run:     ./contacts        (Windows: contacts.exe)
// ============================================================

#include <iostream>   // cin and cout (keyboard and screen)
#include <iomanip>    // setw (neat table columns)
#include <limits>     // numeric_limits (used to throw away bad input)
#include <string>     // string and getline
#include <vector>     // vector (a list that can grow)

using namespace std;  // lets us write cout instead of std::cout

// ------------------------------------------------------------
// A Contact groups two related pieces of data together:
// a name and a phone number (both are strings).
// ------------------------------------------------------------
struct Contact
{
    string name;
    string phone;
};

// ------------------------------------------------------------
// Reset cin after an error and throw away the rest of the line.
// ------------------------------------------------------------
void clearBadInput()
{
    cin.clear();                                          // remove the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // skip the rest of the line
}

// ------------------------------------------------------------
// INPUT: Ask a question and read a whole line of text.
// Keeps asking until the answer is not empty.
// Returns false only if the keyboard input has ended
// (for example Ctrl+D), so the program never loops forever.
// "answer" is passed by reference (&) so the text goes back
// to the caller.
// ------------------------------------------------------------
bool readText(const string &question, string &answer)
{
    while (true)
    {
        cout << question;
        getline(cin, answer);   // getline allows spaces, like "Asha Rao"

        if (cin.eof())
        {
            return false;
        }

        if (answer.empty())
        {
            cout << "  This cannot be empty. Please try again.\n";
            continue;
        }

        return true;
    }
}

// ------------------------------------------------------------
// ADD: Ask for a name and phone, then save them in the list.
// "contacts" is passed by reference (&) so the new contact is
// added to the real list in main(), not to a copy.
// Returns false if the input ended.
// ------------------------------------------------------------
bool addContact(vector<Contact> &contacts)
{
    Contact newContact;   // an empty contact we will fill in

    if (!readText("Enter name  : ", newContact.name))
    {
        return false;
    }
    if (!readText("Enter phone : ", newContact.phone))
    {
        return false;
    }

    contacts.push_back(newContact);   // push_back adds to the END of the vector
    cout << "Contact added!\n";
    return true;
}

// ------------------------------------------------------------
// LIST: Show every contact in a neat table.
// "const" means this function only READS the list, it never
// changes it.
// ------------------------------------------------------------
void listContacts(const vector<Contact> &contacts)
{
    // Empty case
    if (contacts.empty())
    {
        cout << "\nNo contacts yet. Choose option 1 to add one.\n";
        return;
    }

    cout << "\n------- CONTACT LIST (" << contacts.size() << ") -------\n";
    cout << left << setw(5) << "No."
         << setw(20) << "Name"
         << "Phone" << "\n";
    cout << "---------------------------------------\n";

    for (size_t i = 0; i < contacts.size(); i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(20) << contacts[i].name
             << contacts[i].phone << "\n";
    }
    cout << "---------------------------------------\n";
}

// ------------------------------------------------------------
// FIND: Ask for a name and look for an EXACT match.
// (Capital letters matter: "asha" is not the same as "Asha".)
// Returns false if the input ended.
// ------------------------------------------------------------
bool findContact(const vector<Contact> &contacts)
{
    string searchName;

    if (!readText("Enter exact name to find: ", searchName))
    {
        return false;
    }

    // Look at every contact, one by one
    for (size_t i = 0; i < contacts.size(); i++)
    {
        if (contacts[i].name == searchName)
        {
            cout << "\nFound!\n";
            cout << "  Name  : " << contacts[i].name << "\n";
            cout << "  Phone : " << contacts[i].phone << "\n";
            return true;   // stop searching, we found it
        }
    }

    // If we reach here, the loop finished without a match
    cout << "\nNo match found for \"" << searchName << "\".\n";
    return true;
}

// ------------------------------------------------------------
// DISPLAY: Print the menu.
// ------------------------------------------------------------
void displayMenu()
{
    cout << "\n===== CONTACT BOOK =====\n";
    cout << "1. Add contact\n";
    cout << "2. List all contacts\n";
    cout << "3. Find contact by name\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";
}

// ------------------------------------------------------------
// MAIN: Runs the menu loop. The list lives here (no globals).
// ------------------------------------------------------------
int main()
{
    vector<Contact> contacts;   // starts empty
    bool running = true;        // the menu loop runs while this is true

    cout << "Welcome to the Contact Book! (fictional data only)\n";

    while (running)
    {
        displayMenu();

        int choice = 0;
        cin >> choice;

        // Input ended (Ctrl+D / Ctrl+Z): leave the program
        if (cin.eof())
        {
            cout << "\nInput ended. Goodbye!\n";
            break;
        }

        // The user typed text instead of a number
        if (cin.fail())
        {
            cout << "Invalid choice! Please type a number from 1 to 4.\n";
            clearBadInput();
            continue;
        }

        clearBadInput();   // remove the leftover Enter key (and any extra text)

        switch (choice)
        {
            case 1:
                if (!addContact(contacts))
                {
                    cout << "\nInput ended. Goodbye!\n";
                    running = false;
                }
                break;

            case 2:
                listContacts(contacts);
                break;

            case 3:
                if (!findContact(contacts))
                {
                    cout << "\nInput ended. Goodbye!\n";
                    running = false;
                }
                break;

            case 4:
                cout << "\nGoodbye!\n";
                running = false;
                break;

            default:
                cout << "Invalid choice! Please choose 1, 2, 3 or 4.\n";
                break;
        }
    }

    return 0;
}

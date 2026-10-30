// ============================================================
// Student Grade Calculator (C++ console application)
// ============================================================
// What this program does:
//   1. Shows a menu (Enter marks / Show results / Exit)
//   2. Reads a student's name and 5 marks (each must be 0 to 100)
//   3. Calculates total, percentage and letter grade
//   4. Prints a neat report card table
//
// GRADING THRESHOLDS (fictional exercise only - these do NOT
// change any EdBytes certificate grades):
//   Percentage 90 and above   -> Grade A
//   Percentage 80 to below 90 -> Grade B
//   Percentage 70 to below 80 -> Grade C
//   Percentage 60 to below 70 -> Grade D
//   Percentage below 60       -> Grade F
//
// Compile: g++ -std=c++17 main.cpp -o grade_demo
// Run:     ./grade_demo        (Windows: grade_demo.exe)
// ============================================================

#include <iostream>   // cin, cout (keyboard input and screen output)
#include <iomanip>    // setw, setprecision, fixed (table formatting)
#include <limits>     // numeric_limits (used to throw away bad input)
#include <string>     // string, getline (to store the student's name)

using namespace std;  // lets us write cout instead of std::cout

// ------------------------------------------------------------
// Throw away everything the user typed on the current line
// and reset cin so it can be used again after an error.
// ------------------------------------------------------------
void clearBadInput()
{
    cin.clear();                                          // remove the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // skip the rest of the line
}

// ------------------------------------------------------------
// INPUT: Ask for ONE mark and keep asking until it is valid.
// Valid means: a number between 0 and 100.
// Returns the valid mark. Sets inputEnded to true if the
// keyboard input is closed (for example Ctrl+D), so we never
// get stuck in an endless loop.
// ------------------------------------------------------------
double readMark(int subjectNumber, bool &inputEnded)
{
    double mark = 0;

    while (true)
    {
        cout << "Enter mark for subject " << subjectNumber << " (0-100): ";
        cin >> mark;

        // Case 1: the input stream has ended - nothing more can be read
        if (cin.eof())
        {
            inputEnded = true;
            return 0;
        }

        // Case 2: the user typed text (like "abc") instead of a number
        if (cin.fail())
        {
            cout << "  Invalid input! Please type a number.\n";
            clearBadInput();
            continue;   // go back to the top of the loop and ask again
        }

        // Case 3: the number was followed by extra characters (like "85abc")
        if (cin.peek() != '\n')
        {
            cout << "  Invalid input! Please type only a number.\n";
            clearBadInput();
            continue;
        }

        // Case 4: it is a number, but outside the allowed range
        if (mark < 0 || mark > 100)
        {
            cout << "  Mark must be between 0 and 100.\n";
            clearBadInput();
            continue;
        }

        // The mark is good. Remove the leftover Enter key and return it.
        clearBadInput();
        return mark;
    }
}

// ------------------------------------------------------------
// INPUT: Read the student's name and all marks.
// "name" and "marks" are passed by reference (&) so that the
// changes made here are visible back in main().
// Returns true if everything was entered, false if input ended.
// ------------------------------------------------------------
bool enterStudentData(string &name, double marks[], int count)
{
    bool inputEnded = false;

    cout << "\nEnter student name: ";
    getline(cin, name);          // getline allows names with spaces
    if (cin.eof())
    {
        return false;
    }

    // Do not accept an empty name
    while (name.empty())
    {
        cout << "  Name cannot be empty. Enter student name: ";
        getline(cin, name);
        if (cin.eof())
        {
            return false;
        }
    }

    // Read each of the marks one by one
    for (int i = 0; i < count; i++)
    {
        marks[i] = readMark(i + 1, inputEnded);
        if (inputEnded)
        {
            return false;
        }
    }

    cout << "\nMarks saved successfully!\n";
    return true;
}

// ------------------------------------------------------------
// CALCULATION: Add up all the marks.
// ------------------------------------------------------------
double calculateTotal(const double marks[], int count)
{
    double total = 0;
    for (int i = 0; i < count; i++)
    {
        total = total + marks[i];
    }
    return total;
}

// ------------------------------------------------------------
// CALCULATION: Percentage = total / 5.0
// (5 subjects, each out of 100, so the maximum total is 500,
//  and 500 / 5.0 = 100 percent)
// ------------------------------------------------------------
double calculatePercentage(double total)
{
    return total / 5.0;
}

// ------------------------------------------------------------
// CALCULATION: Convert a percentage into a letter grade
// using the thresholds written at the top of this file.
// ------------------------------------------------------------
char assignGrade(double percentage)
{
    if (percentage >= 90)
    {
        return 'A';
    }
    else if (percentage >= 80)
    {
        return 'B';
    }
    else if (percentage >= 70)
    {
        return 'C';
    }
    else if (percentage >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

// ------------------------------------------------------------
// DISPLAY: Print the menu.
// ------------------------------------------------------------
void displayMenu()
{
    cout << "\n===== STUDENT GRADE MENU =====\n";
    cout << "1. Enter marks\n";
    cout << "2. Show results\n";
    cout << "3. Exit\n";
    cout << "Choose an option (1-3): ";
}

// ------------------------------------------------------------
// DISPLAY: Print the formatted report card.
// setw(n)        -> reserve n characters of width for the next item
// fixed          -> show numbers with a fixed number of decimals
// setprecision(2)-> show 2 digits after the decimal point
// ------------------------------------------------------------
void displayResults(const string &name, const double marks[], int count,
                    double total, double percentage, char grade)
{
    cout << "\n=========== REPORT CARD ===========\n";
    cout << "Student Name : " << name << "\n";
    cout << "-----------------------------------\n";
    cout << left << setw(15) << "Subject"
         << right << setw(10) << "Marks" << "\n";
    cout << "-----------------------------------\n";

    cout << fixed << setprecision(2);   // 2 decimal places from now on
    for (int i = 0; i < count; i++)
    {
        cout << left << setw(15) << ("Subject " + to_string(i + 1))
             << right << setw(10) << marks[i] << "\n";
    }

    cout << "-----------------------------------\n";
    cout << left << setw(15) << "Total"
         << right << setw(10) << total << "\n";
    cout << left << setw(15) << "Percentage"
         << right << setw(9) << percentage << "%\n";
    cout << left << setw(15) << "Grade"
         << right << setw(10) << grade << "\n";
    cout << "===================================\n";
}

// ------------------------------------------------------------
// MAIN: Runs the menu loop. All variables live here (no globals).
// ------------------------------------------------------------
int main()
{
    const int NUM_SUBJECTS = 5;      // how many marks we collect
    double marks[NUM_SUBJECTS] = {0};
    string studentName = "";
    bool dataEntered = false;        // becomes true after marks are entered
    bool running = true;             // the menu loop runs while this is true

    cout << "Welcome to the Student Grade Calculator!\n";

    while (running)
    {
        displayMenu();

        int choice = 0;
        cin >> choice;

        // If the input has ended (Ctrl+D / Ctrl+Z), leave the program
        if (cin.eof())
        {
            cout << "\nInput ended. Goodbye!\n";
            break;
        }

        // If the user typed text instead of a number, show a message and loop again
        if (cin.fail())
        {
            cout << "Invalid choice! Please type a number from 1 to 3.\n";
            clearBadInput();
            continue;
        }

        clearBadInput();   // remove the leftover Enter key (and any extra text)

        switch (choice)
        {
            case 1:
            {
                // Read into temporary variables so old data stays safe
                // if the input ends halfway.
                string newName;
                double newMarks[NUM_SUBJECTS] = {0};

                if (enterStudentData(newName, newMarks, NUM_SUBJECTS))
                {
                    studentName = newName;
                    for (int i = 0; i < NUM_SUBJECTS; i++)
                    {
                        marks[i] = newMarks[i];
                    }
                    dataEntered = true;
                }
                else
                {
                    cout << "\nInput ended. Goodbye!\n";
                    running = false;
                }
                break;
            }

            case 2:
            {
                if (!dataEntered)
                {
                    cout << "\nNo data yet! Choose option 1 to enter marks first.\n";
                }
                else
                {
                    double total = calculateTotal(marks, NUM_SUBJECTS);
                    double percentage = calculatePercentage(total);
                    char grade = assignGrade(percentage);
                    displayResults(studentName, marks, NUM_SUBJECTS,
                                   total, percentage, grade);
                }
                break;
            }

            case 3:
                cout << "\nThank you for using the program. Goodbye!\n";
                running = false;
                break;

            default:
                cout << "Invalid choice! Please choose 1, 2 or 3.\n";
                break;
        }
    }

    return 0;
}

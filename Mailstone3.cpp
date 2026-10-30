// ============================================================
// Milestone 3: Three-Mark Grade Calculator (C++)
// ============================================================
// What this program does:
//   1. Reads THREE marks from the user (each must be 0 to 100)
//   2. Rejects bad input (text, or numbers outside 0-100)
//   3. Calculates the average using floating-point division
//   4. Gives a letter grade (A, B, C, D or F)
//
// GRADE THRESHOLDS (applied to the average):
//   Average 90 or more        -> A
//   Average 80 to below 90    -> B
//   Average 70 to below 80    -> C
//   Average 60 to below 70    -> D
//   Average below 60          -> F
//
// NOTE: If your starter pack (START-HERE.md) lists different
// thresholds, just change the five numbers in the "GRADE
// THRESHOLDS" constants below. Nothing else needs to change.
//
// Compile: g++ -std=c++17 main.cpp -o grade3
// Run:     ./grade3        (Windows: grade3.exe)
// ============================================================

#include <iostream>   // cin and cout (keyboard and screen)
#include <iomanip>    // fixed and setprecision (show 2 decimals)
#include <limits>     // numeric_limits (used to throw away bad input)

using namespace std;  // lets us write cout instead of std::cout

// ---------------- GRADE THRESHOLDS (change here only) ----------------
const double A_MIN = 90.0;   // average at or above this -> A
const double B_MIN = 80.0;   // average at or above this -> B
const double C_MIN = 70.0;   // average at or above this -> C
const double D_MIN = 60.0;   // average at or above this -> D
                             // anything lower           -> F
// ---------------------------------------------------------------------

const int NUM_MARKS = 3;     // how many marks we read

// ------------------------------------------------------------
// Reset cin after an error and throw away the rest of the line.
// ------------------------------------------------------------
void clearBadInput()
{
    cin.clear();                                          // remove the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // skip the rest of the line
}

// ------------------------------------------------------------
// INPUT: Ask for ONE mark. Keep asking until it is valid.
// Valid = a number from 0 to 100.
// Returns false only if the keyboard input has ended
// (for example Ctrl+D), so the program never loops forever.
// "mark" is passed by reference (&) so the answer goes back
// to the caller.
// ------------------------------------------------------------
bool readMark(int number, double &mark)
{
    while (true)
    {
        cout << "Enter mark " << number << " (0-100): ";
        cin >> mark;

        // Input ended - nothing more to read
        if (cin.eof())
        {
            return false;
        }

        // The user typed text (like "abc") instead of a number
        if (cin.fail())
        {
            cout << "  Invalid input! Please type a number.\n";
            clearBadInput();
            continue;   // go back and ask again
        }

        // The number was followed by extra characters (like "85abc")
        if (cin.peek() != '\n')
        {
            cout << "  Invalid input! Please type only a number.\n";
            clearBadInput();
            continue;
        }

        // It is a number, but outside the allowed range
        if (mark < 0 || mark > 100)
        {
            cout << "  Mark must be between 0 and 100.\n";
            clearBadInput();
            continue;
        }

        // The mark is good. Remove the leftover Enter key and finish.
        clearBadInput();
        return true;
    }
}

// ------------------------------------------------------------
// CALCULATION: Average of the marks.
// We add the marks, then divide by 3.0 (not 3) so that C++
// uses floating-point division and keeps the decimal part.
// Example: 100 / 3   = 33   (integer division - wrong!)
//          100 / 3.0 = 33.33 (floating-point division - right!)
// ------------------------------------------------------------
double calculateAverage(const double marks[], int count)
{
    double total = 0;
    for (int i = 0; i < count; i++)
    {
        total = total + marks[i];
    }
    return total / count;   // "total" is a double, so this is floating-point division
}

// ------------------------------------------------------------
// CALCULATION: Convert the average into a letter grade
// using the thresholds written at the top of the file.
// ------------------------------------------------------------
char assignGrade(double average)
{
    if (average >= A_MIN)
    {
        return 'A';
    }
    else if (average >= B_MIN)
    {
        return 'B';
    }
    else if (average >= C_MIN)
    {
        return 'C';
    }
    else if (average >= D_MIN)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

// ------------------------------------------------------------
// DISPLAY: Show the marks, the average and the grade.
// fixed + setprecision(2) = always show 2 digits after the point.
// ------------------------------------------------------------
void displayResult(const double marks[], int count, double average, char grade)
{
    cout << fixed << setprecision(2);

    cout << "\n------- RESULT -------\n";
    for (int i = 0; i < count; i++)
    {
        cout << "Mark " << (i + 1) << "  : " << marks[i] << "\n";
    }
    cout << "Average : " << average << "\n";
    cout << "Grade   : " << grade << "\n";
    cout << "----------------------\n";
}

// ------------------------------------------------------------
// MAIN: Reads the marks, calculates, and shows the result.
// ------------------------------------------------------------
int main()
{
    double marks[NUM_MARKS] = {0};   // stores the three marks

    cout << "=== Three-Mark Grade Calculator ===\n";

    // Step 1: read each mark (with validation)
    for (int i = 0; i < NUM_MARKS; i++)
    {
        if (!readMark(i + 1, marks[i]))
        {
            cout << "\nInput ended before all marks were entered. Goodbye!\n";
            return 1;   // 1 means "something went wrong"
        }
    }

    // Step 2: calculate
    double average = calculateAverage(marks, NUM_MARKS);
    char grade = assignGrade(average);

    // Step 3: show the result
    displayResult(marks, NUM_MARKS, average, grade);

    return 0;   // 0 means "everything went fine"
}

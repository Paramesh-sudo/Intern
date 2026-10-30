// ============================================================
// Milestone 5: Simple Training Account Class (C++)
// ============================================================
// What this program does:
//   - Defines a BankAccount class that keeps its balance PRIVATE
//   - The balance is stored as a whole number of MINOR UNITS
//     (for example paise or cents), never as a decimal
//        Rs 100.50  ->  10050 paise
//     Why? Decimal numbers (double) can have tiny rounding
//     errors. Whole numbers are always exact.
//   - deposit()  refuses zero or negative amounts
//   - withdraw() refuses zero, negative, or too-large amounts
//   - main() runs a demo of every case and prints the results
//
// All account names and amounts are FICTIONAL training data.
// There is no real bank connection and nothing is saved to disk.
//
// Compile: g++ -std=c++17 main.cpp -o account_demo
// Run:     ./account_demo        (Windows: account_demo.exe)
// ============================================================

#include <iostream>   // cout (screen output)
#include <iomanip>    // setw, setfill (to print 5 as "05")
#include <string>     // string

using namespace std;  // lets us write cout instead of std::cout

// ------------------------------------------------------------
// Turn minor units into text like "Rs 100.50".
// 10050 paise -> 10050 / 100 = 100 rupees, 10050 % 100 = 50 paise
// ("/" on whole numbers drops the decimal part, "%" gives the
//  remainder - perfect for splitting money.)
// ------------------------------------------------------------
string formatMoney(long long minorUnits)
{
    // Remember if the amount is negative, then work with a positive number
    string sign = "";
    if (minorUnits < 0)
    {
        sign = "-";
        minorUnits = -minorUnits;
    }

    long long whole = minorUnits / 100;   // the rupee part
    long long part = minorUnits % 100;    // the paise part

    string paise = to_string(part);
    if (part < 10)
    {
        paise = "0" + paise;              // 5 becomes "05"
    }

    return "Rs " + sign + to_string(whole) + "." + paise;
}

// ------------------------------------------------------------
// The BankAccount class.
//   private  = only the class itself can touch these
//   public   = anyone can call these
// Because balance is private, other code cannot set it to a
// wrong value. It can only change through deposit/withdraw,
// which check the rules first.
// ------------------------------------------------------------
class BankAccount
{
private:
    string ownerName;       // fictional owner name
    long long balance;      // balance in minor units (whole number)

public:
    // Constructor: runs when we create an account.
    // The account starts with a balance of 0.
    BankAccount(const string &name)
    {
        ownerName = name;
        balance = 0;
    }

    // Getter: lets outside code READ the balance (but not change it)
    long long getBalance() const
    {
        return balance;
    }

    // Getter for the owner's name
    string getOwnerName() const
    {
        return ownerName;
    }

    // DEPOSIT: add money. Returns true if it worked, false if refused.
    bool deposit(long long amount)
    {
        // Rule: the amount must be more than zero
        if (amount <= 0)
        {
            cout << "  REFUSED: deposit of " << formatMoney(amount)
                 << " - amount must be greater than zero.\n";
            return false;
        }

        balance = balance + amount;
        cout << "  OK: deposited " << formatMoney(amount)
             << ". New balance: " << formatMoney(balance) << "\n";
        return true;
    }

    // WITHDRAW: take money out. Returns true if it worked, false if refused.
    bool withdraw(long long amount)
    {
        // Rule 1: the amount must be more than zero
        if (amount <= 0)
        {
            cout << "  REFUSED: withdrawal of " << formatMoney(amount)
                 << " - amount must be greater than zero.\n";
            return false;
        }

        // Rule 2: we cannot take out more than we have (no overdraft)
        if (amount > balance)
        {
            cout << "  REFUSED: withdrawal of " << formatMoney(amount)
                 << " - insufficient funds (balance is "
                 << formatMoney(balance) << ").\n";
            return false;
        }

        balance = balance - amount;
        cout << "  OK: withdrew " << formatMoney(amount)
             << ". New balance: " << formatMoney(balance) << "\n";
        return true;
    }
};

// ------------------------------------------------------------
// DISPLAY: Print a heading for each demo section.
// ------------------------------------------------------------
void printHeading(const string &text)
{
    cout << "\n--- " << text << " ---\n";
}

// ------------------------------------------------------------
// MAIN: Demonstrates every required case on a fictional account.
// ------------------------------------------------------------
int main()
{
    BankAccount account("Asha Rao (fictional)");

    cout << "=== Training Account Demo ===\n";
    cout << "Owner           : " << account.getOwnerName() << "\n";
    cout << "Opening balance : " << formatMoney(account.getBalance()) << "\n";

    printHeading("1. Valid deposit (ordinary case)");
    account.deposit(50000);      // Rs 500.00

    printHeading("2. Valid withdrawal (ordinary case)");
    account.withdraw(12050);     // Rs 120.50

    printHeading("3. Deposit of zero (should be refused)");
    account.deposit(0);

    printHeading("4. Negative deposit (should be refused)");
    account.deposit(-2550);

    printHeading("5. Withdrawal of zero (should be refused)");
    account.withdraw(0);

    printHeading("6. Negative withdrawal (should be refused)");
    account.withdraw(-100);

    printHeading("7. Overdraft: withdraw more than the balance (should be refused)");
    account.withdraw(999999);

    printHeading("8. Boundary: withdraw one paisa MORE than the balance (refused)");
    account.withdraw(account.getBalance() + 1);

    printHeading("9. Boundary: withdraw EXACTLY the balance (allowed, leaves 0)");
    account.withdraw(account.getBalance());

    printHeading("10. Small amount shows two digits (5 paise -> Rs 0.05)");
    account.deposit(5);

    cout << "\nFinal balance: " << formatMoney(account.getBalance()) << "\n";

    return 0;
}

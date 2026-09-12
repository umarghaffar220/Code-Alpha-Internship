 #include <iostream>
#include <string>
#include <iomanip>
using namespace std;


// =====================================================
//                 TRANSACTION CLASS
// =====================================================

class Transaction
{
private:
    string type;
    double amount;
    string details;

public:

    Transaction()
    {
        type = "";
        amount = 0;
        details = "";
    }

    Transaction(string t, double a, string d)
    {
        type = t;
        amount = a;
        details = d;
    }

    void display()
    {
        cout << left
             << setw(15) << type
             << setw(12) << amount
             << details << endl;
    }
};


// =====================================================
//                    ACCOUNT CLASS
// =====================================================

class Account
{
private:
    int accountNumber;
    double balance;

    Transaction transactions[50];
    int transactionCount;

public:

    Account()
    {
        accountNumber = 0;
        balance = 0;
        transactionCount = 0;
    }

    Account(int accNo, double initialBalance)
    {
        accountNumber = accNo;
        balance = initialBalance;
        transactionCount = 0;
    }


    // Get Account Number
    int getAccountNumber()
    {
        return accountNumber;
    }


    // Get Balance
    double getBalance()
    {
        return balance;
    }


    // =================================================
    //                  DEPOSIT FUNCTION
    // =================================================

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "\nInvalid amount!\n";
            return;
        }

        double previousBalance = balance;

        balance = balance + amount;

        transactions[transactionCount] =
            Transaction("Deposit", amount, "Money deposited");

        transactionCount++;

        cout << "\nDeposit successful!\n";

        // Receipt
        cout << "\n";
        cout << "============================================\n";
        cout << "              BANK RECEIPT\n";
        cout << "============================================\n";
        cout << "Transaction Type : Deposit\n";
        cout << "Account Number   : " << accountNumber << endl;
        cout << "Previous Balance : Rs. "
             << fixed << setprecision(2)
             << previousBalance << endl;
        cout << "Amount           : Rs. "
             << amount << endl;
        cout << "New Balance      : Rs. "
             << balance << endl;
        cout << "Status           : Successful\n";
        cout << "============================================\n";
    }


    // =================================================
    //                 WITHDRAW FUNCTION
    // =================================================

    bool withdraw(double amount, bool showReceipt = true)
    {
        if (amount <= 0)
        {
            cout << "\nInvalid amount!\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "\nInsufficient balance!\n";
            return false;
        }

        double previousBalance = balance;

        balance = balance - amount;

        transactions[transactionCount] =
            Transaction("Withdrawal", amount, "Money withdrawn");

        transactionCount++;

        cout << "\nWithdrawal successful!\n";


        // Receipt
        if (showReceipt)
        {
            cout << "\n";
            cout << "============================================\n";
            cout << "              BANK RECEIPT\n";
            cout << "============================================\n";
            cout << "Transaction Type : Withdrawal\n";
            cout << "Account Number   : " << accountNumber << endl;
            cout << "Previous Balance : Rs. "
                 << fixed << setprecision(2)
                 << previousBalance << endl;
            cout << "Amount           : Rs. "
                 << amount << endl;
            cout << "New Balance      : Rs. "
                 << balance << endl;
            cout << "Status           : Successful\n";
            cout << "============================================\n";
        }

        return true;
    }


    // =================================================
    //              ADD TRANSFER TRANSACTION
    // =================================================

    void addTransfer(double amount, string details)
    {
        transactions[transactionCount] =
            Transaction("Transfer", amount, details);

        transactionCount++;
    }


    // =================================================
    //              ACCOUNT INFORMATION
    // =================================================

    void displayAccountInfo()
    {
        cout << "\n";
        cout << "========== ACCOUNT INFORMATION ==========\n";

        cout << "Account Number : "
             << accountNumber << endl;

        cout << "Balance        : Rs. "
             << fixed << setprecision(2)
             << balance << endl;

        cout << "=========================================\n";
    }


    // =================================================
    //             TRANSACTION HISTORY
    // =================================================

    void displayTransactions()
    {
        cout << "\n";
        cout << "========== TRANSACTION HISTORY ==========\n";

        if (transactionCount == 0)
        {
            cout << "No transactions available.\n";
            cout << "=========================================\n";
            return;
        }

        cout << left
             << setw(15) << "Type"
             << setw(12) << "Amount"
             << "Details" << endl;

        cout << "------------------------------------------\n";

        for (int i = 0; i < transactionCount; i++)
        {
            transactions[i].display();
        }

        cout << "==========================================\n";
    }
};


// =====================================================
//                    CUSTOMER CLASS
// =====================================================

class Customer
{
private:
    int customerID;
    string name;
    string phone;

    Account account;

public:

    Customer()
    {
        customerID = 0;
        name = "";
        phone = "";
    }


    Customer(int id, string n, string p,
             int accNo, double balance)
    {
        customerID = id;
        name = n;
        phone = p;

        account = Account(accNo, balance);
    }


    // =================================================
    //          DISPLAY CUSTOMER INFORMATION
    // =================================================

    void displayCustomerInfo()
    {
        cout << "\n";
        cout << "========== CUSTOMER INFORMATION ==========\n";

        cout << "Customer ID : "
             << customerID << endl;

        cout << "Name        : "
             << name << endl;

        cout << "Phone       : "
             << phone << endl;

        account.displayAccountInfo();
    }


    // =================================================
    //                  DEPOSIT
    // =================================================

    void deposit(double amount)
    {
        account.deposit(amount);
    }


    // =================================================
    //                  WITHDRAW
    // =================================================

    void withdraw(double amount)
    {
        account.withdraw(amount);
    }


    // =================================================
    //                  TRANSFER
    // =================================================

    void transfer(Customer &receiver, double amount)
    {
        if (amount <= 0)
        {
            cout << "\nInvalid amount!\n";
            return;
        }

        if (amount > account.getBalance())
        {
            cout << "\nInsufficient balance!\n";
            return;
        }


        double senderPreviousBalance =
            account.getBalance();

        double receiverPreviousBalance =
            receiver.account.getBalance();


        // Withdraw without showing withdrawal receipt
        bool success =
            account.withdraw(amount, false);


        if (success)
        {
            // Deposit without showing deposit receipt
            receiver.account.deposit(amount);


            // Add transfer history
            account.addTransfer(
                amount,
                "Transferred to another account"
            );

            receiver.account.addTransfer(
                amount,
                "Received from another account"
            );


            // =================================================
            //                  TRANSFER RECEIPT
            // =================================================

            cout << "\n";
            cout << "============================================\n";
            cout << "              BANK RECEIPT\n";
            cout << "============================================\n";

            cout << "Transaction Type : Fund Transfer\n";

            cout << "From Account     : "
                 << account.getAccountNumber() << endl;

            cout << "To Account       : "
                 << receiver.account.getAccountNumber()
                 << endl;

            cout << "Previous Balance : Rs. "
                 << fixed << setprecision(2)
                 << senderPreviousBalance << endl;

            cout << "Transfer Amount  : Rs. "
                 << amount << endl;

            cout << "New Balance      : Rs. "
                 << account.getBalance() << endl;

            cout << "Receiver Balance : Rs. "
                 << receiver.account.getBalance()
                 << endl;

            cout << "Status           : Successful\n";

            cout << "============================================\n";

            cout << "\nTransfer successful!\n";
        }
    }


    // =================================================
    //            SHOW TRANSACTION HISTORY
    // =================================================

    void showTransactions()
    {
        account.displayTransactions();
    }
};


// =====================================================
//                    MAIN FUNCTION
// =====================================================

int main()
{
    cout << "============================================\n";
    cout << "             BANKING SYSTEM\n";
    cout << "============================================\n";


    // =================================================
    //                 CREATE CUSTOMERS
    // =================================================

    Customer customer1(
        101,
        "Ali",
        "03001234567",
        1001,
        50000
    );


    Customer customer2(
        102,
        "Ahmed",
        "03111234567",
        1002,
        30000
    );


    int choice;
    double amount;


    // =================================================
    //                    MENU
    // =================================================

    do
    {
        cout << "\n\n============== MENU ==============\n";

        cout << "1. Display Customer Information\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";

        cout << "==================================\n";

        cout << "Enter your choice: ";
        cin >> choice;


        // =================================================
        // OPTION 1
        // =================================================

        if (choice == 1)
        {
            customer1.displayCustomerInfo();
        }
        // =================================================
        // OPTION 2
        // =================================================

        else if (choice == 2)
        {
            cout << "\nEnter amount to deposit: ";
            cin >> amount;

            customer1.deposit(amount);
        }


        // =================================================
        // OPTION 3
        // =================================================

        else if (choice == 3)
        {
            cout << "\nEnter amount to withdraw: ";
            cin >> amount;

            customer1.withdraw(amount);
        }


        // =================================================
        // OPTION 4
        // =================================================

        else if (choice == 4)
        {
            cout << "\nEnter amount to transfer to Ahmed: ";
            cin >> amount;

            customer1.transfer(customer2, amount);
        }


        // =================================================
        // OPTION 5
        // =================================================

        else if (choice == 5)
        {
            customer1.showTransactions();
        }


        // =================================================
        // OPTION 6
        // =================================================

        else if (choice == 6)
        {
            cout << "\n==================================\n";
            cout << "Thank you for using Banking System!\n";
            cout << "==================================\n";
        }


        // =================================================
        // INVALID CHOICE
        // =================================================

        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }

    }
    while (choice != 6);


    return 0;
}

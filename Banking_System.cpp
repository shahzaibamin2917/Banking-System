#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Transaction Class
class Transaction
{
public:
    string type;
    double amount;

    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }
};

// Account Class
class Account
{
public:
    int accountNumber;
    double balance;
    vector<Transaction> history;

    Account(int accNo)
    {
        accountNumber = accNo;
        balance = 0;
    }

    void deposit(double amount)
    {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposit Successful!\n";
    }

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
        }
        else
        {
            balance -= amount;
            history.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal Successful!\n";
        }
    }

    void transfer(Account &receiver, double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
        }
        else
        {
            balance -= amount;
            receiver.balance += amount;

            history.push_back(Transaction("Transfer Sent", amount));
            receiver.history.push_back(Transaction("Transfer Received", amount));

            cout << "Transfer Successful!\n";
        }
    }

    void showTransactions()
    {
        if (history.empty())
        {
            cout << "No Transactions Found!\n";
            return;
        }

        cout << "\nTransaction History\n";
        for (int i = 0; i < history.size(); i++)
        {
            cout << i + 1 << ". "
                 << history[i].type
                 << " : Rs. " << history[i].amount << endl;
        }
    }

    void showAccount()
    {
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Current Balance : Rs. " << balance << endl;
    }
};

// Customer Class
class Customer
{
public:
    int customerID;
    string name;
    Account account;

    Customer(int id, string n, int accNo)
        : account(accNo)
    {
        customerID = id;
        name = n;
    }

    void showCustomer()
    {
        cout << "\nCustomer ID : " << customerID << endl;
        cout << "Customer Name : " << name << endl;
        account.showAccount();
    }
};

int main()
{
    // Create Two Customers
    Customer customer1(101, "Ali", 1001);
    Customer customer2(102, "Ahmed", 1002);

    int choice;
    double amount;

    do
    {
        cout << "\n========== Banking System ==========\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer Money\n";
        cout << "4. View Transaction History\n";
        cout << "5. View Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            customer1.account.deposit(amount);
            break;

        case 2:
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            customer1.account.withdraw(amount);
            break;

        case 3:
            cout << "Enter Transfer Amount: ";
            cin >> amount;
            customer1.account.transfer(customer2.account, amount);
            break;

        case 4:
            customer1.account.showTransactions();
            break;

        case 5:
            customer1.showCustomer();
            break;

        case 6:
            cout << "Thank You for Using Banking System!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Transaction
{
private:
    string productName;
    int unitPrice, productQuantity;

public:
    Transaction() : productName(""), unitPrice(0), productQuantity(0) {}

    void setProductName(string name)
    {
        productName = name;
    }

    void setUnitPrice(int price)
    {
        unitPrice = price;
    }

    void setProductQuantity(int quantity)
    {
        productQuantity = quantity;
    }

    string getProductName()
    {
        return productName;
    }

    int getUnitPrice()
    {
        return unitPrice;
    }

    int getProductQuantity()
    {
        return productQuantity;
    }
};

void addNewProduct(Transaction t)
{
    bool keepRunning = true;
    while (keepRunning)
    {
        int userChoice;
        cout << "\t1. Add Product." << endl;
        cout << "\t2. Return to Main Menu." << endl;
        cout << "\tSelect an option: ";
        cin >> userChoice;

        if (userChoice == 1)
        {
            system("cls");
            string name;
            int price, quantity;

            cout << "\tEnter Product Name: ";
            cin >> name;
            t.setProductName(name);

            cout << "\tEnter Product Price: ";
            cin >> price;
            t.setUnitPrice(price);

            cout << "\tEnter Product Quantity: ";
            cin >> quantity;
            t.setProductQuantity(quantity);

            ofstream outputFile("D:/MarketInventory.txt", ios::app);
            if (!outputFile)
            {
                cout << "\tError: Unable to open file!" << endl;
            }
            else
            {
                outputFile << "\t" << t.getProductName() << " : " << t.getUnitPrice() << " : " << t.getProductQuantity() << endl;
                cout << "\tProduct successfully added!" << endl;
            }
            outputFile.close();
            Sleep(3000);
        }
        else if (userChoice == 2)
        {
            system("cls");
            keepRunning = false;
            cout << "\tReturning to Main Menu!" << endl;
            Sleep(3000);
        }
    }
}

void displayBill()
{
    system("cls");
    int totalAmount = 0;
    bool sessionActive = true;
    while (sessionActive)
    {
        system("cls");
        int selection;
        cout << "\t1. Add to Bill." << endl;
        cout << "\t2. Close and Calculate." << endl;
        cout << "\tChoose an option: ";
        cin >> selection;

        if (selection == 1)
        {
            string productName;
            int quantity;
            cout << "\tEnter Product Name: ";
            cin >> productName;
            cout << "\tEnter Quantity: ";
            cin >> quantity;

            ifstream inputFile("D:/MarketInventory.txt");
            ofstream tempFile("D:/TempInventory.txt");

            string record;
            bool found = false;

            while (getline(inputFile, record))
            {
                stringstream stream(record);
                string name;
                int price, availableQuantity;
                char delimiter;
                stream >> name >> delimiter >> price >> delimiter >> availableQuantity;

                if (productName == name)
                {
                    found = true;
                    if (quantity <= availableQuantity)
                    {
                        int totalCost = price * quantity;
                        cout << "\tProduct | Price | Quantity | Total" << endl;
                        cout << "\t" << name << "\t " << price << "\t " << quantity << "\t " << totalCost << endl;
                        availableQuantity -= quantity;
                        totalAmount += totalCost;

                        tempFile << "\t" << name << " : " << price << " : " << availableQuantity << endl;
                    }
                    else
                    {
                        cout << "\tSorry, not enough stock!" << endl;
                    }
                }
                else
                {
                    tempFile << record << endl;
                }
            }
            if (!found)
            {
                cout << "\tProduct not found!" << endl;
            }
            tempFile.close();
            inputFile.close();
            remove("D:/MarketInventory.txt");
            rename("D:/TempInventory.txt", "D:/MarketInventory.txt");
        }
        else if (selection == 2)
        {
            sessionActive = false;
            cout << "\tFinalizing Bill" << endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout << endl << "\tTotal Amount Due: " << totalAmount << endl;
    cout << "\tThank you for shopping!" << endl;
    Sleep(5000);
}

int main()
{
    Transaction t;

    bool running = true;
    while (running)
    {
        system("cls");
        int option;

        cout << "\tWelcome to the Nisarg Supermart" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add New Product." << endl;
        cout << "\t2. Generate Bill." << endl;
        cout << "\t3. View All Products." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tSelect an option: ";
        cin >> option;

        if (option == 1)
        {
            system("cls");
            addNewProduct(t);
            Sleep(3000);
        }
        else if (option == 2)
        {
            displayBill();
        }
        else if (option == 3)
        {
            system("cls");
            ifstream inputFile("D:/MarketInventory.txt");
            string line;
            cout << "\tProduct Inventory:" << endl;
            while (getline(inputFile, line))
            {
                cout << line << endl;
            }
            inputFile.close();
            Sleep(5000);
        }
        else if (option == 4)
        {
            system("cls");
            running = false;
            cout << "\tGoodbye!" << endl;
            Sleep(3000);
        }
    }
}

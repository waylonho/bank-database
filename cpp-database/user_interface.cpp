/*****************************************************************
//
//  NAME:        Waylon Ho
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 21, 2022
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   The file explains the basis of the program and how to use it,
//   then will ask the user to choose a choice until the user asks
//   to quit the program, at which point the program will terminate.
//
****************************************************************/

#include <iomanip>
#include <iostream>
#include <string.h>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   The function gets the address from the user. The
//                 address will be terminated if the user indicates
//                 a ";" or runs out of the character limit (50).
//
//  Parameters:    address (char[]) : The address of we want to add.
//                 
//                 size (int) : the size of our address
//
//  Return values:  void : There is no return value;
//
****************************************************************/

void getaddress(char address[])
{
    int i = 0;

    cout << "\nEnter an address (if longer than 50 characters, end it with ;. Ex: 123 Fake Ave;): ";
    while((i < 50) && (address[i] = cin.get()) != ';')
    {
        i++;
    }

    address[i] = 0;

}

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function gives the user some background
//                 information, then puts them in a loop and keeps 
//                 checking what the user is inputting until the
//                 user wants to quit. If the user selects a valid
//                 option, the program runs them through the
//                 additional information needed. 
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : ran program successfully.
//                 
//
****************************************************************/

int main(int argc, char* argv[])
{
    char userInput[30];
    char name[30];
    char address[50];

    char addfull[30] = "add";
    char printallfull[30] = "printall";
    char findfull[30] = "find";
    char deletefull[30] = "delete";
    char quitfull[30] = "quit";

    //char testOutput[30] = "testOutput";
    //char testInput[30] = "testInput.txt";

    int accountno;
    int breakout = 0;
    int innerbreakout = 0;
    int intPass = 0;

    #ifdef debug
        cout << "\nRunning in debug mode...\n";
    #endif

    llist testList;

    cout << "\nWelcome to the bank. Please type one of the functions below and hit Enter.\n\n";
    cout << "add: Add a new bank record.\n";
    cout << "printall: Display all bank records.\n";
    cout << "find: Search for a certain bank record.\n";
    cout << "delete: Delete a bank record.\n";
    cout << "quit: Quit the program.\n";

    while (breakout == 0)
    {

    cout << "\nEnter a function: ";
    cin >> userInput;
    
    if (strstr(addfull, userInput))
    {
        innerbreakout = 0;
        intPass = 0;

        do
        {
            cout << "\nEnter an account #: ";
            cin >> accountno;
            if (accountno > 0)
            {
                intPass = 1;
            }

            if (accountno > 0 && intPass == 1)
            {
                innerbreakout++;
            } 
            else if (accountno <= 0 && intPass == 1)
            {
                intPass--;
                cout << "\nPlease enter an int greater than 0.\n";
            }
            else
            {
                cout << "\nPlease enter an INT.\n";
            }
        } while (innerbreakout == 0);

        cin.ignore();
        cout << "\nPlease enter a name: ";
        cin.get(name, 30);
        cin.ignore();

        getaddress(address);
        
        testList.addRecord(accountno, name, address);

    } else if (strstr(printallfull, userInput))
    {
        testList.printAllRecords();
    } else if (strstr(findfull, userInput))
    {
        innerbreakout = 0;
        intPass = 0;

        do
        {
            cout << "\nEnter an account #: ";
            cin >> accountno;
            if (accountno > 0)
            {
                intPass = 1;
            }

            if (accountno > 0 && intPass == 1)
            {
                innerbreakout++;
            }
            else if (accountno <= 0 && intPass == 1)
            {
                cin.ignore();
                intPass--;
                cout << "\nPlease enter an int greater than 0.\n";
            }
            else
            {
                cin.ignore();
                cout << "\nPlease enter an INT.\n";
            }
        } while(innerbreakout == 0);
        testList.findRecord(accountno);
    }
    else if (strstr(deletefull, userInput))
    {        
        innerbreakout = 0;
        intPass = 0;

        do
        {
            cout << "\nEnter an account #: ";
            cin >> accountno;
            if (accountno > 0)
            {
                intPass = 1;
            }
            if (accountno > 0 && intPass ==1)
            {
                innerbreakout++;
            }
            else if (accountno <= 0 && intPass == 1)
            {
                cin.ignore();
                intPass--;
                cout << "\nPlease enter an int greater than 0.\n";
            }
            else
            {
                cin.ignore();
                cout << "\nPlease enter an INT.\n";
            }
        } while(innerbreakout == 0);
        testList.deleteRecord(accountno);
    }
    else if (strstr(quitfull, userInput))
    {
        breakout++;
    }
    else
    {
        cout << "\nInvalid input. Please type an option(Ex. add, delete, etc.)\n";
        cin.ignore();
    }
    
    }

    //cleanup();

    return 0;
    
}

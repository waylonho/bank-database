/*****************************************************************
//
//  NAME:        Waylon Ho
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 19, 2022
//
//  FILE:        llist.cpp
//
//  DESCRIPTION: Contains the functions we will use for the
//               database of records.
//   
****************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "record.h"
#include "llist.h"

using namespace std;

llist::llist()
{
    this->start = NULL;
}

llist::llist(char filename[])
{
    strcpy(this->filename, filename);
    this->start = NULL;
    //readfile();
}

llist::~llist()
{
    //writefile();
    cleanup();
}


/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   The function adds a record to the database.
//
//  Parameters:    uaccountno (int) : account # we are adding
//                 name (char[]) : name of account we are adding
//                 address (char[]) : address of account we are adding
//
//  Return values:  void : the function returns nothing
//
****************************************************************/

void llist::addRecord(int uaccountno, char name[], char address[])
{
    record * newNode = new record();
    record * temp;
    record * prev;

    #ifdef debug
        cout << "\nRunning addRecord...\n";
        cout << "Account No: " << uaccountno << "\n";
        cout << "Name: " << name << "\n";
        cout << "Address: " << address << "\n";
    #endif

    newNode->accountno = uaccountno;
    strcpy(newNode->name, name);
    strcpy(newNode->address, address);
    newNode->next = NULL;

    if (this->start == NULL)
    {
        start = newNode;
    }
    else if (uaccountno <= start->accountno)
    {
        newNode->next = this->start;
        this->start = newNode;
    }
    else
    {
        int breakout = 0;
        temp = this->start;
        prev = this->start;

        do
        {
            if (uaccountno <= temp->accountno)
            {
                prev->next = newNode;
                newNode->next = temp;
                breakout = 1;
            }
            else if (temp->next == NULL)
            {
                temp->next = newNode;
                breakout = 1;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        } while (breakout == 0);
    }

}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   The function prints all the record in the database
//                 along with their information.
//
//  Parameters:    Nothing.
//
//  Return value:  void : the function returns nothing
//
****************************************************************/

void llist::printAllRecords()
{
    int temp = 0;
    record * current;
    current = start;

    #ifdef debug
        cout << "\nRunning printAllRecords...\n";
    #endif

    cout << "\n";

    while (current)
    {
        cout << "Account #: " << current->accountno << "\n";
        cout << "Name: " << current->name << "\n";
        cout << "Address: " << current->address << "\n";
        current = current->next;
        temp++;
    }

    if (temp == 0)
    {
        cout << "There are no records in the database.\n";
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   The function finds the matching record(s) with
//                 the desired account #.
//
//  Parameters:    uaccountno (int) : accountno the user wants
//                 to find associated accounts with.
//
//  Return value:  0 : record(s) was found successfully.
//                 -1 : record(s) was not found successfully.
//
****************************************************************/

int llist::findRecord(int uaccountno)
{
    int finalReturnValue;
    record * current;
    current = start;
    finalReturnValue = -1;

    #ifdef debug
        cout << "\nRunning findRecord...\n";
        cout << "Searching for Account No: " << uaccountno << "\n";
    #endif

    cout << "\n";

    while (current)
    {
        if(current->accountno == uaccountno)
        {
            cout << "Account #: " << current->accountno << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Address: " << current->address << "\n";
            finalReturnValue = 0;
        }

        current = current->next;
    }

    if (finalReturnValue == -1)
    {
        cout << "No record was found with account #: " << uaccountno << "\n";
    }

    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   The function deletes the matching record(s) with
//                 the desired account #.
//
//  Parameters:    uaccountno (int) : accountno the user wants
//                 to delete.
//
//  Return value:  0 : record(s) was deleted  successfully.
//                 -1 : record(s) was not deleted successfully.
//
****************************************************************/

int llist::deleteRecord(int uaccountno)
{
    int finalReturnValue;
    record * prevNode;
    record * currentNode;
    record * releaseNode;

    #ifdef debug
        cout << "\nRunning deleteRecord...\n";
        cout << "Deleting Account No: " << uaccountno << "\n";
    #endif

    if (this->start == NULL)
    {
        finalReturnValue = -1;
    }
    else if (uaccountno == start->accountno && start-> next == NULL)
    {
        delete start;
        start = NULL;
        finalReturnValue = 0;
    }
    else if (uaccountno == start->accountno && start->next != NULL)
    {
        currentNode = start->next;
        delete start;
        while (currentNode->accountno == uaccountno && currentNode->next != NULL)
        {
            releaseNode = currentNode;
            currentNode = currentNode->next;
            delete releaseNode;
        }
        if (currentNode->accountno == uaccountno)
        {
            delete currentNode;
            start = NULL;
        }
        else if (currentNode->accountno > uaccountno)
        {
            start = currentNode;
        }
        finalReturnValue = 0;
    }
    else if (uaccountno != start->accountno && start->next == NULL)
    {
        finalReturnValue = -1;
    }
    else if (uaccountno != start->accountno && start->next != NULL)
    {
        prevNode = start;
        currentNode = start->next;
        while (currentNode->accountno < uaccountno && currentNode->next != NULL)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->accountno != uaccountno)
        {
            finalReturnValue = -1;
        }
        else if (currentNode->accountno == uaccountno)
        {
            while (currentNode->accountno == uaccountno && currentNode->next != NULL)
            {
                releaseNode = currentNode;
                currentNode = currentNode->next;
                delete releaseNode;
            }
            if (currentNode->accountno == uaccountno && currentNode->next == NULL)
            {
                delete currentNode;
                prevNode->next = NULL;
            }
            else
            {
                prevNode->next = currentNode;
            }
            finalReturnValue = 0;
        }
    }

    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Function that writes the linked list at the end
//                 to a txt file. If there is already a txt file with
//                 the same name, it will be overwritten.
//
//  Parameters:    Nothing.
//
//  Return values:  0 : writefile ran successfully.
//                  -1 : writefile ran unsuccessfully.
//
****************************************************************/

int llist::writefile()
{
    int finalReturnValue;
    int counter;
    record * temp;
    FILE *fout;
    counter = 0;
    temp = start;
    fout = fopen(filename, "w");

    #ifdef debug
        cout << "\nRunning writefile...\n";
        cout << "filename : " << filename << "\n";
    #endif

    if (fout == NULL)
    {
        finalReturnValue = -1;
    }
    else
    {
        while(temp)
        {
            if (temp->next == NULL)
            {
                fprintf(fout, "%d\n%s\n%s", temp->accountno, temp->name, temp->address);
            }
            else
            {
                fprintf(fout, "%d\n%s\n%s\n", temp->accountno, temp->name, temp->address);
            }
            counter++;
            temp = temp->next;
        }
        finalReturnValue = 0;
    }

    fclose(fout);
    return finalReturnValue;

}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Function that reads from a file and loads records.
//
//  Parameters:    Nothing.
//
//  Return values:  0 : readfile ran successfully.
//                  -1 : readfile ran unsuccessfully.
//
****************************************************************/

int llist::readfile()
{
    int finalReturnValue;
    int counter;
    int accountno;

    char name[30];
    char address[50];
    ifstream fin;
    counter = 0;
    fin.open(filename);

    #ifdef debug
        cout << "\nRunning readfile...\n";
        cout << "filename : " << filename << "\n";
    #endif

    if (fin == NULL)
    {
        finalReturnValue = -1;
    }
    else
    {
        while (!fin.eof())
        {
            fin >> accountno;
            fin.get();
            fin.getline(name, 30);
            fin.getline(address, 50);
            fin.get();

            addRecord(accountno, name, address);

            counter++;
        }
        finalReturnValue = 0;
    }

    fin.close();
    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Frees up all the memory that was used by the program.
//
//  Parameters:    Nothing.
//
//  Return values:  void: There is no return value.
//
****************************************************************/

void llist::cleanup()
{
    record * lagging;
    lagging = start;

    #ifdef debug
        cout << "\nRunning cleanup...\n";
    #endif

    while(start->next != NULL)
    {
        lagging = start;
        start = start->next;
        delete lagging;
    }

    delete start;
    start = NULL;
}



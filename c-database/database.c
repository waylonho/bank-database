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
//  DATE:        March 23, 2022
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   These functions are called in user_interface.c to run our
//   record program. All the functions are defined below.
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"

extern int debugmode;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   We don't use the main function in database.c. I
//                 decided to comment it out rather than delete it,
//                 as it's always good to have it just in case we
//                 need it in the future.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : no meaning (as of current date)
//
****************************************************************

int main(int argc, char* argv[])
{
    printf("THIS CODE DOES NOT RUN");
    return 0;
}
*/

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   The function adds a new record to the database.
//                 If we are in debug mode, we print out the info
//                 so that we can see if everything is being passed
//                 properly.
//
//  Parameters:    start (struct record**) : the pointer to
//                 the starting record  pointer (if not null)
//                 uaccountno (int) : account # we are adding
//                 name (char[]) : name of account we are adding
//                 address (char[]) : address of account we are adding
//
//  Return values:  void : There is no return value.
//
****************************************************************/

void addRecord(struct record** start, int uaccountno, char name[30], char address[50])
{
    struct record * newNode = (struct record*)malloc(sizeof(struct record));
    struct record * temp;
    struct record * prev;

    if (debugmode == 1)
    {
        printf("\nRunning addRecord...\n");
        printf("Account #: %d\n", uaccountno);
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
    }

    newNode->accountno = uaccountno;
    strcpy(newNode->name, name);
    strcpy(newNode->address, address);
    newNode->next = NULL;
 
    if (*start == NULL)
    {
        *start = newNode;
    }
    else if (uaccountno <= (*start)[0].accountno)
    {
        newNode->next = *start;
        *start = newNode;
    }
    else
    {
        int breakout = 0;
        temp = *start;
        prev = *start;

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
//  DESCRIPTION:   The function prints all the records in the database.
//                 
//  Parameters:    start (record *) : contains the address for the
//                 first record (if not null) in the database.
//
//  Return values:  void : There is no return value.
//
****************************************************************/

void printAllRecords(struct record* start)
{
    int temp;
    struct record * current;
    current = start;
    temp = 0;

    if (debugmode == 1)
    {
        printf("\nRunning printAllRecords...\n");
    }

    while (current)
    {
        printf("\nAccount #: %d\nAccount Name: %s\nAddress: %s\n", current->accountno, current->name, current->address);
        current = current->next;
        temp = 1;
    }

    if (temp == 0)
        printf("\nThere are no records in the database.\n");

}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   The function finds a record in a specific database.
//
//  Parameters:    start (record *) : The pointer to the starting
//                 record (if not null) in the database.
//
//                 accountno (int) : The account number we are searching
//                 for.
//
//  Return values:  0 : The record was not found.
//                  1 : The record was found successfully.
//
****************************************************************/

int findRecord(struct record * start, int accountno)
{
    int finalReturnValue;
    struct record * current;
    current = start;
    finalReturnValue = 0;

    if (debugmode == 1)
    {
        printf("\nRunning findRecord...\n");
        printf("Account #: %d\n", accountno);
    }

    while (current)
    {
        if (current->accountno == accountno)
        {
            printf("\nAccount #: %d\n", current->accountno);
            printf("Name: %s\n", current->name);
            printf("Address: %s\n", current->address);
            finalReturnValue = 1;
        }

        current = current->next;
    }

    if (finalReturnValue == 0)
    {
        printf("\nFound no record with account #: %d\n", accountno);
    }

    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   The function deletes a record in the database.
//
//  Parameters:    start (record **) : The pointer to the pointer to
//                 the first record (if not null) in the database.
//
//                 uaccountno (int) : The account number we want 
//                 to delete.
//
//  Return values:  -1 : The record was not removed.
//                  0 : The record was removed successfully.
//
****************************************************************/

int deleteRecord (struct record** start, int uaccountno)
{

    int finalreturnvalue;
    struct record * prevNode;
    struct record * currentNode;
    struct record * releaseNode;

    if (debugmode == 1)
    {
        printf("\nRunning deleteRecord...\n");
        printf("Account #: %d\n", uaccountno);
    }

    if (*start == NULL)
    {
        finalreturnvalue = -1;
    }
    else if (uaccountno == (*start)[0].accountno && (*start)[0].next == NULL)
    {
        free(*start);
        *start = NULL;
        finalreturnvalue = 0;
    }
    else if (uaccountno == (*start)[0].accountno && (*start)[0].next != NULL)
    {
        currentNode = (*start)[0].next;
        free(*start);
        while (currentNode->accountno == uaccountno && currentNode->next != NULL)
        {
            releaseNode = currentNode;
            currentNode = currentNode->next;
            free(releaseNode);
        }
        if (currentNode->accountno == uaccountno)
        {
            free(currentNode);
            *start = NULL;
        }
        else if (currentNode->accountno > uaccountno)
        {
            *start = currentNode;
        }
        finalreturnvalue = 0;
    }
    else if (uaccountno != (*start)[0].accountno && (*start)[0].next == NULL)
    {
        finalreturnvalue = -1;
    }
    else if (uaccountno != (*start)[0].accountno && (*start)[0].next != NULL)
    {

        prevNode = *start;
        currentNode = (*start)[0].next;
        while (currentNode->accountno < uaccountno && currentNode->next != NULL)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->accountno != uaccountno)
        {
            finalreturnvalue = -1;
        }
        else if (currentNode->accountno == uaccountno)
        {
            while (currentNode->accountno == uaccountno && currentNode->next != NULL)
            {
                releaseNode = currentNode;
                currentNode = currentNode->next;
                free(releaseNode);
            }
            if (currentNode->accountno == uaccountno && currentNode->next == NULL)
            {
                free(currentNode);
                prevNode->next = NULL;
            }
            else
            {
                prevNode->next = currentNode;
            }
            finalreturnvalue = 0;
        }
    }

    return finalreturnvalue;
}

/*****************************************************************
//
//  Function name: writefile 
//
//  DESCRIPTION: A iofunctions.c function from the header. 
//  This function writes the data stored in the input 
//  array into a text file. If there is already a text 
//  file with the same name, it will be overwritten. 
// 
//  Parameters: start (struct record *) : A pointer that points to
//              the starting record (if not null) of the database.
//
//              filename[] (char []) : A char array that contains 
//              the name of our final text file.
// 
//  Return values:  0 : file was written successfully 
//                 -1 : file was written unsuccessfully 
//
****************************************************************/

int writefile (struct record * start, char filename[30])
{
    int finalReturnValue;
    int counter;
    FILE *fout;
    counter = 0;
    strcat(filename, ".txt");
    fout = fopen(filename, "w");

    if (fout == NULL)
    {
        finalReturnValue = -1;
    }
    else
    {
        while (start)
        {
            if (start->next == NULL)
            {
                fprintf(fout, "%d\n%s\n%s", start->accountno, start->name, start->address);
            }
            else
            {
                fprintf(fout, "%d\n%s\n%s\n", start->accountno, start->name, start->address);
            }
            counter++;
            start = start->next;
        }
        finalReturnValue = 0;
    }

    if (debugmode == 1)
    {
        printf("\nRunning writefile...\n");
        printf("There were %d records in database\n", counter);
    }

    fclose(fout);
    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION: A iofunctions.c function from the header.
//  This function reads the data stored in the input
//  file and loads it into an array.
//
//  Parameters: start (struct record *) : A pointer that points to
//              the pointer that points to the starting record
//              (if not null) if the database.
//
//              filename[] (char []) : A char array that contains
//              the name of our final text file.
//
//  Return values:  0 : file was written successfully
//                 -1 : file was written unsuccessfully
//
****************************************************************/

int readfile (struct record ** start, char filename[])
{
    int finalReturnValue;
    int counter;
    int accountno;
    char line[50];
    char name[30];
    char address[50];
    FILE *fin;
    counter = 0;
    fin = fopen(filename, "r");

    if (fin == NULL)
    {
        finalReturnValue = -1;
    }
    else
    {
        fscanf(fin, "%s", line);
        while(!feof(fin))
        {
            
            sscanf(line, "%d", &accountno);

            fgets(line, 50, fin);
            fgets(name, 30, fin);
            name[strlen(name) - 1] = 0;        

            fgets(address, 50, fin);
            address[strlen(address) - 1] = 0;

            addRecord(start, accountno, name, address);

            fscanf(fin, "%s", line);
            counter++;
        }

        if (debugmode == 1)
        {
            printf("Amount of records loaded from readfile: %d\n", counter);
        }
        finalReturnValue = 0;
    }

    fclose(fin);
    return finalReturnValue;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Frees up all the memory that was taken by the
//                 record database.
//
//  Parameters:    start (struct record **): A pointer that points
//                 to the pointer that points to the starting record.
//  
//  Return values: void (no return value)
//
*****************************************************************/

void cleanup (struct record ** start)
{
    struct record * lagging;
    lagging = *start;

    while ((*start)[0].next != NULL)
    {
        lagging = *start;
        *start = (*start)[0].next;
        free(lagging);
    }

    free(*start);
    *start = NULL;
}

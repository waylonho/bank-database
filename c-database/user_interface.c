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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   The file explains the basis of the program and how to use it,
//   then will ask the user to choose a choice until the user asks
//   to quit the program, at which point the program will terminate.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"
int debugmode;

/*****************************************************************
//
//  Function name: getaddress
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

void getaddress(char address[], int size)
{
    int i = 0;
    printf("\nPlease enter an address (if shorter than 50 characters, put ; at the end). Ex: 1234 Hawaii Avenue; : ");
    do
    {
        char c = fgetc(stdin);
        address[i] = c;
        i++;

        if (address[i-1] == ';')
        {
            address[i-1] = 0;
            i = size + 1;
        }

    } while (i < size);

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
    char trash[30];
    char name[30];
    char address[50];

    char addfull[30] = "add";
    char printallfull[30] = "printall";
    char findfull[30] = "find";
    char deletefull[30] = "delete";
    char testOutput[30] = "testOutput";
    char testInput[30] = "testInput.txt";

    int accountno;
    int breakout = 0;
    int innerbreakout = 0;
    int intPass = 0;
    struct record * start = NULL;

    if (argc == 1)
    {
        debugmode = 0;
    }
    else if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
    }
    else
    {
        printf("Not a valid mode to launch the program. Please relaunch appropiately.\n");
        return 0;
        /*
        I know this is not allowed. I was supposed to do an if statement, then put EVERYTHING
        below under that if statement. I would have to put 4 spaces after EVERY line. So instead,
        I put a different return statement. Sorry.
        */
    }

    readfile(&start, testInput);

    printf("\nWelcome to the bank. Please type one of the functions below and hit Enter. Depending on your input, there may be further details asked.\n\n");
    printf("add: Add a new bank record.\n");
    printf("printall: Display all bank records.\n");
    printf("find: Search for a certain bank record.\n");
    printf("delete: Delete a bank record.\n");
    printf("quit: Quit the program.\n");

    do
    {

    printf("\nEnter a function: ");
    scanf("%s", userInput);
    
    if (strstr(addfull, userInput))
    {
        innerbreakout = 0;
        intPass = 0;

        do
        {
            printf("\nEnter an account #: ");
            if (scanf("%d", &accountno))
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
                printf("\nPlease enter an int greater than 0.\n");
            }
            else
            {
                fgets(trash, 30, stdin);
                printf("\nPlease enter an INT.\n");
            }
        } while (innerbreakout == 0);

        printf("\nPlease enter a name: ");
        fgetc(stdin);
        fgets(name, 20, stdin);
        name[strlen(name) - 1] = 0;

        getaddress(address, 50);
        
        addRecord(&start, accountno, name, address);

    } else if (strstr(printallfull, userInput))
    {
        printAllRecords(start);
    } else if (strstr(findfull, userInput))
    {
        innerbreakout = 0;
        intPass = 0;

        do
        {
            printf("\nEnter an account #: ");
            if (scanf("%d", &accountno))
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
                printf ("\nPlease enter an int greater than 0.\n");
            }
            else
            {
                fgets(trash, 30, stdin);
                printf("\nPlease enter an INT.\n");
            }
        } while(innerbreakout == 0);
        findRecord(start, accountno);
    }
     else if (strstr(deletefull, userInput))
    {        
        innerbreakout = 0;
        intPass = 0;

        do
        {
            printf("\nEnter an account #: ");
            if (scanf("%d", &accountno))
            {
                intPass = 1;
            }
            if (accountno > 0 && intPass ==1)
            {
                innerbreakout++;
            }
            else if (accountno <= 0 && intPass == 1)
            {
                intPass--;
                printf ("\nPlease enter an int greater than 0.\n");
            }
            else
            {
                fgets(trash, 30, stdin);
                printf("\nPlease enter an INT.\n");
            }
        } while(innerbreakout == 0);
        deleteRecord(&start, accountno);
    }
    else if (strcmp("quit", userInput) == 0)
    {
        breakout++;
    }
    else
    {
        printf("\nInvalid input. Please type an option(Ex. add, delete, etc.)\n");
        fgets(trash, 30, stdin);
    }
    
    } while (breakout == 0);

    writefile(start, testOutput);
    cleanup(&start);
    return 0;
    
}

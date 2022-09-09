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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Header that defines what we need for llist.cpp.
//
****************************************************************/

class llist
{
private:
    record *    start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    void addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This header file declares multiple variables for record, specifically
//   variables we need to access the bank account and its info.
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};

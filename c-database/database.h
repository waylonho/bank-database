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
//  FILE:        database.h
//
//  DESCRIPTION:
//   This file declares the functions we are going to use in the 
//   database.c file. This is only a header file, so there is no
//   definition for the functions.
//
****************************************************************/

void addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char []);
int readfile(struct record **, char[]);
void cleanup(struct record **);

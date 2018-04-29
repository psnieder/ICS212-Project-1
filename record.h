/*****************************************************************
 //
 //  NAME:        Paul Snieder
 //
 //  HOMEWORK:    Project 1
 //
 //  CLASS:       ICS 212
 //
 //  INSTRUCTOR:  Ravi Narayan
 //
 //  DATE:        October 15, 2017
 //
 //  FILE:        record.h
 //
 //  DESCRIPTION:
 //   This file contains the structure for the records that are
 //   entered in the bank database application.
 //
 //
 ****************************************************************/

#ifndef record_h
#define record_h

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif /* record_h */

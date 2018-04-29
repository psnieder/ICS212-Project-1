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
 //  FILE:        project1_db.c
 //
 //  DESCRIPTION:
 //   This file contains the database functions for the bank
 //   database application.
 //
 //
 ****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

extern int debugmode;

/*****************************************************************
 //
 //  Function name: addRecord
 //
 //  DESCRIPTION:   Adds a record containing an account number, name,
 //                 and address to the database
 //
 //  Parameters:    record (struct ** record) : Pointer to the record database
 //                 accountno (int)           : The acount number of the person
 //                 name (char[])             : The name of the person
 //                 address (char[])          : The address of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int addRecord (struct record ** record, int accountno, char name[], char address[])
{
    int ret;
    struct record * recordToAdd;
    struct record * temp;
    
    temp = *record;
    ret = 0;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: addRecord\n**DEBUG** Account Number: %d\n**DEBUG** Name: %s**DEBUG** Address: %s\n", accountno, name, address);
    }
    
    while (temp != NULL)
    {
        if (accountno == (*temp).accountno)
        {
            ret = -1;
        }
        
        temp = (*temp).next;
    }
    
    if (*record == NULL)
    {
        recordToAdd = (struct record *) malloc(sizeof(struct record));
        *record = recordToAdd;
        (*recordToAdd).accountno = accountno;
        strcpy((*recordToAdd).name, name);
        strcpy((*recordToAdd).address, address);
        (*recordToAdd).next = NULL;
    }
    else if (ret == 0)
    {
        recordToAdd = (struct record *) malloc(sizeof(struct record));
        temp = *record;
        
        while ((*temp).next != NULL)
        {
            temp = (*temp).next;
        }
        
        (*temp).next = recordToAdd;
        (*recordToAdd).accountno = accountno;
        strcpy((*recordToAdd).name, name);
        strcpy((*recordToAdd).address, address);
        (*recordToAdd).next = NULL;
    }
    else
    {
        ret = -1;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: printRecord
 //
 //  DESCRIPTION:   Prints the record with account number "accountno"
 //
 //  Parameters:    record (struct * record) : Pointer to the record database
 //                 accountno (int)          : The acount number of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int printRecord (struct record * record, int accountno)
{
    
    int ret = -1;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: printRecord\n**DEBUG** Account Number: %d\n", accountno);
    }
    
    while (record != NULL)
    {
        if (accountno == (*record).accountno)
        {
            ret = 0;
            printf("\n");
            printf("Account Number: %d\n", (*record).accountno);
            printf("Name: %s", (*record).name);
            printf("Address: %s", (*record).address);
        }
        
        record = (*record).next;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: modifyRecord
 //
 //  DESCRIPTION:   Modifies the address field of the record with account
 //                 number "accountno"
 //
 //  Parameters:    record (struct ** record) : Pointer to the record database
 //                 accountno (int)           : The acount number of the person
 //                 address (char[])          : The address of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int modifyRecord (struct record * record, int accountno, char address[])
{
    
    int ret = -1;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: modifyRecord\n**DEBUG** Account Number: %d\n**DEBUG** Address: %s\n", accountno, address);
    }
    
    while (record != NULL)
    {
        if (accountno == (*record).accountno)
        {
            ret = 0;
            strcpy((*record).address, address);
        }
        
        record = (*record).next;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: printAllRecords
 //
 //  DESCRIPTION:   Prints all records in the database
 //
 //  Parameters:    record (struct * record) : Pointer to the record database
 //
 //  Return values:  none
 //
 ****************************************************************/

void printAllRecords(struct record * record)
{
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: printAllRecords\n");
    }
    
    while (record != NULL)
    {
        printf("\n");
        printf("Account Number: %d\n", (*record).accountno);
        printf("Name: %s", (*record).name);
        printf("Address: %s", (*record).address);
        
        record = (*record).next;
    }
}

/*****************************************************************
 //
 //  Function name: deleteRecord
 //
 //  DESCRIPTION:   Deletes the record with account number "accountno"
 //
 //  Parameters:    record (struct * record) : Pointer to the record database
 //                 accountno (int)          : The acount number of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int deleteRecord(struct record ** record, int accountno)
{
    
    int ret;
    struct record * recordToDelete;
    struct record * temp;
    
    recordToDelete = *record;
    temp = *record;
    ret = -1;
    
    while (recordToDelete != NULL)
    {
        if ((*recordToDelete).accountno == accountno)
        {
            ret = 0;
            
            if (recordToDelete == *record)
            {
                *record = (*recordToDelete).next;
                temp = *record;
            }
            else
            {
                while ((*temp).next != recordToDelete)
                {
                    temp = (*temp).next;
                }
                
                (*temp).next = (*recordToDelete).next;
            }
            
            free(recordToDelete);
            recordToDelete = temp;
        }
        
        if (temp != NULL)
        {
            recordToDelete = (*recordToDelete).next;
        }
    }
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: deleteRecord\n**DEBUG** Account Number: %d\n\n", accountno);
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: readfile
 //
 //  DESCRIPTION:   Adds records read from a file to the database
 //
 //  Parameters:    record (struct ** record) : Pointer to the record database
 //                 filename (char[])         : File to be read
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int readfile(struct record ** record, char filename[])
{
    int ret;
    char tempArray[80];
    char addressArray[80];
    struct record * recordToRead;
    struct record * temp;
    FILE * file;
    
    ret = 0;
    file = fopen(filename, "r");
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: readfile\n**DEBUG** Start's Address: %p\n**DEBUG** Filename: %s\n\n", (void*)(record), filename);
    }

    if (file == NULL)
    {
        ret = -1;
    }
    
    while (file != NULL && fgets(tempArray, 80, file) != NULL)
    {
        recordToRead = (struct record *) malloc(sizeof(struct record));
        if (*record == NULL)
        {
            *record = recordToRead;
        }
        else
        {
            temp = *record;
            while ((*temp).next != NULL)
            {
                temp = (*temp).next;
            }
            (*temp).next = recordToRead;
        }
        (*recordToRead).accountno = atoi(tempArray);
        fgets(tempArray, 80, file);
        strcpy((*recordToRead).name, tempArray);
        memset(addressArray, '\0', 80);
        while ((fgets(tempArray, 80, file) != NULL) && (strcmp(tempArray, "\n") != 0) && (strcmp(tempArray, "\r\n") != 0))
        {
            strcat(addressArray, tempArray);
        }
        
        strcpy((*recordToRead).address, addressArray);
        memset(addressArray, '\0', 80);
        (*recordToRead).next = NULL;
    }
    
    if (file != NULL)
    {
        fclose(file);
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: writefile
 //
 //  DESCRIPTION:   Writes records in the database to a file
 //
 //  Parameters:    record (struct * record) : Pointer to the record database
 //                 filename (char[])        : File to write to
 //
 //  Return values:  None
 //
 ****************************************************************/

void writefile(struct record * record, char filename[])
{
    FILE * file;;
    file = fopen(filename, "w");
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: writefile\n**DEBUG** Start: %p\n**DEBUG** Filename: %s\n\n", (void*)(record), filename);
    }
    
    while (record != NULL && file != NULL)
    {
        fprintf(file, "%d\n", (*record).accountno);
        fputs((*record).name, file);
        fputs((*record).address, file);
        fputs("\n", file);
        
        record = (*record).next;
    }
    
    if (file != NULL)
    {
        fclose(file);
    }
}

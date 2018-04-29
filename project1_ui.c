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
 //  FILE:        project1_ui.c
 //
 //  DESCRIPTION:
 //   This file contains the user interface functions and main function
 //   for the bank database application
 //
 //
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
int addRecord (struct record **, int, char[], char[]);
int printRecord (struct record *, int);
int modifyRecord (struct record *, int, char[]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
void writefile(struct record *, char[]);
void getAddress (char[], int);
void getName (char[], int);
void getAccountno (int *);

int debugmode;

/*****************************************************************
 //
 //  Function name: getAddress
 //
 //  DESCRIPTION:   Gets the user's address from the user
 //
 //  Parameters:    address (char[])    : Array to hold the address
 //                 maxCharacters (int) : Max characters allowed in
 //                                       the address
 //
 //  Return values: none
 //
 ****************************************************************/

void getAddress (char address[], int maxCharacters)
{
    char temp[100];
    char getsAddress[80];
    char ** userAddress = &address;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: getAddress\n**DEBUG** Address: %s\n**DEBUG** Maximum Address Character Length: %d\n", address, maxCharacters);
    }
    
    printf("Please enter your address. When you are finished, enter 0 on a new line: ");
    
    fgets(address, maxCharacters, stdin);
    
    while (strcmp(fgets(getsAddress, maxCharacters - strlen(address), stdin), "0\n") != 0)
    {
        strcat(address, getsAddress);
        
        if (strlen(address) == maxCharacters - 1)
        {
            printf("The address you entered is too long. The maximum length accepted is %d characters, including white space, and a new line counts as a character.\n", maxCharacters - 2);
            printf("Please enter your address. When you are finished, enter 0 on a new line: ");
            
            fgets(temp, 100, stdin);
            fgets(address, maxCharacters, stdin);
        }
    }
    *userAddress = address;
}

/*****************************************************************
 //
 //  Function name: getName
 //
 //  DESCRIPTION:   Gets the user's name from the user
 //
 //  Parameters:    name (char[])       : Array to hold the name
 //                 maxCharacters (int) : Max characters allowed in
 //                                       the address
 //
 //  Return values: none
 //
 ****************************************************************/

void getName (char name[], int maxCharacters)
{
    char temp[100];
    char ** userName = &name;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: getName\n**DEBUG** Name: %s\n**DEBUG** Maximum Name Character Length: %d\n", name, maxCharacters);
    }
    
    printf("Please enter your name: ");
    
    fgets(name, maxCharacters, stdin);
    
    while (strlen(name) == maxCharacters - 1)
    {
        printf("The name you entered is too long. The maximum length accepted is %d characters, including whitespace.\n", maxCharacters - 2);
        printf("Please enter your name: ");
        
        fgets(temp, 100, stdin);
        fgets(name, maxCharacters, stdin);
    }
    *userName = name;
}

/*****************************************************************
 //
 //  Function name: getAccountno
 //
 //  DESCRIPTION:   Gets the user's account number from the user
 //
 //  Parameters:    accountno (int) : The user's account number
 //                                   that they entered
 //
 //  Return values: none
 //
 ****************************************************************/

void getAccountno (int * accountno)
{
    char temp[100];
    int scanReturn;
    int ** number = &accountno;
    
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: getAccountno\n**DEBUG** Account Number Address: %p\n", (void*)accountno);
    }
    
    printf("Please enter your account number: ");
    
    scanReturn = scanf("%d", accountno);
    fgets(temp, 100, stdin);
    
    while (scanReturn != 1)
    {
        printf("Invalid entry. Please enter a positive integer account number: ");
        scanReturn = scanf("%d", accountno);
        fgets(temp, 100, stdin);
    }
    *number = accountno;
}

/*****************************************************************
 //
 //  Function name: main
 //
 //  DESCRIPTION:   Main function to run the program, a bank database
 //                 application
 //
 //  Parameters:    argc (int)    : the number of arguments passed
 //                 argv[] (char*): pointer array which points to each
 //                                 argument passed to the program
 //
 //  Return values:  0 : success
 //
 ****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start;
    struct record * freeTemp;
    int userAccountNo = 0;
    char userName[25] = "";
    char userAddress[80] = "";
    int maxCharName = 25;
    int maxCharAddress = 80;
    int userMenuChoice = 10;
    char temp[100];
    char message[] = "Please select an option below by typing the corresponding number, followed by the enter key:\n 1: Add a record\n 2: Modify an existing record\n 3: Print a record\n 4: Print all records in the database\n 5: Delete an existing record\n 0: Quit the application\n\n";
    
    start = NULL;
    debugmode = 0;
    
    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
    }
    if (argc > 2)
    {
        printf("project1: Too many file operands.\nOnly file operand accepted is debug.\n");
        exit(1);
    }
    if (argc == 2 && strcmp(argv[1], "debug") != 0)
    {
        printf("project1: Incorrect file operand.\nOnly file operand accepted is debug.\n");
        exit(1);
    }
    if (debugmode == 1)
    {
        printf("**DEBUG** Function: main\n**DEBUG** argc: %d\n**DEBUG** argv[0]: %s\n**DEBUG** argv[1]: %s\n", argc, argv[0], argv[1]);
    }
    
    printf("\nWelcome to the ICS212 Bank Database Application. Please look closely because our menu options may have changed.\n\n");
    
    readfile(&start, "records.txt");
    
    while (userMenuChoice != 0)
    {
        printf("%s\n", message);
        scanf("%d", &userMenuChoice);
        fgets(temp, 100, stdin);
        
        switch (userMenuChoice)
        {
            case 1:
                getAccountno(&userAccountNo);
                while (userAccountNo < 1)
                {
                    printf("Invalid entry. Please enter a positive integer account number.\n");
                    getAccountno(&userAccountNo);
                }
                getName(userName, maxCharName);
                getAddress(userAddress, maxCharAddress);
                if (addRecord(&start, userAccountNo, userName, userAddress) == 0)
                {
                    printf("Successfully added your record!\n\n");
                }
                else
                {
                    printf("The account number you entered already exists. Please use a different account number and try again.\n\n");
                }
                break;
            case 2:
                getAccountno(&userAccountNo);
                while (userAccountNo < 1)
                {
                    printf("Invalid entry. Please enter a positive integer account number: \n");
                    getAccountno(&userAccountNo);
                }
                getAddress(userAddress, maxCharAddress);
                if (modifyRecord(start, userAccountNo, userAddress) == 0)
                {
                    printf("Successfully updated your record!\n");
                    printf("Your updated record is as follows:\n");
                    printRecord(start, userAccountNo);
                }
                else
                {
                    printf("There was an error trying to find your record to modify. Please make sure the account number you entered is correct and try again.\n");
                }
                printf("\n");
                break;
            case 3:
                getAccountno(&userAccountNo);
                while (userAccountNo < 1)
                {
                    printf("Invalid entry. Please enter a positive integer account number: \n");
                    getAccountno(&userAccountNo);
                }
                if (printRecord(start, userAccountNo) == 0)
                {
                    printf("\nSuccessfully printed your record!\n");
                }
                else
                {
                    printf("\nThere was an error trying to find your record to print. Please make sure the account number you entered is correct and try again.\n");
                }
                printf("\n");
                break;
            case 4:
                if (start == NULL)
                {
                    printf("\nThere are no records entered in the database.\n");
                }
                else
                {
                    printf("\nThe records in the database are as follows:\n");
                }
                printAllRecords(start);
                printf("\n");
                break;
            case 5:
                getAccountno(&userAccountNo);
                while (userAccountNo < 1)
                {
                    printf("Invalid entry. Please enter a positive integer account number: \n");
                    getAccountno(&userAccountNo);
                }
                if (deleteRecord(&start, userAccountNo) == 0)
                {
                    printf("Successfully deleted your record!\n\n");
                }
                else
                {
                    printf("There was an error trying to find your record to delete. Please make sure the account number you entered is correct and try again.\n\n");
                }
                break;
            case 0:
                writefile(start, "records.txt");
                while (start != NULL)
                {
                    freeTemp = (*start).next;
                    free(start);
                    start = freeTemp;
                }
                printf("Thank you for using the ICS212 Bank Database Application! Have a great day!\n");
                break;
            default:
                printf("You entered an invalid menu option.\n");
                break;
        }
    }
    return 0;
}

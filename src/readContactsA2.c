/* 

© 2024 Louis Nguyen. All rights reserved. 

*/

#include "../include/nguyenLouisHeader.h"

int readContacts(char * fileName)
{
    FILE *fptr;
    int empID = 0;
    char *firstName = NULL;
    char *lastName = NULL;
    char *email = NULL;
    struct contact contact;
    long pos = 0, endPosn = 0;
    long len = 0;

    fptr = fopen(fileName, "rb"); // open the file in read binary mode
                                  // starts at the beginning of the file

    // if file cannot be opened
    if (fptr == NULL)
    {
        return -1;
    }

    else
    {
        // allocating memory for the 3 strings
        firstName = malloc(sizeof(char) * 100);
        lastName = malloc(sizeof(char) * 100);
        email = malloc(sizeof(char) * 100);

        // find the end position of the file (this will determine the condition when we print all contacts)
        fseek(fptr, 0, SEEK_END);
        endPosn = ftell(fptr);

        // seeking back to the beginning of the file to start reading in order
        fseek(fptr, 0, SEEK_SET);

        while (endPosn != pos) // will run until the pos is equal to the end position (this indicates there are no more contacts)
        {
            // read the positions of the first contact before entering the loop
            fread(&contact, sizeof(contact), 1, fptr);

            // read employee ID
            fseek(fptr, contact.empIdPosn, SEEK_SET);
            fread(&empID, sizeof(int), 1, fptr);

            // read first name
            fseek(fptr, contact.firstNamePosn, SEEK_SET);
            len = contact.lastNamePosn - contact.firstNamePosn; // find length of string
            fread(firstName, sizeof(char), len, fptr);
   
            // read last name
            fseek(fptr, contact.lastNamePosn, SEEK_SET);
            len = contact.emailPosn - contact.lastNamePosn; // find length of string
            fread(lastName, sizeof(char), len, fptr);

            // read email
            fseek(fptr, contact.emailPosn, SEEK_SET);
            len = contact.next - contact.emailPosn; // find length of string
            fread(email, sizeof(char), len, fptr);

            // printing out record
            printf("************************************************************\n");

            printf("Employee id: %d\n", empID);
            printf("First Name: %s\n", firstName);
            printf("Last Name: %s\n", lastName);
            printf("Email: %s\n", email);

            printf("************************************************************\n");
            printf("\n");

            // keeping track of the pointer position to see if it's the end of the file
            pos = ftell(fptr);

            // fseek to next contact
            fseek(fptr, contact.next, SEEK_SET);
        }
    }

    // freeing memory
    free(firstName);
    free(lastName);
    free(email);

    fclose(fptr);

    return 1;
}
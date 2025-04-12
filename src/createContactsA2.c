/* 

© 2024 Louis Nguyen. All rights reserved. 

*/

#include "../include/nguyenLouisHeader.h"
#include <ctype.h> // this library is included to use the tolower() function

void createContacts(char * fileName)
{
    FILE *fptr;
    char *option = NULL;
    int len = 0;
    int i = 0;
    int loop = 0;
    int empID = 0, existingID = 0;
    char *firstName = NULL;
    char *lastName = NULL;
    char *email = NULL;
    struct contact contact;
    long pos = 0;
    int count = 0;

    fptr = fopen(fileName, "a+"); // open file in append mode to read and write to file
                                  // writes to the end of the file

    // allocating memory for user input
    option = malloc(sizeof(char) * 100);

    // allocating memory for the 3 strings
    firstName = malloc(sizeof(char) * 100);
    lastName = malloc(sizeof(char) * 100);
    email = malloc(sizeof(char) * 100);
    
    // set loop to true (1) to keep running until the user enters "No"
    loop = 1;
    do
    {
        printf("Do you wish to enter a new contact (Yes or No)?:");
        scanf("%s", option);
        getchar(); // removes the newline after the user input of 'yes' or 'no'

        if (strcmp("No", option) == 0)
        {
            // set to false if the user inputs exactly "No" to exit the loop
            loop = 0;
        }

        len = strlen(option);
    
        // the tolower() function converts all uppercase letters to lowercase so any variation of "yes" will work
        for (i = 0; i < len; i++)
        {
            option[i] = tolower(option[i]);
        }

        if (strcmp("yes", option) == 0)
        {
            fseek(fptr, 0, SEEK_END); // go to the end of the file
            pos = ftell(fptr); // get the position of the beginning of the record and save it (where the struct will go)

            // check for duplicate id's first
            do
            {
                // first check if id inputted already exists to the file (preventing duplicate contact id's)
                fseek(fptr, 0, SEEK_SET); // going to the beginning of the file to read duplicate id's
                count = 0;

                // employee id
                printf("Employee Id: ");
                scanf("%d", &empID);
                getchar(); // remove the newline character

                // the loop runs until there are no more contacts to read (fread() = 1 if a contact is read)
                while (fread(&contact, sizeof(contact), 1, fptr) == 1)
                {
                    // read existing employee ID
                    fseek(fptr, contact.empIdPosn, SEEK_SET);
                    fread(&existingID, sizeof(int), 1, fptr);

                    if (existingID == empID)
                    {
                        // duplicate counter
                        count++;
                    }

                    else
                    {
                        // check the next contact
                        fseek(fptr, contact.next, SEEK_SET);
                    }
                }

            } while (!(empID >= 1 && empID <= 9999) || count > 0);

            contact.empIdPosn = pos + sizeof(contact); // current pos + sizeof the struct to reserve bytes when we write the struct later
            
            fseek(fptr, 0, SEEK_END); // going back to the end of the file to keep creating the contact

            // first name
            printf("First Name: ");
            fgets(firstName, 100, stdin);
            
            // checking if the user decides to add their first name or not
            if (firstName[0] == '\n' && strlen(firstName) == 1) 
            {
                strcpy(firstName, " "); // if not then make the string a space
            }
            
            else
            {
                firstName[strlen(firstName) - 1] = '\0'; // if they do then just remove the newline
            }
            
            contact.firstNamePosn = contact.empIdPosn + sizeof(int); // getting position of the first name

            // last name
            printf("Last Name: ");
            fgets(lastName, 100, stdin);
            
            // checking if the user decides to add their last name or not
            if (lastName[0] == '\n' && strlen(lastName) == 1)
            {
                strcpy(lastName, " ");
            }
            
            else
            {
                lastName[strlen(lastName) - 1] = '\0';
            }

            contact.lastNamePosn = contact.firstNamePosn + (sizeof(char) * (strlen(firstName) + 1)); // getting the position of the last name
            
            // email
            printf("Email: ");
            fgets(email, 100, stdin);
            
            // checking if the user decides to add their email or not
            if (email[0] == '\n' && strlen(email) == 1)
            {
                strcpy(email, " ");
            }

            else
            {
                email[strlen(email) - 1] = '\0';
            }

            contact.emailPosn = contact.lastNamePosn + (sizeof(char) * (strlen(lastName) + 1)); // getting position of email
            contact.next = contact.emailPosn + (sizeof(char) * (strlen(email) + 1)); // getting position of next

            // fseek back to the beginning of the record to write the struct with all the positions of the contact
            fseek(fptr, pos, SEEK_SET);
            
            // write the entire struct and contact records at the beginning of the record (position is stored in 'pos' variable)
            fwrite(&contact, sizeof(contact), 1, fptr);
            fwrite(&empID, sizeof(int), 1, fptr);
            fwrite(firstName, sizeof(char), strlen(firstName) + 1, fptr);
            fwrite(lastName, sizeof(char), strlen(lastName) + 1, fptr);
            fwrite(email, sizeof(char), strlen(email) + 1, fptr);

            printf("\n");
        }

    } while(loop);

    // freeing memory
    free(firstName);
    free(lastName);
    free(email);
    free(option);

    fclose(fptr);
}
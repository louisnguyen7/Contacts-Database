/* 

© 2024 Louis Nguyen. All rights reserved. 

*/

#include "../include/nguyenLouisHeader.h"

int main(int argc, char *argv[])
{
    int choice = 0;
    int keyId = 0;
    int found = 0;

    // call function
    createContacts(argv[1]);

    do
    {
        do
        {
            printf("Enter a choice :\n");
            printf("1 to print, 2 to search, 3 to create more, -1 to exit : ");
            scanf("%d", &choice);
            getchar();

        } while (!(choice >= 1 && choice <= 3) && choice != -1);
    
        // printing
        if (choice == 1)
        {
            // calling function and passing the file name as a parameter
            printf("Printing Employee records saved on file:\n");
            printf("\n");

            // call function
            readContacts(argv[1]);
        }
        
        // searching
        else if (choice == 2)
        {
            do
            {
                printf("Enter the id to search: ");
                scanf("%d", &keyId);
                getchar();

            } while (!(keyId >= 1 && keyId <= 9999));

            // call function
            found = searchContacts(argv[1], keyId);
    
            // if there is no user with that id, then the function will return 0 and print this
            if (found == 0)
            {
                printf("No match found!\n");
                printf("\n");
            }
        }
        
        // creating 
        else if (choice == 3)
        {
            // call function
            createContacts(argv[1]);
        }

    } while (choice != -1);
    
    // exiting program
    if (choice == -1)
    {
        printf("\nExiting....\n\n");
    }

    return 0;
}
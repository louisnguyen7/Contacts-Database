/* 

© 2024 Louis Nguyen. All rights reserved. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
   long empIdPosn;
   long firstNamePosn;
   long lastNamePosn;
   long emailPosn;
   long next;
};

void createContacts (char * fileName);

int readContacts (char * fileName);

int searchContacts (char * fileName, int keyId);

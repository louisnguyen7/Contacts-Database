myContacts1321410: contactsA2.o createContactsA2.o readContactsA2.o searchContactsA2.o
	gcc contactsA2.o createContactsA2.o readContactsA2.o searchContactsA2.o -o bin/myContacts1321410
contactsA2.o: src/contactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/contactsA2.c
createContactsA2.o: src/createContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/createContactsA2.c
readContactsA2.o: src/readContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/readContactsA2.c
searchContactsA2.o: src/searchContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/searchContactsA2.c
clean:
	rm *.o bin/myContacts1321410
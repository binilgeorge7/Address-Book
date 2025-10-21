#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(struct AddressBook *addressBook); //function declaration to save to csv file
void loadContactsFromFile(struct AddressBook *addressBook); //function declaration load from csv file

#endif

#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact  // initializing contact structure
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook  // initializing address book structure
{
    struct Contact contacts[100];
    int contactCount;
};

//  declaration of all functions used
void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *AddressBook);
int validphone(char* phone, struct AddressBook *addressBook );
int validemail(char* email , struct AddressBook *addressBook);
void searchbyname(struct AddressBook *addressBook);
int searchbyphone(struct AddressBook *addressBook);
int searchbyemail(struct AddressBook *addressBook);
int byname(struct AddressBook *addressBook);
void edit_field(struct AddressBook* addressBook, int index);
void delete_contact(struct AddressBook* addressBook, int index);
void display_contact(struct AddressBook* addressBook, int index);


#endif

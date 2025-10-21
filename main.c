/*
Name : Binil George
Date : 10-10-2025
Description : Address Book Project - 
			Capable of
			1. Creating new contact 
			2. Search contacts by name or phone number or email
			3. Input validation for email and phone number
			4. Edit existing contacts
			5. Delete contacts
			6. List all saved contacts 
			7. Data storage using files
*/
#include "contact.h"

int main() 
{
    int choice;  // declaring choice variable for switching

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
		//Address book main menu
		printf("\nAddress Book Menu:\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) 
		{
			case 1:
			createContact(&addressBook);  //function call for create contact
			break;
			case 2:
			searchContact(&addressBook);  //function call for search contact
			break;
			case 3:
			editContact(&addressBook);   //function call for edit contact
			break;
			case 4:
			deleteContact(&addressBook); //function call for delete contact
			break;
			case 5:
			listContacts(&addressBook);  //function call for listing contacts 
			break;
			case 6:
			printf("Saving and Exiting...\n");
			saveContactsToFile(&addressBook); //function call for saving contacts to csv file
			break;
			default:
			printf("Invalid choice. Please try again.\n");
		}
    } while (choice != 6);  //loop continues till choice != 6

    return 0;
}

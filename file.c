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

#include <stdio.h>
#include "file.h"

void saveContactsToFile(struct AddressBook *addressBook) {
    FILE* fp = NULL; //intialize file pointer with null
    fp = fopen("contacts.csv","w");
    if(fp == NULL) //in case if file opening failed
    {
        printf("Error\n");
    }
    else
    {
        fprintf(fp,"#%d\n",addressBook->contactCount); //to print count to csv file
        for(int i = 0; i < addressBook->contactCount; i++)  //for printing data to csv file
        {
            fprintf(fp,"%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        fclose(fp); //close file
    }
}

void loadContactsFromFile(struct AddressBook *addressBook) {
    FILE* fp = NULL; //initialize file pointer with null
    fp = fopen("contacts.csv","r");
    if(fp == NULL) //incase if file opening failed
    {
        printf("Error\n");
    }
    else
    {
        fscanf(fp, "#%d", &addressBook->contactCount); //to load count
        for(int i = 0; i < addressBook->contactCount; i++ ) //to load data
        {
            fscanf(fp," %[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        fclose(fp); //close file
    }  
}

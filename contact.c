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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include<ctype.h>

void listContacts(struct AddressBook *addressBook) 
{
    printf("\t\t\t\t\t\tCONTACTS\n");
    printf("\t\t\t\t\t -----------------------\n");
    /*for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("contact : %d\n", i + 1);  //prints contact No.
        display_contact(addressBook, i);  // function call for printing contact
    }
    printf("---------------------------------------------------------\n");*/
    printf("_________________________________________________________________________________________________________________\n");
    printf("|\t%-5s \t| \t%-15s | \t%-20s\t|\t %-30s |\n", "No", "Name", "Phone", "Email");
    printf("=================================================================================================================\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("|\t%d\t|", i + 1);
        display_contact(addressBook, i);
        printf("\n");
    }
    
}

void initialize(struct AddressBook *addressBook) {
    addressBook->contactCount = 0;  //initially contact count is given as zero but updated while loading from file
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(struct AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(struct AddressBook *addressBook)  //function definition for create contact
{
    char tempname[50], tempphone[20], tempemail[50]; // temparary string variables

    //To enter Name
    printf("Enter Name : ");
    scanf("%[^\n]", tempname);

    //To enter ph number
    do{
        printf("Enter Ph number : ");
        scanf(" %[^\n]", tempphone);
    }while(validphone(tempphone, addressBook));  //function call for validating phone number

    //To enter email
    do
    {
        printf("Enter Email : ");
        scanf(" %[^\n]", tempemail);
    }while(validemail(tempemail, addressBook));  //function call for validating email
    
    // Copies temporary name, ph no, email to address book structure
    strcpy(addressBook -> contacts[addressBook -> contactCount].name, tempname);
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone, tempphone);
    strcpy(addressBook -> contacts[addressBook -> contactCount].email, tempemail);
    addressBook -> contactCount++;
    printf("\n\tContact Created Successfully\n");
}

void searchContact(struct AddressBook *addressBook)  //function definition for search contactr
{
    int choice;
    do{
        //Menu for search contact
        printf("\nSelect from Menu:\n");
        printf("1. Search by Name\n");
        printf("2. Search by phone no\n");
        printf("3. Search by Email\n");
        printf("4. Exit Search Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // collects the newline, and if any character is entered

        switch (choice) 
        {
            case 1:
            searchbyname(addressBook);  //function call for search by name
            break;
            case 2:
            searchbyphone(addressBook);  //function call for search by phone no
            break;
            case 3:
            searchbyemail(addressBook);  //function call for search by email
            break;
            case 4:
            break;
            default:
            printf("Invalid choice.\n");
        }
    }while(choice != 4);  //loop continues till choice != 4
}

void editContact(struct AddressBook *addressBook)  // function for edit contact
{
    /* logic for Editcontact */
    int choice;
    int index = -1;

    do{
        printf("\nSelect from Menu:\n");
        printf("1. Edit by Name\n");
        printf("2. Edit by phone no\n");
        printf("3. Edit by Email\n");
        printf("4. Exit Edit Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // collects the newline, and if any character is entered

        switch (choice) 
        {
            case 1:
            index = byname(addressBook);  //function call for getting index by name, returns the contact index selected by user
            if(index > -1)
            {
                edit_field(addressBook, index);  //function call for editing all fields
            }
            break;
            case 2:
            index = searchbyphone(addressBook);  //function call for search by phone, returns contact index
            if(index > -1)
            {
                edit_field(addressBook, index);  //function call for editing all fields
            }
            break;
            case 3:
            index = searchbyemail(addressBook);  //function call for search by email, returns contact index
            if(index > -1)
            {
                edit_field(addressBook, index);  //function call for editing all fields
            }
            break;
            case 4:
            break;
            default:
            printf("Invalid choice.\n");
        }
    }while(choice != 4); //loop continues till choice != 4 
}

void deleteContact(struct AddressBook *addressBook)  //function definition for delete contact
{
    /* logic for deletecontact */
    int choice;
    do{
        //menu for delete, select how you want to find the contact
        printf("\nSelect from Menu:\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by phone no\n");
        printf("3. Delete by Email\n");
        printf("4. Exit Delete Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // collects the newline, and if any character is entered
        int index;

        switch (choice) 
        {
            case 1:
            index = byname(addressBook); //function call for getting index by name, returns the contact index selected by user
            if(index > -1)
            {
                delete_contact(addressBook, index);  //function call for deleting contact
            }
            break;
            case 2:
            index = searchbyphone(addressBook);  //function call for search by phone, returns contact index
            if(index > -1)
            {
                delete_contact(addressBook, index);   //function call for deleting contact
            }
            break;
            case 3:
            index = searchbyemail(addressBook);  //function call for search by email, returns contact index
            if(index > -1)
            {
                delete_contact(addressBook, index);   //function call for deleting contact
            }
            break;
            case 4:
            break;
            default:
            printf("Invalid choice.\n");
        }
    }while(choice != 4);
}

int validphone(char* phone , struct AddressBook *addressBook) //function definition for phone validation
{
    if(strlen(phone) != 10)  //checks if phone no has 10 characters
    {
        printf("Invalid phone number, should contain 10 digits Enter again\n");
        return 1;
    }
    int i = 0;
    while(phone[i] != '\0')
    {
        if(!(isdigit(phone[i]))) // to check if any character is not a digit
        {
            printf("Invalid phone number, Should contaion only digits, Enter again\n");
            return 1;
        }
        i++;
    }
    // to check if phone number already exist
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].phone, phone))) //compare with each phone number
        {
            printf("Phone number Already Exists, Enter new number\n");
            return 1;
        }
    }
    return 0;
}

int validemail(char* email , struct AddressBook *addressBook)  //function definition for checking email validation
{
    char* ptr1 = strstr(email, "@"); //returns address of '@' to ptr1 if present or return NULL
    char* ptr2 = strstr(email, ".com");//returns address of '.com' to ptr2 if present or return NULL
    if(!((ptr1) && (ptr2) ))  //check if @ or .com is missing
    {
        printf("Invalid email id, Must contain'@' and '.com'\n");
        return 1;
    }
    if(ptr1 == email || (!(isalnum(*(ptr1 - 1)) && isalnum(*(ptr1 + 1))) )) //ensures if a alnum is pressent befor and after @
    {
        printf("Invalid email id, Must contain atleast one character before and after '@'\n");
        return 1;
    }
    int i = 0;
    while(email[i] != '\0')  //checks for upper cases
    {
        if(isupper(email[i]))
        {
            printf("Invalid email id, Should not contain any uppercace characters\n");
            return 1;
        }
        i++;
    }
    if(*(ptr2 + 4) != '\0')  //ensures .com is in last
    {
        printf("Invalid email id, '.com' should be pressent at last\n");
        return 1;
    }
    for(int i = 0; i < addressBook->contactCount; i++)  //checks if email id already exists
    {
        if(!(strcmp(addressBook->contacts[i].email, email)))
        {
            printf("Email id Already Exists, Enter new Email \n");
            return 1;
        }
    }
    return 0;
}

void searchbyname(struct AddressBook *addressBook)  //function definition for searching by name
{
    char name[50];
    printf("Enter the Name :");
    scanf("%[^\n]", name);  //reads name
    int flag = 0;
    int count = 0; //to store index no
    //checks if name is present
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].name, name))) 
        {
            flag =1; //to indicate name available
            count++;
            if(count == 1)
            {
                printf("_________________________________________________________________________________________________________________\n");
                printf("|\t%-5s \t| \t%-15s | \t%-20s\t|\t %-30s |\n", "No", "Name", "Phone", "Email");
                printf("=================================================================================================================\n");
            }
            printf("|\t%d\t|", count); //to print index
            display_contact(addressBook, i);
            printf("\n");
            //display_contact(addressBook, i); // display the contact by passing index
            //printf("---------------------------------------------------------\n");
        }
    }
    if(flag == 0) //if name not pressent
    {
        printf("\n!Entered Name does not exist\n");
    }
}

int searchbyphone(struct AddressBook *addressBook) //function definition for searching by phone
{
    char phone[20];
    printf("Enter the Phone no :");
    scanf("%[^\n]", phone);  //reads phone
    int flag = 0;
    //check if phone no is pressent
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].phone, phone))) //if phone no matches
        {
            flag =1;
            printf("_________________________________________________________________________________________________________________\n");
            printf("|\t%-5s \t| \t%-15s | \t%-20s\t|\t %-30s |\n", "No", "Name", "Phone", "Email");
            printf("=================================================================================================================\n");
            printf("|\t1\t|"); //to print index
            display_contact(addressBook, i);
            printf("\n");
            return i; //since phone number is unique, returns index
        }
    }
    if(flag == 0) // incase phone no not pressent
    {
        printf("\n!Entered Phone no. does not exist\n");
        return -1;
    }
    return -1;
}

int searchbyemail(struct AddressBook *addressBook)
{
    char email[20];
    printf("Enter the Email :");
    scanf("%[^\n]", email);  //reads email as input
    int flag = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].email, email))) //checks if entered email matches
        {
            flag =1;
            printf("_________________________________________________________________________________________________________________\n");
            printf("|\t%-5s \t| \t%-15s | \t%-20s\t|\t %-30s |\n", "No", "Name", "Phone", "Email");
            printf("=================================================================================================================\n");
            printf("|\t1\t|"); //to print index
            display_contact(addressBook, i);
            printf("\n");
            return i;  //since email is unique.           
        }
    }
    if(flag == 0) //if entered email does not matches
    {
        printf("\n!Entered Email. does not exist\n");
        return -1;
    }
    return -1;
}

int byname(struct AddressBook *addressBook)
{
    int index_arr[addressBook->contactCount]; //array to store index of contacts with entered name
    int count = 0; //to store the number of match contacts found
    char name[50];
    printf("Enter the Name :");
    scanf("%[^\n]", name);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].name, name)))  //checks if name matches
        {
            index_arr[count] = i; //index of match array added to index array
            count++; //count is incremented 
            if(count == 1)
            {
                printf("\n\t\tSelect the contact you want \n");
                printf("\n");
                printf("_________________________________________________________________________________________________________________\n");
                printf("|\t%-5s \t| \t%-15s | \t%-20s\t|\t %-30s |\n", "No", "Name", "Phone", "Email");
                printf("=================================================================================================================\n");
            }
            printf("|\t%d\t|", count); //to print index
            display_contact(addressBook, i);
            printf("\n");
            /*printf("contact no : %d\n", count);  //prints the no of match contact
            display_contact(addressBook, i);  //displays contact
            printf("---------------------------------------------------------\n");*/

        }
    }
    if(count == 0) //if no contact is found with the entered name
    {
        printf("\n!Entered Name does not exist\n");
        return -1;
    }
    else //asks to select the contact yu want to edit/delete
    {
        int choice;
        do
        {
            printf("Enter Contact no : ");
            scanf("%d", &choice);  //reads the choice
            if(choice > count || choice < 1)
            {
                printf("Invalid Choice, Enter again\n");
            }
        }while(choice < 1 || choice > count);
        return index_arr[choice - 1];  //returns the index of the chosen contact
    }
}

void display_contact(struct AddressBook* addressBook, int index)  //to display contact
{
           /* printf("---------------------------------------------------------\n");
            printf("\t\tName  :%s\n", addressBook->contacts[index].name);
            printf("\t\tPhone :%s\n", addressBook->contacts[index].phone);
            printf("\t\tEmail :%s\n", addressBook->contacts[index].email);*/
            printf("\t%-15s\t|\t%-20s\t|\t%-30s\t|\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
            printf("_________________________________________________________________________________________________________________\n");
            
}

void edit_field(struct AddressBook* addressBook, int index)
{
    int choice;
    do
    {
        //edit field Menu
        printf("\nSelect Field you want to Edit:\n");
        printf("1. Edit Name\n");
        printf("2. Edit phone no\n");
        printf("3. Edit Email\n");
        printf("4. Exit Edit Field Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
            char tempname[50];
            printf("Enter new Name :");
            scanf(" %[^\n]", tempname);
            strcpy(addressBook->contacts[index].name, tempname);  //copies temporary name to structure
            printf("Name Edited.\n");
            printf("_________________________________________________________________________________________________________________\n");
            printf("|\t%-5s \t| \t%-15s | \t%-20s\t |\t %-30s |\n", "No", "Name", "Phone", "Email");
            printf("=================================================================================================================\n");
            printf("|\t1\t|"); //to print index
            display_contact(addressBook, index);
            printf("\n");
            break;

            case 2:
            char tempphone[20];
            do{
            printf("Enter Ph number : ");
            scanf(" %[^\n]", tempphone);
            }while(validphone(tempphone, addressBook));  //loop continues till phone number is valid

            strcpy(addressBook->contacts[index].phone, tempphone);  //copies phone number to structure
            printf("Phone no Edited.\n");
            printf("_________________________________________________________________________________________________________________\n");
            printf("|\t%-5s \t| \t%-15s | \t%-20s\t |\t %-30s |\n", "No", "Name", "Phone", "Email");
            printf("=================================================================================================================\n");
            printf("|\t1\t|"); //to print index
            display_contact(addressBook, index);
            printf("\n");
            break;

            case 3:
            char tempemail[50];
            do
            {
            printf("Enter Email : ");
            scanf(" %[^\n]", tempemail);
            }while(validemail(tempemail, addressBook)); //loop continues till email is valid

            strcpy(addressBook->contacts[index].email, tempemail); //copies email to structure
            printf("Email Edited.\n");
            printf("_________________________________________________________________________________________________________________\n");
            printf("|\t%-5s \t| \t%-15s | \t%-20s\t |\t %-30s |\n", "No", "Name", "Phone", "Email");
            printf("=================================================================================================================\n");
            printf("|\t1\t|"); //to print index
            display_contact(addressBook, index);
            printf("\n");
            break;

            case 4:
            printf("Exiting...\n");
            break;

            default:
            printf("Invalid choice.\n");
        }
    }while(choice != 4); //loop continues till choice != 4
}
void delete_contact(struct AddressBook* addressBook, int index) //function definition for deleting
{
    int choice;
    printf("Do you want to delete,(Yes - 1/No - 0)\n"); //Final Confirmation
    printf("Your choice : ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        while(index < addressBook->contactCount - 1)
        {
            addressBook->contacts[index] = addressBook->contacts[index + 1]; //left shift structures by 1 position in the array from index
            index++;
        }
        addressBook->contactCount--;  //decrements contact count
        printf("Contact Deleted\n");
    }
    else
    {
        printf("Contact Not Deleted\n");
        return;
    }
}

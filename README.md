# Address-Book

Address Book Project
Overview

This Address Book Project is a C-based console application designed to manage contact information efficiently. It allows users to create, search, edit, delete, and list contacts easily through a simple menu-driven interface.

Features :

Create new contacts
Search contacts by name, phone number, or email
Edit existing contact details
Delete contacts
List all saved contacts
Input validation for phone numbers and email IDs
File-based data storage for persistence across sessions

Concepts Used :
Structured programming
File handling in C
String manipulation
Modular programming (multiple header and source files)
Input validation and error handling

File Structure :
📁 AddressBookProject
│
├── main.c
├── contact.c
├── file.c
├── contact.h
├── file.h
└── README.md

How to Run :

Clone the repository:

git clone https://github.com/<your-username>/AddressBookProject.git
cd AddressBookProject


Compile the program:
gcc main.c contact.c file.c -o addressbook


Run the executable:
./addressbook

Example Operations:

Add a new contact with name, phone, and email.
Search contacts by name or phone.
Edit or delete any contact.
List all stored contacts.

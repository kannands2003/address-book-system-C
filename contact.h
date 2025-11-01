#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void saveAndExit(AddressBook *addressBook);
int validate_phone(char *phone, AddressBook *addressBook);
int  validate_email(char *email, AddressBook *addressBook);
int* search_name(AddressBook *addressBook, int arr[]);
int search_phone(AddressBook *addressBook);
int search_email(AddressBook *addressBook);
void edit_search_name(AddressBook *addressBook);
void edit_search_phone(AddressBook *addressBook);
void edit_search_email(AddressBook *addressBook);
void delete_search_name(AddressBook *addressBook);
void delete_search_phone(AddressBook *addressBook);
void delete_search_email(AddressBook *addressBook);


void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif

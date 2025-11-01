#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria
    printf("..........................................................................................\n");
    printf("%-10s%-25s%-20s%-30s\n","sl.no","name","phone number","email.id");
    printf("...........................................................................................\n");
    for(int i = 0; i < addressBook->contactCount ; i++)
    {
	    printf("%-10d", i + 1);
	    printf("%-25s", addressBook->contacts[i].name );
	    printf("%-20s", addressBook->contacts[i].phone );
	    printf("%-30s\n", addressBook->contacts[i].email );
                            
    }
    printf("...........................................................................................\n");

}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program

    
}

                
void createContact(AddressBook *addressBook)
{
        /* Define the logic to create a Contacts */
        if(addressBook->contactCount < MAX_CONTACTS)
        {
		printf("enter the name : ");
                scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name); // scanning the name
                
                int res1;

                do
                {
                        char phone[20];
			printf("enter the phone number  : ");
                        scanf(" %[^\n]", phone);
                        res1 = validate_phone(phone, addressBook); // validate mobile number

                }
                while(res1 == 0);
                
                int res2;

                do
                {
                        char email[50];
			printf("enter the email.id : ");
                        scanf(" %[^\n]", email);
                        res2 = validate_email(email, addressBook); // validate email.id
                }
                while(res2 == 0);
                addressBook->contactCount++;
        }
        else
                printf("space reached\n");


}


void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choice;
    do{
        printf("1. search by name\n2. search by phone number\n3. search by email id\n4. exit\n");
        printf("enter the choice : ");
        scanf("%d", &choice);
        int arr[100];
  
        switch(choice)
        {
                case 1: search_name(addressBook, arr); //search by name
                        break;
                case 2: search_phone(addressBook); // search by phone number
                        break;
                case 3: search_email(addressBook); // search by email.id
                        break;
                default : printf("give valid input\n");
        }
    }while(choice != 4);
}



void editContact(AddressBook *addressBook)
{
        // Define the logic for Editcontact 
        int choice;
        do{
                printf("enter the choice\n");
                printf("1. search by name\n2. search by phone number\n3. search by email id\n4. exit\n");
	        printf("enter the choice : ");
	        scanf("%d", &choice);
                switch(choice)
	        {
                        case 1: edit_search_name(addressBook); //search by name for edit
	                        break;
                        case 2: edit_search_phone(addressBook); //search by phone for edit
                                break;
                        case 3: edit_search_email(addressBook); //search by email for edit
                                break;
                        default : printf("give valid input\n"); // exit
	        }
        }while(choice != 4);

}


void deleteContact(AddressBook *addressBook)
{
        /* Define the logic for deletecontact */
	int choice;
        do{
                printf("1. search by name\n2. search by phone number\n3. search by email id\n4. exit\n");
                printf("enter the choice : ");
         	scanf("%d", &choice);

	        switch(choice)
                {
                        case 1: delete_search_name(addressBook); //search by name for delete
                                break;
                        case 2: delete_search_phone(addressBook); //search by phone for delete
                                break;
                        case 3: delete_search_email(addressBook); //search by email for delete
                                break;
                        default : printf("give valid input\n"); // exit
                }
        }while(choice != 4);

}

int validate_phone(char *phone, AddressBook *addressBook)
{
        if(strlen(phone) != 10) // check number is 10 digit or not
        {
                printf("invalid number\n");
                return 0;
        }
        else
        {
                int i = 0, flag = 0;
                while(phone[i]) // phone number is digit character or not
                {
                        if('0' <= phone[i] && phone[i] <= '9')
                               i++;
                        else
                        {
                                printf("invalid number\n");
                                flag = 1;
                                break;
                        }
                }
                if(flag == 1)
                        return 0;
                else
                {
                        int set = 0;
                        for(int i = 0; i < addressBook->contactCount ; i++) // check the phone number is used before or not
                        {
                                if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                                {
                                        printf("number is already exist\n");
                                        set = 1;
                                        break;
                                }
                        }
                        if(set == 1)
                                return 0;
                        else // if the above three validation are passed the number is store in main structure
                        {
                                strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
                                return 1;
                        }
                }
        }
}

int  validate_email(char *email, AddressBook *addressBook)
{
    char *pt = strchr(email , '@'); //check @ is present or not and @ is not in the first of the mail
        if(( pt == NULL) || email[0] == '@')
        {
                printf("invalid emailid\n");
                return 0;
        }
        else
        {
                char *ptr = strstr(email, ".com"); //check .com is present or not
                if(ptr == NULL || strcmp(ptr, ".com") != 0) // check .com is in the last of the mail id
                {
                    printf("invalid email\n");
                    return 0;
                }
                else
                {
                        int i = 0, flag = 0;
                        while(email[i])
                        {
                                if(('A' <= email[i] && email[i] <= 'Z') || email[i] == ' ') // check the mail id has no capital and space in between
                                {
                                        printf("invalid emai\n");
                                        flag = 1;
                                        break;
                                }
                                else
                                {
                                        i++;
                                }
                        }
                        if(flag == 1)
                                return 0;
                        else
                        {
                           char *p = strchr(email, '@'); // check after @ present any alphanumeric charcter or not
			   if(!(('a' <=  *(p + 1 )  &&  *(p + 1)  <=  'z') || ('A'  <=  *(p+1)  &&  *(p+1)  <=  'Z') || ('0'  <=  *(p+1)  &&  *(p+1)  <=  '9')) || *(p+1) == '\0')
			   {
                               printf("invalid email.id\n");
                               return 0;
                           }
                           else
                           {
                               int set = 0;
			       for(int i = 0; i < addressBook->contactCount ; i++) // check the emailid is used before or not
			       {
				       if(strcmp(addressBook->contacts[i].email, email) == 0)
				       {
					       printf("invalid email\n");
                                               set = 1;
                                               break;
				       }
                               }
                        
                               if(set == 1)
				       return 0;
                               else // all the validation condition passed store to the main structure
			       {
				       strcpy(addressBook->contacts[addressBook->contactCount].email, email);
                                       return 1;
			       }
                           }
			}
		}
	}
}

int* search_name(AddressBook *addressBook, int arr[])
{
        char data[30];
	printf("enter the name : ");
	scanf(" %[^\n]", data);
	int j = 0, flag = 0;
        
	for(int i = 0; i < addressBook->contactCount ; i++) // search by name
        {
                if(strcmp(addressBook->contacts[i].name, data) == 0) // compare the given name with structure
                {
                        if(flag == 0)
                        {
                                printf("..........................................................................................\n");
                                printf("%-10s%-25s%-20s%-30s\n","sl.no","name","phone number","email.id");
                                printf("...........................................................................................\n");
                        }
                        flag = 1;
        		arr[j] = i;
			j++;
                        printf("%-10d", j);
                        printf("%-25s", addressBook->contacts[i].name );
                        printf("%-20s", addressBook->contacts[i].phone );
	                printf("%-30s\n", addressBook->contacts[i].email );

                        
                }
        }

	
        if(flag == 0)
        {
                printf("name not found\n");
                return NULL;
        }
        else
        {
                arr[j] = -1;
                printf("...........................................................................................\n");
                return arr;

        }
                
}

int search_phone(AddressBook *addressBook)
{
        char data[30];
	printf("enter the phone number : ");
	scanf(" %[^\n]", data);
	int i, flag = 0;
	for(i = 0; i < addressBook->contactCount ; i++) // search by phone number
        {
                if(strcmp(addressBook->contacts[i].phone, data) == 0) // compare the given phone number with structure
                {
                        flag = 1;
			printf("..........................................................................................\n");
                        printf("%-25s%-20s%-30s\n","name","phone number","email.id");
                        printf("...........................................................................................\n");
                        printf("%-25s", addressBook->contacts[i].name );
                        printf("%-20s", addressBook->contacts[i].phone );
	                printf("%-30s\n", addressBook->contacts[i].email );
                        printf("...........................................................................................\n");				
			
                        break;
                }
        }
        if(flag == 0)
        {
                printf("phone number not found\n");
                return -1;
        }
        else
        	return i;
}

int search_email(AddressBook *addressBook)
{
        char data[30];
	printf("enter the email.id : ");
	scanf(" %[^\n]", data);
	int i, flag = 0;
	for(i = 0; i < addressBook->contactCount ; i++) // search by email.id
        {
                if(strcmp(addressBook->contacts[i].email, data) == 0) // compare the given email  with structure
                {
                        flag = 1;
                        printf("..........................................................................................\n");
                        printf("%-25s%-20s%-30s\n","name","phone number","email.id");
                        printf("...........................................................................................\n");
                        printf("%-25s", addressBook->contacts[i].name );
                        printf("%-20s", addressBook->contacts[i].phone );
	                printf("%-30s\n", addressBook->contacts[i].email );
                        printf("...........................................................................................\n");
                
                        break;
                }
        }
        if(flag == 0)
        {
                printf("email id not found\n");
                return -1;
        }
        else
                return i;
}

void edit_search_name(AddressBook *addressBook)
{
        int arr[10];
        int *res = search_name(addressBook, arr); // calling search name

        if(res == NULL)
                return;

	int num;

	int count = 0;
	while(res[count] != -1)
	{
		count++;
	}


	if(count == 1)
		num = 1;
	else
	{
		printf("which is been changed : ");
		scanf("%d", &num);
		if(num > count)
			return;
	}
        int s; 

        do{
                printf("enter which was been changed\n");
                printf("1. name\n2. phone number\n3. email\n4. exit\n");
                
                printf("enter the choice : ");
                scanf("%d", &s);

                switch(s)
                {
                        case 1: char name[30];
	                        printf("enter the new name : ");
	                        scanf(" %[^\n]", name);
	                        strcpy(addressBook->contacts[res[num - 1]].name, name);
                                break;
                        case 2: int res1 = 0;
	                        char phone[20];
	                        do
	                        {
	                   	       printf("enter the new phone number  : ");
		                       scanf(" %[^\n]", phone);
		                       res1 = validate_phone(phone, addressBook); // validate mobile number                        
	                        }        
	                        while(res1 == 0);
	                        strcpy(addressBook->contacts[res[num - 1]].phone, phone);
                                break;
                        case 3: int res2 = 0;
	                        char email[20];
	                        do
	                        {
		                        printf("enter the new mail id  : ");
	                            	scanf(" %[^\n]", email);
		                        res2 = validate_email(email, addressBook); // validate  email
                                }
 	                        while(res2 == 0);
	                        strcpy(addressBook->contacts[res[num - 1]].email, email);
                                break;
                        default : printf("enter valid \n"); // exit
                }
        }while (s != 4);


	printf("succesfullly updated !!\n");

        printf("..........................................................................................\n");
        printf("%-25s%-20s%-30s\n","name","phone number","email.id");
        printf("...........................................................................................\n");
        
        printf("%-25s", addressBook->contacts[res[num - 1]].name );
        printf("%-20s", addressBook->contacts[res[num - 1]].phone );
	printf("%-30s\n", addressBook->contacts[res[num - 1]].email );
                            
        
        printf("...........................................................................................\n");

}

void edit_search_phone(AddressBook *addressBook)
{
        
        int k = search_phone(addressBook); // calling search phone
        if(k == -1)
             return;
        int s ;

        do{
                printf("enter which was been changed\n");
                printf("1. name\n2. phone number\n3. email\n4. exit\n");
                
                printf("enter the choice : ");
                scanf("%d", &s);

                switch(s)
                {
                        case 1: char name[30];
	                        printf("enter the new name : ");
	                        scanf(" %[^\n]", name);
	                        strcpy(addressBook->contacts[k].name, name);
                                break;
                        case 2: int res1 = 0;
	                        char phone[20];
	                        do
	                        {
	                   	       printf("enter the new phone number  : ");
		                       scanf(" %[^\n]", phone);
		                       res1 = validate_phone(phone, addressBook); // validate mobile number                        
	                        }        
	                        while(res1 == 0);
	                        strcpy(addressBook->contacts[k].phone, phone);
                                break;
                        case 3: int res2 = 0;
	                        char email[20];
	                        do
	                        {
		                        printf("enter the new mail id  : ");
	                            	scanf(" %[^\n]", email);
		                        res2 = validate_email(email, addressBook); // validate email
                                }
 	                        while(res2 == 0);
	                        strcpy(addressBook->contacts[k].email, email);
                                break;
                        default : printf("enter valid \n"); // exit
                }
        }while (s != 4);


	printf("succesfullly updated !!\n");

        printf("..........................................................................................\n");
        printf("%-25s%-20s%-30s\n","name","phone number","email.id");
        printf("...........................................................................................\n");
        
        printf("%-25s", addressBook->contacts[k].name );
        printf("%-20s", addressBook->contacts[k].phone );
	printf("%-30s\n", addressBook->contacts[k].email );
                            
        
        printf("...........................................................................................\n");

}

void edit_search_email(AddressBook *addressBook)
{
       
        int l = search_email(addressBook);// calling search eamil
        if(l == -1)
             return;
        int s;

        do{
                printf("enter which was been changed\n");
                printf("1. name\n2. phone number\n3. email\n4. exit\n");
                
                printf("enter the choice : ");
                scanf("%d", &s);

                switch(s)
                {
                        case 1: char name[30];
	                        printf("enter the new name : ");
	                        scanf(" %[^\n]", name);
	                        strcpy(addressBook->contacts[l].name, name);
                                break;
                        case 2: int res1 = 0;
	                        char phone[20];
	                        do
	                        {
	                   	       printf("enter the new phone number  : ");
		                       scanf(" %[^\n]", phone);
		                       res1 = validate_phone(phone, addressBook); // validate mobile number                        
	                        }        
	                        while(res1 == 0);
	                        strcpy(addressBook->contacts[l].phone, phone);
                                break;
                        case 3: int res2 = 0;
	                        char email[20];
	                        do
	                        {
		                        printf("enter the new mail id  : ");
	                            	scanf(" %[^\n]", email);
		                        res2 = validate_email(email, addressBook); // validate email
                                }
 	                        while(res2 == 0);
	                        strcpy(addressBook->contacts[l].email, email);
                                break;
                        default : printf("enter valid \n"); // exit
                }
        }while (s != 4);


	printf("succesfullly updated !!\n");

        printf("..........................................................................................\n");
        printf("%-25s%-20s%-30s\n","name","phone number","email.id");
        printf("...........................................................................................\n");
        
        printf("%-25s", addressBook->contacts[l].name );
        printf("%-20s\t", addressBook->contacts[l].phone );
	printf("%-30s\n", addressBook->contacts[l].email );
                            
        
        printf("...........................................................................................\n");

}

void delete_search_name(AddressBook *addressBook)
{
        
        int arr[10];

        int *res = search_name(addressBook, arr); // calling search name

        if(res == NULL)
            return;

        int num;

	int count = 0;
	while(res[count] != -1)
	{
		count++;
	}
	if(count == 1)
		num = 1;
	else
	{
		printf("which is been deleted : ");
		scanf("%d", &num);
		if(num > count)
			return;
	}

        printf("do you want to delete it (1(yes)/0(no)) : ");
        int n;
        scanf("%d", &n);
        if(n)
        {
                for(int i = res[num - 1]; i < addressBook->contactCount - 1 ; i++)
                {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("succesfullly deleted !!\n");
        }
        else
                printf("deletion cancelled\n");
}
void delete_search_phone(AddressBook *addressBook)
{       
        int k = search_phone(addressBook); // calling search phone

        if(k == -1)
            return;


        printf("do you want to delete it (1(yes)/0(no)) : ");
        int n;
        scanf("%d", &n);
        if(n)
        {
                for(int i = k; i < addressBook->contactCount - 1 ; i++)
                {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("succesfullly deleted !!\n");
        }
        else
                printf("deletion cancelled\n");
}

void delete_search_email(AddressBook *addressBook)
{
        int k = search_email(addressBook); // calling search email

        if(k == -1)
             return;

        printf("do you want to delete it (1(yes)/0(no)) : ");
        int n;
        scanf("%d", &n);
        if(n)
        {
                for(int i = k; i < addressBook->contactCount - 1 ; i++)
                {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("succesfullly deleted !!\n");
        }
        else
                printf("deletion cancelled\n");
}





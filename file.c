#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp  = fopen("contacts.csv", "w");

    if(fp == NULL)
    {
        printf("file not exist\n"); // check the file is exist or not
        return;
    }


    //store the data to the file
    for(int i = 0; i < addressBook->contactCount ; i++)
    {
	    fprintf(fp,"%s,", addressBook->contacts[i].name );    
	    fprintf(fp,"%s,", addressBook->contacts[i].phone );
	    fprintf(fp,"%s\n", addressBook->contacts[i].email );
                            
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fpp = fopen("contacts.csv", "r");

    if(fpp == NULL)
    {
        printf("file not exist\n"); // check the file is exist or not
        return;
    }

    addressBook->contactCount = 0;

    //collect the date from the file
    while (fscanf(fpp, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) != -1)
    {
        addressBook->contactCount++;
    }

    fclose(fpp);

}

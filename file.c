#include <stdio.h>
#include "file.h"
#include <unistd.h>

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp;
    if((fp=fopen("contact.csv","w")) == NULL)
    {
        fprintf(stderr,"file not found\n");
    }
    for(int i=0;i<addressBook->contactCount;i++)
       fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    fclose(fp);
    for(int i=0;i<100;i++) //saving animation
    {
        printf("\tsaving contacts ---------> %d%%\r",i);
        fflush(stdout);
        usleep(50000);
    }
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;
    if((fp=fopen("contact.csv","r")) == NULL)
    {
        fprintf(stderr,"file not found\n");
    }
    int i=0;
    while(fscanf(fp,"%[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email) == 3)
    {
        addressBook->contactCount++;
        i++;
    }
    fclose(fp);
}

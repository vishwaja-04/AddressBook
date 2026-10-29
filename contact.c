#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#define _GNU_SOURCE
int arr[100],size=0;

int validate_name(char *temp)
{
    int i=0;
    while(temp[i]!='\0')
    {
        if((temp[i]>='a' && temp[i]<='z' || temp[i]>='A' && temp[i]<='Z') || (temp[i]==' '))
        {
            i++;
        }
        else
        { 
            printf("\tEntered name is invalid\n");
            return 1; // Invalid character found
        }
    }
    return 0; // Valid name
}
int validate_mobile(char *temp)
{
    int i=0;
    while(temp[i]!='\0')
    {
        if(temp[i]>='0' && temp[i]<='9')
        {
            i++;
        }
        else
        {
            printf("\tEntered mobile number is invalid\n");
            return 1;
        }

    }
    if(i>10 || i<10)
    {
        printf("\tEntered mobile number is invalid\n");
            return 1;
    }
    else
    return 0;
}
int validate_email(char *temp)
{
    if(strstr(temp,".com") == NULL)
    {
        printf("\tEntered email is invalid\n");
        return 1;
    }
    if(strchr(temp,'@') == NULL)
    {
        printf("\tEntered email is invalid\n");
        return 1;
    }
    return 0;
}
int unique_phone(char *temp,AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(temp,addressBook->contacts[i].phone) ==0)
        {
            printf("\tEnter a unique phone number\n");
            return 1;
        }
        return 0;
    }
}
int unique_email(char *temp,AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(temp,addressBook->contacts[i].email) ==0)
        {
            printf("\tEnter a unique email address\n");
            return 1;
        }
        return 0;
    }
}
void listContacts(AddressBook *addressBook) 
{
     Contact temp;
     printf("Select sort criteria:\n");
     printf("1. Sort by name\n");
     printf("2. Sort by phone\n");
     printf("3. Sort by email\n");
     printf("-----------------------------------------------------------------------\n");
     printf("Index\t| Name\t\t| Phone\t\t| Email\t\t\t|\n");
     printf("-----------------------------------------------------------------------\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
           printf("%d\t| %s\t| %s\t| %s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
           printf("-----------------------------------------------------------------------\n");
        }
     printf("Enter your choice: ");
     int sortChoice;
     scanf("%d", &sortChoice);
     switch(sortChoice)
     {
        case 1:
        printf("SORTING BY NAME-------------------->\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t|Name\t\t|Phone\t\t|Email\t\t\t|\n");
        for(int i=0;i<addressBook->contactCount;i++)
           printf("%d\t|%s\t|%s\t|%s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        break;


        case 2:
        printf("SORTING BY PHONE-------------------->\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t|Name\t\t|Phone\t\t|Email\t\t\t|\n");
        for(int i=0;i<addressBook->contactCount;i++)
           printf("%d\t|%s\t|%s\t|%s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        break;


        case 3:
        printf("SORTING BY EMAIL----------------->\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Index\t|Name\t\t|Phone\t\t|Email\t\t\t|\n");
        for(int i=0;i<addressBook->contactCount;i++)
           printf("%d\t|%s\t|%s\t|%s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        

        break;


        default:
        printf("Invalid sort choice criteria\n");
     }    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}




void createContact(AddressBook *addressBook)
{
    char temp[50];
    printf("\tCREATE CONTACT\n");
    do
    {
    printf("\tenter the name : ");
    scanf(" %[^\n]",temp);
    }while(validate_name(temp));
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp);

    do
    {
    printf("\tenter the phone number : ");
    scanf(" %[^\n]",temp);
    }while((validate_mobile(temp)) | unique_phone(temp,addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].phone,temp);

    do
    {
    printf("\tenter the email : ");
    scanf(" %[^\n]",temp);
    }while(validate_email(temp) | unique_email(temp,addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp);

    printf("\tContact created successfully\n");
    addressBook->contactCount++;
	/* Define the logic to create a Contacts */
    
}

int searchContact(AddressBook *addressBook) 
{
    char temp[20];
    int opt,count=0;
    printf("\tMENU SEARCH CONTACT\n");
    printf("\tPress 1 for search by name\n\tPress 2 for search by phone\n\tPress 3 for search by email\n");
    scanf("%d",&opt);
    switch(opt)
    {
        case 1:
        printf("\tsearching by name :\n");
        printf("\tEnter the name  : ");
        scanf(" %[^\n]",temp);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].name,temp)!=NULL)
            {
                arr[size]=i+1;//storing the indexes of the searched contacts in an array to use in edit contact
                size++;
                count++;
                printf("\t%d\t|%s\t|%s\t|%s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

            }
        }
        if(count==0)
        printf("\tContact not found\n");
        break;
        case 2:
        printf("\tsearching by phone :\n");
        printf("\tEnter the phone : ");
        scanf(" %[^\n]",temp);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].phone,temp)!=NULL)
            {
                arr[size]=i+1;//storing the indexes of the searched contacts in an array to use in edit contact
                size++;
                count++;
                printf("\t%d\t|%s\t|%s\t|%s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        if(count==0)
        printf("\tContact not found\n");
        break;
        case 3:
        printf("\tEnter the email  : ");
        scanf(" %[^\n]",temp);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].email,temp)!=NULL)
            {
                arr[size]=i+1;//storing the indexes of the searched contacts in an array to use in edit contact
                size++;
                count++;
                printf("\t%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

            }
        }
        if(count==0)
        printf("\tContact not found\n");
        break;

        default:
        printf("\tInvalid search criteria\n");
    }   /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
    char temp[20];
    int opt,index,flag=1;
    printf("\tMENU EDIT THE CONTACT :\n");
    if(searchContact(addressBook))
    {
        label:
            printf("\tenter the index you want to edit :");
            scanf("%d",&index);
            for(int i=0;i<size;i++)
            {
                if(index == arr[i]) // checking if the entered index is present in array of searched contacts indexes
                {
                    flag=0;
                }
            }
            if(flag)
            {
                printf("\t you have entered an invalid index\n");
                goto label;
            }
        edit:
            printf("\tpress 1 to edit name\n\tpress 2 to edit phone\n\tpress 3 to edit email\n\t :");
            scanf("%d",&opt);
            switch(opt)
            {
                case 1:
                      do{
                        printf("\tEnter the name to edit : ");
                        scanf(" %[^\n]",temp);
                      }
                      while(validate_name(temp));
                      strcpy(addressBook->contacts[index-1].name,temp);
                      printf("\tname edited successfully\n");
                      break;
                case 2:
                      do{
                        printf("\tEnter the phone to edit : ");
                        scanf(" %[^\n]",temp);
                      }
                      while(validate_mobile(temp) | unique_phone(temp,addressBook));
                      strcpy(addressBook->contacts[index-1].phone,temp);
                      printf("\tphone edited successfully\n");
                      break;
                case 3:
                      do{
                        printf("\tEnter the email to edit : ");
                        scanf(" %[^\n]",temp);
                      }
                      while(validate_email(temp) | unique_email(temp,addressBook));
                      strcpy(addressBook->contacts[index-1].email,temp);
                      printf("\temail edited successfully\n");
                      break;
                default:
                      printf("\tinavlid choice\n");
                      goto edit;
            }
            
    }

    /* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	int index,flag=1;
    char opt;
    printf("\tMENU DELETE CONTACT\n");
    if(searchContact(addressBook))
    {
        start:
            printf("\tenter the index you want to delete :");
            scanf("%d",&index);
            for(int i=0;i<size;i++)
            {
                if(index == arr[i]) // checking if the entered index is present in array of searched contacts indexes
                {
                    flag=0;
                }
            }
            if(flag)
            {
                printf("\t you have entered an invalid index\n");
                goto start;
            }
            label1:
            printf("\tDelete confirmation\n");
            printf("\t%d\t%s\t%s\t%s\n",index+1,addressBook->contacts[index-1].name,addressBook->contacts[index-1].phone,addressBook->contacts[index-1].email);
            printf("Enter 'Y' or 'y' for yes & 'N' or 'n' for no :");
            scanf(" %c",&opt);
            switch(opt)
            {
                case 'Y':
                case 'y':
                {
                    for(int i=index-1;i<addressBook->contactCount;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];

                    }
                    addressBook->contactCount--;
                    printf("\tcontact deleted successfully\n");
                    break;
                }
                case 'N':
                case 'n':
                {
                    return;
                }
        
                default:
                    printf("\tinvalid choice\n");
                    goto label1;
            }

          
    }        
}    /* Define the logic for deletecontact */
   


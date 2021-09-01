#include <stdio.h>
#include <stdlib.h>
#define QUIT 8
#include <string.h>
#include <strings.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

int count=0;
char junk;
int save=1;
int flagDelete=0;
int j=0;

typedef struct{
char change[100];
}recap;

typedef struct{
int day;
int month;
int year;
}date;

typedef struct{
char last_name[30];
char first_name[30];
date DOB;
char Street_address[100];
char phone_number[12];
char email[100];
}contact;

contact list[100];
recap info[100];


void print();
int display_instructions();
void load_phonebook();
int valid_email(char email[]);
int valid_phone(char phone[]);
int valid_date(int day,int month,int year);
void print_contact(contact person);
void search_phonebook();
void add_contact();
void delete_contact();
void modify_contact();
void sort_by_name();
void sort_by_dob();
void save_contacts();
void casesensitive(char word[]);

int display_instructions(void){
    int choice;
    puts("Please choose an option:");
    puts("\t1-\tSEARCH for a contact.");
    puts("\t2-\tADD a new contact.");
    puts("\t3-\tDELETE an existing contact.");
    puts("\t4-\tMODIFY data of an existing contact.");
    puts("\t5-\tPRINT the entire contact list (Sorted by Last Name)");
    puts("\t6-\tPRINT the entire contact list (Sorted by Date of birth)");
    puts("\t7-\tSAVE the changes you have made.");
    puts("\t8-\tQUIT the program.");
    scanf("%d",&choice);

                system("cls");

    return choice;
}
void load_phonebook(void){
   char name[50];
    FILE* fp;
    printf("Please enter the name of the file you wish to open: ");
    gets(name);
    if((fp=fopen(name,"r"))==NULL)
    {
        fprintf(stderr,"ERROR IN LOADING FILE.");
        exit(1);
    }
    else printf("File loaded successfully.\n\n\n");
    while(!feof(fp))
    {
        fscanf(fp,"\n%[^,],",list[count].last_name);
        fscanf(fp,"%[^,],",list[count].first_name);
        fscanf(fp,"%d-%d-%d,",&list[count].DOB.day,&list[count].DOB.month,&list[count].DOB.year);
        fscanf(fp,"%[^,],",list[count].Street_address);
        fscanf(fp,"%[^,],",list[count].phone_number);
        fscanf(fp,"%[^\n]",list[count].email);
        count++;
    }
    fclose(fp);
}
int main(){
    puts("\t\t\tWELCOME TO YOUR PHONE BOOK");
    puts("\t\tYour best way to deal with your contacts!");
    int choice=0;
    int choice_2=0;
    int flag=0;
    int times=0,generic;
    load_phonebook();
    while(flag==0)
    {
        if(times>0)
        {
           printf("Press any key to get back to menu.\n");
           getch();
           system("cls");
        }
        choice=display_instructions();
        switch (choice)
        {
            case 1: {search_phonebook(); break;}
            case 2: {add_contact();break;}
            case 3: {delete_contact();break;}
            case 4: {modify_contact(); break;}
            case 5: {sort_by_name();break;}
            case 6: {sort_by_dob();break;}
            case 7: {save_contacts();break;}
            case QUIT:
            {

               if(save==1)
               {
                    puts("Here is a recap of what you have done:");
                   for(j=0;j<times;j++)
                   printf("\t%d\t%s\n",j+1,info[j].change);

                   printf("\n\tYou are now quitting your phonebook.\n\tWe really hope it was useful!\n\tGoodbye!\n");
                   exit(0);
               }
               else if(save==0)
               {
                    puts("Here is a recap of what you have done:");
                   for(j=0;j<times;j++)
                   printf("\t%d\t%s\n",j+1,info[j].change);

                    puts("\nYour last change hasn't been saved, are you sure you want to exit? (Y/N)");
                    char letter[2];
                    while(1)
                    {
                        puts("If you want to exit anyway input 'Y', if not, input 'N' to get back to menu.");
                        scanf("%s",letter);
                        if((letter[0]=='Y')|| (letter[0]=='y')) exit(0);
                        else  if((letter[0]=='N')|| (letter[0]=='n'))
                        {
                            times=times-1;
                          break;
                        }
                        else puts("Please enter a valid input.");
                    }

               }
               break;
            }
                    default:
            {
            puts("Please choose a number between 1-8. Try again.");
            times=-1;
            break;
            }

        }
                times++;

    }


    return 0;
}
void modify_contact(){
    puts("\tNote: Searching is not case sensitive. Inputs \"Mohamed\" and \"mohamed\" are considered the same.");
    int i,x;
    char temp[30];
    while (1)
    {
        puts("Enter last name of the contact you would like to modify,\tor press zero to exit:");
        scanf("%s", temp);
        if(strcmp(temp,"0") == 0)
        {
            break;
        }
        puts("\tSearching...");
        int arr[count];
        int flag = 0;
        for(i = 0; i < count; i++)
        {
            if(strcasecmp(list[i].last_name, temp) == 0)
            {
                printf("\tContact Found #%d:", flag+1);
                arr[flag] = i;
                print_contact(list[i]);
                flag++;
            }
        }
        if(flag == 0)
        {
            puts("No contacts found. Try again!");

        }
        else
        {
            int number;
            puts("Enter # of contact to modify,\tor press zero to exit:");
            scanf("%d", &number);
            if(number == 0)
            {
                break;
            }
            int flag2=0;
            for(i = 0; i < flag; i++)
            {
                if(arr[number] == arr[i+1])
                {
                   x = arr[i];
                    printf("\nYou are now modifying the contact \"%s, %s\"\n", list[x].last_name, list[x].first_name);
                    puts("Enter new last name:");
                    scanf("%s", list[x].last_name);
                    casesensitive(list[x].last_name);
                    puts("Enter new first name:");
                    scanf("%s", list[x].first_name);
                    casesensitive(list[x].first_name);
                    fflush(stdin);
                    puts("Enter new street address:");
                    scanf("%[^\n]",list[x].Street_address);
                    fflush(stdin);
                    puts("Enter new phone number:");
                    gets(list[x].phone_number);
                    while(!valid_phone(list[x].phone_number))
                    {
                        puts("INVALID INPUT. TRY AGAIN.");
                        puts("Re-enter new phone number:");
                        scanf("%s", list[x].phone_number);
                    }
                    fflush(stdin);
                    puts("Enter new date of birth (DD/MM/YYYY):");
                    scanf("%d%c%d%c%d", &list[x].DOB.day, &junk, &list[x].DOB.month, &junk, &list[x].DOB.year);
                    while(!valid_date(list[x].DOB.day,list[x].DOB.month,list[x].DOB.year))
                    {
                        puts("INVALID INPUT. TRY AGAIN.");
                        puts("Re-enter new date of birth:");
                        scanf("%d%c%d%c%d", &list[x].DOB.day, &junk, &list[x].DOB.month, &junk, &list[x].DOB.year);
                    }
                    fflush(stdin);
                    puts("Enter new email address:");
                    scanf("%s", list[x].email);
                    while(!valid_email(list[x].email))
                    {
                        puts("INVALID INPUT. TRY AGAIN.");
                        puts("Re-enter new email address:");
                        scanf("%s", list[x].email);
                    }
                    flag2 = 1;
                }

            }
            if(!flag2)
            {
                puts("Error occurred. Wrong choice. Try again!");
            }
            else if(flag2)
            {
                puts("DATA MODIFIED SUCCESSFULLY!");
                break;
            }
        }
    }
    save=0;
    char buffer[100];
    int o = snprintf(buffer, 100, "You modified an existing contact %s %s.", list[x].first_name, list[x].last_name);
    strcpy(info[j++].change,buffer);
}
void sort_by_name(){
    int i,pass,sorted=0;
    contact temp;
    for(pass=1;pass<count && !sorted;pass++)
    {
        sorted = 1;
        for(i=0;i<count-pass;i++)
        {
            if(strcmp(list[i].last_name,list[i+1].last_name)>0)
            {
                temp=list[i];
                list[i]=list[i+1];
                list[i+1]=temp;
                sorted = 0;
            }
        }
    }
    sorted=0;
        for(pass=1;pass<count && !sorted;pass++)
    {
        sorted = 1;
        for(i=0;i<count-pass;i++)
       {
        if((strcmp(list[i].last_name,list[i+1].last_name)==0)&&(strcmp(list[i].first_name,list[i+1].first_name)>0))
            {
                temp=list[i];
                list[i]=list[i+1];
                list[i+1]=temp;
                sorted = 0;
            }
        }
    }

    print();
    save=0;
        strcpy(info[j++].change,"You sorted your contacts by Last Name.");

}
void sort_by_dob(){
    contact temp;
    int i,pass,sorted=0;
    for(pass=1;pass<count && !sorted;pass++){
        sorted = 1;
        for(i=0;i<count-pass;i++){
            if(list[i].DOB.year>list[i+1].DOB.year || (list[i].DOB.year==list[i+1].DOB.year && list[i].DOB.month>list[i+1].DOB.month) || (list[i].DOB.year==list[i+1].DOB.year && list[i].DOB.month==list[i+1].DOB.month && list[i].DOB.day>list[i+1].DOB.day)){
                temp=list[i];
                list[i]=list[i+1];
                list[i+1]=temp;
                sorted = 0;

            }
        }
    }
    print();
    save=0;
            strcpy(info[j++].change,"You sorted your contacts by Date of Birth.");


}
void print(){
        int i;
        for(i=0;i<count;i++){
        printf("#%d Contact\n",i+1);
        printf("Last Name \t %s\n",list[i].last_name);
        printf("First Name \t %s\n",list[i].first_name);
        printf("Date of birth \t %d-%d-%d\n",list[i].DOB.day,list[i].DOB.month,list[i].DOB.year);
        printf("Street address   %s\n",list[i].Street_address);
        printf("Phone number \t %s\n",list[i].phone_number);
        printf("Email address \t %s\n",list[i].email);
        printf("\n\n");
        }
        save=0;

}
void print_contact(contact person){
        printf("\n");
        printf("Last Name \t %s\n",person.last_name);
        printf("First Name \t %s\n",person.first_name);
        printf("Date of birth \t %d-%d-%d\n",person.DOB.day,person.DOB.month,person.DOB.year);
        printf("Street address   %s\n",person.Street_address);
        printf("Phone number \t %s\n",person.phone_number);
        printf("Email address \t %s\n",person.email);
        printf("\n\n");
            save=0;

}
void add_contact() {
        fflush(stdin);
    printf("Enter contact's last name: ");
        scanf("%[^\n]",list[count].last_name);
    casesensitive(list[count].last_name);
    fflush(stdin);

     printf("Enter contact's first name: ");
    scanf("%[^\n]",list[count].first_name);
    casesensitive(list[count].first_name);
        fflush(stdin);
    printf("Enter contact's date of birth DD/MM/YYYY: ");
    scanf("%d%c%d%c%d",&list[count].DOB.day, &junk, &list[count].DOB.month, &junk, &list[count].DOB.year);
    while(valid_date(list[count].DOB.day,list[count].DOB.month,list[count].DOB.year) == 0) {
        puts("INVALID INPUT. TRY AGAIN.");
        printf("Re-enter contact's date of birth DD/MM/YYYY: ");
        scanf("%d%c%d%c%d",&list[count].DOB.day, &junk, &list[count].DOB.month, &junk, &list[count].DOB.year);
    }
    fflush(stdin);
    printf("Enter contact's street address: ");
    scanf("%[^\n]",list[count].Street_address);
    fflush(stdin);
    printf("Enter contact's phone number: ");
    scanf("%s",list[count].phone_number);
    while(valid_phone(list[count].phone_number) ==0) {
        puts("INVALID INPUT. TRY AGAIN.");
        printf("Re-enter contact's phone number: ");
        scanf("%s",list[count].phone_number);
    }
    printf("Enter contact's email: ");
    scanf("%s",list[count].email);
    while(valid_email(list[count].email) == 0) {
        puts("INVALID INPUT. TRY AGAIN.");
        printf("Re-enter contact's email: ");
        scanf("%s",list[count].email);
    }
    char buffer[100];
    int o = snprintf(buffer, 100, "You added a new contact %s %s.", list[count].first_name, list[count].last_name);
    strcpy(info[j++].change,buffer);
    printf("CONTACT ADDED SUCCESSFULLY!\n");
        save=0;
        count=count+1;



}
int valid_date(int day,int month,int year) {
    if((month>12 || year>2020) ||
    ((month==1||month==3||month==5||month==7||month==8||month==10||month==12) && (day>31))
    || ((month==4 || month==6 || month==9 || month==11) && (day>30))
    || ((month==2) && ((year%4==0 && year%100==0 && year%400!=0) || (year%4!=0) ) && day>28)
    || ((month==2) && ((year%4==0 && year%100!=0) || (year%4==0 && year%100==0 && year%400==0)) && (day>29)))
        return 0;
    else return 1;
}
int valid_phone(char phone[]){
    int L = strlen(phone);
    if((L!=11) || (phone[0]!='0') || (phone[1]!='1') || ((phone[2]!='0') && (phone[2]!='1') && (phone[2]!='2')&&(phone[2]!='5')))
        return 0;
    else return 1;

}
int valid_email(char email[]){
    if(!isalpha(email[0]))
    {
        return 0;
    }
    int at=-1,dot=-1,i;
    for(i=0;i<strlen(email);i++) {
        if(email[i]=='@')
            at = i;
        else if(email[i]=='.')
            dot = i;
    }
    if(at==-1 || dot==-1)
        return 0;
    if(at - dot > -2)
        return 0;
    return !(dot >=strlen(email)-1);

}
void save_contacts(void){

        FILE* p;
   if ((p=fopen("PhoneBookModified.txt","w"))==NULL)
   {
       fprintf(stderr,"ERROR IN SAVING FILE.\n");
   }
   else
{
    for(int i=0;i<count;i++)    {
        fprintf(p,"%s,",list[i].last_name);
        fprintf(p,"%s,",list[i].first_name);
        fprintf(p,"%d-%d-%d,",list[i].DOB.day,list[i].DOB.month,list[i].DOB.year);
        fprintf(p,"%s,",list[i].Street_address);
        fprintf(p,"%s,",list[i].phone_number);
        fprintf(p,"%s\n",list[i].email);
        }
    fclose(p);
    printf("DATA SAVED SUCCESSFULLY!\n");
        save=1;
char buffer[100];
    int o = snprintf(buffer, 100, "You saved your previous change.");
    strcpy(info[j++].change,buffer);
}
}
void search_phonebook(){
    puts("\tNote: Searching is not case sensitive. Inputs \"Mohamed\" and \"mohamed\" are considered the same.");
    int i,x;
    char temp[20];
    while(1)
    {
        int flag = 0;
        puts("Enter the last name you want to search for,\t or press zero to exit:");
        scanf("%s", temp);
        if(strcmp(temp,"0") == 0)
        {
            break;
        }
        puts("\tSearching...");
        for(i = 0; i < count; i++)
        {
            if(strcasecmp(list[i].last_name, temp) == 0)
            {
                printf("\tContact Found #%d:", flag+1);
                print_contact(list[i]);
                x=i;
                flag++;

            }
        }
        if(flag == 0)
        {
            puts("No contacts found. Try again!");

        }
        else
        {
            break;
        }

    }
    save=1;
        char buffer[100];
        int o = snprintf(buffer, 100, "You searched for contacts with last name %s.",list[x].last_name);
        strcpy(info[j++].change,buffer);

}
void delete_contact(){
    fflush(stdin);
    contact temp;
    char first[20],last[20];
    int i,k,x;
    puts("\tNote: Deleting is not case sensitive. Inputs \"Mohamed\" and \"mohamed\" are considered the same.");
    printf("Enter the first name for the contact you want to delete,\t or press zero to exit:\n");
    scanf("%[^\n]",first);
    if(strcmp(first, "0")== 0)
    {
        return;
    }
    fflush(stdin);
    printf("Enter the last name for the contact you want to delete,\t or press zero to exit:\n");
    scanf("%[^\n]",last);
    if(strcmp(last, "0")== 0)
    {
        return;
    }
    fflush(stdin);
    for(i=0;i<count;i++)
    {
        if(strcasecmp(list[i].first_name,first)==0 && strcasecmp(list[i].last_name,last)==0)
        {
        x=i;
        char buffer[100];
        int o = snprintf(buffer, 100, "You deleted an existing contact %s %s.",list[x].first_name,list[x].last_name);
        strcpy(info[j++].change,buffer);
            for(k=i;k<count;k++){
                temp=list[k];
                list[k]=list[k+1];
                list[k+1]=temp;
            }
                flagDelete++;


    }else
    continue;
    }
    if(flagDelete)
      {
    printf("Contact successfully deleted\n");
count=count-1;
      }
    else
       {
                  printf("Contact not found, please try again!\n\n\n\n\n");
                    delete_contact();
       }
           save=0;


}
void casesensitive(char word[])
{
    word[0] = toupper(word[0]);
    int i;
    for(i = 1; i < strlen(word); i++)
    {
        if(word[i-1] != ' ') word[i] = tolower(word[i]);
        else if(word[i-1]== ' ')
        {
            word[i] = toupper(word[i]);
        }

    }
}

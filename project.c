#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_NAME 50
#define MAX_CODE 10

typedef struct item
{
    char name[MAX_NAME];
    char code[MAX_CODE];
    float unitPrice;
    int quantity;
    int reserved;
    struct item *next;
}item;

item *head=NULL;

void clearScreen()
{
    system("cls");
}

void addNewItem()
{
    clearScreen();

    item* newItem=(item*)malloc(sizeof(item));

    printf("Adding a new item...\n");
    printf("Enter Item Name: ");
    scanf("%s",newItem->name);
    printf("Enter Item Code: ");
    scanf("%s",newItem->code);
    printf("Enter Unit Price: ");
    scanf("%f",&newItem->unitPrice);
    printf("Enter Item Quantity: ");
    scanf("%d",&newItem->quantity);

    newItem->reserved=0;
    newItem->next=head;
    head=newItem;

    FILE* file=fopen("items.txt", "a");
    if (file==NULL) {
        printf("Error opening file.\n");
        free(newItem);
        return;
    }

    fprintf(file,"%s %s %.2f %d\n", newItem->name,newItem->code,newItem->unitPrice,newItem->quantity);
    fclose(file);

    printf("Item added successfully!\n");
    printf("Press any key to continue...\n");
    getchar();
}

void updateFile()
{
    FILE* file=fopen("items.txt", "w");
    if (file==NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    item* current=head;
    while(current!=NULL)
    {
        fprintf(file,"%s %s %.2f %d\n",current->name,current->code,current->unitPrice,current->quantity);
        current=current->next;
    }

    fclose(file);
}

void printBillSlip(float total)
{
    clearScreen();

    printf("------------\n");
    printf("TOTAL AMOUNT: Rs. %.2f\n", total);
    printf("Thank you for shopping with us!\n");
    printf("------------\n");


    item* current=head;
    while(current!=NULL)
    {
        current->quantity-=current->reserved;
        current->reserved=0;
        current=current->next;
    }


    updateFile();

    printf("Press any key to continue...\n");
    getchar();

}
void calculateBill() 
{
    clearScreen();
    char code[MAX_CODE];
    int quantity;
    float total = 0;
    char choice;

    printf("Calculating the bill...\n");

    do 
    {
        printf("Enter Item Code: ");
        scanf("%s", code);

        printf("Enter Quantity: ");
        scanf("%d", &quantity);

        item *current = head;
        int found = 0;

        while (current != NULL)
        {
            if (strcmp(current->code, code) == 0) 
            {
                found = 1;
                if (current->quantity - current->reserved >= quantity) {
                    total += current->unitPrice * quantity;
                    current->reserved += quantity;
                } 
                else 
                {
                    printf("Not enough quantity available for %s.\n", current->name);
                }
                break;
            }
            current = current->next;
        }

        if (found==0) 
        {
            printf("Item with code %s not found!\n", code);
        }

        printf("Do you want to add another item? (y/n): ");
        scanf(" %c", &choice);

    } while (choice=='y');

    printBillSlip(total);
    printf("Press any key to continue...\n");
    getchar();
}
void displayAllItems()
{
    clearScreen();
    printf("Displaying all items...\n");
    printf("Name\t\tCode\tUnit Price\tQuantity\n");
    printf("--------------------------------------------\n");

    item* current=head;
    while (current!=NULL)
    {
        printf("%s\t\t%s\t%.2f\t%d\n",current->name,current->code,current->unitPrice,current->quantity);
        current=current->next;
    }

    printf("Press any key to continue...\n");
    getchar();

}

void search()
 {
    clearScreen();
    int choice;
    char searchKey[50];

    printf("Search items by:\n");
    printf("1. Code\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) 
    {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter search key: ");
    scanf("%s", searchKey);

    item* current = head;
    int found = 0;

    printf("Search Results:\n");
    printf("Name\t\tCode\tUnit Price\tQuantity\n");
    printf("--------------------------------------------\n");

    while (current != NULL) {
        if ((choice == 1 && strcmp(current->code, searchKey) == 0) ||
            (choice == 2 && strcmp(current->name, searchKey) == 0)) 
        {
            printf("%s\t\t%s\t%.2f\t\t%d\n",current->name, current->code, current->unitPrice, current->quantity);
            found = 1;
        }
        current = current->next;
    }

    if (found == 0) 
    {
        printf("No items found\n");
    }

    printf("Press any key to continue...\n");
    getchar(); 
    getchar(); 
    
}


bool authenticate()
{
    char username[20];
    char password[20];
    printf("                                        ---------------------------------------------\n");
    printf("                                                     Departmental Store\n");
    printf("                                        ---------------------------------------------\n\n\n\n\n");
    printf("                                                    Enter username: ");
    scanf("%s", username);

    printf("                                                    Enter password: ");
    scanf("%s", password);

    if (strcmp(username,"admin") == 0 && strcmp(password,"1234") == 0)
    {
        return true;
    }
    else
    {
        printf("Incorrect username or password.\n");
        return false;
    }
}


void displayMainMenu()
{
    system("color 3");

    clearScreen();
    int choice;

    if (!authenticate())
    {
        return;
    }

    do
     {
        clearScreen();

        printf("                                      ---------------------------------------------\n");
        printf("                                                        MAIN MENU\n");
        printf("                                      ---------------------------------------------\n");
        printf("                                                      1. Add New Item\n");
        printf("                                                      2. Edit Item\n");
        printf("                                                      3. Delete Item\n");
        printf("                                                      4. Calculate Bill\n");
        printf("                                                      5. Display All Items\n");
        printf("                                                      6. Search Items\n");
        printf("                                                      7. Exit\n");

        printf("\n                                                    Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) 
        {
        case 1:
            addNewItem();
            break;
        case 2:
            editItem();
            break;
        case 3:
            deleteItem();
            break;
        case 4:
            calculateBill();
            break;
        case 5:
            displayAllItems();
            break;
        case 6:
            search();
            break;
        case 7:
            printf("Exiting the program...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
     while (choice != 7);
}

void savefile()
{
    FILE* file = fopen("items.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    item newItem;

    while (fscanf(file, "%s %s %f %d", newItem.name, newItem.code, &newItem.unitPrice, &newItem.quantity) == 4) {
        item* newItemPtr = (item*)malloc(sizeof(item));
        if (newItemPtr == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }
        strcpy(newItemPtr->name,newItem.name);
        strcpy(newItemPtr->code,newItem.code);
        newItemPtr->unitPrice =newItem.unitPrice;
        newItemPtr->quantity =newItem.quantity;
        newItemPtr->reserved = 0;
        newItemPtr->next = head;
        head = newItemPtr;
    }

    fclose(file);
}

void editItem()
{
    clearScreen();
    char code[MAX_CODE];
    printf("Editing an existing item...\n");
    printf("Enter Item Code to edit: ");
    scanf("%s", code);

    item* current = head;
    while (current!=NULL)
        {
        if (strcmp(current->code,code)==0)
        {
            printf("Item found! Enter updated details:\n");
            printf("Enter Item Name: ");
            scanf("%s", current->name);
            printf("Enter Unit Price: ");
            scanf("%f", &current->unitPrice);
            printf("Enter Item Quantity: ");
            scanf("%d", &current->quantity);
            printf("Item updated successfully!\n");
            printf("Press any key to continue...\n");
            getchar();
            getchar();
            return;
        }
        current=current->next;
    }

    printf("Item is not found!\n");
    printf("Press any key to continue...\n");
    getchar();
}

void deleteItem()
{
    clearScreen();
    char code[MAX_CODE];
    printf("Deleting an existing item...\n");
    printf("Enter Item Code to delete: ");
    scanf("%s",code);

    item* current=head;
    item* prev=NULL;

    while (current!=NULL)
        {
        if (strcmp(current->code,code)==0)
        {
            if (prev==NULL)
            {
                head=current->next;
            }
            else
            {
                prev->next=current->next;
            }
            free(current);
            printf("Item with code %s deleted successfully!\n", code);
            printf("Press any key to continue...\n");
            getchar();
            getchar();
            return;
        }
        prev=current;
        current=current->next;
    }
    printf("Item with code %s not found!\n", code);
    printf("Press any key to continue...\n");
    getchar();
}

int main()
{
    savefile();
    displayMainMenu();
    return 0;
}

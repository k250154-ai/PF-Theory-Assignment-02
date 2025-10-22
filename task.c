#include <stdio.h>
#include <stdlib.h>

int isbns[100];
char titles[100][50];
float prices[100];
int quantities[100];
int current_count = 0;
int choice;

void AddNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *current_count) {
   
    if (*current_count >= 100) {
        printf("Inventory full!\n"); 
        return;
    }

    int index = *current_count;

    printf("Enter ISBN: ");
    scanf("%d", &isbns[index]);

    // Check for duplicate ISBN
    for (int i = 0; i < index; i++) {
        if (isbns[index] == isbns[i]) {
            printf("ISBN already exists.\n");
            return;
        }
    }
    
    printf("Enter Title: ");
    scanf(" %[^\n]", titles[index]);
    printf("Enter Price: ");
    scanf("%f", &prices[index]);
    printf("Enter Quantity: ");
    scanf("%d", &quantities[index]);

    (*current_count)++;
    printf("Book added successfully.\n");
}

void ProcessBook(int isbns[], char titles[][50], float prices[], int quantities[], int current_count) {
    int Process_isbn, SellQuantity;
    int found = 0;  // Flag to track if book is found
    
    printf("Enter ISBN to process: ");
    scanf("%d", &Process_isbn);
    printf("Enter Number Of Copies to Sell: ");
    scanf("%d", &SellQuantity);
    
    for (int i = 0; i < current_count; i++) {
        if (isbns[i] == Process_isbn) {
            found = 1;  // Book found
            if (quantities[i] >= SellQuantity) {
                quantities[i] -= SellQuantity;
                printf("Book sold successfully.\n");
            } else {
                printf("Insufficient stock to sell %d copies. Only %d copies available.\n", 
                       SellQuantity, quantities[i]);
            }
            break;  // Exit loop once book is found
        }
    }
    
    if (!found) {
        printf("Book with ISBN %d not found.\n", Process_isbn);
    }
}

void LowStock(int isbns[], char titles[][50], int quantities[], int current_count) {
    int lowStockCount = 0;  // Count books with low stock
    
    printf("\n=== Low Stock Report ===\n");
    for (int i = 0; i < current_count; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: \"%s\" | Stock: %d copies\n", 
                   isbns[i], titles[i], quantities[i]);
            lowStockCount++;
        }
    }
    
    if (lowStockCount == 0) {
        printf("No books are low in stock.\n");
    } else {
        printf("\nTotal books with low stock: %d\n", lowStockCount);
    }
}

int main() {
    
    do {
        printf("\n===== Book Inventory System =====\n");
        printf("1- Add Book\n");
        printf("2- Process a Sale\n");
        printf("3- Low Stock\n");
        printf("4- Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                AddNewBook(isbns, titles, prices, quantities, &current_count);
                break;
            case 2:
                system("cls");
                ProcessBook(isbns, titles, prices, quantities, current_count);
                break;
            case 3:
                system("cls");
                LowStock(isbns, titles, quantities, current_count);
                break;
            case 4:
                system("cls");
                printf("Exiting the program.\n");
                break;
            default:
                system("cls");
                printf("Invalid choice. Please try again.\n");
        }   
    } while (choice != 4);  // Changed from 5 to 4

    return 0;
}
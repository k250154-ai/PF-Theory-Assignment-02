#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// Global variables
char customerCNIC[20];
char customerName[50];
char productCode[4][4] = {"001", "002", "003", "004"};
int productCount[4] = {50, 10, 20, 8};
int productPrice[4] = {100, 200, 300, 150};
char cartProductCode[10][4];  // Increased size for multiple items
int cartProductCount[10] = {0}; 
int cartSize = 0;  // Tracks how many different items in cart
float appliedDiscount = 0.0;  // Store discount for invoice
float finalTotal = 0.0;  // Store final total for invoice

// Function prototypes
void getCustomerDetails();
void displayInventory();
void addItemToCart();
void updateInventory();
void displayTotalBill();
void showInvoice();
void displayCart();

// Get customer details (called once at start)
void getCustomerDetails() {
    printf("\n===== Customer Information =====\n");
    printf("Enter Customer CNIC: ");
    scanf("%s", customerCNIC);
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", customerName);
    printf("\nWelcome, %s!\n", customerName);
}

// Display current inventory
void displayInventory() {
    printf("\n===== Current Inventory =====\n");
    printf("-----------------------------------------------\n");
    printf("| %-14s | %-13s | %-8s |\n", "Product Code", "Price (Rs.)", "Stock");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        printf("| %-14s | %-13d | %-8d |\n", 
               productCode[i], productPrice[i], productCount[i]);
    }

    printf("-----------------------------------------------\n");
}

// Display current cart contents
void displayCart() {
    if (cartSize == 0) {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf("\n===== Your Cart =====\n");
    printf("-----------------------------------------------\n");
    printf("| %-14s | %-13s | %-8s |\n", "Product Code", "Price (Rs.)", "Quantity");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < cartSize; i++) {
        // Find the price for this product
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                printf("| %-14s | %-13d | %-8d |\n", 
                       cartProductCode[i], productPrice[j], cartProductCount[i]);
                break;
            }
        }
    }
    printf("-----------------------------------------------\n");
}

// Add item to cart
void addItemToCart() {
    char inputCode[4];
    int quantity;
    int productIndex = -1;
    int cartIndex = -1;

    printf("\n===== Add Item to Cart =====\n");
    printf("Enter Product Code: ");
    scanf("%s", inputCode);

    // Find product in inventory
    for (int i = 0; i < 4; i++) {
        if (strcmp(productCode[i], inputCode) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("Error: Product code '%s' not found!\n", inputCode);
        return;
    }

    // Check if product already in cart
    for (int i = 0; i < cartSize; i++) {
        if (strcmp(cartProductCode[i], inputCode) == 0) {
            cartIndex = i;
            break;
        }
    }

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    // Validate quantity
    if (quantity <= 0) {
        printf("Error: Quantity must be greater than 0!\n");
        return;
    }

    if (quantity > productCount[productIndex]) {
        printf("Error: Only %d items available in stock!\n", 
               productCount[productIndex]);
        return;
    }

    // Add to cart or update existing item
    if (cartIndex == -1) {
        // New item - add to cart
        strcpy(cartProductCode[cartSize], inputCode);
        cartProductCount[cartSize] = quantity;
        cartSize++;
    } else {
        // Item already in cart - update quantity
        cartProductCount[cartIndex] += quantity;
    }

    // Update inventory
    productCount[productIndex] -= quantity;

    printf("✓ Successfully added %d unit(s) of %s to cart!\n", 
           quantity, inputCode);
    
    displayCart();
}

// Update inventory manually (not through purchase)
void updateInventory() {
    char inputCode[4];
    int newQuantity;
    int found = 0;

    printf("\n===== Update Inventory =====\n");
    printf("Enter Product Code to update: ");
    scanf("%s", inputCode);

    for (int i = 0; i < 4; i++) {
        if (strcmp(productCode[i], inputCode) == 0) {
            found = 1;
            printf("Current quantity of %s: %d\n", inputCode, productCount[i]);
            printf("Enter new quantity: ");
            scanf("%d", &newQuantity);

            if (newQuantity < 0) {
                printf("Error: Quantity cannot be negative!\n");
                return;
            }

            productCount[i] = newQuantity;
            printf("✓ Inventory updated successfully!\n");
            printf("New quantity of %s: %d\n", inputCode, productCount[i]);
            break;
        }
    }

    if (!found) {
        printf("Error: Product code '%s' not found!\n", inputCode);
    }
}

// Display total bill with optional discount
void displayTotalBill() {
    float totalBill = 0.0;
    char promoCode[20];

    if (cartSize == 0) {
        printf("\nYour cart is empty! Add items first.\n");
        return;
    }

    printf("\n===== Bill Summary =====\n");
    printf("---------------------------------------------------------------\n");
    printf("| %-12s | %-10s | %-8s | %-12s |\n", 
           "Product", "Price (Rs.)", "Qty", "Subtotal");
    printf("---------------------------------------------------------------\n");

    // Calculate bill
    for (int i = 0; i < cartSize; i++) {
        // Find matching product price
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                float subtotal = cartProductCount[i] * productPrice[j];
                printf("| %-12s | %-10d | %-8d | %-12.2f |\n",
                       cartProductCode[i], productPrice[j], 
                       cartProductCount[i], subtotal);
                totalBill += subtotal;
                break;
            }
        }
    }
    
    printf("---------------------------------------------------------------\n");
    printf("Subtotal: Rs. %.2f\n", totalBill);

    // Promo code
    printf("\nDo you have a promo code? (Enter code or type 'NO'): ");
    scanf("%s", promoCode);

    if (strcmp(promoCode, "Eid2025") == 0) {
        appliedDiscount = totalBill * 0.25;  // 25% discount
        finalTotal = totalBill - appliedDiscount;
        printf("\n✓ Promo code 'Eid2025' applied successfully!\n");
        printf("Discount (25%%): Rs. %.2f\n", appliedDiscount);
        printf("\n========================================\n");
        printf("   FINAL TOTAL: Rs. %.2f\n", finalTotal);
        printf("========================================\n");
    } else {
        appliedDiscount = 0.0;
        finalTotal = totalBill;
        if (strcmp(promoCode, "NO") != 0 && strcmp(promoCode, "no") != 0) {
            printf("\n✗ Invalid promo code.\n");
        }
        printf("\n========================================\n");
        printf("   TOTAL: Rs. %.2f\n", finalTotal);
        printf("========================================\n");
    }
}

// Show detailed invoice
void showInvoice() {
    if (cartSize == 0) {
        printf("\nNo items to show in invoice! Add items to cart first.\n");
        return;
    }

    float totalWithoutDiscount = 0.0;

    printf("\n");
    printf("================================================================\n");
    printf("                       INVOICE                                  \n");
    printf("================================================================\n");
    printf("Customer Name: %s\n", customerName);
    printf("Customer CNIC: %s\n", customerCNIC);
    printf("================================================================\n");
    printf("| %-12s | %-10s | %-8s | %-12s |\n", 
           "Product", "Price (Rs.)", "Qty", "Subtotal");
    printf("----------------------------------------------------------------\n");

    // Display all items
    for (int i = 0; i < cartSize; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                float subtotal = cartProductCount[i] * productPrice[j];
                printf("| %-12s | %-10d | %-8d | %-12.2f |\n",
                       cartProductCode[i], productPrice[j], 
                       cartProductCount[i], subtotal);
                totalWithoutDiscount += subtotal;
                break;
            }
        }
    }

    printf("================================================================\n");
    printf("Total (without discount): Rs. %.2f\n", totalWithoutDiscount);
    
    if (appliedDiscount > 0) {
        printf("Discount Applied (25%%):   Rs. %.2f\n", appliedDiscount);
        printf("----------------------------------------------------------------\n");
        printf("FINAL AMOUNT (with discount): Rs. %.2f\n", finalTotal);
    } else {
        printf("Discount Applied:         Rs. 0.00\n");
        printf("----------------------------------------------------------------\n");
        printf("FINAL AMOUNT:             Rs. %.2f\n", finalTotal);
    }
    
    printf("================================================================\n");
    printf("           Thank you for shopping with us!                     \n");
    printf("================================================================\n");
}

int main() {
    int choice;
    
    // Get customer details once at the start
    getCustomerDetails();
    
    do {
        printf("\n\n===== Supermarket Inventory System =====\n");
        printf("1. Display Inventory\n");
        printf("2. Add Item to Cart\n");
        printf("3. Update Inventory\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. View Cart\n");
        printf("7. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                system("cls");
                displayInventory();
                break;
            case 2:
                system("cls");
                addItemToCart();
                break;
            case 3:
                system("cls");
                updateInventory();
                break;
            case 4:
                system("cls");
                displayTotalBill();
                break;
            case 5:
                system("cls");
                showInvoice();
                break;
            case 6:
                system("cls");
                displayCart();
                break;
            case 7:
                system("cls");
                printf("\nThank you for using our system!\n");
                printf("Goodbye, %s!\n", customerName);
                break;
            default:
                system("cls");
                printf("\n✗ Invalid choice! Please select 1-7.\n");
        }
        
    } while (choice != 7);
    
    return 0;
}
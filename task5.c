#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);

int main() {
    char message[500];
    int choice;

    printf("\n===== TCS Courier Message Security Tool =====\n");
    printf("Welcome to Tranzum Courier Service Encoding System\n");

    do {
        printf("\n\n===== Main Menu =====\n");
        printf("1- Encode Message\n");
        printf("2- Decode Message\n");
        printf("3- Exit\n");
        printf("======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                printf("\n===== Encode Message =====\n");
                printf("Enter message to encode: ");
                scanf(" %[^\n]", message);
                encodeMessage(message);
                break;

            case 2:
                system("cls");
                printf("\n===== Decode Message =====\n");
                printf("Enter message to decode: ");
                scanf(" %[^\n]", message);
                decodeMessage(message);
                break;

            case 3:
                system("cls");
                printf("\nShutting down TCS Security Tool...\n");
                printf("Thank you for using our system!\n");
                break;

            default:
                system("cls");
                printf("\n✗ Invalid choice! Please select 1-3.\n");
        }

    } while (choice != 3);

    return 0;
}

void encodeMessage(char message[]) {
    int len = strlen(message);
    char reversed[500];
    
    for (int i = 0; i < len; i++) {
        reversed[i] = message[len - 1 - i];
    }
    reversed[len] = '\0';
    
    for (int i = 0; i < len; i++) {
        int ascii = (int)reversed[i];
        ascii = ascii ^ (1 << 1);
        ascii = ascii ^ (1 << 4);
        reversed[i] = (char)ascii;
    }
    
    printf("\nOriginal Message: %s\n", message);
    printf("Encoded Message: %s\n", reversed);
    printf("✓ Message encoded successfully!\n");
}

void decodeMessage(char message[]) {
    int len = strlen(message);
    char decoded[500];
    
    strcpy(decoded, message);
    
    for (int i = 0; i < len; i++) {
        int ascii = (int)decoded[i];
        ascii = ascii ^ (1 << 1);
        ascii = ascii ^ (1 << 4);
        decoded[i] = (char)ascii;
    }
    
    char final[500];
    for (int i = 0; i < len; i++) {
        final[i] = decoded[len - 1 - i];
    }
    final[len] = '\0';
    
    printf("\nEncoded Message: %s\n", message);
    printf("Decoded Message: %s\n", final);
    printf("✓ Message decoded successfully!\n");
}
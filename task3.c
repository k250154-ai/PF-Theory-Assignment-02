#include <stdio.h>
#include <stdlib.h>

int grid[5][5];

void updateStatus(int row, int col, int bit, int value) {
    if (value == 1) {
        grid[row][col] = grid[row][col] | (1 << bit);
    } else {
        grid[row][col] = grid[row][col] & ~(1 << bit);
    }
}

void checkSector(int row, int col) {
    int status = grid[row][col];
    
    printf("\n===== Sector [%d][%d] Status =====\n", row, col);
    printf("Power Status: %s\n", (status & 1) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & 2) ? "Overloaded" : "Normal");
    printf("Maintenance Required: %s\n", (status & 4) ? "Yes" : "No");
    printf("Raw Status Value: %d\n", status);
}

void systemCheck() {
    int overloadCount = 0;
    int maintenanceCount = 0;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i][j] & 2) {
                overloadCount++;
            }
            if (grid[i][j] & 4) {
                maintenanceCount++;
            }
        }
    }
    
    printf("\n===== System Diagnostic Report =====\n");
    printf("Total sectors with overload: %d\n", overloadCount);
    printf("Total sectors needing maintenance: %d\n", maintenanceCount);
    printf("Total problematic sectors: %d\n", overloadCount + maintenanceCount);
}

int main() {
    int choice;
    int row, col, bit, value;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            grid[i][j] = 0;
        }
    }
    
    printf("\n===== IESCO Power Grid System =====\n");
    printf("Welcome to Islamabad Capital Territory Grid Monitor\n");
    
    do {
        printf("\n\n===== Main Menu =====\n");
        printf("1. Update Sector Status\n");
        printf("2. Check Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit System\n");
        printf("======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                system("cls");
                printf("\n===== Update Sector Status =====\n");
                printf("Enter row (0-4): ");
                scanf("%d", &row);
                printf("Enter column (0-4): ");
                scanf("%d", &col);
                
                if (row < 0 || row > 4 || col < 0 || col > 4) {
                    printf("Error: Invalid coordinates!\n");
                    break;
                }
                
                printf("\nSelect status to update:\n");
                printf("0 = Power Status\n");
                printf("1 = Overload Warning\n");
                printf("2 = Maintenance Required\n");
                printf("Enter bit number: ");
                scanf("%d", &bit);
                
                printf("Enter value (0=OFF/Clear, 1=ON/Set): ");
                scanf("%d", &value);
                
                updateStatus(row, col, bit, value);
                printf("✓ Sector [%d][%d] status updated successfully!\n", row, col);
                break;
                
            case 2:
                system("cls");
                printf("\n===== Query Sector Status =====\n");
                printf("Enter row (0-4): ");
                scanf("%d", &row);
                printf("Enter column (0-4): ");
                scanf("%d", &col);
                
                if (row < 0 || row > 4 || col < 0 || col > 4) {
                    printf("Error: Invalid coordinates!\n");
                    break;
                }
                
                checkSector(row, col);
                break;
                
            case 3:
                system("cls");
                systemCheck();
                break;
                
            case 4:
                system("cls");
                printf("\nShutting down IESCO Grid Monitor...\n");
                printf("Thank you for using the system!\n");
                break;
                
            default:
                system("cls");
                printf("\n✗ Invalid choice! Please select 1-4.\n");
        }
        
    } while (choice != 4);
    
    return 0;
}
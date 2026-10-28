/**
 * ============================================================================
 * Project Title : Cafeteria Management System
 * Language      : C (Standard ANSI/C99/C11)
 * File Name     : cafeteria.c
 * Description   : A menu-driven console application to manage food menus,
 *                 take customer orders, compute billing, store order
 *                 history in a text file (orders.txt), search records,
 *                 and calculate cafeteria sales.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* ============================================================================
 * CONSTANTS AND DEFINITIONS
 * ============================================================================ */
#define MAX_ITEMS 9
#define MAX_ORDER_ITEMS 20
#define NAME_LEN 50
#define DATE_LEN 30
#define FILE_NAME "orders.txt"

/* ============================================================================
 * STRUCTURE DEFINITIONS
 * ============================================================================ */

/* Represents a single food item in the cafeteria menu */
struct MenuItem {
    int id;
    char name[30];
    float price;
};

/* Represents an individual item selected within a customer's order */
struct OrderItem {
    int itemId;
    char itemName[30];
    int quantity;
    float price;
    float subtotal;
};

/* Represents a complete customer order with metadata and line items */
struct Order {
    int orderId;
    char customerName[NAME_LEN];
    char orderDate[DATE_LEN];
    struct OrderItem items[MAX_ORDER_ITEMS];
    int itemCount;
    float grandTotal;
};

/* ============================================================================
 * GLOBAL MENU DATABASE (Predefined Menu Items)
 * ============================================================================ */
struct MenuItem menu[MAX_ITEMS] = {
    {1, "Idli", 30.0f},
    {2, "Dosa", 50.0f},
    {3, "Poori", 40.0f},
    {4, "Veg Meals", 100.0f},
    {5, "Fried Rice", 80.0f},
    {6, "Sandwich", 60.0f},
    {7, "Tea", 15.0f},
    {8, "Coffee", 20.0f},
    {9, "Fresh Juice", 40.0f}
};

/* ============================================================================
 * FUNCTION DECLARATIONS (PROTOTYPES)
 * ============================================================================ */
void displayMenu(void);
void placeOrder(void);
void saveOrder(struct Order ord);
void viewOrders(void);
void searchOrderById(void);
void searchOrdersByName(void);
void calculateTotalSales(void);
int getNextOrderId(void);
void getCurrentDateTime(char *buffer, int bufferSize);
void clearInputBuffer(void);
void trimNewline(char *str);
int caseInsensitiveContains(const char *source, const char *search);

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================ */
int main(void) {
    int choice = 0;

    printf("\n==================================================\n");
    printf("     WELCOME TO CAFETERIA MANAGEMENT SYSTEM       \n");
    printf("==================================================\n");

    while (1) {
        printf("\n------------------- MAIN MENU --------------------\n");
        printf("1. Display Food Menu\n");
        printf("2. Place Customer Order\n");
        printf("3. View All Customer Orders\n");
        printf("4. Search Order by Order ID\n");
        printf("5. Search Orders by Customer Name\n");
        printf("6. Calculate Total Sales\n");
        printf("7. Exit\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input! Please enter a number between 1 and 7.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                placeOrder();
                break;
            case 3:
                viewOrders();
                break;
            case 4:
                searchOrderById();
                break;
            case 5:
                searchOrdersByName();
                break;
            case 6:
                calculateTotalSales();
                break;
            case 7:
                printf("\n==================================================\n");
                printf("  Thank you for visiting the Cafeteria! Have a great day!\n");
                printf("==================================================\n\n");
                return 0;
            default:
                printf("\n[ERROR] Invalid choice! Please select an option from 1 to 7.\n");
                break;
        }
    }

    return 0;
}

/* ============================================================================
 * FUNCTION IMPLEMENTATIONS
 * ============================================================================ */

/**
 * Displays the list of all available food items and their prices.
 */
void displayMenu(void) {
    int i;
    printf("\n==================================================\n");
    printf("               CAFETERIA FOOD MENU                \n");
    printf("==================================================\n");
    printf("%-8s %-25s %-12s\n", "Item ID", "Food Item", "Price (INR)");
    printf("--------------------------------------------------\n");
    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%-8d %-25s Rs. %-8.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("==================================================\n");
}

/**
 * Handles placing a customer order, item validation, bill calculation,
 * invoice printing, and file persistence.
 */
void placeOrder(void) {
    struct Order ord;
    int itemId, qty;
    int addMore = 1;
    int foundIndex = -1;
    int i;

    memset(&ord, 0, sizeof(struct Order));
    ord.orderId = getNextOrderId();
    getCurrentDateTime(ord.orderDate, sizeof(ord.orderDate));

    printf("\n==================================================\n");
    printf("              PLACE CUSTOMER ORDER                \n");
    printf("==================================================\n");

    printf("Enter Customer Name: ");
    if (fgets(ord.customerName, sizeof(ord.customerName), stdin) == NULL) {
        strcpy(ord.customerName, "Guest Customer");
    }
    trimNewline(ord.customerName);

    if (strlen(ord.customerName) == 0) {
        strcpy(ord.customerName, "Walk-in Customer");
    }

    /* Show quick menu reference for convenience */
    displayMenu();

    while (addMore && ord.itemCount < MAX_ORDER_ITEMS) {
        printf("\nSelect food item ID (1-%d): ", MAX_ITEMS);
        if (scanf("%d", &itemId) != 1) {
            printf("[ERROR] Please enter a valid numeric item ID.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        /* Validate item ID */
        foundIndex = -1;
        for (i = 0; i < MAX_ITEMS; i++) {
            if (menu[i].id == itemId) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1) {
            printf("[ERROR] Invalid Item ID '%d'. Please select from the menu.\n", itemId);
            continue;
        }

        printf("Selected: %s | Price: Rs. %.2f\n", menu[foundIndex].name, menu[foundIndex].price);
        printf("Enter quantity: ");
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            printf("[ERROR] Quantity must be a positive integer greater than 0.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        /* Record item into order */
        ord.items[ord.itemCount].itemId = menu[foundIndex].id;
        strncpy(ord.items[ord.itemCount].itemName, menu[foundIndex].name, sizeof(ord.items[ord.itemCount].itemName) - 1);
        ord.items[ord.itemCount].quantity = qty;
        ord.items[ord.itemCount].price = menu[foundIndex].price;
        ord.items[ord.itemCount].subtotal = qty * menu[foundIndex].price;

        ord.grandTotal += ord.items[ord.itemCount].subtotal;
        ord.itemCount++;

        printf("-> Added: %s x %d = Rs. %.2f (Current Total: Rs. %.2f)\n",
               menu[foundIndex].name, qty,
               ord.items[ord.itemCount - 1].subtotal,
               ord.grandTotal);

        if (ord.itemCount >= MAX_ORDER_ITEMS) {
            printf("[NOTE] Maximum order capacity reached (%d items).\n", MAX_ORDER_ITEMS);
            break;
        }

        printf("\nSelect another item? (1 = Yes, 0 = No): ");
        if (scanf("%d", &addMore) != 1) {
            addMore = 0;
            clearInputBuffer();
        } else {
            clearInputBuffer();
        }
    }

    if (ord.itemCount == 0) {
        printf("\n[INFO] Order cancelled. No items were selected.\n");
        return;
    }

    /* Print Order Summary / Detailed Bill */
    printf("\n==================================================\n");
    printf("                  ORDER SUMMARY                   \n");
    printf("==================================================\n");
    printf("Order ID      : %d\n", ord.orderId);
    printf("Customer Name : %s\n", ord.customerName);
    printf("Order Date    : %s\n", ord.orderDate);
    printf("--------------------------------------------------\n");
    printf("%-4s %-16s %-8s %-10s %-10s\n", "#", "Item", "Qty", "Price", "Subtotal");
    printf("--------------------------------------------------\n");
    for (i = 0; i < ord.itemCount; i++) {
        printf("%-4d %-16s %-8d Rs.%-7.2f Rs.%-7.2f\n",
               i + 1,
               ord.items[i].itemName,
               ord.items[i].quantity,
               ord.items[i].price,
               ord.items[i].subtotal);
    }
    printf("--------------------------------------------------\n");
    printf("%-30s Rs. %-10.2f\n", "Grand Total:", ord.grandTotal);
    printf("==================================================\n");

    /* Save to file */
    saveOrder(ord);
    printf("[SUCCESS] Order #%d saved successfully to '%s'!\n", ord.orderId, FILE_NAME);
}

/**
 * Saves a completed order to orders.txt in append mode.
 * Existing records are never overwritten or deleted.
 */
void saveOrder(struct Order ord) {
    FILE *fp = fopen(FILE_NAME, "a");
    int i;

    if (fp == NULL) {
        printf("[ERROR] Failed to open '%s' for saving order!\n", FILE_NAME);
        return;
    }

    fprintf(fp, "==================================================\n");
    fprintf(fp, "ORDER_ID: %d\n", ord.orderId);
    fprintf(fp, "CUSTOMER: %s\n", ord.customerName);
    fprintf(fp, "DATE: %s\n", ord.orderDate);
    fprintf(fp, "ITEMS_COUNT: %d\n", ord.itemCount);
    for (i = 0; i < ord.itemCount; i++) {
        fprintf(fp, "ITEM: %d | %s | %d | %.2f | %.2f\n",
                ord.items[i].itemId,
                ord.items[i].itemName,
                ord.items[i].quantity,
                ord.items[i].price,
                ord.items[i].subtotal);
    }
    fprintf(fp, "GRAND_TOTAL: %.2f\n", ord.grandTotal);
    fprintf(fp, "==================================================\n");

    fclose(fp);
}

/**
 * Reads all order records from orders.txt and displays them.
 */
void viewOrders(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[256];
    int count = 0;

    if (fp == NULL) {
        printf("\n[INFO] No order records found. (File '%s' does not exist yet).\n", FILE_NAME);
        printf("Place a customer order first to create the record file.\n");
        return;
    }

    printf("\n==================================================\n");
    printf("            ALL SAVED CUSTOMER ORDERS             \n");
    printf("==================================================\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "ORDER_ID:") != NULL) {
            count++;
        }
        printf("%s", line);
    }

    fclose(fp);

    if (count == 0) {
        printf("\n[INFO] The file '%s' exists, but contains no customer orders yet.\n", FILE_NAME);
    } else {
        printf("\n[INFO] Displayed %d order record(s) from '%s'.\n", count, FILE_NAME);
    }
}

/**
 * Searches for an order by its unique Order ID.
 */
void searchOrderById(void) {
    FILE *fp;
    char line[256];
    int targetId;
    int currentId = -1;
    int found = 0;
    int printing = 0;

    printf("\n==================================================\n");
    printf("              SEARCH ORDER BY ORDER ID            \n");
    printf("==================================================\n");
    printf("Enter Order ID to search: ");

    if (scanf("%d", &targetId) != 1) {
        printf("[ERROR] Invalid numeric Order ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("[INFO] No orders found! '%s' does not exist yet.\n", FILE_NAME);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "ORDER_ID: %d", &currentId) == 1) {
            if (currentId == targetId) {
                found = 1;
                printing = 1;
                printf("\n--- MATCHING RECORD FOUND ---\n");
                printf("==================================================\n");
                printf("%s", line);
                continue;
            } else {
                printing = 0;
            }
        }

        if (printing) {
            printf("%s", line);
            if (strstr(line, "GRAND_TOTAL:") != NULL) {
                if (fgets(line, sizeof(line), fp) != NULL) {
                    printf("%s", line);
                }
                printing = 0;
                break;
            }
        }
    }

    fclose(fp);

    if (!found) {
        printf("\n[RESULT] No order found with Order ID: %d\n", targetId);
    }
}

/**
 * Searches for orders matching a customer's name (case-insensitive search).
 */
void searchOrdersByName(void) {
    FILE *fp;
    char targetName[NAME_LEN];
    char line[256];
    char orderBuffer[4096];
    char customerInOrder[NAME_LEN];
    int foundCount = 0;
    int inOrder = 0;

    printf("\n==================================================\n");
    printf("            SEARCH ORDERS BY CUSTOMER NAME        \n");
    printf("==================================================\n");
    printf("Enter Customer Name to search: ");

    if (fgets(targetName, sizeof(targetName), stdin) == NULL) {
        printf("[ERROR] Failed to read customer name.\n");
        return;
    }
    trimNewline(targetName);

    if (strlen(targetName) == 0) {
        printf("[ERROR] Customer name cannot be empty.\n");
        return;
    }

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("[INFO] No orders found! '%s' does not exist yet.\n", FILE_NAME);
        return;
    }

    orderBuffer[0] = '\0';
    customerInOrder[0] = '\0';

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "ORDER_ID:") != NULL) {
            inOrder = 1;
            orderBuffer[0] = '\0';
            customerInOrder[0] = '\0';
            strcat(orderBuffer, "==================================================\n");
            strcat(orderBuffer, line);
            continue;
        }

        if (inOrder) {
            strcat(orderBuffer, line);

            if (strncmp(line, "CUSTOMER: ", 10) == 0) {
                strncpy(customerInOrder, line + 10, sizeof(customerInOrder) - 1);
                trimNewline(customerInOrder);
            }

            if (strstr(line, "GRAND_TOTAL:") != NULL) {
                if (fgets(line, sizeof(line), fp) != NULL) {
                    strcat(orderBuffer, line);
                }

                if (caseInsensitiveContains(customerInOrder, targetName)) {
                    printf("\n--- MATCH #%d ---\n", ++foundCount);
                    printf("%s", orderBuffer);
                }

                inOrder = 0;
            }
        }
    }

    fclose(fp);

    if (foundCount == 0) {
        printf("\n[RESULT] No orders found matching customer name: '%s'\n", targetName);
    } else {
        printf("\n[RESULT] Total %d order(s) found for customer '%s'.\n", foundCount, targetName);
    }
}

/**
 * Calculates and displays total sales collected across all saved orders.
 */
void calculateTotalSales(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[256];
    float totalSales = 0.0f;
    float currentTotal = 0.0f;
    int orderCount = 0;

    if (fp == NULL) {
        printf("\n[INFO] No orders found! '%s' does not exist yet.\n", FILE_NAME);
        printf("Current Total Sales: Rs. 0.00\n");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "ORDER_ID:") != NULL) {
            orderCount++;
        }
        if (sscanf(line, "GRAND_TOTAL: %f", &currentTotal) == 1) {
            totalSales += currentTotal;
        }
    }

    fclose(fp);

    printf("\n==================================================\n");
    printf("             TOTAL CAFETERIA SALES REPORT         \n");
    printf("==================================================\n");
    printf("Total Completed Orders : %d\n", orderCount);
    printf("Gross Revenue / Sales  : Rs. %.2f\n", totalSales);
    if (orderCount > 0) {
        printf("Average Ticket Value   : Rs. %.2f\n", totalSales / orderCount);
    }
    printf("==================================================\n");
}

/**
 * Reads orders.txt to find the highest existing Order ID and returns (highest + 1).
 * If no orders exist, returns default starting ID 1001.
 */
int getNextOrderId(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[256];
    int maxId = 1000;
    int tempId = 0;

    if (fp == NULL) {
        return 1001;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "ORDER_ID: %d", &tempId) == 1) {
            if (tempId > maxId) {
                maxId = tempId;
            }
        }
    }

    fclose(fp);
    return maxId + 1;
}

/**
 * Generates the current timestamp in "YYYY-MM-DD HH:MM:SS" format.
 */
void getCurrentDateTime(char *buffer, int bufferSize) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (t != NULL) {
        strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", t);
    } else {
        strncpy(buffer, "2026-10-28 12:00:00", bufferSize);
    }
}

/**
 * Clears remaining characters from stdin input buffer to prevent scanf issues.
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard characters until newline or EOF */
    }
}

/**
 * Strips trailing newline ('\n' or '\r') characters from strings read by fgets.
 */
void trimNewline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

/**
 * Performs a case-insensitive substring search.
 * Returns 1 if search substring is found within source, else 0.
 */
int caseInsensitiveContains(const char *source, const char *search) {
    char lowerSource[NAME_LEN * 2];
    char lowerSearch[NAME_LEN * 2];
    int i;

    if (!source || !search) return 0;

    for (i = 0; source[i] && i < sizeof(lowerSource) - 1; i++) {
        lowerSource[i] = (char)tolower((unsigned char)source[i]);
    }
    lowerSource[i] = '\0';

    for (i = 0; search[i] && i < sizeof(lowerSearch) - 1; i++) {
        lowerSearch[i] = (char)tolower((unsigned char)search[i]);
    }
    lowerSearch[i] = '\0';

    return (strstr(lowerSource, lowerSearch) != NULL) ? 1 : 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- MENU STRUCTURE ---------------- */

struct Food {
    int id;
    char name[50];
    float price;
    struct Food *next;
};

/* ---------------- CART STRUCTURE ---------------- */

struct Cart {
    int foodId;
    char name[50];
    float price;
    int quantity;
    struct Cart *next;
};

/* ---------------- ORDER QUEUE ---------------- */

struct Order {
    int orderId;
    float amount;
    struct Order *next;
};

struct Order *front = NULL;
struct Order *rear = NULL;

int nextOrderId = 1001;

/* ---------------- CREATE FOOD ---------------- */

struct Food* createFood(int id, char name[], float price) {
    struct Food *newFood;

    newFood = (struct Food*)malloc(sizeof(struct Food));

    newFood->id = id;
    strcpy(newFood->name, name);
    newFood->price = price;
    newFood->next = NULL;

    return newFood;
}

/* ---------------- ADD FOOD TO MENU ---------------- */

void addFood(struct Food **head, int id, char name[], float price) {
    struct Food *newFood = createFood(id, name, price);

    if (*head == NULL) {
        *head = newFood;
    } else {
        struct Food *temp = *head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newFood;
    }
}

/* ---------------- DISPLAY MENU ---------------- */

void displayMenu(struct Food *head) {
    printf("\n========== FOOD MENU ==========\n");
    printf("ID\tFood Name\t\tPrice\n");
    printf("--------------------------------------\n");

    while (head != NULL) {
        printf("%d\t%-20s\t%.2f\n",
               head->id, head->name, head->price);

        head = head->next;
    }

    printf("--------------------------------------\n");
}

/* ---------------- SEARCH FOOD ---------------- */

struct Food* searchFood(struct Food *head, int id) {

    while (head != NULL) {

        if (head->id == id)
            return head;

        head = head->next;
    }

    return NULL;
}

/* ---------------- ADD TO CART ---------------- */

void addToCart(struct Cart **cart, struct Food *food, int quantity) {

    struct Cart *temp = *cart;

    /* Check whether food already exists in cart */
    while (temp != NULL) {

        if (temp->foodId == food->id) {
            temp->quantity += quantity;

            printf("\nQuantity updated successfully!\n");
            return;
        }

        temp = temp->next;
    }

    /* Create new cart item */
    struct Cart *newItem;

    newItem = (struct Cart*)malloc(sizeof(struct Cart));

    newItem->foodId = food->id;
    strcpy(newItem->name, food->name);
    newItem->price = food->price;
    newItem->quantity = quantity;
    newItem->next = NULL;

    if (*cart == NULL) {
        *cart = newItem;
    } else {

        temp = *cart;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newItem;
    }

    printf("\nFood added to cart successfully!\n");
}

/* ---------------- DISPLAY CART ---------------- */

float displayCart(struct Cart *cart) {

    float total = 0;

    printf("\n========== YOUR CART ==========\n");

    if (cart == NULL) {
        printf("Cart is empty.\n");
        return 0;
    }

    printf("Food\t\tQuantity\tPrice\n");
    printf("--------------------------------------\n");

    while (cart != NULL) {

        float amount = cart->price * cart->quantity;

        printf("%-15s\t%d\t\t%.2f\n",
               cart->name,
               cart->quantity,
               amount);

        total += amount;

        cart = cart->next;
    }

    printf("--------------------------------------\n");
    printf("TOTAL BILL = Rs. %.2f\n", total);

    return total;
}

/* ---------------- REMOVE FROM CART ---------------- */

void removeFromCart(struct Cart **cart, int id) {

    struct Cart *temp = *cart;
    struct Cart *prev = NULL;

    while (temp != NULL) {

        if (temp->foodId == id) {

            if (prev == NULL)
                *cart = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            printf("\nItem removed from cart.\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nFood item not found in cart.\n");
}

/* ---------------- SORT MENU BY PRICE ---------------- */

void sortMenu(struct Food *head) {

    struct Food *i, *j;

    int tempId;
    char tempName[50];
    float tempPrice;

    for (i = head; i != NULL; i = i->next) {

        for (j = i->next; j != NULL; j = j->next) {

            if (i->price > j->price) {

                tempId = i->id;
                i->id = j->id;
                j->id = tempId;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                tempPrice = i->price;
                i->price = j->price;
                j->price = tempPrice;
            }
        }
    }

    printf("\nMenu sorted by price successfully!\n");
}

/* ---------------- ENQUEUE ORDER ---------------- */

void placeOrder(float amount) {

    struct Order *newOrder;

    newOrder = (struct Order*)malloc(sizeof(struct Order));

    newOrder->orderId = nextOrderId++;
    newOrder->amount = amount;
    newOrder->next = NULL;

    if (rear == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf("\n========== ORDER PLACED ==========\n");
    printf("Order ID : %d\n", newOrder->orderId);
    printf("Amount   : Rs. %.2f\n", amount);
    printf("Order added to queue successfully!\n");
}

/* ---------------- PROCESS ORDER ---------------- */

void processOrder() {

    if (front == NULL) {
        printf("\nNo pending orders.\n");
        return;
    }

    struct Order *temp = front;

    printf("\n========== PROCESSING ORDER ==========\n");
    printf("Order ID : %d\n", temp->orderId);
    printf("Amount   : Rs. %.2f\n", temp->amount);

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);

    printf("Order processed successfully!\n");
}

/* ---------------- DISPLAY ORDER QUEUE ---------------- */

void displayOrders() {

    struct Order *temp = front;

    if (temp == NULL) {
        printf("\nNo pending orders.\n");
        return;
    }

    printf("\n========== PENDING ORDERS ==========\n");

    while (temp != NULL) {

        printf("Order ID: %d | Amount: Rs. %.2f\n",
               temp->orderId,
               temp->amount);

        temp = temp->next;
    }
}

/* ---------------- MAIN FUNCTION ---------------- */

int main() {

    struct Food *menu = NULL;
    struct Cart *cart = NULL;

    int choice;
    int id;
    int quantity;

    /* Default Food Menu */

    addFood(&menu, 1, "Burger", 120);
    addFood(&menu, 2, "Pizza", 250);
    addFood(&menu, 3, "Biryani", 180);
    addFood(&menu, 4, "Momos", 100);
    addFood(&menu, 5, "Sandwich", 90);
    addFood(&menu, 6, "Cold Drink", 50);

    do {

        printf("\n\n====================================\n");
        printf("   FOOD ORDERING MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Display Food Menu\n");
        printf("2. Search Food\n");
        printf("3. Add Food to Cart\n");
        printf("4. View Cart\n");
        printf("5. Remove Food from Cart\n");
        printf("6. Sort Menu by Price\n");
        printf("7. Place Order\n");
        printf("8. View Pending Orders\n");
        printf("9. Process Order\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayMenu(menu);
                break;

            case 2: {

                printf("\nEnter Food ID to search: ");
                scanf("%d", &id);

                struct Food *food = searchFood(menu, id);

                if (food != NULL) {
                    printf("\nFood Found!\n");
                    printf("ID    : %d\n", food->id);
                    printf("Name  : %s\n", food->name);
                    printf("Price : Rs. %.2f\n", food->price);
                } else {
                    printf("\nFood not found.\n");
                }

                break;
            }

            case 3: {

                printf("\nEnter Food ID: ");
                scanf("%d", &id);

                struct Food *food = searchFood(menu, id);

                if (food == NULL) {
                    printf("\nInvalid Food ID.\n");
                } else {

                    printf("Enter Quantity: ");
                    scanf("%d", &quantity);

                    if (quantity <= 0) {
                        printf("\nInvalid quantity.\n");
                    } else {
                        addToCart(&cart, food, quantity);
                    }
                }

                break;
            }

            case 4:
                displayCart(cart);
                break;

            case 5:

                printf("\nEnter Food ID to remove: ");
                scanf("%d", &id);

                removeFromCart(&cart, id);

                break;

            case 6:

                sortMenu(menu);
                displayMenu(menu);

                break;

            case 7: {

                if (cart == NULL) {
                    printf("\nCart is empty. Add food first.\n");
                } else {

                    float total = displayCart(cart);

                    placeOrder(total);

                    /* Clear cart after placing order */

                    while (cart != NULL) {

                        struct Cart *temp = cart;
                        cart = cart->next;

                        free(temp);
                    }
                }

                break;
            }

            case 8:
                displayOrders();
                break;

            case 9:
                processOrder();
                break;

            case 0:
                printf("\nThank you for using Food Ordering System!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
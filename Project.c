#include <stdio.h>
#include <string.h>

#define MAX_MEDICINES 100
#define MAX_QUEUE 50
#define MAX_STACK 50

// =====================================================
// MEDICINE STRUCTURE
// =====================================================

struct Medicine
{
    int id;
    char name[50];
    char company[50];
    char category[30];
    float price;
    int quantity;
};


// =====================================================
// ORDER STRUCTURE FOR QUEUE
// =====================================================

struct Order
{
    int medicineID;
    char medicineName[50];
    int quantity;
};


// =====================================================
// SALE STRUCTURE FOR STACK
// =====================================================

struct Sale
{
    int medicineID;
    char medicineName[50];
    int quantity;
    float totalPrice;
};


// =====================================================
// GLOBAL ARRAYS
// =====================================================

// Main Medicine Array
struct Medicine medicines[MAX_MEDICINES];

int medicineCount = 0;


// Queue
struct Order orderQueue[MAX_QUEUE];

int front = -1;
int rear = -1;


// Stack
struct Sale saleStack[MAX_STACK];

int top = -1;


// =====================================================
// FUNCTION PROTOTYPES
// =====================================================

void addMedicine();
void displayMedicines();
void searchMedicine();
void searchByID();
void checkAvailability();
void updateStock();
void deleteMedicine();
void sortByPrice();
void sortByName();
void lowStockReport();

void addOrder();
void processOrder();
void displayQueue();

void sellMedicine();
void showLastSale();
void displayStack();


// =====================================================
// FIND MEDICINE BY ID
// =====================================================

int findMedicine(int id)
{
    int i;

    for(i = 0; i < medicineCount; i++)
    {
        if(medicines[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


// =====================================================
// ADD MEDICINE TO ARRAY
// =====================================================

void addMedicine()
{
    int id;
    int i;

    if(medicineCount >= MAX_MEDICINES)
    {
        printf("\nMedicine storage is full!\n");
        return;
    }

    printf("\n========== ADD MEDICINE ==========\n");

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    // Check duplicate ID
    for(i = 0; i < medicineCount; i++)
    {
        if(medicines[i].id == id)
        {
            printf("\nMedicine ID already exists!\n");
            return;
        }
    }

    medicines[medicineCount].id = id;

    printf("Enter Medicine Name: ");
    scanf(" %[^\n]", medicines[medicineCount].name);

    printf("Enter Company Name: ");
    scanf(" %[^\n]", medicines[medicineCount].company);

    printf("Enter Category: ");
    scanf(" %[^\n]", medicines[medicineCount].category);

    printf("Enter Price: ");
    scanf("%f", &medicines[medicineCount].price);

    printf("Enter Quantity: ");
    scanf("%d", &medicines[medicineCount].quantity);

    medicineCount++;

    printf("\nMedicine added successfully!\n");
}


// =====================================================
// DISPLAY ALL MEDICINES
// =====================================================

void displayMedicines()
{
    int i;

    if(medicineCount == 0)
    {
        printf("\nNo medicines available!\n");
        return;
    }

    printf("\n================ MEDICINE LIST ================\n");

    printf("%-5s %-18s %-18s %-15s %-10s %-10s\n",
           "ID",
           "Name",
           "Company",
           "Category",
           "Price",
           "Stock");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < medicineCount; i++)
    {
        printf("%-5d %-18s %-18s %-15s %-10.2f %-10d\n",
               medicines[i].id,
               medicines[i].name,
               medicines[i].company,
               medicines[i].category,
               medicines[i].price,
               medicines[i].quantity);
    }
}


// =====================================================
// SEARCH MEDICINE BY NAME
// =====================================================

void searchMedicine()
{
    char name[50];
    int i;
    int found = 0;

    printf("\n========== SEARCH MEDICINE ==========\n");

    printf("Enter Medicine Name: ");
    scanf(" %[^\n]", name);

    for(i = 0; i < medicineCount; i++)
    {
        if(strcmp(medicines[i].name, name) == 0)
        {
            printf("\nMedicine Found!\n");

            printf("ID       : %d\n", medicines[i].id);
            printf("Name     : %s\n", medicines[i].name);
            printf("Company  : %s\n", medicines[i].company);
            printf("Category : %s\n", medicines[i].category);
            printf("Price    : %.2f BDT\n", medicines[i].price);
            printf("Stock    : %d\n", medicines[i].quantity);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nMedicine not found!\n");
    }
}


// =====================================================
// SEARCH MEDICINE BY ID
// =====================================================

void searchByID()
{
    int id;
    int index;

    printf("\n========== SEARCH BY ID ==========\n");

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    printf("\nMedicine Found!\n");

    printf("ID       : %d\n", medicines[index].id);
    printf("Name     : %s\n", medicines[index].name);
    printf("Company  : %s\n", medicines[index].company);
    printf("Category : %s\n", medicines[index].category);
    printf("Price    : %.2f BDT\n", medicines[index].price);
    printf("Stock    : %d\n", medicines[index].quantity);
}


// =====================================================
// CHECK AVAILABILITY
// =====================================================

void checkAvailability()
{
    int id;
    int index;

    printf("\n========== CHECK AVAILABILITY ==========\n");

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    printf("\nMedicine: %s\n", medicines[index].name);

    if(medicines[index].quantity > 0)
    {
        printf("Status: AVAILABLE\n");
        printf("Available Quantity: %d\n",
               medicines[index].quantity);
    }
    else
    {
        printf("Status: OUT OF STOCK\n");
    }
}


// =====================================================
// UPDATE STOCK
// =====================================================

void updateStock()
{
    int id;
    int quantity;
    int index;

    printf("\n========== UPDATE STOCK ==========\n");

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    printf("Medicine: %s\n",
           medicines[index].name);

    printf("Current Stock: %d\n",
           medicines[index].quantity);

    printf("Enter New Quantity: ");
    scanf("%d", &quantity);

    if(quantity < 0)
    {
        printf("\nInvalid quantity!\n");
        return;
    }

    medicines[index].quantity = quantity;

    printf("\nStock updated successfully!\n");
}


// =====================================================
// DELETE MEDICINE FROM ARRAY
// =====================================================

void deleteMedicine()
{
    int id;
    int index;
    int i;

    printf("\n========== DELETE MEDICINE ==========\n");

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    // Shift elements to left
    for(i = index; i < medicineCount - 1; i++)
    {
        medicines[i] = medicines[i + 1];
    }

    medicineCount--;

    printf("\nMedicine deleted successfully!\n");
}


// =====================================================
// SORT BY PRICE
// =====================================================

void sortByPrice()
{
    int i;
    int j;

    struct Medicine temp;

    for(i = 0; i < medicineCount - 1; i++)
    {
        for(j = 0; j < medicineCount - i - 1; j++)
        {
            if(medicines[j].price >
               medicines[j + 1].price)
            {
                temp = medicines[j];

                medicines[j] = medicines[j + 1];

                medicines[j + 1] = temp;
            }
        }
    }

    printf("\nMedicines sorted by price!\n");

    displayMedicines();
}


// =====================================================
// SORT BY NAME
// =====================================================

void sortByName()
{
    int i;
    int j;

    struct Medicine temp;

    for(i = 0; i < medicineCount - 1; i++)
    {
        for(j = 0; j < medicineCount - i - 1; j++)
        {
            if(strcmp(medicines[j].name,
                      medicines[j + 1].name) > 0)
            {
                temp = medicines[j];

                medicines[j] = medicines[j + 1];

                medicines[j + 1] = temp;
            }
        }
    }

    printf("\nMedicines sorted by name!\n");

    displayMedicines();
}


// =====================================================
// LOW STOCK REPORT
// =====================================================

void lowStockReport()
{
    int i;
    int found = 0;

    printf("\n========== LOW STOCK REPORT ==========\n");

    for(i = 0; i < medicineCount; i++)
    {
        if(medicines[i].quantity <= 10)
        {
            printf("\nID       : %d",
                   medicines[i].id);

            printf("\nName     : %s",
                   medicines[i].name);

            printf("\nCompany  : %s",
                   medicines[i].company);

            printf("\nStock    : %d",
                   medicines[i].quantity);

            if(medicines[i].quantity == 0)
            {
                printf("\nStatus   : OUT OF STOCK\n");
            }
            else
            {
                printf("\nStatus   : LOW STOCK\n");
            }

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nNo low-stock medicines!\n");
    }
}


// =====================================================
// QUEUE - ADD ORDER
// =====================================================

void addOrder()
{
    int id;
    int quantity;
    int index;

    printf("\n========== ADD MEDICINE ORDER ==========\n");

    if(rear == MAX_QUEUE - 1)
    {
        printf("\nQueue is full!\n");
        return;
    }

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    printf("Medicine: %s\n",
           medicines[index].name);

    printf("Available Stock: %d\n",
           medicines[index].quantity);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if(quantity <= 0)
    {
        printf("\nInvalid quantity!\n");
        return;
    }

    if(quantity > medicines[index].quantity)
    {
        printf("\nNot enough stock!\n");
        return;
    }

    // First order
    if(front == -1)
    {
        front = 0;
    }

    rear++;

    orderQueue[rear].medicineID = id;

    strcpy(orderQueue[rear].medicineName,
           medicines[index].name);

    orderQueue[rear].quantity = quantity;

    printf("\nOrder added to queue successfully!\n");
}


// =====================================================
// QUEUE - PROCESS ORDER
// =====================================================

void processOrder()
{
    int id;
    int index;

    if(front == -1 || front > rear)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    id = orderQueue[front].medicineID;

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine no longer exists!\n");

        front++;

        return;
    }

    // Reduce stock
    medicines[index].quantity -=
        orderQueue[front].quantity;

    printf("\n========== ORDER PROCESSED ==========\n");

    printf("Medicine : %s\n",
           orderQueue[front].medicineName);

    printf("Quantity : %d\n",
           orderQueue[front].quantity);

    printf("Remaining Stock : %d\n",
           medicines[index].quantity);

    // Remove from queue
    front++;

    if(front > rear)
    {
        front = -1;
        rear = -1;
    }
}


// =====================================================
// DISPLAY QUEUE
// =====================================================

void displayQueue()
{
    int i;

    if(front == -1)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\n========== ORDER QUEUE ==========\n");

    for(i = front; i <= rear; i++)
    {
        printf("\nOrder %d\n", i - front + 1);

        printf("Medicine ID : %d\n",
               orderQueue[i].medicineID);

        printf("Medicine    : %s\n",
               orderQueue[i].medicineName);

        printf("Quantity    : %d\n",
               orderQueue[i].quantity);
    }
}


// =====================================================
// STACK - SELL MEDICINE
// =====================================================

void sellMedicine()
{
    int id;
    int quantity;
    int index;
    float total;

    printf("\n========== SELL MEDICINE ==========\n");

    if(top == MAX_STACK - 1)
    {
        printf("\nSale stack is full!\n");
        return;
    }

    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    index = findMedicine(id);

    if(index == -1)
    {
        printf("\nMedicine not found!\n");
        return;
    }

    printf("Medicine: %s\n",
           medicines[index].name);

    printf("Available Stock: %d\n",
           medicines[index].quantity);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if(quantity <= 0)
    {
        printf("\nInvalid quantity!\n");
        return;
    }

    if(quantity > medicines[index].quantity)
    {
        printf("\nNot enough stock!\n");
        return;
    }

    // Reduce stock
    medicines[index].quantity -= quantity;

    total = quantity * medicines[index].price;

    // PUSH INTO STACK
    top++;

    saleStack[top].medicineID = id;

    strcpy(saleStack[top].medicineName,
           medicines[index].name);

    saleStack[top].quantity = quantity;

    saleStack[top].totalPrice = total;

    printf("\nMedicine sold successfully!\n");

    printf("Total Price: %.2f BDT\n", total);

    printf("Remaining Stock: %d\n",
           medicines[index].quantity);
}


// =====================================================
// STACK - SHOW LAST SALE
// =====================================================

void showLastSale()
{
    if(top == -1)
    {
        printf("\nSale stack is empty!\n");
        return;
    }

    printf("\n========== LAST SALE ==========\n");

    printf("Medicine ID : %d\n",
           saleStack[top].medicineID);

    printf("Medicine    : %s\n",
           saleStack[top].medicineName);

    printf("Quantity    : %d\n",
           saleStack[top].quantity);

    printf("Total Price : %.2f BDT\n",
           saleStack[top].totalPrice);
}


// =====================================================
// DISPLAY STACK
// =====================================================

void displayStack()
{
    int i;

    if(top == -1)
    {
        printf("\nSale stack is empty!\n");
        return;
    }

    printf("\n========== SALES STACK ==========\n");

    for(i = top; i >= 0; i--)
    {
        printf("\nSale %d\n", top - i + 1);

        printf("Medicine ID : %d\n",
               saleStack[i].medicineID);

        printf("Medicine    : %s\n",
               saleStack[i].medicineName);

        printf("Quantity    : %d\n",
               saleStack[i].quantity);

        printf("Total Price : %.2f BDT\n",
               saleStack[i].totalPrice);
    }
}


// =====================================================
// MAIN FUNCTION
// =====================================================

int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("====================================================\n");
        printf("          MEDICINE AVAILABILITY FINDER\n");
        printf("             ARRAY + QUEUE + STACK\n");
        printf("====================================================\n");

        printf("\n----- MEDICINE ARRAY -----\n");
        printf("1.  Add Medicine\n");
        printf("2.  Display Medicines\n");
        printf("3.  Search Medicine by Name\n");
        printf("4.  Search Medicine by ID\n");
        printf("5.  Check Availability\n");
        printf("6.  Update Stock\n");
        printf("7.  Delete Medicine\n");
        printf("8.  Sort by Name\n");
        printf("9.  Sort by Price\n");
        printf("10. Low Stock Report\n");

        printf("\n----- ORDER QUEUE -----\n");
        printf("11. Add Medicine Order\n");
        printf("12. Process Next Order\n");
        printf("13. Display Order Queue\n");

        printf("\n----- SALES STACK -----\n");
        printf("14. Sell Medicine\n");
        printf("15. Show Last Sale\n");
        printf("16. Display Sales Stack\n");

        printf("\n0. Exit\n");

        printf("====================================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            // ARRAY
            case 1:
                addMedicine();
                break;

            case 2:
                displayMedicines();
                break;

            case 3:
                searchMedicine();
                break;

            case 4:
                searchByID();
                break;

            case 5:
                checkAvailability();
                break;

            case 6:
                updateStock();
                break;

            case 7:
                deleteMedicine();
                break;

            case 8:
                sortByName();
                break;

            case 9:
                sortByPrice();
                break;

            case 10:
                lowStockReport();
                break;


            // QUEUE
            case 11:
                addOrder();
                break;

            case 12:
                processOrder();
                break;

            case 13:
                displayQueue();
                break;


            // STACK
            case 14:
                sellMedicine();
                break;

            case 15:
                showLastSale();
                break;

            case 16:
                displayStack();
                break;


            case 0:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 0);


    return 0;
}

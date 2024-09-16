#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_expenses 100
#define FILE_NAME "expenses.txt"
struct expense {
    char description[60];
    float amount;
     char date[20];
};

struct expense expenses[MAX_expenses];// to hold all the expesnes
int numExpenses =0;//the current nbr of expenses

void addExpenses(char description[],float amount){
    if (numExpenses<MAX_expenses)
    {
        strcpy(expenses[numExpenses].description,description);
        expenses[numExpenses].amount=amount;
        numExpenses++;
        printf("added successfully! \n ");
    }
    else
    {
        printf("cannot add any more expenses.\n");
    }        
}
void viewExpenses(){
    if (numExpenses<=0)
    {
        printf("no expenses to show\n");
    }
    else
    {
        printf("list of expenses:\n");
        for (int i = 0; i < numExpenses; i++)
        {
            printf("%d description : %s, Amount: %.2f\n",i+1,expenses[i].description,expenses[i].amount);
        }  
    }   
}

float calculateTotalExpenses(){
    float total = 0.0;
    for (int i = 0; i < numExpenses; i++)
    {
        total +=expenses[i].amount;
    }
    return total;
}

void loadExpensesFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No previous expenses found.\n");
        return;
    }

    numExpenses = 0;  // Reset number of expenses
    while (fscanf(file, " %49[^,],%f\n", expenses[numExpenses].description, &expenses[numExpenses].amount) != EOF) {
        numExpenses++;
        if (numExpenses >= MAX_expenses) {
            printf("Warning: Maximum number of expenses reached.\n");
            break;
        }
    }

    fclose(file);
    printf("Expenses loaded from file successfully.\n");
}

void saveExpensesToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numExpenses; i++) {
        fprintf(file, "%s,%.2f\n", expenses[i].description, expenses[i].amount);
    }

    fclose(file);
    printf("Expenses saved to file successfully.\n");
}

int main(){
    int choice;
    char description[60];
    float amount;

    loadExpensesFromFile();

    do{
         printf("\nExpense Tracker Menu:\n");
        printf("1. Add an expense\n");
        printf("2. View all expenses\n");
        printf("3. Calculate total expenses\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("enter description of expense:\n");
            scanf("%[^\n]s \n",description);
            printf("enter the amount:\n");
            scanf("%f",&amount);
            addExpenses(description,amount);
            break; // Added break to avoid fall-through
        case 2:
            viewExpenses();
            break; // Added break to avoid fall-through
        case 3:
            printf("total expennses: %.2f\n",calculateTotalExpenses());
            break;
        case 4: // Added break to avoid fall-through
            printf("Exiting program...\n");
            break; // Added break to avoid fall-through
        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    }while(choice!=4);

    return 0;
}
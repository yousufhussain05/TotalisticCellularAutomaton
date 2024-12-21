/*-------------------------------------------
Program 1: Totalistic Cellular Automaton
Course: CS 211, Fall 2024, UIC
Author: Yousuf Hussain
-------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

// Struct to store each cell's properties
typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// Function to set values for each possible local sum
// Parameters: int valArray[7] - the array to store rule values, int rule - the rule number
// Return: bool indicating if the rule was valid or not
bool setValArray(int valArray[7], int rule) {
    if ((rule < 0) || (rule > 2186)) {
        return false;
    }
    for (int i = 0; i < 7; i++) {
        valArray[i] = rule % 3;
        rule = rule / 3;
    }

    return true;
}

// Function to commute the local sums for each cell based on its neighbor
// Parameters: cell world[WORLD_SIZE] - the world of cells
void setSums(cell world[WORLD_SIZE]) {
    int left;
    int right;

    // Iterate over each cell and calculate local sums based on neighbors
    for (int i = 0; i < 65; i++) {
        left = (i == 0) ? WORLD_SIZE - 1 : i - 1;
        right = (i == WORLD_SIZE - 1) ? 0 : i + 1;
        
        world[i].localSum = world[left].status + world[i].status + world[right].status;
    }

    return;
}

// Function to evolve the world by updating the cell status for each generation
// Parameters: cell world[WORLD_SIZE] - the world of cells, int ruleValArray[7] - rule array
// Return: int total sum of cell statuses in each generation
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    int newSum = 0; 

    for (int i = 0; i < WORLD_SIZE; i++) {
        int newStatus = ruleValArray[world[i].localSum];
        world[i].count += newStatus;
        world[i].status = newStatus;
        newSum += newStatus;        

    }

    return newSum;
}


int main() {

    cell world[WORLD_SIZE];
    int rule, remainder;
    int result[7];

    printf("Welcome to the Totalistic Cellular Automaton!\n");

    do {
        printf("Enter the rule # (0-2186): \n");
        scanf("%d", &rule);
    }
    while (!(setValArray(result, rule))); // Loop until a valid rule is entered
    
    printf("\nThe value array for rule #%d is ", rule);

    for (int i = 6; i >= 0; i--) {
        printf("%d", result[i]);
    }
    printf("\n\n");
    
    // Display local sum evolution states
    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");

    for (int i = 6; i >= 0; i--) {
        printf("|");
        if (result[i] == 0) {
            printf(" "); // Display space for inactive status
        }
        else if (result[i] == 1) {
            printf("-"); // Display '-' for active status 1
        }
        else if (result[i] == 2) {
            printf("+"); // Display '+' for active status 2
        }
        printf("|     ");
    }

    printf("\n\n");

    int generation;

    while (generation < 1 || generation > 49) {
        printf("Enter the number of generations (1-49): \n");
        scanf("%d", &generation);
    }
    
    int values;

    do {
        printf("Enter the value (1 or 2) for the initial active cell: \n");
        scanf("%d", &values);
    }
    while ((values != 1) && (values != 2));

    printf("\n");
    printf("Initializing world & evolving...\n");

    // Initialize the world - all cells inactive initially
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = 0;
        world[i].count = 0;
    }

    // Set the middle cell as the initial active cell
    int mid = WORLD_SIZE / 2;
    world[mid].status = values;
    world[mid].count += values;
    setSums(world);

    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].status == 1) {
            printf("-");
        }
        else if (world[i].status == 2) {
            printf("+");
        }
        else {
            printf(" ");
        }
    }

    int sum = 0;

    for (int i = 0; i < WORLD_SIZE; i++) {
        sum += world[i].status;
    }
    printf(" %d \n", sum);

    // Evolve the world for the given number of generations
    for (int gen = 1; gen < generation; gen++) {
        int totalSum;
        totalSum = evolveWorld(world, result);
        setSums(world);

        // Print the state of the world for the current generation
        for (int i = 0; i < WORLD_SIZE; i++) {
            if (world[i].status == 1) {
            printf("-");
            }
            else if (world[i].status == 2) {
                printf("+");
            }
            else {  
                printf(" ");
            }
        }
        
        printf(" %d \n", totalSum);

    }
    printf("_________________________________________________________________");


    printf("\n");

    // Print the total counts for each cell
    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].count >= 10) {
            int tens = world[i].count / 10;
            printf("%d", tens);
        }
        else {
            printf(" ");
        }
    }

    printf("\n");

    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].count > 0) {
            int ones = world[i].count % 10;
            printf("%d", ones);
        }
        else {
            printf(" ");
        }
    }
    printf("\n"); 

    return 0;
}

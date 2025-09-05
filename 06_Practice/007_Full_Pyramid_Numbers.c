// Practical 7: Full Pyramid of Numbers
// This program prints a full pyramid pattern using numbers

#include <stdio.h>

int main() {
    int rows;

    // Get number of rows from user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Input validation
    if (rows <= 0) {
        printf("Please enter a positive number!\n");
        return 1;
    }

    printf("Full Pyramid of Numbers:\n");
    printf("========================\n");

    // Outer loop for rows
    for (int i = 1; i <= rows; i++) {
        // First inner loop for leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Second inner loop for numbers
        for (int k = 1; k <= i; k++) {
            printf("%d ", k);
        }

        printf("\n");
    }

    return 0;
}
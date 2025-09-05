// Practical 8: Inverted Full Pyramid of Stars
// This program prints an inverted full pyramid pattern using stars

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

    printf("Inverted Full Pyramid of Stars:\n");
    printf("==============================\n");

    // Outer loop for rows
    for (int i = rows; i >= 1; i--) {
        // First inner loop for leading spaces
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Second inner loop for stars
        for (int k = 1; k <= i; k++) {
            printf("* ");
        }

        printf("\n");
    }

    return 0;
}
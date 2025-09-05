# 🎯 Practical 32: Figure Calculator

## 📋 Problem Statement

Design a program which displays following options on screen
1. Figure
2. Exit
3. Enter Choice
Once valid choice is entered it executes further.
If choice one is entered, then it should display
1. TRIANGLE
2. SQUARE
3. RHOMBUS
4. TRAPEZIUM
5. RETURN TO PREVIOUS MENU
ENTER CHOICE
Once valid choice is entered it executes further.
After that it ask for specific data and prints the area and volume and perimeter/circumference of the respective figure.
After that a choice is to be asked for
Do you wish to continue (Y/N)? And should work accordingly. Before every menu, the screen should be cleared.

## 🎯 Learning Objectives

- Understand menu-driven programs
- Practice geometric calculations
- Learn switch-case with nested menus
- Understand figure properties
- Practice input validation

## 📝 Requirements

1. Display main menu with Figure/Exit options
2. Show figure submenu with TRIANGLE/SQUARE/RHOMBUS/TRAPEZIUM/RETURN options
3. Accept dimensions for selected figure
4. Calculate and display area and perimeter
5. Ask "Do you wish to continue (Y/N)?"
6. Clear screen before every menu

## 💡 Hints

- Use nested switch-case
- Clear screen with system("cls") or system("clear")
- Validate inputs
- Use functions for calculations
- Handle different figure types

## 🔧 Solution

```c
// Practical 32: Figure Calculator
// Calculates area and perimeter of geometric figures

#include <stdio.h>
#include <stdlib.h>

int main() {
    int main_choice, figure_choice;
    char continue_choice;
    float area, perimeter;

    do {
        // Clear screen
        system("cls");

        printf("Figure Calculator\n");
        printf("=================\n");
        printf("1. Figure\n");
        printf("2. Exit\n");
        printf("3. Enter Choice\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        if (main_choice == 2) {
            break;
        }

        if (main_choice == 1) {
            // Clear screen for figure menu
            system("cls");

            printf("Figure Menu\n");
            printf("===========\n");
            printf("1. TRIANGLE\n");
            printf("2. SQUARE\n");
            printf("3. RHOMBUS\n");
            printf("4. TRAPEZIUM\n");
            printf("5. RETURN TO PREVIOUS MENU\n");
            printf("ENTER CHOICE: ");
            scanf("%d", &figure_choice);

            if (figure_choice == 5) {
                continue;
            }

            // Clear screen for input
            system("cls");

            switch (figure_choice) {
                case 1: { // TRIANGLE
                    float base, height, side1, side2;
                    printf("Enter base: ");
                    scanf("%f", &base);
                    printf("Enter height: ");
                    scanf("%f", &height);
                    printf("Enter side1: ");
                    scanf("%f", &side1);
                    printf("Enter side2: ");
                    scanf("%f", &side2);

                    area = 0.5 * base * height;
                    perimeter = base + side1 + side2;

                    printf("TRIANGLE\n");
                    printf("Area: %.2f\n", area);
                    printf("Perimeter: %.2f\n", perimeter);
                    break;
                }
                case 2: { // SQUARE
                    float side;
                    printf("Enter side: ");
                    scanf("%f", &side);

                    area = side * side;
                    perimeter = 4 * side;

                    printf("SQUARE\n");
                    printf("Area: %.2f\n", area);
                    printf("Perimeter: %.2f\n", perimeter);
                    break;
                }
                case 3: { // RHOMBUS
                    float diagonal1, diagonal2, side;
                    printf("Enter diagonal1: ");
                    scanf("%f", &diagonal1);
                    printf("Enter diagonal2: ");
                    scanf("%f", &diagonal2);
                    printf("Enter side: ");
                    scanf("%f", &side);

                    area = 0.5 * diagonal1 * diagonal2;
                    perimeter = 4 * side;

                    printf("RHOMBUS\n");
                    printf("Area: %.2f\n", area);
                    printf("Perimeter: %.2f\n", perimeter);
                    break;
                }
                case 4: { // TRAPEZIUM
                    float parallel1, parallel2, height, side1, side2;
                    printf("Enter parallel side1: ");
                    scanf("%f", &parallel1);
                    printf("Enter parallel side2: ");
                    scanf("%f", &parallel2);
                    printf("Enter height: ");
                    scanf("%f", &height);
                    printf("Enter non-parallel side1: ");
                    scanf("%f", &side1);
                    printf("Enter non-parallel side2: ");
                    scanf("%f", &side2);

                    area = 0.5 * (parallel1 + parallel2) * height;
                    perimeter = parallel1 + parallel2 + side1 + side2;

                    printf("TRAPEZIUM\n");
                    printf("Area: %.2f\n", area);
                    printf("Perimeter: %.2f\n", perimeter);
                    break;
                }
                default:
                    printf("Invalid choice!\n");
            }
        } else {
            printf("Invalid choice!\n");
        }

        printf("\nDo you wish to continue (Y/N)? ");
        scanf(" %c", &continue_choice);

    } while (continue_choice == 'Y' || continue_choice == 'y');

    printf("Program ended.\n");
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Triangle Calculation
```
Main Choice: 1
Figure Choice: 1
Base: 6, Height: 4, Side1: 5, Side2: 5
Continue: Y
Expected Output:
TRIANGLE
Area: 12.00
Perimeter: 16.00
```

### Test Case 2: Square Calculation
```
Main Choice: 1
Figure Choice: 2
Side: 5
Continue: N
Expected Output:
SQUARE
Area: 25.00
Perimeter: 20.00
```

## 🔍 Explanation

1. **Main Menu**: Displays Figure/Exit options with screen clear
2. **Figure Menu**: TRIANGLE/SQUARE/RHOMBUS/TRAPEZIUM/RETURN with screen clear
3. **Input Screen**: Clears screen before asking for dimensions
4. **Calculations**: Computes area and perimeter for selected figure
5. **Continue Prompt**: Asks "Do you wish to continue (Y/N)?"

## 🎯 Key Concepts Covered

- Menu-driven programs
- Nested switch-case
- Screen clearing
- Geometric calculations
- Input validation
- Loop control with Y/N

## 🚀 Extensions

1. Add more figures
2. Add volume calculations for 3D shapes
3. Save calculation history
4. Add drawing functions
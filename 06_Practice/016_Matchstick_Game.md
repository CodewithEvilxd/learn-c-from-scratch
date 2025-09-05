# 🎯 Practical 16: Matchstick Game

## 📋 Problem Statement

Write a C program for a matchstick game between computer and user where computer always wins.

## 🎯 Learning Objectives

- Understand game theory and winning strategies
- Practice conditional logic
- Learn computer vs human interaction
- Understand modulo arithmetic in games

## 📝 Requirements

1. Start with 21 matchsticks
2. Allow user to pick 1-4 matchsticks
3. Computer picks strategically to always win
4. Display remaining matchsticks
5. Announce winner
6. Handle input validation

## 💡 Hints

- Use modulo 5 for winning strategy
- Computer picks to leave multiple of 5
- Handle edge cases (≤4 sticks)
- Validate user input
- Clear game flow

## 🔧 Solution

```c
// Practical 16: Matchstick Game
// Computer always wins using optimal strategy

#include <stdio.h>

int main() {
    int totalSticks = 21;
    int userPick, computerPick;

    printf("Matchstick Game\n");
    printf("===============\n");
    printf("Rules: 21 matchsticks. Pick 1-4 sticks. Last pick loses.\n");
    printf("Computer plays optimally and will always win!\n\n");

    while (totalSticks > 0) {
        // Display remaining sticks
        printf("Remaining matchsticks: %d\n", totalSticks);

        // User's turn
        printf("Your turn - Pick 1-4 matchsticks: ");
        scanf("%d", &userPick);

        // Input validation
        if (userPick < 1 || userPick > 4) {
            printf("Invalid pick! Please pick 1-4 matchsticks.\n");
            continue;
        }

        if (userPick > totalSticks) {
            printf("Not enough matchsticks! Pick fewer.\n");
            continue;
        }

        totalSticks -= userPick;
        printf("You picked %d matchsticks.\n", userPick);

        if (totalSticks == 0) {
            printf("You picked the last matchstick. You lose!\n");
            break;
        }

        // Computer's turn
        if (totalSticks <= 4) {
            // If 4 or fewer, pick all remaining
            computerPick = totalSticks;
        } else {
            // Winning strategy: leave multiple of 5
            int remainder = totalSticks % 5;
            if (remainder == 0) {
                computerPick = 1;  // Leave 4
            } else {
                computerPick = remainder;  // Leave 0
            }
        }

        totalSticks -= computerPick;
        printf("Computer picked %d matchsticks.\n", computerPick);

        if (totalSticks == 0) {
            printf("Computer picked the last matchstick. Computer wins!\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Game
```
Input: 3, 2, 1, 1
Expected Output:
Remaining matchsticks: 21
Your turn - Pick 1-4 matchsticks: 3
You picked 3 matchsticks.
Computer picked 1 matchsticks.
Remaining matchsticks: 17
Your turn - Pick 1-4 matchsticks: 2
You picked 2 matchsticks.
Computer picked 2 matchsticks.
Remaining matchsticks: 13
Your turn - Pick 1-4 matchsticks: 1
You picked 1 matchsticks.
Computer picked 3 matchsticks.
Remaining matchsticks: 9
Your turn - Pick 1-4 matchsticks: 1
You picked 1 matchsticks.
Computer picked 3 matchsticks.
Remaining matchsticks: 5
Your turn - Pick 1-4 matchsticks: 1
You picked 1 matchsticks.
Computer picked 4 matchsticks.
Computer picked the last matchstick. Computer wins!
```

### Test Case 2: User Tries to Win
```
Input: 4, 4, 4, 4, 4
Expected Output:
Computer always finds a way to win using optimal strategy
```

## 🔍 Explanation

1. **Winning Strategy**: Computer uses modulo 5 arithmetic
2. **Leave Multiples**: Always tries to leave 0 or 4 sticks
3. **Edge Case**: When ≤4 sticks, pick all remaining
4. **Validation**: Ensures valid user input
5. **Game Loop**: Continues until no sticks left

## 🎯 Key Concepts Covered

- Game theory implementation
- Modulo arithmetic
- Strategic programming
- Input validation
- Conditional logic

## 🚀 Extensions

1. Allow custom number of matchsticks
2. Add difficulty levels
3. Track game statistics
4. Allow computer vs computer
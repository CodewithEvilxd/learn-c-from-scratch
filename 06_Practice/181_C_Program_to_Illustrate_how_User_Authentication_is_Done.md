# 🎯 Practical 181: Illustrate User Authentication

## 📋 Problem Statement

C Program to Illustrate how User Authentication is Done.

## 🎯 Learning Objectives

- Understand authentication concepts
- Practice user credential management
- Learn password validation
- Understand security basics
- Practice user session management

## 📝 Requirements

1. Implement user registration
2. Implement user login
3. Store user credentials
4. Validate login attempts
5. Handle authentication failures

## 💡 Hints

- Use structures for user data
- Implement simple password storage
- Compare credentials for login
- Handle multiple users
- Provide authentication status

## 🔧 Solution

```c
// Practical 181: Illustrate User Authentication
// Demonstrates basic user authentication system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME 20
#define MAX_PASSWORD 20

struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int isActive;
};

struct User users[MAX_USERS];
int userCount = 0;

int registerUser(const char *username, const char *password) {
    // Check if user already exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 0; // User already exists
        }
    }

    // Check if we have space for new user
    if (userCount >= MAX_USERS) {
        return -1; // No space
    }

    // Add new user
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].isActive = 1;
    userCount++;

    return 1; // Success
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0 &&
            users[i].isActive) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void displayMenu() {
    printf("\nUser Authentication System\n");
    printf("==========================\n");
    printf("1. Register new user\n");
    printf("2. Login\n");
    printf("3. Display all users\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

int main() {
    int choice;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Register
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                int result = registerUser(username, password);
                if (result == 1) {
                    printf("User registered successfully!\n");
                } else if (result == 0) {
                    printf("Username already exists!\n");
                } else {
                    printf("Maximum users reached!\n");
                }
                break;

            case 2: // Login
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                if (authenticateUser(username, password)) {
                    printf("Login successful! Welcome %s\n", username);
                } else {
                    printf("Login failed! Invalid credentials.\n");
                }
                break;

            case 3: // Display users
                printf("\nRegistered Users:\n");
                printf("=================\n");
                for (int i = 0; i < userCount; i++) {
                    printf("Username: %s (Active: %s)\n",
                           users[i].username,
                           users[i].isActive ? "Yes" : "No");
                }
                if (userCount == 0) {
                    printf("No users registered yet.\n");
                }
                break;

            case 4: // Exit
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: User Registration and Login
```
Register: username: john, password: pass123
Login: username: john, password: pass123
Expected Output:
User registered successfully!
Login successful! Welcome john
```

### Test Case 2: Invalid Login
```
Login: username: john, password: wrongpass
Expected Output:
Login failed! Invalid credentials.
```

## 🔍 Explanation

1. **User Registration**: Store username and password
2. **Credential Storage**: Use array to store user data
3. **Authentication**: Compare login credentials
4. **Session Management**: Track active users
5. **Error Handling**: Handle invalid operations

## 🎯 Key Concepts Covered

- User credential management
- Authentication logic
- Data validation
- Security basics
- User session handling

## 🚀 Extensions

1. Add password encryption
2. Implement user roles
3. Add login attempt limits
4. Store users in file
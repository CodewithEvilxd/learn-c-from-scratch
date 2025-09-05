# 🎯 Practical 182: Shutdown Computer in Linux

## 📋 Problem Statement

C Program to Shutdown Computer in Linux.

## 🎯 Learning Objectives

- Understand system control in Linux
- Practice system command execution
- Learn shutdown procedures
- Understand system permissions
- Practice system programming

## 📝 Requirements

1. Implement shutdown functionality
2. Provide user options
3. Execute system commands
4. Handle permissions
5. Display status messages

## 💡 Hints

- Use system() function
- Execute shutdown commands
- Handle different shutdown options
- Check user permissions
- Provide confirmation

## 🔧 Solution

```c
// Practical 182: Shutdown Computer in Linux
// Demonstrates system shutdown using Linux commands

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void displayMenu() {
    printf("\nLinux System Control\n");
    printf("===================\n");
    printf("1. Shutdown immediately\n");
    printf("2. Shutdown with delay\n");
    printf("3. Restart system\n");
    printf("4. Cancel scheduled shutdown\n");
    printf("5. Check system status\n");
    printf("6. Exit\n");
    printf("Choice: ");
}

void executeCommand(const char *command, const char *description) {
    printf("Executing: %s\n", description);
    int result = system(command);

    if (result == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command failed or was cancelled.\n");
    }
}

int main() {
    int choice;
    int delay;

    // Check if running as root (recommended for shutdown)
    if (getuid() != 0) {
        printf("Warning: This program should be run as root for shutdown operations.\n");
        printf("Some operations may fail without proper permissions.\n\n");
    }

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Shutdown immediately
                printf("Warning: System will shutdown immediately!\n");
                printf("Press 'y' to confirm: ");
                getchar(); // Clear buffer
                if (getchar() == 'y') {
                    executeCommand("shutdown -h now", "System shutdown");
                } else {
                    printf("Shutdown cancelled.\n");
                }
                break;

            case 2: // Shutdown with delay
                printf("Enter delay in minutes: ");
                scanf("%d", &delay);
                if (delay < 0) delay = 0;
                printf("System will shutdown in %d minutes.\n", delay);
                printf("Press 'y' to confirm: ");
                getchar(); // Clear buffer
                if (getchar() == 'y') {
                    char command[50];
                    sprintf(command, "shutdown -h +%d", delay);
                    executeCommand(command, "Scheduled system shutdown");
                } else {
                    printf("Shutdown cancelled.\n");
                }
                break;

            case 3: // Restart system
                printf("Warning: System will restart!\n");
                printf("Press 'y' to confirm: ");
                getchar(); // Clear buffer
                if (getchar() == 'y') {
                    executeCommand("shutdown -r now", "System restart");
                } else {
                    printf("Restart cancelled.\n");
                }
                break;

            case 4: // Cancel shutdown
                executeCommand("shutdown -c", "Cancel scheduled shutdown");
                break;

            case 5: // Check status
                printf("System Status:\n");
                executeCommand("uptime", "System uptime");
                executeCommand("who", "Logged in users");
                break;

            case 6: // Exit
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

### Test Case 1: Immediate Shutdown
```
Choice: 1, Confirm: y
Expected Output:
Warning: System will shutdown immediately!
Executing: System shutdown
Command executed successfully.
```

### Test Case 2: Delayed Shutdown
```
Choice: 2, Delay: 5, Confirm: y
Expected Output:
System will shutdown in 5 minutes.
Executing: Scheduled system shutdown
Command executed successfully.
```

## 🔍 Explanation

1. **Menu System**: Provide shutdown options
2. **Command Execution**: Use system() for Linux commands
3. **User Confirmation**: Require confirmation for critical operations
4. **Permission Check**: Warn about root requirements
5. **Status Display**: Show command execution results

## 🎯 Key Concepts Covered

- System command execution
- Linux shutdown procedures
- User permission handling
- System control
- Command-line interface

## 🚀 Extensions

1. Add custom shutdown messages
2. Implement power-off options
3. Add system monitoring
4. Support different Linux distributions
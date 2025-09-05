# 🎯 Practical 166: System Shutdown/Sleep on Idle

## 📋 Problem Statement

Program to shut down/sleep a system if not component is being touched.

## 🎯 Learning Objectives

- Understand system control
- Practice idle detection
- Learn system commands
- Understand user activity monitoring
- Practice system programming

## 📝 Requirements

1. Monitor user activity
2. Detect idle periods
3. Implement timeout mechanism
4. Execute system commands
5. Handle shutdown/sleep options

## 💡 Hints

- Use GetLastInputInfo for Windows
- Implement timer mechanism
- Execute system commands
- Handle user permissions
- Provide configuration options

## 🔧 Solution

```c
// Practical 166: System Shutdown/Sleep on Idle
// Monitors user activity and shuts down/sleeps system when idle

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define IDLE_TIMEOUT_MINUTES 5
#define CHECK_INTERVAL_SECONDS 30

typedef enum {
    ACTION_SHUTDOWN,
    ACTION_SLEEP,
    ACTION_HIBERNATE
} IdleAction;

void executeSystemAction(IdleAction action) {
    switch (action) {
        case ACTION_SHUTDOWN:
            printf("Shutting down system...\n");
            system("shutdown /s /t 60 /c \"System shutting down due to inactivity\"");
            break;
        case ACTION_SLEEP:
            printf("Putting system to sleep...\n");
            SetSuspendState(FALSE, FALSE, FALSE);
            break;
        case ACTION_HIBERNATE:
            printf("Hibernating system...\n");
            SetSuspendState(TRUE, FALSE, FALSE);
            break;
    }
}

BOOL isUserActive() {
    LASTINPUTINFO lii;
    lii.cbSize = sizeof(LASTINPUTINFO);
    
    if (GetLastInputInfo(&lii)) {
        DWORD currentTick = GetTickCount();
        DWORD idleTime = currentTick - lii.dwTime;
        
        // Convert to minutes
        DWORD idleMinutes = idleTime / (1000 * 60);
        
        printf("System idle for %lu minutes\n", idleMinutes);
        
        return (idleMinutes < IDLE_TIMEOUT_MINUTES);
    }
    
    return TRUE; // Assume active if we can't get info
}

void displayMenu() {
    printf("System Idle Monitor\n");
    printf("===================\n");
    printf("1. Monitor with Shutdown\n");
    printf("2. Monitor with Sleep\n");
    printf("3. Monitor with Hibernate\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

int main() {
    int choice;
    IdleAction action;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        if (choice == 4) {
            break;
        }
        
        switch (choice) {
            case 1:
                action = ACTION_SHUTDOWN;
                printf("Monitoring for shutdown...\n");
                break;
            case 2:
                action = ACTION_SLEEP;
                printf("Monitoring for sleep...\n");
                break;
            case 3:
                action = ACTION_HIBERNATE;
                printf("Monitoring for hibernate...\n");
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        
        printf("Idle timeout: %d minutes\n", IDLE_TIMEOUT_MINUTES);
        printf("Check interval: %d seconds\n", CHECK_INTERVAL_SECONDS);
        printf("Press Ctrl+C to stop monitoring\n\n");
        
        // Monitoring loop
        while (1) {
            if (!isUserActive()) {
                printf("System idle timeout reached!\n");
                executeSystemAction(action);
                break;
            }
            
            Sleep(CHECK_INTERVAL_SECONDS * 1000); // Wait before next check
        }
        
        printf("Monitoring stopped.\n\n");
    }
    
    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Idle Detection
```
Expected: Monitor system activity and detect idle periods
```

### Test Case 2: System Action
```
Expected: Execute appropriate system action when idle timeout reached
```

## 🔍 Explanation

1. **Activity Monitoring**: Use Windows API to track user input
2. **Idle Detection**: Calculate time since last user activity
3. **Timeout Check**: Compare idle time with configured timeout
4. **System Action**: Execute shutdown, sleep, or hibernate
5. **User Control**: Allow user to choose action type

## 🎯 Key Concepts Covered

- System API usage
- Idle time calculation
- System control commands
- Timer implementation
- User activity monitoring

## 🚀 Extensions

1. Add custom timeout settings
2. Implement warning messages
3. Add activity logging
4. Support multiple platforms
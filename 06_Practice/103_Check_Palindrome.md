# 🎯 Practical 103: Check Palindrome

## 📋 Problem Statement

Write a program in C to check a string is palindrome or not.

## 🎯 Learning Objectives

- Understand palindrome concept
- Practice string reversal
- Learn two-pointer technique
- Understand character comparison
- Practice case sensitivity handling

## 📝 Requirements

1. Accept a string input
2. Check if it's a palindrome
3. Display result clearly
4. Handle case sensitivity
5. Show comparison process

## 💡 Hints

- Compare characters from start and end
- Use two pointers (start and end)
- Ignore case for comparison
- Handle spaces and punctuation
- Stop at middle of string

## 🔧 Solution

```c
// Practical 103: Check Palindrome
// Checks if a string is a palindrome

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters from left
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        
        // Skip non-alphanumeric characters from right
        while (left < right && !isalnum(str[right])) {
            right--;
        }
        
        // Compare characters (case insensitive)
        if (tolower(str[left]) != tolower(str[right])) {
            return 0;
        }
        
        left++;
        right--;
    }
    
    return 1;
}

int main() {
    char str[1000];

    printf("Check Palindrome\n");
    printf("================\n");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    printf("String: \"%s\"\n", str);

    if (isPalindrome(str)) {
        printf("✓ The string is a palindrome!\n");
    } else {
        printf("✗ The string is not a palindrome.\n");
    }

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Simple Palindrome
```
Input: radar
Expected Output:
String: "radar"
✓ The string is a palindrome!
```

### Test Case 2: Not a Palindrome
```
Input: hello
Expected Output:
String: "hello"
✗ The string is not a palindrome.
```

### Test Case 3: Palindrome with Spaces
```
Input: A man a plan a canal Panama
Expected Output:
String: "A man a plan a canal Panama"
✓ The string is a palindrome!
```

### Test Case 4: Single Character
```
Input: A
Expected Output:
String: "A"
✓ The string is a palindrome!
```

### Test Case 5: Empty String
```
Input: (empty)
Expected Output:
String: ""
✓ The string is a palindrome!
```

## 🔍 Explanation

1. **Two Pointers**: left and right pointers
2. **Skip Non-Alphanumeric**: Ignore spaces and punctuation
3. **Case Insensitive**: Convert to lowercase for comparison
4. **Middle Check**: Stop when pointers meet
5. **Character Comparison**: Check if characters match

## 🎯 Key Concepts Covered

- Palindrome definition
- Two-pointer technique
- Character validation
- Case conversion
- String traversal

## 🚀 Extensions

1. Check numeric palindromes
2. Find longest palindromic substring
3. Check sentence palindromes
4. Handle Unicode characters
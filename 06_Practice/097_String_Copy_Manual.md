# 🎯 Practical 97: Manual String Copy

## 📋 Problem Statement

Write a C program to copy string without using strcpy().

## 🎯 Learning Objectives

- Understand manual string copying
- Practice character-by-character copying
- Learn null termination handling
- Understand buffer management
- Practice loop implementation

## 📝 Requirements

1. Accept source string
2. Copy to destination manually
3. Handle null termination
4. Check buffer bounds
5. Compare with library function

## 💡 Hints

- Use loop to copy characters
- Copy until null terminator
- Ensure destination is large enough
- Add null terminator to destination
- Compare manual vs library copy

## 🔧 Solution

```c
// Practical 97: Manual String Copy
// Copies string without using strcpy() function

#include <stdio.h>
#include <string.h>

void manualStringCopy(char *dest, const char *src, size_t dest_size) {
    size_t i = 0;
    
    // Copy characters until null terminator or buffer limit
    while (src[i] != '\0' && i < dest_size - 1) {
        dest[i] = src[i];
        i++;
    }
    
    // Null terminate the destination
    dest[i] = '\0';
    
    // Check if source was truncated
    if (src[i] != '\0') {
        printf("Warning: Source string was truncated!\n");
    }
}

int main() {
    char source[100], destination_manual[100], destination_library[100];

    printf("Manual String Copy\n");
    printf("==================\n");

    printf("Enter a string to copy: ");
    fgets(source, sizeof(source), stdin);

    // Remove newline character if present
    if (source[strlen(source) - 1] == '\n') {
        source[strlen(source) - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", source);

    // Manual copy
    manualStringCopy(destination_manual, source, sizeof(destination_manual));
    printf("Manual copy: \"%s\"\n", destination_manual);

    // Library function copy
    strcpy(destination_library, source);
    printf("Library copy: \"%s\"\n", destination_library);

    // Verify results
    if (strcmp(destination_manual, destination_library) == 0) {
        printf("✓ Both copies are identical!\n");
    } else {
        printf("✗ Copies differ!\n");
    }

    // Show memory addresses
    printf("\nMemory Information:\n");
    printf("Source address: %p\n", source);
    printf("Manual destination: %p\n", destination_manual);
    printf("Library destination: %p\n", destination_library);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal String
```
Input: Hello World
Expected Output:
Original string: "Hello World"
Manual copy: "Hello World"
Library copy: "Hello World"
✓ Both copies are identical!
```

### Test Case 2: Empty String
```
Input: (empty)
Expected Output:
Original string: ""
Manual copy: ""
Library copy: ""
✓ Both copies are identical!
```

### Test Case 3: Single Character
```
Input: A
Expected Output:
Original string: "A"
Manual copy: "A"
Library copy: "A"
✓ Both copies are identical!
```

## 🔍 Explanation

1. **Manual Copy**: Loop through characters until null
2. **Buffer Check**: Prevent overflow
3. **Null Termination**: Properly terminate destination
4. **Library Comparison**: Use strcpy() for verification
5. **Result Validation**: Ensure identical copies

## 🎯 Key Concepts Covered

- Character-by-character copying
- Null termination handling
- Buffer overflow prevention
- String manipulation
- Memory addressing

## 🚀 Extensions

1. Copy with length limit
2. Copy until specific character
3. Reverse copy
4. Copy with case conversion
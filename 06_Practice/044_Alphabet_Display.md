# 🎯 Practical 44: Alphabet Display

## 📋 Problem Statement

Write a C program to display characters from A to Z using loop.

## 🎯 Learning Objectives

- Understand character data type
- Practice loop with characters
- Learn ASCII values
- Understand character arithmetic
- Practice formatted output

## 📝 Requirements

1. Display A to Z
2. Use loop
3. Format output
4. Show ASCII values
5. Handle case variations

## 💡 Hints

- Use char data type
- Loop from 'A' to 'Z'
- Use %c for character
- Use %d for ASCII
- Clear output

## 🔧 Solution

```c
// Practical 44: Alphabet Display
// Displays characters from A to Z

#include <stdio.h>

int main() {
    printf("Characters from A to Z:\n");
    printf("======================\n");

    // Display uppercase letters
    printf("Uppercase:\n");
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        printf("%c ", ch);
    }
    printf("\n\n");

    // Display with ASCII values
    printf("Character and ASCII values:\n");
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        printf("%c: %d\n", ch, ch);
    }
    printf("\n");

    // Display lowercase letters
    printf("Lowercase:\n");
    for (char ch = 'a'; ch <= 'z'; ch++) {
        printf("%c ", ch);
    }
    printf("\n");

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Uppercase
```
Expected Output:
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
```

### Test Case 2: With ASCII
```
Expected Output:
A: 65
B: 66
...
Z: 90
```

### Test Case 3: Lowercase
```
Expected Output:
a b c d e f g h i j k l m n o p q r s t u v w x y z
```

## 🔍 Explanation

1. **Character Loop**: for (char ch = 'A'; ch <= 'Z'; ch++)
2. **ASCII Values**: Characters are integers
3. **Uppercase**: 'A' to 'Z' (65-90)
4. **Lowercase**: 'a' to 'z' (97-122)
5. **Output**: Formatted display

## 🎯 Key Concepts Covered

- Character data type
- ASCII values
- Loop with characters
- Character arithmetic
- Formatted output

## 🚀 Extensions

1. Display Z to A
2. Show only vowels
3. Display with positions
4. Add user input range
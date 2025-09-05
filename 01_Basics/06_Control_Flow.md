# 🔀 Lesson 6: Control Flow in C
## Decision Making and Loops

---

## 🎯 Learning Objectives

- Master conditional statements (if-else, switch)
- Understand different types of loops
- Learn jump statements and their uses
- Create flowcharts for program logic
- Handle nested control structures

---

## 📖 What is Control Flow?

**Control flow** basically program mein statements ka execution order decide karta hai. C language mein conditions aur loops ke basis pe execution control karne ke liye kai constructs hain.

### **Control Flow ke Types**
1. **Conditional Statements** - Conditions ke basis pe code execute karna
2. **Loops** - Code ko repeat karna
3. **Jump Statements** - Program ke different parts mein control transfer karna

### **Control Flow ki Importance**
- **Decision Making**: Program ko smart decisions lene deta hai
- **Repetition**: Tedious tasks ko automate karta hai
- **Error Handling**: Runtime errors ko handle karna
- **Optimization**: Code efficiency improve karna

---

## ❓ Conditional Statements

### **1. if Statement**
```c
#include <stdio.h>

int main() {
    int age = 20;

    if (age >= 18) {
        printf("You are eligible to vote!\n");
    }

    return 0;
}
```

### **2. if-else Statement**
```c
#include <stdio.h>

int main() {
    int number = 10;

    if (number % 2 == 0) {
        printf("Even number\n");
    } else {
        printf("Odd number\n");
    }

    return 0;
}
```

### **3. if-else if-else Ladder**
```c
#include <stdio.h>

int main() {
    int marks = 85;

    if (marks >= 90) {
        printf("Grade: A\n");
    } else if (marks >= 80) {
        printf("Grade: B\n");
    } else if (marks >= 70) {
        printf("Grade: C\n");
    } else if (marks >= 60) {
        printf("Grade: D\n");
    } else {
        printf("Grade: F\n");
    }

    return 0;
}
```

### **4. Nested if Statements**
```c
#include <stdio.h>

int main() {
    int age = 25;
    int income = 50000;

    if (age >= 18) {
        if (income >= 30000) {
            printf("Eligible for premium loan\n");
        } else {
            printf("Eligible for regular loan\n");
        }
    } else {
        printf("Not eligible for loan\n");
    }

    return 0;
}
```

---

## 🔄 switch-case Statement

The switch statement provides multi-way selection based on the value of an expression.

### **Basic switch-case**
```c
#include <stdio.h>

int main() {
    int day = 3;

    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Invalid day\n");
    }

    return 0;
}
```

### **Multiple Cases (Fall-through)**
```c
#include <stdio.h>

int main() {
    char grade = 'B';

    switch (grade) {
        case 'A':
        case 'B':
        case 'C':
            printf("Passed\n");
            break;
        case 'D':
        case 'F':
            printf("Failed\n");
            break;
        default:
            printf("Invalid grade\n");
    }

    return 0;
}
```

### **switch with Expressions**
```c
#include <stdio.h>

int main() {
    int num = 15;

    switch (num % 3) {
        case 0:
            printf("Divisible by 3\n");
            break;
        case 1:
            printf("Remainder 1 when divided by 3\n");
            break;
        case 2:
            printf("Remainder 2 when divided by 3\n");
            break;
    }

    return 0;
}
```

### **Nested switch-case**
```c
#include <stdio.h>

int main() {
    int category = 1;
    int item = 2;

    switch (category) {
        case 1:  // Electronics
            switch (item) {
                case 1:
                    printf("Laptop\n");
                    break;
                case 2:
                    printf("Phone\n");
                    break;
                default:
                    printf("Unknown electronic item\n");
            }
            break;

        case 2:  // Clothing
            switch (item) {
                case 1:
                    printf("Shirt\n");
                    break;
                case 2:
                    printf("Pants\n");
                    break;
                default:
                    printf("Unknown clothing item\n");
            }
            break;

        default:
            printf("Unknown category\n");
    }

    return 0;
}
```

---

## 🔁 Loops in C

### **1. for Loop**
```c
#include <stdio.h>

int main() {
    // Basic for loop
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // Multiple variables
    for (int i = 0, j = 10; i < j; i++, j--) {
        printf("i=%d, j=%d\n", i, j);
    }

    // Infinite loop (use break to exit)
    for (;;) {
        printf("Infinite loop!\n");
        break;  // Exit condition
    }

    return 0;
}
```

### **2. while Loop**
```c
#include <stdio.h>

int main() {
    int i = 1;

    // Basic while loop
    while (i <= 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");

    // Sum of numbers using while
    int sum = 0, num = 1;
    while (num <= 10) {
        sum += num;
        num++;
    }
    printf("Sum: %d\n", sum);

    return 0;
}
```

### **3. do-while Loop**
```c
#include <stdio.h>

int main() {
    int i = 1;

    // do-while executes at least once
    do {
        printf("%d ", i);
        i++;
    } while (i <= 5);
    printf("\n");

    // Menu system example
    int choice;
    do {
        printf("1. Add\n2. Subtract\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Adding...\n");
                break;
            case 2:
                printf("Subtracting...\n");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}
```

---

## 🛑 Jump Statements

### **1. break Statement**
```c
#include <stdio.h>

int main() {
    // break in loop
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            break;  // Exit loop when i == 5
        }
        printf("%d ", i);
    }
    printf("\n");

    // break in switch
    int num = 2;
    switch (num) {
        case 1:
            printf("One\n");
            break;
        case 2:
            printf("Two\n");
            break;  // Exit switch
        case 3:
            printf("Three\n");
            break;
    }

    return 0;
}
```

### **2. continue Statement**
```c
#include <stdio.h>

int main() {
    // Skip even numbers
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip rest of loop body
        }
        printf("%d ", i);
    }
    printf("\n");

    // Skip negative numbers in sum
    int numbers[] = {1, -2, 3, -4, 5};
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        if (numbers[i] < 0) {
            continue;
        }
        sum += numbers[i];
    }
    printf("Sum of positive numbers: %d\n", sum);

    return 0;
}
```

### **3. goto Statement**
```c
#include <stdio.h>

int main() {
    int num = 10;

    if (num > 5) {
        goto label1;  // Jump to label1
    }

    printf("This won't be printed\n");

    label1:
    printf("Jumped to label1\n");

    // Error handling with goto
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        goto error;
    }

    // Process file
    fclose(file);
    goto success;

    error:
    printf("Error opening file\n");
    return 1;

    success:
    printf("File processed successfully\n");
    return 0;
}
```

### **4. return Statement**
```c
#include <stdio.h>

// Function with return
int add(int a, int b) {
    return a + b;  // Return sum
}

// Function with early return
int divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero!\n");
        return 0;  // Early return
    }
    return a / b;
}

int main() {
    int result = add(5, 3);
    printf("Sum: %d\n", result);

    int quotient = divide(10, 2);
    printf("Quotient: %d\n", quotient);

    return 0;  // Exit main function
}
```

---

## 📊 Loop Control Techniques

### **1. Nested Loops**
```c
#include <stdio.h>

int main() {
    // Multiplication table
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("%d\t", i * j);
        }
        printf("\n");
    }

    // Pattern printing
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}
```

### **2. Loop with break and continue**
```c
#include <stdio.h>

int main() {
    // Find first even number
    int numbers[] = {1, 3, 5, 6, 7, 8};
    int found = 0;

    for (int i = 0; i < 6; i++) {
        if (numbers[i] % 2 != 0) {
            continue;  // Skip odd numbers
        }
        printf("First even number: %d at index %d\n", numbers[i], i);
        found = 1;
        break;  // Exit after finding first even
    }

    if (!found) {
        printf("No even number found\n");
    }

    return 0;
}
```

### **3. Advanced Loop Techniques**

#### **Loop Unrolling (Performance Optimization)**
```c
#include <stdio.h>

// Normal loop
void normal_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("Normal sum: %d\n", sum);
}

// Unrolled loop (process 4 elements at a time)
void unrolled_sum(int arr[], int size) {
    int sum = 0;
    int i = 0;

    // Process 4 elements at a time
    for (i = 0; i <= size - 4; i += 4) {
        sum += arr[i] + arr[i+1] + arr[i+2] + arr[i+3];
    }

    // Handle remaining elements
    for (; i < size; i++) {
        sum += arr[i];
    }

    printf("Unrolled sum: %d\n", sum);
}
```

#### **Loop Fusion (Combining Multiple Loops)**
```c
#include <stdio.h>

void separate_loops(int arr1[], int arr2[], int result[], int size) {
    // Separate loops
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] * 2;
    }

    for (int i = 0; i < size; i++) {
        result[i] += arr2[i];
    }
}

void fused_loop(int arr1[], int arr2[], int result[], int size) {
    // Single fused loop (better cache performance)
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] * 2 + arr2[i];
    }
}
```

#### **Loop Inversion (Better Branch Prediction)**
```c
#include <stdio.h>

// Traditional loop
void traditional_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            printf("Found at index %d\n", i);
            return;
        }
    }
    printf("Not found\n");
}

// Loop inversion (better for branch prediction)
void inverted_search(int arr[], int size, int target) {
    int i = 0;
    while (i < size && arr[i] != target) {
        i++;
    }

    if (i < size) {
        printf("Found at index %d\n", i);
    } else {
        printf("Not found\n");
    }
}
```

#### **Duff's Device (Advanced Loop Unrolling)**
```c
#include <stdio.h>

// Duff's device for efficient copying
void duff_copy(char* to, char* from, int count) {
    int n = (count + 7) / 8;  // Number of iterations

    switch (count % 8) {
        case 0: do { *to++ = *from++;
        case 7:      *to++ = *from++;
        case 6:      *to++ = *from++;
        case 5:      *to++ = *from++;
        case 4:      *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
                } while (--n > 0);
    }
}
```

---

## 🔄 Infinite Loops

### **Common Infinite Loop Patterns**
```c
#include <stdio.h>

int main() {
    // Method 1: for loop
    // for (;;) {
    //     printf("Infinite loop!\n");
    // }

    // Method 2: while loop
    // while (1) {
    //     printf("Infinite loop!\n");
    // }

    // Method 3: do-while loop
    // do {
    //     printf("Infinite loop!\n");
    // } while (1);

    // Practical use: Server loop
    int running = 1;
    int counter = 0;

    while (running) {
        counter++;
        printf("Counter: %d\n", counter);

        if (counter >= 10) {
            running = 0;  // Exit condition
        }
    }

    return 0;
}
```

---

## 📈 Flowcharts aur Advanced Control Flow

### **Basic Flowcharts**

#### **if-else Flowchart**
```
Start
  │
  ▼
 ┌─────────────┐
 │  Condition  │
 └─────┬───────┘
       │
   ┌───▼───┐
   │ True  │
   └─┬─────┘
     │
 ┌───▼───┐     ┌─────────────┐
 │Execute│     │   False     │
 │Block A │     │   Block B  │
 └───────┘     └─────────────┘
     │               │
     └──────┬────────┘
            │
           End
```

#### **for Loop Flowchart**
```
Start
  │
  ▼
 ┌─────────────────┐
 │Initialization   │
 └─────┬───────────┘
       │
   ┌───▼───┐
   │Condition│
   └─┬─────┬┘
     │     │
 ┌───▼───┐ │
 │Execute│ │
 │ Body  │ │
 └───────┘ │
     │     │
 ┌───▼───┐ │
 │Update │ │
 └───────┘ │
     │     │
     └─────┘
       │
      End
```

### **Advanced Flowcharts**

#### **Complex Decision Tree Flowchart**
```
Start
  │
  ▼
 ┌─────────────┐
 │  Input > 0  │
 └─────┬───────┘
       │
   ┌───▼───┐
   │  Yes  │
   └─┬─────┘
     │
 ┌───▼───┐     ┌─────────────┐
 │Input <│     │   Input =   │
 │  100   │     │     0      │
 └─┬─────┘     └─────┬───────┘
   │                 │
   ▼                 ▼
 ┌─────┐     ┌─────┐     ┌─────┐
 │Small│     │Zero │     │Large│
 └─────┘     └─────┘     └─────┘
   │           │           │
   └─────┬─────┬─────┘
         │
        End
```

#### **State Machine Flowchart**
```
 ┌─────────────┐
 │   State A   │ ◄─────────────────┐
 └─────┬───────┘                   │
       │                           │
   ┌───▼───┐                       │
   │Event X│                       │
   └─┬─────┬┘                       │
     │     │                         │
 ┌───▼───┐ │                     ┌───▼───┐
 │State B│ │                     │State C│
 └───────┘ │                     └───────┘
     │     │                         │
 ┌───▼───┐ │                     ┌───▼───┐
 │Event Y│ │                     │Event Z│
 └─┬─────┬┘                     └─┬─────┬┘
   │     │                         │     │
   └─────┼─────────────────────────┼─────┘
        │                         │
        └─────────────────────────┘
                 │
              ┌───▼───┐
              │ State D│
              └────────┘
```

#### **Error Handling Flowchart**
```
Start
  │
  ▼
 ┌─────────────┐
 │  Operation  │
 └─────┬───────┘
       │
   ┌───▼───┐
   │Success│
   └─┬─────┘
     │
 ┌───▼───┐     ┌─────────────┐
 │Process│     │   Error     │
 │Result │     │  Occurred   │
 └───────┘     └─────┬───────┘
     │               │
 ┌───▼───┐     ┌─────▼─────┐
 │Cleanup│     │  Log Error │
 └───────┘     └─────┬─────┘
     │               │
 ┌───▼───┐     ┌─────▼─────┐
 │Return │     │Retry Logic│
 │Success│     └─────┬─────┘
 └───────┘           │
                 ┌───▼───┐
                 │ Max    │
                 │Retries │
                 └─┬─────┬┘
                   │     │
               ┌───▼───┐ │
               │Return │ │
               │Failure│ │
               └───────┘ │
                   │     │
                   └─────┘
                     │
                    End
```

### **Control Flow Optimization Techniques**

#### **1. Branch Prediction Optimization**
```c
#include <stdio.h>

// Poor branch prediction (random pattern)
void poor_prediction(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {  // Random true/false
            arr[i] *= 2;
        }
    }
}

// Better branch prediction (predictable pattern)
void good_prediction(int arr[], int size) {
    // Process positive numbers first
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            arr[i] *= 2;
        }
    }

    // Then process non-positive numbers
    for (int i = 0; i < size; i++) {
        if (arr[i] <= 0) {
            arr[i] = 0;
        }
    }
}
```

#### **2. Loop Interchange (Cache Optimization)**
```c
#include <stdio.h>
#define ROWS 1000
#define COLS 1000

// Poor cache performance (column-major access)
void poor_cache(int matrix[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            matrix[i][j] *= 2;
        }
    }
}

// Better cache performance (row-major access)
void good_cache(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] *= 2;
        }
    }
}
```

#### **3. Early Exit Optimization**
```c
#include <stdio.h>

// Without early exit
int search_without_early_exit(int arr[], int size, int target) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            found = 1;
            // Continue searching unnecessarily
        }
    }
    return found;
}

// With early exit
int search_with_early_exit(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return 1;  // Early exit
        }
    }
    return 0;
}
```

#### **4. Switch-case Optimization**
```c
#include <stdio.h>

// Poor switch-case (scattered cases)
void poor_switch(int value) {
    switch (value) {
        case 100: printf("Hundred\n"); break;
        case 1: printf("One\n"); break;
        case 50: printf("Fifty\n"); break;
        case 10: printf("Ten\n"); break;
        default: printf("Other\n");
    }
}

// Optimized switch-case (grouped cases)
void optimized_switch(int value) {
    switch (value) {
        case 1: printf("One\n"); break;
        case 10: printf("Ten\n"); break;
        case 50: printf("Fifty\n"); break;
        case 100: printf("Hundred\n"); break;
        default: printf("Other\n");
    }
}
```

---

## 🎯 Best Practices

### **1. Use Braces for Single Statements**
```c
// ✅ Always use braces
if (condition) {
    statement1;
    statement2;
}

// ❌ Avoid omitting braces
if (condition)
    statement1;  // Can cause bugs
    statement2;  // This executes regardless of condition
```

### **2. Avoid Deep Nesting**
```c
// ✅ Flat structure
if (!condition1) {
    return;
}
if (!condition2) {
    return;
}
// Process data

// ❌ Deep nesting (hard to read)
if (condition1) {
    if (condition2) {
        if (condition3) {
            // Deep nesting
        }
    }
}
```

### **3. Use Meaningful Loop Variables**
```c
// ✅ Descriptive names
for (int studentIndex = 0; studentIndex < numStudents; studentIndex++) {
    // Process student
}

// ❌ Generic names
for (int i = 0; i < n; i++) {
    // What does i represent?
}
```

### **4. Avoid goto (Generally)**
```c
// ✅ Structured approach
int process_data() {
    if (validate_input() != SUCCESS) {
        return ERROR;
    }
    if (process_data() != SUCCESS) {
        return ERROR;
    }
    return SUCCESS;
}

// ❌ goto usage (hard to follow)
int process_data() {
    if (validate_input() != SUCCESS) {
        goto error;
    }
    if (process_data() != SUCCESS) {
        goto error;
    }
    return SUCCESS;

    error:
    return ERROR;
}
```

---

## 🐛 Common Mistakes

### **1. Missing Break in switch**
```c
// Wrong: fall-through without break
switch (grade) {
    case 'A':
        printf("Excellent\n");
    case 'B':  // This will execute even if grade is 'A'
        printf("Good\n");
        break;
}

// Correct
switch (grade) {
    case 'A':
        printf("Excellent\n");
        break;
    case 'B':
        printf("Good\n");
        break;
}
```

### **2. Off-by-One Errors in Loops**
```c
int arr[5] = {1, 2, 3, 4, 5};

// Wrong: accesses arr[5] which is out of bounds
for (int i = 0; i <= 5; i++) {
    printf("%d ", arr[i]);
}

// Correct
for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
}
```

### **3. Semicolon After if/while**
```c
// Wrong: empty statement after if
if (condition); {  // Semicolon creates empty statement
    printf("This always executes\n");
}

// Correct
if (condition) {
    printf("This executes only if condition is true\n");
}
```

### **4. Infinite Loops**
```c
// Wrong: missing increment
int i = 0;
while (i < 10) {
    printf("%d ", i);
    // Forgot i++
}

// Correct
int i = 0;
while (i < 10) {
    printf("%d ", i);
    i++;
}
```

---

## 📝 Practice Exercises

### **Exercise 1: Conditional Statements**
Write a program that:
- Takes a number as input
- Checks if it's positive, negative, or zero
- Prints appropriate message

### **Exercise 2: switch-case Calculator**
Create a calculator using switch-case that:
- Takes two numbers and an operator (+, -, *, /)
- Performs the operation
- Handles division by zero

### **Exercise 3: Loop Patterns**
Write programs to print:
- Numbers from 1 to 100
- Even numbers between 1 and 50
- Multiplication table for a given number
- Sum of first N natural numbers

### **Exercise 4: Nested Loops**
Create programs for:
- Printing star patterns (triangle, diamond)
- Matrix operations
- Finding prime numbers
- Generating calendar

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What is the output of this code?
```c
int x = 5;
if (x > 3)
    printf("A");
    printf("B");
```
a) A
b) B
c) AB
d) Nothing

### **Question 2:**
Which loop is guaranteed to execute at least once?
a) for loop
b) while loop
c) do-while loop
d) None of the above

### **Question 3:**
What happens if you forget `break` in switch-case?
a) Compilation error
b) Runtime error
c) Fall-through to next case
d) Program terminates

### **Question 4:**
Which statement is used to skip the current iteration of a loop?
a) break
b) continue
c) return
d) goto

### **Question 5:**
What is the correct syntax for an infinite loop?
a) `for (;;) { }`
b) `while (1) { }`
c) `do { } while (1);`
d) All of the above

---

## 🔗 Additional Resources

### **Flowchart Tools**
- [Draw.io](https://www.draw.io/) - Free flowchart maker
- [Lucidchart](https://www.lucidchart.com/) - Professional diagrams
- [Mermaid](https://mermaid-js.github.io/) - Text-based diagrams

### **Further Reading**
- [Control Flow](https://en.cppreference.com/w/c/language/statements)
- [Loop Statements](https://en.cppreference.com/w/c/language/statements#Iteration_statements)
- [Selection Statements](https://en.cppreference.com/w/c/language/statements#Selection_statements)

---

## 🎯 Next Steps

**Great job!** You've mastered:
- ✅ Conditional statements (if-else, switch)
- ✅ Different types of loops
- ✅ Jump statements and their uses
- ✅ Nested control structures
- ✅ Flowchart creation

**Next Lesson Preview:**
- Functions and modular programming
- Function declaration, definition, and calls
- Parameter passing (pass by value, pass by reference)
- Recursion and recursive functions

---

**🚀 Ready to create functions?**

[⬅️ Previous: Operators](05_Operators.md) | [Next: Functions ➡️](07_Functions.md)
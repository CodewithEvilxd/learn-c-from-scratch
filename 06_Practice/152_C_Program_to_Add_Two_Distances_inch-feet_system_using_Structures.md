# 🎯 Practical 152: Add Two Distances (inch-feet system) using Structures

## 📋 Problem Statement

C Program to Add Two Distances (in inch-feet system) using Structures.

## 🎯 Learning Objectives

- Understand structure for distance
- Practice data organization
- Learn distance addition logic
- Understand carry-over in measurements
- Practice structured programming

## 📝 Requirements

1. Define a distance structure
2. Accept two distances
3. Add distances with carry-over
4. Display result
5. Handle inch to feet conversion

## 💡 Hints

- Define struct with feet and inches
- Add inches first, handle carry
- Add feet with carry from inches
- Use 12 inches = 1 foot
- Display formatted result

## 🔧 Solution

```c
// Practical 152: Add Two Distances (inch-feet system) using Structures
// Demonstrates adding distances with proper carry-over

#include <stdio.h>

struct Distance {
    int feet;
    int inches;
};

struct Distance addDistances(struct Distance d1, struct Distance d2) {
    struct Distance result;
    
    // Add inches
    result.inches = d1.inches + d2.inches;
    
    // Convert excess inches to feet
    result.feet = d1.feet + d2.feet + (result.inches / 12);
    result.inches = result.inches % 12;
    
    return result;
}

int main() {
    struct Distance dist1, dist2, sum;

    printf("Add Two Distances (inch-feet system)\n");
    printf("=====================================\n");

    printf("Enter first distance:\n");
    printf("Feet: ");
    scanf("%d", &dist1.feet);
    printf("Inches: ");
    scanf("%d", &dist1.inches);

    printf("\nEnter second distance:\n");
    printf("Feet: ");
    scanf("%d", &dist2.feet);
    printf("Inches: ");
    scanf("%d", &dist2.inches);

    sum = addDistances(dist1, dist2);

    printf("\nDistance 1: %d feet %d inches\n", dist1.feet, dist1.inches);
    printf("Distance 2: %d feet %d inches\n", dist2.feet, dist2.inches);
    printf("Sum: %d feet %d inches\n", sum.feet, sum.inches);

    return 0;
}
```

## 📊 Test Cases

### Test Case 1: Normal Addition
```
Input: Distance 1: 5 feet 8 inches, Distance 2: 3 feet 9 inches
Expected Output:
Distance 1: 5 feet 8 inches
Distance 2: 3 feet 9 inches
Sum: 9 feet 5 inches
```

### Test Case 2: Carry Over
```
Input: Distance 1: 4 feet 10 inches, Distance 2: 2 feet 8 inches
Expected Output:
Distance 1: 4 feet 10 inches
Distance 2: 2 feet 8 inches
Sum: 7 feet 6 inches
```

### Test Case 3: Large Carry
```
Input: Distance 1: 1 feet 11 inches, Distance 2: 1 feet 11 inches
Expected Output:
Distance 1: 1 feet 11 inches
Distance 2: 1 feet 11 inches
Sum: 3 feet 10 inches
```

## 🔍 Explanation

1. **Structure Definition**: Define Distance struct with feet and inches
2. **Input Reading**: Read two distances from user
3. **Addition Logic**: Add inches first, handle carry to feet
4. **Carry Handling**: Convert excess inches to feet (12 inches = 1 foot)
5. **Result Display**: Show formatted distance sum

## 🎯 Key Concepts Covered

- Structure definition
- Distance arithmetic
- Carry-over logic
- Unit conversion
- Structured data handling

## 🚀 Extensions

1. Subtract distances
2. Multiply distance by scalar
3. Compare distances
4. Convert to other units
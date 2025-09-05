# 🎯 Assignment 1.14: Enumerations and Typedef

## 📋 Problem Statement

Create a C program that demonstrates enumerations and typedef usage. Implement a traffic light system, card game, and state machine using enumerations with typedef for better code organization.

## 🎯 Learning Objectives

- Understand enumeration declaration and usage
- Learn typedef for type aliases
- Practice enum with switch statements
- Implement state machines with enums
- Use typedef with structures and function pointers
- Understand enum scoping and values

## 📝 Requirements

1. Define enumerations for different scenarios
2. Use typedef to create type aliases
3. Implement traffic light state machine
4. Create card game with enum suits and ranks
5. Demonstrate enum iteration
6. Handle enum input/output
7. Use typedef with complex types

## 💡 Hints

- Enums provide named constants
- Typedef creates aliases for existing types
- Enum values start from 0 by default
- Use meaningful names for enum constants
- Typedef improves code readability

## 🔧 Solution

```c
// Assignment 1.14: Enumerations and Typedef
// Demonstrating enums and type aliases

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Basic enumerations
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

typedef enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} DayOfWeek;

// Traffic light system
typedef enum {
    TRAFFIC_RED,
    TRAFFIC_YELLOW,
    TRAFFIC_GREEN
} TrafficLightState;

typedef struct {
    TrafficLightState current_state;
    int duration;  // seconds
} TrafficLight;

// Card game enumerations
typedef enum {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} Suit;

typedef enum {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

// State machine for vending machine
typedef enum {
    VM_IDLE,
    VM_WAITING_PAYMENT,
    VM_DISPENSING,
    VM_OUT_OF_ORDER
} VendingMachineState;

typedef struct {
    VendingMachineState state;
    int balance;
    int selected_item;
} VendingMachine;

// Function prototypes
const char* color_to_string(Color color);
const char* day_to_string(DayOfWeek day);
const char* traffic_light_to_string(TrafficLightState state);
const char* suit_to_string(Suit suit);
const char* rank_to_string(Rank rank);

void demonstrate_basic_enums();
void demonstrate_traffic_light();
void demonstrate_card_game();
void demonstrate_vending_machine();
void demonstrate_typedef_complex();

// Complex typedef examples
typedef int (*MathOperation)(int, int);
typedef void (*PrintFunction)(const char*);

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

void print_upper(const char* str) {
    while (*str) {
        putchar(toupper(*str));
        str++;
    }
    putchar('\n');
}

void print_lower(const char* str) {
    while (*str) {
        putchar(tolower(*str));
        str++;
    }
    putchar('\n');
}

int main() {
    printf("=== Enumerations and Typedef Demonstration ===\n\n");

    demonstrate_basic_enums();
    demonstrate_traffic_light();
    demonstrate_card_game();
    demonstrate_vending_machine();
    demonstrate_typedef_complex();

    return 0;
}

void demonstrate_basic_enums() {
    printf("1. Basic Enumerations\n");

    Color favorite_color = BLUE;
    DayOfWeek today = WEDNESDAY;

    printf("Favorite color: %s\n", color_to_string(favorite_color));
    printf("Today is: %s\n", day_to_string(today));

    // Enum iteration
    printf("Days of the week:\n");
    for (DayOfWeek day = MONDAY; day <= SUNDAY; day++) {
        printf("  %s\n", day_to_string(day));
    }

    printf("\n");
}

void demonstrate_traffic_light() {
    printf("2. Traffic Light System\n");

    TrafficLight light = {TRAFFIC_RED, 30};

    printf("Current state: %s\n", traffic_light_to_string(light.current_state));
    printf("Duration: %d seconds\n", light.duration);

    // State transitions
    printf("State transitions:\n");
    TrafficLightState states[] = {TRAFFIC_RED, TRAFFIC_YELLOW, TRAFFIC_GREEN};
    int durations[] = {30, 5, 25};

    for (int i = 0; i < 3; i++) {
        light.current_state = states[i];
        light.duration = durations[i];
        printf("  %s: %d seconds\n",
               traffic_light_to_string(light.current_state),
               light.duration);
    }

    printf("\n");
}

void demonstrate_card_game() {
    printf("3. Card Game\n");

    Card deck[52];
    int card_index = 0;

    // Create deck
    for (Suit suit = CLUBS; suit <= SPADES; suit++) {
        for (Rank rank = ACE; rank <= KING; rank++) {
            deck[card_index].suit = suit;
            deck[card_index].rank = rank;
            card_index++;
        }
    }

    // Display some cards
    printf("Sample cards:\n");
    for (int i = 0; i < 5; i++) {
        Card card = deck[i];
        printf("  %s of %s\n",
               rank_to_string(card.rank),
               suit_to_string(card.suit));
    }

    // Find specific card
    Card search_card = {HEARTS, ACE};
    printf("Looking for: %s of %s\n",
           rank_to_string(search_card.rank),
           suit_to_string(search_card.suit));

    for (int i = 0; i < 52; i++) {
        if (deck[i].suit == search_card.suit &&
            deck[i].rank == search_card.rank) {
            printf("Found at position %d\n", i);
            break;
        }
    }

    printf("\n");
}

void demonstrate_vending_machine() {
    printf("4. Vending Machine State Machine\n");

    VendingMachine vm = {VM_IDLE, 0, 0};

    printf("Initial state: %d\n", vm.state);

    // Simulate state transitions
    vm.state = VM_WAITING_PAYMENT;
    vm.selected_item = 1;
    vm.balance = 50;
    printf("Selected item %d, inserted $%d\n", vm.selected_item, vm.balance);

    if (vm.balance >= 75) {  // Assume item costs $75
        vm.state = VM_DISPENSING;
        printf("Dispensing item...\n");
        vm.balance -= 75;
        vm.state = VM_IDLE;
        printf("Change: $%d\n", vm.balance);
    } else {
        printf("Insufficient payment\n");
    }

    printf("\n");
}

void demonstrate_typedef_complex() {
    printf("5. Complex Typedef Usage\n");

    // Function pointer typedef
    MathOperation operations[] = {add, multiply};
    const char* op_names[] = {"Addition", "Multiplication"};

    for (int i = 0; i < 2; i++) {
        int result = operations[i](10, 5);
        printf("%s: 10 ? 5 = %d\n", op_names[i], result);
    }

    // Print function typedef
    PrintFunction printers[] = {print_upper, print_lower};
    const char* printer_names[] = {"Uppercase", "Lowercase"};

    const char* test_string = "Hello World";

    for (int i = 0; i < 2; i++) {
        printf("%s: ", printer_names[i]);
        printers[i](test_string);
    }

    printf("\n");
}

// String conversion functions
const char* color_to_string(Color color) {
    switch (color) {
        case RED: return "Red";
        case GREEN: return "Green";
        case BLUE: return "Blue";
        default: return "Unknown";
    }
}

const char* day_to_string(DayOfWeek day) {
    switch (day) {
        case MONDAY: return "Monday";
        case TUESDAY: return "Tuesday";
        case WEDNESDAY: return "Wednesday";
        case THURSDAY: return "Thursday";
        case FRIDAY: return "Friday";
        case SATURDAY: return "Saturday";
        case SUNDAY: return "Sunday";
        default: return "Unknown";
    }
}

const char* traffic_light_to_string(TrafficLightState state) {
    switch (state) {
        case TRAFFIC_RED: return "Red";
        case TRAFFIC_YELLOW: return "Yellow";
        case TRAFFIC_GREEN: return "Green";
        default: return "Unknown";
    }
}

const char* suit_to_string(Suit suit) {
    switch (suit) {
        case CLUBS: return "Clubs";
        case DIAMONDS: return "Diamonds";
        case HEARTS: return "Hearts";
        case SPADES: return "Spades";
        default: return "Unknown";
    }
}

const char* rank_to_string(Rank rank) {
    switch (rank) {
        case ACE: return "Ace";
        case TWO: return "Two";
        case THREE: return "Three";
        case FOUR: return "Four";
        case FIVE: return "Five";
        case SIX: return "Six";
        case SEVEN: return "Seven";
        case EIGHT: return "Eight";
        case NINE: return "Nine";
        case TEN: return "Ten";
        case JACK: return "Jack";
        case QUEEN: return "Queen";
        case KING: return "King";
        default: return "Unknown";
    }
}
```

## 📊 Test Cases

### Test Case 1: Basic Enums
```
Expected Output:
Favorite color: Blue
Today is: Wednesday
Days of the week:
  Monday
  Tuesday
  ...
  Sunday
```

### Test Case 2: Traffic Light
```
Expected Output:
Current state: Red
Duration: 30 seconds
State transitions:
  Red: 30 seconds
  Yellow: 5 seconds
  Green: 25 seconds
```

### Test Case 3: Card Game
```
Expected Output:
Sample cards:
  Ace of Clubs
  Two of Clubs
  Three of Clubs
  Four of Clubs
  Five of Clubs
Looking for: Ace of Hearts
Found at position 26
```

### Test Case 4: Function Pointers
```
Expected Output:
Addition: 10 + 5 = 15
Multiplication: 10 * 5 = 50
Uppercase: HELLO WORLD
Lowercase: hello world
```

## 🔍 Explanation

1. **Enumeration Declaration**: `enum { RED, GREEN, BLUE } Color;`
2. **Typedef**: `typedef enum { ... } Color;` creates alias
3. **Enum Values**: Start from 0 unless specified
4. **Switch with Enums**: Clean state machine implementation
5. **Function Pointers**: Typedef for function signatures
6. **Complex Types**: Typedef with structures and pointers

## 🎯 Key Concepts Covered

- Enumeration declaration and usage
- Typedef for type aliases
- State machines with enums
- Function pointer typedefs
- Enum iteration and conversion
- Complex type definitions

## 🚀 Extensions

1. Add enum with custom values
2. Implement enum serialization/deserialization
3. Create a more complex state machine
4. Add enum validation and bounds checking
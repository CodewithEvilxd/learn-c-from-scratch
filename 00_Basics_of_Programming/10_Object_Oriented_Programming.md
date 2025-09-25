# 10. Object-Oriented Programming - Comprehensive Guide to OOP Principles and Design Patterns

## Introduction

Object-Oriented Programming (OOP) is a fundamental programming paradigm that revolutionized software development by organizing code around objects rather than functions and logic. OOP models real-world entities and their interactions, creating programs that are more modular, flexible, maintainable, and scalable. This comprehensive chapter explores OOP concepts, design patterns, advanced techniques, and real-world applications.

## What is Object-Oriented Programming? - Deep Analysis

OOP is a programming methodology that uses objects and classes as the primary building blocks of software systems. It emerged in the 1960s with Simula and became mainstream with languages like Smalltalk, C++, and Java.

### Core Principles of OOP

1. **Objects**: Instances of classes that represent real-world entities with state and behavior
2. **Classes**: Blueprints or templates for creating objects, defining properties and methods
3. **Encapsulation**: Bundling data and methods within a single unit, hiding internal implementation
4. **Inheritance**: Creating new classes from existing ones, establishing hierarchical relationships
5. **Polymorphism**: Ability of objects to take multiple forms, enabling dynamic method dispatch
6. **Abstraction**: Focusing on essential features while hiding unnecessary implementation details

### Benefits of Object-Oriented Programming

- **Modularity**: Code organized into independent, reusable components
- **Maintainability**: Easier to modify and extend existing code
- **Reusability**: Classes and objects can be reused across projects
- **Scalability**: Large systems can be built by composing smaller objects
- **Real-world Modeling**: Natural representation of real-world entities
- **Data Security**: Encapsulation protects data integrity
- **Team Development**: Multiple developers can work on different classes simultaneously

### OOP vs Procedural Programming

| Aspect | Procedural Programming | Object-Oriented Programming |
|--------|----------------------|----------------------------|
| Focus | Functions and procedures | Objects and their interactions |
| Data | Global variables | Encapsulated in objects |
| Code Organization | Functions grouped by functionality | Classes with related data/methods |
| Reusability | Function libraries | Class inheritance and composition |
| Maintenance | Harder to modify | Easier with encapsulation |
| Real-world Modeling | Abstract functions | Natural object relationships |

## Classes and Objects - The Building Blocks of OOP

### Understanding Classes

A class is a blueprint or template that defines the structure and behavior of objects. It encapsulates data (attributes/properties) and functions (methods) that operate on that data.

#### Class Components

1. **Attributes/Properties**: Data members that store object state
2. **Methods**: Functions that define object behavior
3. **Constructor**: Special method called when creating objects
4. **Destructor**: Method called when objects are destroyed (in some languages)

#### Class Definition Syntax

**Python:**
```python
class ClassName:
    """Docstring describing the class."""
    
    # Class attributes (shared by all instances)
    class_attribute = "shared_value"
    
    def __init__(self, parameter1, parameter2):
        """Constructor - initializes object state."""
        self.instance_attribute1 = parameter1
        self.instance_attribute2 = parameter2
    
    def instance_method(self):
        """Instance method - operates on instance data."""
        return f"{self.instance_attribute1} {self.instance_attribute2}"
    
    @classmethod
    def class_method(cls):
        """Class method - operates on class data."""
        return cls.class_attribute
    
    @staticmethod
    def static_method():
        """Static method - utility function."""
        return "Static method called"
```

**Java:**
```java
public class ClassName {
    // Instance variables
    private String instanceVariable;
    private int number;
    
    // Class variables (static)
    private static int objectCount = 0;
    
    // Constructor
    public ClassName(String instanceVariable, int number) {
        this.instanceVariable = instanceVariable;
        this.number = number;
        objectCount++;
    }
    
    // Instance methods
    public String getInstanceVariable() {
        return instanceVariable;
    }
    
    public void setInstanceVariable(String instanceVariable) {
        this.instanceVariable = instanceVariable;
    }
    
    // Class method
    public static int getObjectCount() {
        return objectCount;
    }
    
    // Static method
    public static String utilityMethod() {
        return "Utility method";
    }
}
```

### Understanding Objects

An object is a concrete instance of a class. It has its own state (attribute values) and can perform actions defined by its class methods.

#### Object Characteristics

1. **Identity**: Unique identifier distinguishing it from other objects
2. **State**: Current values of its attributes
3. **Behavior**: Methods it can perform

#### Object Creation and Usage

**Python:**
```python
# Creating objects (instances)
car1 = Car("Toyota", "Camry", 2020)
car2 = Car("Honda", "Civic", 2019)

# Accessing attributes
print(car1.make)    # Toyota
print(car2.year)    # 2019

# Calling methods
car1.accelerate(30)
print(car1.speed)   # 30

# Checking object identity
print(id(car1))     # Unique memory address
print(car1 is car2) # False - different objects

# Object comparison
car3 = Car("Toyota", "Camry", 2020)
print(car1 == car3) # Depends on __eq__ method implementation
```

**Java:**
```java
// Creating objects
Car car1 = new Car("Toyota", "Camry", 2020);
Car car2 = new Car("Honda", "Civic", 2019);

// Accessing attributes (through methods)
System.out.println(car1.getMake());  // Toyota

// Calling methods
car1.accelerate(30);
System.out.println(car1.getSpeed()); // 30

// Object comparison
Car car3 = new Car("Toyota", "Camry", 2020);
System.out.println(car1 == car3);    // false (different references)
System.out.println(car1.equals(car3)); // depends on equals() implementation
```

### Advanced Class Features

#### Class Variables vs Instance Variables

```python
class Employee:
    # Class variable - shared by all instances
    company_name = "Tech Corp"
    total_employees = 0
    
    def __init__(self, name, salary):
        # Instance variables - unique to each instance
        self.name = name
        self.salary = salary
        Employee.total_employees += 1
    
    def get_info(self):
        return f"{self.name} works at {Employee.company_name}, salary: ${self.salary}"
    
    @classmethod
    def change_company_name(cls, new_name):
        cls.company_name = new_name
    
    @classmethod
    def get_total_employees(cls):
        return cls.total_employees

# Usage
emp1 = Employee("Alice", 75000)
emp2 = Employee("Bob", 80000)

print(Employee.company_name)      # Tech Corp
print(emp1.company_name)          # Tech Corp (accessed via instance)
print(Employee.total_employees)   # 2

Employee.change_company_name("Innovate Ltd")
print(emp1.company_name)          # Innovate Ltd (changed for all instances)
```

#### Property Decorators (Python)

```python
class Temperature:
    def __init__(self, celsius=0):
        self._celsius = celsius
    
    @property
    def celsius(self):
        """Getter for celsius."""
        return self._celsius
    
    @celsius.setter
    def celsius(self, value):
        """Setter for celsius with validation."""
        if value < -273.15:
            raise ValueError("Temperature cannot be below absolute zero")
        self._celsius = value
    
    @property
    def fahrenheit(self):
        """Computed property for fahrenheit."""
        return (self._celsius * 9/5) + 32
    
    @fahrenheit.setter
    def fahrenheit(self, value):
        """Setter that converts fahrenheit to celsius."""
        self._celsius = (value - 32) * 5/9

# Usage
temp = Temperature(20)
print(temp.celsius)      # 20
print(temp.fahrenheit)   # 68.0

temp.fahrenheit = 100
print(temp.celsius)      # 37.777...
print(temp.fahrenheit)   # 100.0
```

#### Operator Overloading

```python
class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __add__(self, other):
        """Vector addition."""
        return Vector(self.x + other.x, self.y + other.y)
    
    def __sub__(self, other):
        """Vector subtraction."""
        return Vector(self.x - other.x, self.y - other.y)
    
    def __mul__(self, scalar):
        """Scalar multiplication."""
        return Vector(self.x * scalar, self.y * scalar)
    
    def __eq__(self, other):
        """Equality comparison."""
        return self.x == other.x and self.y == other.y
    
    def __str__(self):
        """String representation."""
        return f"Vector({self.x}, {self.y})"
    
    def __repr__(self):
        """Official string representation."""
        return f"Vector({self.x}, {self.y})"

# Usage
v1 = Vector(2, 3)
v2 = Vector(1, 4)

print(v1 + v2)      # Vector(3, 7)
print(v1 - v2)      # Vector(1, -1)
print(v1 * 3)       # Vector(6, 9)
print(v1 == v2)     # False
print(str(v1))      # Vector(2, 3)
```

### Comprehensive Car Class Example

```python
class Car:
    """Comprehensive Car class demonstrating OOP concepts."""
    
    # Class attributes
    total_cars = 0
    fuel_efficiency_standard = 25  # mpg
    
    def __init__(self, make, model, year, fuel_capacity=15):
        # Instance attributes
        self.make = make
        self.model = model
        self.year = year
        self.fuel_capacity = fuel_capacity
        self.fuel_level = fuel_capacity  # Start with full tank
        self.speed = 0
        self.mileage = 0
        
        Car.total_cars += 1
    
    def accelerate(self, increment):
        """Increase car speed."""
        if increment > 0:
            self.speed += increment
            # Consume fuel based on acceleration
            fuel_consumed = increment * 0.01
            self.fuel_level = max(0, self.fuel_level - fuel_consumed)
    
    def brake(self, decrement):
        """Decrease car speed."""
        self.speed = max(0, self.speed - decrement)
    
    def drive(self, distance):
        """Drive for a certain distance."""
        if self.fuel_level <= 0:
            print("Out of fuel! Cannot drive.")
            return False
        
        # Calculate fuel consumption (simplified)
        fuel_needed = distance / self.fuel_efficiency_standard
        
        if fuel_needed > self.fuel_level:
            max_distance = self.fuel_level * self.fuel_efficiency_standard
            print(f"Insufficient fuel. Can only drive {max_distance:.1f} miles.")
            return False
        
        self.fuel_level -= fuel_needed
        self.mileage += distance
        print(f"Drove {distance} miles. Fuel remaining: {self.fuel_level:.1f} gallons.")
        return True
    
    def refuel(self, gallons):
        """Add fuel to the tank."""
        if gallons > 0:
            self.fuel_level = min(self.fuel_capacity, self.fuel_level + gallons)
            print(f"Added {gallons} gallons. Fuel level: {self.fuel_level:.1f} gallons.")
    
    def get_info(self):
        """Get car information."""
        return f"{self.year} {self.make} {self.model}"
    
    def get_status(self):
        """Get current car status."""
        return {
            'speed': self.speed,
            'fuel_level': self.fuel_level,
            'mileage': self.mileage,
            'fuel_percentage': (self.fuel_level / self.fuel_capacity) * 100
        }
    
    @classmethod
    def get_total_cars(cls):
        """Get total number of cars created."""
        return cls.total_cars
    
    @staticmethod
    def convert_mpg_to_kmpl(mpg):
        """Convert miles per gallon to kilometers per liter."""
        return mpg * 0.425
    
    def __str__(self):
        """String representation."""
        return f"{self.get_info()} - Speed: {self.speed} mph, Fuel: {self.fuel_level:.1f} gal"
    
    def __eq__(self, other):
        """Check equality based on make, model, and year."""
        if not isinstance(other, Car):
            return False
        return (self.make == other.make and
                self.model == other.model and
                self.year == other.year)

# Usage
car1 = Car("Toyota", "Camry", 2020)
car2 = Car("Honda", "Civic", 2019)

print(f"Total cars created: {Car.get_total_cars()}")

car1.accelerate(50)
car1.drive(100)
print(car1.get_status())

car1.refuel(5)
print(car1)

print(f"25 MPG = {Car.convert_mpg_to_kmpl(25):.2f} KM/L")
```

## Encapsulation - Data Hiding and Protection

Encapsulation is the fundamental OOP principle of bundling data (attributes) and methods (functions) that operate on that data within a single unit (class). It restricts direct access to some components, protecting the integrity of object state.

### Access Control Mechanisms

#### Access Modifiers

1. **Public**: Accessible from anywhere (no leading underscore in Python)
2. **Protected**: Accessible within class and subclasses (single underscore in Python)
3. **Private**: Accessible only within the class (double underscore in Python)

#### Python Access Control

```python
class BankAccount:
    def __init__(self, balance, account_holder):
        # Public attributes
        self.account_holder = account_holder
        
        # Protected attribute (convention)
        self._branch_code = "001"
        
        # Private attribute (name mangling)
        self.__balance = balance
        self.__account_number = self.__generate_account_number()
    
    def __generate_account_number(self):
        """Private method to generate account number."""
        import random
        return f"ACC{random.randint(10000, 99999)}"
    
    # Public methods
    def deposit(self, amount):
        """Deposit money into account."""
        if self.__validate_amount(amount):
            self.__balance += amount
            self.__log_transaction("DEPOSIT", amount)
            return True
        return False
    
    def withdraw(self, amount):
        """Withdraw money from account."""
        if self.__validate_amount(amount) and amount <= self.__balance:
            self.__balance -= amount
            self.__log_transaction("WITHDRAWAL", amount)
            return True
        return False
    
    def get_balance(self):
        """Get current balance."""
        return self.__balance
    
    def get_account_info(self):
        """Get public account information."""
        return {
            'account_holder': self.account_holder,
            'account_number': self.__account_number,
            'branch': self._branch_code,
            'balance': self.__balance
        }
    
    # Protected method (accessible to subclasses)
    def _calculate_interest(self, rate):
        """Calculate interest (can be overridden by subclasses)."""
        return self.__balance * rate / 100
    
    # Private helper methods
    def __validate_amount(self, amount):
        """Validate transaction amount."""
        return isinstance(amount, (int, float)) and amount > 0
    
    def __log_transaction(self, transaction_type, amount):
        """Log transaction (private implementation detail)."""
        print(f"{transaction_type}: ${amount:.2f} - Balance: ${self.__balance:.2f}")

# Usage
account = BankAccount(1000, "John Doe")

# Public access
print(account.account_holder)        # John Doe
print(account.get_balance())         # 1000

# Protected access (discouraged but possible)
print(account._branch_code)          # 001

# Private access (will fail due to name mangling)
try:
    print(account.__balance)         # AttributeError
except AttributeError:
    print("Cannot access private attribute directly")

# Name mangling allows access (but shouldn't be used)
print(account._BankAccount__balance)  # 1000 (not recommended)

# Using public interface
account.deposit(500)
account.withdraw(200)
print(account.get_account_info())
```

#### Java Access Control

```java
public class BankAccount {
    // Public field
    public String accountHolder;
    
    // Protected field
    protected String branchCode = "001";
    
    // Private fields
    private double balance;
    private String accountNumber;
    
    // Public constructor
    public BankAccount(String accountHolder, double initialBalance) {
        this.accountHolder = accountHolder;
        this.balance = initialBalance;
        this.accountNumber = generateAccountNumber();
    }
    
    // Public methods
    public boolean deposit(double amount) {
        if (validateAmount(amount)) {
            balance += amount;
            logTransaction("DEPOSIT", amount);
            return true;
        }
        return false;
    }
    
    public boolean withdraw(double amount) {
        if (validateAmount(amount) && amount <= balance) {
            balance -= amount;
            logTransaction("WITHDRAWAL", amount);
            return true;
        }
        return false;
    }
    
    public double getBalance() {
        return balance;
    }
    
    // Protected method
    protected double calculateInterest(double rate) {
        return balance * rate / 100;
    }
    
    // Private methods
    private boolean validateAmount(double amount) {
        return amount > 0 && amount <= 10000; // Max transaction limit
    }
    
    private void logTransaction(String type, double amount) {
        System.out.printf("%s: $%.2f - Balance: $%.2f%n", type, amount, balance);
    }
    
    private String generateAccountNumber() {
        return "ACC" + (int)(Math.random() * 90000 + 10000);
    }
}

// Usage
BankAccount account = new BankAccount("John Doe", 1000.0);
account.deposit(500.0);
account.withdraw(200.0);
System.out.println("Balance: $" + account.getBalance());
```

### Data Validation and Integrity

#### Property-Based Encapsulation

```python
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    
    @property
    def name(self):
        """Getter for name."""
        return self._name
    
    @name.setter
    def name(self, value):
        """Setter for name with validation."""
        if not isinstance(value, str) or len(value.strip()) == 0:
            raise ValueError("Name must be a non-empty string")
        self._name = value.strip().title()
    
    @property
    def age(self):
        """Getter for age."""
        return self._age
    
    @age.setter
    def age(self, value):
        """Setter for age with validation."""
        if not isinstance(value, int) or value < 0 or value > 150:
            raise ValueError("Age must be an integer between 0 and 150")
        self._age = value

# Usage
person = Person("john doe", 25)
print(person.name)  # John Doe
print(person.age)   # 25

try:
    person.age = 200  # Will raise ValueError
except ValueError as e:
    print(e)

try:
    person.name = ""  # Will raise ValueError
except ValueError as e:
    print(e)
```

### Information Hiding Benefits

1. **Data Protection**: Prevents unauthorized access and modification
2. **Implementation Flexibility**: Internal implementation can change without affecting users
3. **Reduced Coupling**: Classes depend only on public interfaces
4. **Improved Maintainability**: Changes to private implementation don't break other code
5. **Enhanced Security**: Sensitive data and operations are protected

### Encapsulation Best Practices

1. **Make attributes private by default**
2. **Provide public getter/setter methods when needed**
3. **Validate data in setters**
4. **Use properties in Python for cleaner syntax**
5. **Document the public interface clearly**
6. **Avoid exposing internal implementation details**
7. **Use protected for inheritance-related access**

## Inheritance - Code Reuse and Hierarchical Relationships

Inheritance is a powerful OOP mechanism that allows a class (derived/child class) to inherit properties and methods from another class (base/parent class). It establishes "is-a" relationships and promotes code reuse while creating hierarchical class structures.

### Basic Inheritance Concepts

#### Base Class and Derived Class

- **Base/Parent Class**: The class being inherited from (superclass)
- **Derived/Child Class**: The class that inherits (subclass)
- **Inheritance Hierarchy**: Tree-like structure of classes

#### Single Inheritance Example

```python
class Animal:
    """Base class for all animals."""
    
    def __init__(self, name, species):
        self.name = name
        self.species = species
        self.energy = 100
    
    def eat(self, food_amount=10):
        """Animal eats and gains energy."""
        self.energy = min(100, self.energy + food_amount)
        return f"{self.name} ate and gained {food_amount} energy."
    
    def sleep(self):
        """Animal sleeps and restores energy."""
        self.energy = 100
        return f"{self.name} slept and is fully rested."
    
    def make_sound(self):
        """Generic animal sound."""
        return "Some animal sound"
    
    def get_info(self):
        """Get animal information."""
        return f"{self.name} is a {self.species} with {self.energy} energy."

class Dog(Animal):
    """Dog class inheriting from Animal."""
    
    def __init__(self, name, breed, color):
        # Call parent constructor
        super().__init__(name, "Dog")
        # Add dog-specific attributes
        self.breed = breed
        self.color = color
        self.tricks = []
    
    def make_sound(self):
        """Override parent method."""
        return "Woof! Woof!"
    
    def fetch(self, item):
        """Dog-specific method."""
        return f"{self.name} fetched the {item}!"
    
    def learn_trick(self, trick):
        """Teach dog a new trick."""
        self.tricks.append(trick)
        return f"{self.name} learned to {trick}!"
    
    def perform_tricks(self):
        """Show all learned tricks."""
        if not self.tricks:
            return f"{self.name} doesn't know any tricks yet."
        return f"{self.name} can: {', '.join(self.tricks)}"

class Cat(Animal):
    """Cat class inheriting from Animal."""
    
    def __init__(self, name, breed, fur_pattern):
        super().__init__(name, "Cat")
        self.breed = breed
        self.fur_pattern = fur_pattern
        self.lives_remaining = 9
    
    def make_sound(self):
        """Override parent method."""
        return "Meow!"
    
    def climb_tree(self):
        """Cat-specific method."""
        return f"{self.name} climbed the tree gracefully."
    
    def use_lives(self):
        """Cats have 9 lives."""
        if self.lives_remaining > 0:
            self.lives_remaining -= 1
            return f"{self.name} used a life! {self.lives_remaining} lives remaining."
        return f"{self.name} has no more lives!"

# Usage
dog = Dog("Buddy", "Golden Retriever", "Golden")
cat = Cat("Whiskers", "Siamese", "Seal Point")

print(dog.get_info())           # Buddy is a Dog with 100 energy.
print(dog.make_sound())         # Woof! Woof!
print(dog.fetch("ball"))        # Buddy fetched the ball!
print(dog.learn_trick("sit"))   # Buddy learned to sit!
print(dog.perform_tricks())     # Buddy can: sit

print(cat.get_info())           # Whiskers is a Cat with 100 energy.
print(cat.make_sound())         # Meow!
print(cat.climb_tree())         # Whiskers climbed the tree gracefully.
print(cat.use_lives())          # Whiskers used a life! 8 lives remaining.

# Both inherit common behavior
print(dog.eat(20))              # Buddy ate and gained 20 energy.
print(cat.sleep())              # Whiskers slept and is fully rested.
```

### Advanced Inheritance Patterns

#### Multiple Inheritance

```python
class Flyable:
    """Mixin class for flying capability."""
    
    def __init__(self, max_altitude=1000):
        self.max_altitude = max_altitude
        self.current_altitude = 0
    
    def fly(self, altitude):
        """Fly to specified altitude."""
        if altitude <= self.max_altitude:
            self.current_altitude = altitude
            return f"Flying at {altitude} feet"
        return f"Cannot fly above {self.max_altitude} feet"
    
    def land(self):
        """Land on ground."""
        self.current_altitude = 0
        return "Landed safely"

class Swimmable:
    """Mixin class for swimming capability."""
    
    def __init__(self, max_depth=100):
        self.max_depth = max_depth
        self.current_depth = 0
    
    def dive(self, depth):
        """Dive to specified depth."""
        if depth <= self.max_depth:
            self.current_depth = depth
            return f"Diving to {depth} feet"
        return f"Cannot dive below {self.max_depth} feet"
    
    def surface(self):
        """Surface from water."""
        self.current_depth = 0
        return "Surfaced successfully"

class Duck(Animal, Flyable, Swimmable):
    """Duck class with multiple inheritance."""
    
    def __init__(self, name, feather_color):
        # Initialize all parent classes
        Animal.__init__(self, name, "Duck")
        Flyable.__init__(self, max_altitude=500)  # Ducks don't fly very high
        Swimmable.__init__(self, max_depth=50)    # Ducks dive moderately
        
        self.feather_color = feather_color
    
    def make_sound(self):
        return "Quack!"
    
    def swim(self):
        """Duck-specific swimming."""
        return "Swimming gracefully on water surface"

# Usage
duck = Duck("Donald", "White")

print(duck.get_info())           # Donald is a Duck with 100 energy.
print(duck.make_sound())         # Quack!
print(duck.fly(200))             # Flying at 200 feet
print(duck.dive(20))             # Diving to 20 feet
print(duck.swim())               # Swimming gracefully on water surface
print(duck.land())               # Landed safely
print(duck.surface())            # Surfaced successfully
```

#### Method Resolution Order (MRO)

```python
# Multiple inheritance can create diamond problem
class A:
    def method(self):
        return "A"

class B(A):
    def method(self):
        return "B"

class C(A):
    def method(self):
        return "C"

class D(B, C):  # Multiple inheritance
    pass

# Method Resolution Order
d = D()
print(D.__mro__)          # (<class '__main__.D'>, <class '__main__.B'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>)
print(d.method())         # B (follows MRO: D -> B -> C -> A)
```

#### Abstract Base Classes and Interfaces

```python
from abc import ABC, abstractmethod

class Vehicle(ABC):
    """Abstract base class for vehicles."""
    
    def __init__(self, make, model, fuel_capacity):
        self.make = make
        self.model = model
        self.fuel_capacity = fuel_capacity
        self.fuel_level = fuel_capacity
    
    @abstractmethod
    def start_engine(self):
        """Must be implemented by subclasses."""
        pass
    
    @abstractmethod
    def move(self, distance):
        """Must be implemented by subclasses."""
        pass
    
    def refuel(self, amount):
        """Concrete method that can be inherited."""
        self.fuel_level = min(self.fuel_capacity, self.fuel_level + amount)
        return f"Refueled {amount} gallons"

class Car(Vehicle):
    """Concrete car implementation."""
    
    def __init__(self, make, model, fuel_capacity, num_doors):
        super().__init__(make, model, fuel_capacity)
        self.num_doors = num_doors
        self.speed = 0
    
    def start_engine(self):
        return "Vroom! Car engine started."
    
    def move(self, distance):
        fuel_needed = distance / 25  # 25 mpg
        if fuel_needed > self.fuel_level:
            return "Not enough fuel!"
        
        self.fuel_level -= fuel_needed
        return f"Drove {distance} miles"

class Motorcycle(Vehicle):
    """Concrete motorcycle implementation."""
    
    def __init__(self, make, model, fuel_capacity, engine_size):
        super().__init__(make, model, fuel_capacity)
        self.engine_size = engine_size
        self.speed = 0
    
    def start_engine(self):
        return "Brrrrm! Motorcycle engine started."
    
    def move(self, distance):
        fuel_needed = distance / 40  # 40 mpg
        if fuel_needed > self.fuel_level:
            return "Not enough fuel!"
        
        self.fuel_level -= fuel_needed
        return f"Rode {distance} miles"

# Usage
car = Car("Toyota", "Camry", 15, 4)
bike = Motorcycle("Harley", "Sportster", 5, "1200cc")

print(car.start_engine())     # Vroom! Car engine started.
print(car.move(100))          # Drove 100 miles
print(car.refuel(5))          # Refueled 5 gallons

print(bike.start_engine())    # Brrrrm! Motorcycle engine started.
print(bike.move(100))         # Rode 100 miles

# Cannot instantiate abstract class
try:
    vehicle = Vehicle("Generic", "Model", 10)  # TypeError
except TypeError as e:
    print(f"Cannot instantiate abstract class: {e}")
```

### Inheritance Best Practices

1. **Use inheritance for "is-a" relationships**
2. **Favor composition over inheritance when possible**
3. **Keep inheritance hierarchies shallow**
4. **Use abstract base classes for common interfaces**
5. **Override methods responsibly (Liskov Substitution Principle)**
6. **Call parent constructors appropriately**
7. **Document inheritance relationships clearly**
8. **Avoid multiple inheritance unless necessary**

## Polymorphism - Same Interface, Different Behavior

Polymorphism is the ability of objects of different classes to respond to the same method call in different ways. It allows for flexible and extensible code by treating objects of different types through a common interface.

### Types of Polymorphism

#### 1. Compile-time Polymorphism (Static Binding)
- **Method Overloading**: Multiple methods with same name but different parameters
- **Operator Overloading**: Redefining operators for custom classes
- **Resolved at compile time**

#### 2. Runtime Polymorphism (Dynamic Binding)
- **Method Overriding**: Subclass provides different implementation of inherited method
- **Virtual Functions**: Methods that can be overridden in derived classes
- **Resolved at runtime based on actual object type**

### Method Overriding - Runtime Polymorphism

```python
class Shape:
    """Base class for geometric shapes."""
    
    def __init__(self, name):
        self.name = name
    
    def area(self):
        """Calculate area - to be overridden by subclasses."""
        raise NotImplementedError("Subclasses must implement area()")
    
    def perimeter(self):
        """Calculate perimeter - to be overridden by subclasses."""
        raise NotImplementedError("Subclasses must implement perimeter()")
    
    def describe(self):
        """Describe the shape."""
        return f"I am a {self.name}"

class Rectangle(Shape):
    """Rectangle class."""
    
    def __init__(self, width, height):
        super().__init__("Rectangle")
        self.width = width
        self.height = height
    
    def area(self):
        return self.width * self.height
    
    def perimeter(self):
        return 2 * (self.width + self.height)
    
    def describe(self):
        return f"I am a {self.name} with width {self.width} and height {self.height}"

class Circle(Shape):
    """Circle class."""
    
    def __init__(self, radius):
        super().__init__("Circle")
        self.radius = radius
    
    def area(self):
        return 3.14159 * self.radius ** 2
    
    def perimeter(self):
        return 2 * 3.14159 * self.radius
    
    def describe(self):
        return f"I am a {self.name} with radius {self.radius}"

class Triangle(Shape):
    """Triangle class."""
    
    def __init__(self, base, height, side1, side2, side3):
        super().__init__("Triangle")
        self.base = base
        self.height = height
        self.sides = [side1, side2, side3]
    
    def area(self):
        return 0.5 * self.base * self.height
    
    def perimeter(self):
        return sum(self.sides)

# Polymorphism in action
def print_shape_info(shape):
    """Function that works with any shape object."""
    print(shape.describe())
    print(f"Area: {shape.area():.2f}")
    print(f"Perimeter: {shape.perimeter():.2f}")
    print()

# Create different shapes
shapes = [
    Rectangle(5, 3),
    Circle(4),
    Triangle(6, 4, 3, 4, 5)
]

# Same function call, different behavior
for shape in shapes:
    print_shape_info(shape)

# Polymorphism with collections
def total_area(shapes):
    """Calculate total area of all shapes."""
    return sum(shape.area() for shape in shapes)

def find_largest_shape(shapes):
    """Find shape with largest area."""
    return max(shapes, key=lambda s: s.area())

print(f"Total area: {total_area(shapes):.2f}")
largest = find_largest_shape(shapes)
print(f"Largest shape: {largest.describe()} (area: {largest.area():.2f})")
```

### Method Overloading - Compile-time Polymorphism

```python
# Python doesn't support method overloading directly
# But we can simulate it using default parameters or *args

class Calculator:
    """Calculator with overloaded add method (simulated)."""
    
    def add(self, *args):
        """Add method that accepts variable number of arguments."""
        if len(args) == 0:
            return 0
        elif len(args) == 1:
            return args[0]
        elif len(args) == 2:
            return args[0] + args[1]
        else:
            return sum(args)
    
    def multiply(self, a, b=1, c=1):
        """Multiply with default parameters."""
        return a * b * c

# Java example (true method overloading)
"""
public class Calculator {
    public int add(int a, int b) {
        return a + b;
    }
    
    public double add(double a, double b) {
        return a + b;
    }
    
    public int add(int a, int b, int c) {
        return a + b + c;
    }
    
    public String add(String a, String b) {
        return a + b;
    }
}
"""

# Usage
calc = Calculator()
print(calc.add())           # 0
print(calc.add(5))          # 5
print(calc.add(3, 4))       # 7
print(calc.add(1, 2, 3, 4)) # 10

print(calc.multiply(5))     # 5 (5 * 1 * 1)
print(calc.multiply(5, 2))  # 10 (5 * 2 * 1)
print(calc.multiply(5, 2, 3)) # 30 (5 * 2 * 3)
```

### Duck Typing and Polymorphism

```python
# Python's duck typing allows polymorphism without inheritance
class Dog:
    def speak(self):
        return "Woof!"
    
    def move(self):
        return "Runs on four legs"

class Robot:
    def speak(self):
        return "Beep boop!"
    
    def move(self):
        return "Rolls on wheels"

class Person:
    def speak(self):
        return "Hello!"
    
    def move(self):
        return "Walks on two legs"

def interact(entity):
    """Function works with any object that has speak() and move() methods."""
    print(entity.speak())
    print(entity.move())
    print()

# All work the same way despite different classes
entities = [Dog(), Robot(), Person()]

for entity in entities:
    interact(entity)
```

### Polymorphism with Abstract Base Classes

```python
from abc import ABC, abstractmethod

class PaymentProcessor(ABC):
    """Abstract base class for payment processing."""
    
    @abstractmethod
    def process_payment(self, amount):
        """Process payment - must be implemented by subclasses."""
        pass
    
    @abstractmethod
    def validate_payment(self, payment_info):
        """Validate payment information."""
        pass
    
    def log_transaction(self, amount, status):
        """Concrete method for logging."""
        print(f"Transaction: ${amount:.2f} - Status: {status}")

class CreditCardProcessor(PaymentProcessor):
    """Credit card payment processor."""
    
    def process_payment(self, amount):
        # Simulate credit card processing
        print(f"Processing credit card payment of ${amount:.2f}")
        # Actual implementation would connect to payment gateway
        return True
    
    def validate_payment(self, payment_info):
        card_number = payment_info.get('card_number', '')
        expiry = payment_info.get('expiry', '')
        cvv = payment_info.get('cvv', '')
        
        # Simple validation
        if len(card_number) == 16 and len(expiry) == 5 and len(cvv) == 3:
            return True
        return False

class PayPalProcessor(PaymentProcessor):
    """PayPal payment processor."""
    
    def process_payment(self, amount):
        print(f"Processing PayPal payment of ${amount:.2f}")
        # Actual implementation would use PayPal API
        return True
    
    def validate_payment(self, payment_info):
        email = payment_info.get('email', '')
        return '@' in email and '.' in email

class BankTransferProcessor(PaymentProcessor):
    """Bank transfer payment processor."""
    
    def process_payment(self, amount):
        print(f"Processing bank transfer of ${amount:.2f}")
        # Actual implementation would use banking API
        return True
    
    def validate_payment(self, payment_info):
        account = payment_info.get('account_number', '')
        routing = payment_info.get('routing_number', '')
        return len(account) >= 8 and len(routing) == 9

# Polymorphic payment processing
def process_order(payment_processor, amount, payment_info):
    """Process payment using any payment processor."""
    if not payment_processor.validate_payment(payment_info):
        payment_processor.log_transaction(amount, "Validation Failed")
        return False
    
    if payment_processor.process_payment(amount):
        payment_processor.log_transaction(amount, "Success")
        return True
    else:
        payment_processor.log_transaction(amount, "Failed")
        return False

# Usage
processors = [
    CreditCardProcessor(),
    PayPalProcessor(),
    BankTransferProcessor()
]

payment_infos = [
    {'card_number': '1234567890123456', 'expiry': '12/25', 'cvv': '123'},
    {'email': 'user@example.com'},
    {'account_number': '123456789', 'routing_number': '123456789'}
]

for processor, info in zip(processors, payment_infos):
    process_order(processor, 99.99, info)
    print()
```

### Polymorphism Best Practices

1. **Program to interfaces, not implementations**
2. **Use abstract base classes to define contracts**
3. **Leverage duck typing in dynamic languages**
4. **Ensure Liskov Substitution Principle compliance**
5. **Use polymorphism to reduce conditional logic**
6. **Document polymorphic behavior clearly**
7. **Test polymorphic code with different implementations**

## Abstraction - Hiding Complexity, Showing Essentials

Abstraction is the process of identifying essential features of an object while hiding unnecessary details. It allows programmers to focus on what an object does rather than how it does it, managing complexity in large systems.

### Levels of Abstraction

#### 1. Data Abstraction
- Hiding data implementation details
- Providing public interface for data access
- Using properties and accessors

#### 2. Procedural Abstraction
- Hiding implementation details of procedures
- Providing function interfaces
- Modular code organization

#### 3. Control Abstraction
- Hiding control flow details
- Using loops, conditionals, and functions
- Managing program execution flow

### Abstract Classes and Interfaces

#### Abstract Base Classes in Python

```python
from abc import ABC, abstractmethod
from math import pi

class Shape(ABC):
    """Abstract base class for geometric shapes."""
    
    def __init__(self, name):
        self.name = name
    
    @abstractmethod
    def area(self):
        """Calculate area - must be implemented by subclasses."""
        pass
    
    @abstractmethod
    def perimeter(self):
        """Calculate perimeter - must be implemented by subclasses."""
        pass
    
    @abstractmethod
    def draw(self):
        """Draw the shape - must be implemented by subclasses."""
        pass
    
    def describe(self):
        """Concrete method that can be inherited."""
        return f"I am a {self.name}"
    
    @classmethod
    def create_shape(cls, shape_type, **kwargs):
        """Factory method to create shapes."""
        if shape_type == "rectangle":
            return Rectangle(**kwargs)
        elif shape_type == "circle":
            return Circle(**kwargs)
        elif shape_type == "triangle":
            return Triangle(**kwargs)
        else:
            raise ValueError(f"Unknown shape type: {shape_type}")

class Rectangle(Shape):
    """Concrete rectangle implementation."""
    
    def __init__(self, width, height, **kwargs):
        super().__init__("Rectangle")
        self.width = width
        self.height = height
    
    def area(self):
        return self.width * self.height
    
    def perimeter(self):
        return 2 * (self.width + self.height)
    
    def draw(self):
        """Simple ASCII art representation."""
        return f"""
+{'-' * (self.width * 2)}+
|{' ' * (self.width * 2)}|
|{' ' * (self.width * 2)}|
+{'-' * (self.width * 2)}+
"""

class Circle(Shape):
    """Concrete circle implementation."""
    
    def __init__(self, radius, **kwargs):
        super().__init__("Circle")
        self.radius = radius
    
    def area(self):
        return pi * self.radius ** 2
    
    def perimeter(self):
        return 2 * pi * self.radius
    
    def draw(self):
        """Simple ASCII art representation."""
        return f"""
   *****
  *     *
 *   O   *
  *     *
   *****
"""

class Triangle(Shape):
    """Concrete triangle implementation."""
    
    def __init__(self, base, height, **kwargs):
        super().__init__("Triangle")
        self.base = base
        self.height = height
    
    def area(self):
        return 0.5 * self.base * self.height
    
    def perimeter(self):
        # Assuming equilateral for simplicity
        return 3 * self.base
    
    def draw(self):
        """Simple ASCII art representation."""
        return """
   /\\
  /  \\
 /____\\
"""

# Usage
shapes = [
    Shape.create_shape("rectangle", width=5, height=3),
    Shape.create_shape("circle", radius=4),
    Shape.create_shape("triangle", base=6, height=4)
]

for shape in shapes:
    print(shape.describe())
    print(f"Area: {shape.area():.2f}")
    print(f"Perimeter: {shape.perimeter():.2f}")
    print(shape.draw())
    print()

# Polymorphic processing
def process_shapes(shapes):
    """Process any collection of shapes."""
    total_area = sum(shape.area() for shape in shapes)
    total_perimeter = sum(shape.perimeter() for shape in shapes)
    
    return {
        'count': len(shapes),
        'total_area': total_area,
        'total_perimeter': total_perimeter,
        'average_area': total_area / len(shapes)
    }

stats = process_shapes(shapes)
print("Shape Statistics:")
for key, value in stats.items():
    print(f"{key}: {value}")
```

#### Interfaces in Java

```java
// Shape.java - Interface
public interface Shape {
    double area();
    double perimeter();
    void draw();
    String describe();
}

// Rectangle.java - Implementation
public class Rectangle implements Shape {
    private double width;
    private double height;
    
    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }
    
    @Override
    public double area() {
        return width * height;
    }
    
    @Override
    public double perimeter() {
        return 2 * (width + height);
    }
    
    @Override
    public void draw() {
        System.out.println("Drawing a rectangle");
    }
    
    @Override
    public String describe() {
        return "Rectangle with width " + width + " and height " + height;
    }
}

// Usage
List<Shape> shapes = Arrays.asList(
    new Rectangle(5, 3),
    new Circle(4),
    new Triangle(6, 4)
);

for (Shape shape : shapes) {
    System.out.println(shape.describe());
    System.out.println("Area: " + shape.area());
    System.out.println("Perimeter: " + shape.perimeter());
    shape.draw();
    System.out.println();
}
```

### Design Patterns - Reusable Solutions to Common Problems

#### Creational Patterns

##### Singleton Pattern
```python
class Singleton:
    """Singleton pattern implementation."""
    
    _instance = None
    
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance
    
    def __init__(self):
        if not hasattr(self, 'initialized'):
            self.initialized = True
            self.data = "Singleton data"

# Usage
s1 = Singleton()
s1.data = "Modified by s1"

s2 = Singleton()
print(s2.data)  # "Modified by s1" - same instance
print(s1 is s2)  # True
```

##### Factory Pattern
```python
from abc import ABC, abstractmethod

class Animal(ABC):
    @abstractmethod
    def speak(self):
        pass
    
    @abstractmethod
    def move(self):
        pass

class Dog(Animal):
    def speak(self):
        return "Woof!"
    
    def move(self):
        return "Runs"

class Cat(Animal):
    def speak(self):
        return "Meow!"
    
    def move(self):
        return "Walks"

class AnimalFactory:
    """Factory pattern for creating animals."""
    
    @staticmethod
    def create_animal(animal_type):
        if animal_type == "dog":
            return Dog()
        elif animal_type == "cat":
            return Cat()
        else:
            raise ValueError(f"Unknown animal type: {animal_type}")

# Usage
animals = []
for animal_type in ["dog", "cat", "dog"]:
    animal = AnimalFactory.create_animal(animal_type)
    animals.append(animal)
    print(f"{animal_type}: {animal.speak()}, {animal.move()}")
```

#### Structural Patterns

##### Adapter Pattern
```python
class EuropeanSocket:
    """European socket interface."""
    
    def voltage(self):
        return 220
    
    def live(self):
        return 1
    
    def neutral(self):
        return -1
    
    def earth(self):
        return 0

class AmericanPlug:
    """American plug interface."""
    
    def __init__(self):
        self.voltage = 110
        self.live = 1
        self.neutral = -1
        # No earth wire

class Adapter:
    """Adapter to make American plug work with European socket."""
    
    def __init__(self, american_plug):
        self.plug = american_plug
    
    def voltage(self):
        return self.plug.voltage
    
    def live(self):
        return self.plug.live
    
    def neutral(self):
        return self.plug.neutral
    
    def earth(self):
        return 0  # Adapter provides earth

# Usage
plug = AmericanPlug()
adapter = Adapter(plug)

socket = EuropeanSocket()

print("Original plug voltage:", plug.voltage)
print("With adapter voltage:", adapter.voltage)
print("Socket voltage:", socket.voltage)
```

##### Decorator Pattern
```python
class Coffee:
    """Base coffee class."""
    
    def cost(self):
        return 2.0
    
    def description(self):
        return "Plain coffee"

class CoffeeDecorator:
    """Base decorator class."""
    
    def __init__(self, coffee):
        self.coffee = coffee
    
    def cost(self):
        return self.coffee.cost()
    
    def description(self):
        return self.coffee.description()

class MilkDecorator(CoffeeDecorator):
    """Milk decorator."""
    
    def cost(self):
        return self.coffee.cost() + 0.5
    
    def description(self):
        return self.coffee.description() + ", milk"

class SugarDecorator(CoffeeDecorator):
    """Sugar decorator."""
    
    def cost(self):
        return self.coffee.cost() + 0.2
    
    def description(self):
        return self.coffee.description() + ", sugar"

class WhipDecorator(CoffeeDecorator):
    """Whip cream decorator."""
    
    def cost(self):
        return self.coffee.cost() + 0.7
    
    def description(self):
        return self.coffee.description() + ", whip cream"

# Usage
coffee = Coffee()
coffee = MilkDecorator(coffee)
coffee = SugarDecorator(coffee)
coffee = WhipDecorator(coffee)

print(f"Description: {coffee.description()}")
print(f"Cost: ${coffee.cost():.2f}")
```

#### Behavioral Patterns

##### Observer Pattern
```python
class Subject:
    """Subject being observed."""
    
    def __init__(self):
        self._observers = []
        self._state = None
    
    def attach(self, observer):
        """Attach an observer."""
        self._observers.append(observer)
    
    def detach(self, observer):
        """Detach an observer."""
        self._observers.remove(observer)
    
    def notify(self):
        """Notify all observers."""
        for observer in self._observers:
            observer.update(self)
    
    def set_state(self, state):
        """Set state and notify observers."""
        self._state = state
        self.notify()
    
    def get_state(self):
        return self._state

class Observer:
    """Observer interface."""
    
    def update(self, subject):
        pass

class ConcreteObserver(Observer):
    """Concrete observer implementation."""
    
    def __init__(self, name):
        self.name = name
    
    def update(self, subject):
        print(f"{self.name} received update: {subject.get_state()}")

# Usage
subject = Subject()

observer1 = ConcreteObserver("Observer 1")
observer2 = ConcreteObserver("Observer 2")

subject.attach(observer1)
subject.attach(observer2)

subject.set_state("State 1")
subject.set_state("State 2")

subject.detach(observer1)
subject.set_state("State 3")  # Only observer2 gets notified
```

##### Strategy Pattern
```python
from abc import ABC, abstractmethod

class SortingStrategy(ABC):
    """Strategy interface for sorting."""
    
    @abstractmethod
    def sort(self, data):
        pass

class BubbleSort(SortingStrategy):
    """Bubble sort strategy."""
    
    def sort(self, data):
        arr = data.copy()
        n = len(arr)
        for i in range(n):
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
        return arr

class QuickSort(SortingStrategy):
    """Quick sort strategy."""
    
    def sort(self, data):
        arr = data.copy()
        if len(arr) <= 1:
            return arr
        
        pivot = arr[len(arr) // 2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        
        return self.sort(left) + middle + self.sort(right)

class Sorter:
    """Context that uses sorting strategies."""
    
    def __init__(self, strategy):
        self.strategy = strategy
    
    def set_strategy(self, strategy):
        self.strategy = strategy
    
    def sort(self, data):
        return self.strategy.sort(data)

# Usage
data = [64, 34, 25, 12, 22, 11, 90]

sorter = Sorter(BubbleSort())
print("Bubble sort:", sorter.sort(data))

sorter.set_strategy(QuickSort())
print("Quick sort:", sorter.sort(data))
```

### SOLID Principles

#### Single Responsibility Principle (SRP)
A class should have only one reason to change.

```python
# Bad: Multiple responsibilities
class Employee:
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary
    
    def calculate_pay(self):
        return self.salary * 1.1
    
    def save_to_database(self):
        # Database logic here
        pass
    
    def generate_report(self):
        # Report generation logic here
        pass

# Good: Single responsibility per class
class Employee:
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary
    
    def calculate_pay(self):
        return self.salary * 1.1

class EmployeeRepository:
    def save(self, employee):
        # Database logic here
        pass

class EmployeeReportGenerator:
    def generate_report(self, employee):
        # Report generation logic here
        pass
```

#### Open-Closed Principle (OCP)
Software entities should be open for extension but closed for modification.

```python
# Bad: Adding new shapes requires modifying existing code
class AreaCalculator:
    def calculate_area(self, shapes):
        total = 0
        for shape in shapes:
            if isinstance(shape, Rectangle):
                total += shape.width * shape.height
            elif isinstance(shape, Circle):
                total += 3.14 * shape.radius ** 2
            # Adding new shape requires modifying this method
        return total

# Good: Open for extension through polymorphism
class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class AreaCalculator:
    def calculate_area(self, shapes):
        return sum(shape.area() for shape in shapes)
        # No modification needed when adding new shapes
```

#### Liskov Substitution Principle (LSP)
Subtypes must be substitutable for their base types.

```python
# Bad: Violates LSP
class Rectangle:
    def __init__(self, width, height):
        self.width = width
        self.height = height
    
    def set_width(self, width):
        self.width = width
    
    def set_height(self, height):
        self.height = height
    
    def area(self):
        return self.width * self.height

class Square(Rectangle):
    def set_width(self, width):
        self.width = width
        self.height = width  # Square constraint
    
    def set_height(self, height):
        self.width = height  # Square constraint
        self.height = height

# Usage - breaks expectations
rect = Rectangle(5, 3)
rect.set_width(4)
print(rect.area())  # 12 (4 * 3)

square = Square(5, 5)
square.set_width(4)
print(square.area())  # 16 (4 * 4) - unexpected behavior

# Good: Proper inheritance hierarchy
class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height
    
    def area(self):
        return self.width * self.height

class Square(Shape):
    def __init__(self, side):
        self.side = side
    
    def area(self):
        return self.side ** 2
```

#### Interface Segregation Principle (ISP)
Clients should not be forced to depend on interfaces they don't use.

```python
# Bad: Fat interface
class Worker:
    def work(self):
        pass
    
    def eat(self):
        pass
    
    def sleep(self):
        pass

class Robot(Worker):
    def work(self):
        print("Working...")
    
    def eat(self):
        pass  # Robots don't eat
    
    def sleep(self):
        pass  # Robots don't sleep

# Good: Segregated interfaces
class Workable:
    def work(self):
        pass

class Eatable:
    def eat(self):
        pass

class Sleepable:
    def sleep(self):
        pass

class Human(Workable, Eatable, Sleepable):
    def work(self):
        print("Working...")
    
    def eat(self):
        print("Eating...")
    
    def sleep(self):
        print("Sleeping...")

class Robot(Workable):
    def work(self):
        print("Working...")
```

#### Dependency Inversion Principle (DIP)
High-level modules should not depend on low-level modules. Both should depend on abstractions.

```python
# Bad: High-level module depends on low-level module
class LightBulb:
    def turn_on(self):
        print("Light bulb turned on")
    
    def turn_off(self):
        print("Light bulb turned off")

class Switch:
    def __init__(self):
        self.bulb = LightBulb()  # Direct dependency
    
    def operate(self):
        self.bulb.turn_on()

# Good: Both depend on abstraction
class Switchable(ABC):
    @abstractmethod
    def turn_on(self):
        pass
    
    @abstractmethod
    def turn_off(self):
        pass

class LightBulb(Switchable):
    def turn_on(self):
        print("Light bulb turned on")
    
    def turn_off(self):
        print("Light bulb turned off")

class Fan(Switchable):
    def turn_on(self):
        print("Fan turned on")
    
    def turn_off(self):
        print("Fan turned off")

class Switch:
    def __init__(self, device: Switchable):
        self.device = device  # Depends on abstraction
    
    def operate(self):
        self.device.turn_on()

# Usage
bulb = LightBulb()
fan = Fan()

switch1 = Switch(bulb)
switch2 = Switch(fan)

switch1.operate()  # Light bulb turned on
switch2.operate()  # Fan turned on
```

### Advanced OOP Concepts

#### Composition over Inheritance

```python
# Inheritance approach (tight coupling)
class Car:
    def __init__(self):
        self.engine = Engine()
        self.wheels = [Wheel() for _ in range(4)]
    
    def start(self):
        self.engine.start()

# Composition approach (loose coupling)
class Car:
    def __init__(self, engine, wheels):
        self.engine = engine
        self.wheels = wheels
    
    def start(self):
        self.engine.start()

# Usage
v8_engine = V8Engine()
michelin_wheels = [MichelinWheel() for _ in range(4)]

car = Car(v8_engine, michelin_wheels)
car.start()
```

#### Mixins and Traits

```python
class LoggerMixin:
    """Mixin for logging functionality."""
    
    def log(self, message):
        print(f"[{self.__class__.__name__}]: {message}")

class SerializableMixin:
    """Mixin for serialization."""
    
    def to_dict(self):
        return self.__dict__.copy()
    
    def from_dict(self, data):
        self.__dict__.update(data)

class User(LoggerMixin, SerializableMixin):
    """User class with logging and serialization."""
    
    def __init__(self, name, email):
        self.name = name
        self.email = email
    
    def save(self):
        self.log("Saving user...")
        # Save logic here
        data = self.to_dict()
        self.log(f"Saved: {data}")

# Usage
user = User("Alice", "alice@example.com")
user.save()
```

### Summary

Object-Oriented Programming provides powerful tools for organizing complex software systems. The four pillars - Encapsulation, Inheritance, Polymorphism, and Abstraction - work together to create maintainable, extensible, and reusable code.

Design patterns offer proven solutions to common design problems, while SOLID principles guide the creation of well-structured object-oriented systems. Understanding these concepts deeply enables developers to create software that is both robust and adaptable to changing requirements.

The key to mastering OOP is practice: implementing classes, designing inheritance hierarchies, applying design patterns, and refactoring code to follow best practices. With experience, these principles become second nature, leading to cleaner, more maintainable codebases.

## Comprehensive OOP Best Practices and Guidelines

### Class Design Principles

#### 1. Single Responsibility Principle (SRP) - Deep Analysis

**Definition**: A class should have only one reason to change, meaning it should have only one job or responsibility.

**Benefits**:
- Easier testing and maintenance
- Clearer class purposes
- Reduced coupling between classes
- Improved code readability

**Example**:
```python
# Bad: Multiple responsibilities
class UserManager:
    def __init__(self, user):
        self.user = user
    
    def save_user(self):
        # Database logic
        pass
    
    def send_email(self, message):
        # Email logic
        pass
    
    def generate_report(self):
        # Report generation logic
        pass
    
    def validate_user(self):
        # Validation logic
        pass

# Good: Single responsibility per class
class UserRepository:
    def save(self, user):
        # Only database operations
        pass
    
    def find_by_id(self, user_id):
        # Only database queries
        pass

class EmailService:
    def send_welcome_email(self, user):
        # Only email sending
        pass
    
    def send_password_reset(self, user):
        # Only password reset emails
        pass

class UserValidator:
    def validate(self, user):
        # Only validation logic
        pass

class ReportGenerator:
    def generate_user_report(self, users):
        # Only report generation
        pass
```

#### 2. Open-Closed Principle (OCP) - Extension without Modification

**Definition**: Software entities should be open for extension but closed for modification.

**Benefits**:
- Existing code doesn't break when adding new features
- Easier to add new functionality
- Reduced risk of introducing bugs
- Better maintainability

**Example**:
```python
# Bad: Modifying existing code for new features
class PaymentProcessor:
    def process_payment(self, payment_type, amount):
        if payment_type == "credit_card":
            # Credit card processing logic
            return self._process_credit_card(amount)
        elif payment_type == "paypal":
            # PayPal processing logic
            return self._process_paypal(amount)
        elif payment_type == "bank_transfer":
            # Bank transfer logic - NEW FEATURE
            return self._process_bank_transfer(amount)

# Good: Extension through inheritance/polymorphism
class PaymentProcessor(ABC):
    @abstractmethod
    def process_payment(self, amount):
        pass

class CreditCardProcessor(PaymentProcessor):
    def process_payment(self, amount):
        # Credit card specific logic
        return f"Processed ${amount} via credit card"

class PayPalProcessor(PaymentProcessor):
    def process_payment(self, amount):
        # PayPal specific logic
        return f"Processed ${amount} via PayPal"

class BankTransferProcessor(PaymentProcessor):
    def process_payment(self, amount):
        # Bank transfer specific logic
        return f"Processed ${amount} via bank transfer"

# Usage - no modification needed for new payment types
def process_order(processor, amount):
    return processor.process_payment(amount)
```

#### 3. Liskov Substitution Principle (LSP) - Behavioral Subtyping

**Definition**: Subtypes must be substitutable for their base types without altering the correctness of the program.

**Benefits**:
- Ensures proper inheritance hierarchies
- Prevents unexpected behavior in polymorphic code
- Improves code reliability
- Makes refactoring safer

**Example**:
```python
# Bad: Violates LSP
class Rectangle:
    def __init__(self, width, height):
        self.width = width
        self.height = height
    
    @property
    def width(self):
        return self._width
    
    @width.setter
    def width(self, value):
        self._width = value
    
    @property
    def height(self):
        return self._height
    
    @height.setter
    def height(self, value):
        self._height = value
    
    def area(self):
        return self.width * self.height

class Square(Rectangle):
    def __init__(self, side):
        super().__init__(side, side)
    
    @Rectangle.width.setter
    def width(self, value):
        self._width = value
        self._height = value  # Square constraint
    
    @Rectangle.height.setter
    def height(self, value):
        self._width = value   # Square constraint
        self._height = value

# Usage - breaks expectations
def print_area(rectangle):
    original_width = rectangle.width
    rectangle.width = 5
    print(f"Width: {rectangle.width}, Height: {rectangle.height}, Area: {rectangle.area()}")

rect = Rectangle(4, 6)
square = Square(4)

print("Rectangle:")
print_area(rect)    # Width: 5, Height: 6, Area: 30

print("Square:")
print_area(square)  # Width: 5, Height: 5, Area: 25 (unexpected!)

# Good: Proper design
class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height
    
    def area(self):
        return self.width * self.height

class Square(Shape):
    def __init__(self, side):
        self.side = side
    
    def area(self):
        return self.side ** 2
```

#### 4. Interface Segregation Principle (ISP) - Client-Specific Interfaces

**Definition**: Clients should not be forced to depend on interfaces they don't use.

**Benefits**:
- Reduces coupling between classes
- Makes interfaces more focused
- Easier to implement and maintain
- Prevents "fat" interfaces

**Example**:
```python
# Bad: Fat interface
class Worker:
    def work(self):
        pass
    
    def eat(self):
        pass
    
    def sleep(self):
        pass

class HumanWorker(Worker):
    def work(self):
        print("Working...")
    
    def eat(self):
        print("Eating...")
    
    def sleep(self):
        print("Sleeping...")

class RobotWorker(Worker):
    def work(self):
        print("Working...")
    
    def eat(self):
        pass  # Robots don't eat
    
    def sleep(self):
        pass  # Robots don't sleep

# Good: Segregated interfaces
class Workable(ABC):
    @abstractmethod
    def work(self):
        pass

class Eatable(ABC):
    @abstractmethod
    def eat(self):
        pass

class Sleepable(ABC):
    @abstractmethod
    def sleep(self):
        pass

class HumanWorker(Workable, Eatable, Sleepable):
    def work(self):
        print("Working...")
    
    def eat(self):
        print("Eating...")
    
    def sleep(self):
        print("Sleeping...")

class RobotWorker(Workable):
    def work(self):
        print("Working...")

# Usage
def manage_worker(worker):
    worker.work()
    # Only call eat/sleep if worker supports it
    if isinstance(worker, Eatable):
        worker.eat()
    if isinstance(worker, Sleepable):
        worker.sleep()
```

#### 5. Dependency Inversion Principle (DIP) - Depend on Abstractions

**Definition**: High-level modules should not depend on low-level modules. Both should depend on abstractions.

**Benefits**:
- Reduces coupling between modules
- Makes code more testable
- Enables easier refactoring
- Supports plugin architectures

**Example**:
```python
# Bad: High-level module depends on low-level module
class EmailService:
    def send_email(self, recipient, message):
        # Direct dependency on SMTP implementation
        smtp_client = SMTPClient()
        smtp_client.connect("smtp.gmail.com")
        smtp_client.send(recipient, message)

class UserNotification:
    def __init__(self):
        self.email_service = EmailService()
    
    def notify_user(self, user, message):
        self.email_service.send_email(user.email, message)

# Good: Both depend on abstractions
class MessageService(ABC):
    @abstractmethod
    def send_message(self, recipient, message):
        pass

class EmailService(MessageService):
    def __init__(self, smtp_client=None):
        self.smtp_client = smtp_client or SMTPClient()
    
    def send_message(self, recipient, message):
        self.smtp_client.connect("smtp.gmail.com")
        self.smtp_client.send(recipient, message)

class SMSService(MessageService):
    def send_message(self, recipient, message):
        # SMS sending logic
        print(f"Sending SMS to {recipient}: {message}")

class UserNotification:
    def __init__(self, message_service: MessageService):
        self.message_service = message_service
    
    def notify_user(self, user, message):
        self.message_service.send_message(user.email, message)

# Usage - easily switch implementations
email_notification = UserNotification(EmailService())
sms_notification = UserNotification(SMSService())

# Can even use mock for testing
class MockMessageService(MessageService):
    def __init__(self):
        self.sent_messages = []
    
    def send_message(self, recipient, message):
        self.sent_messages.append((recipient, message))

mock_notification = UserNotification(MockMessageService())
```

### Design Patterns - Comprehensive Catalog

#### Creational Patterns

##### Builder Pattern - Complex Object Construction
```python
class Computer:
    """Product class."""
    
    def __init__(self):
        self.cpu = None
        self.ram = None
        self.storage = None
        self.gpu = None
        self.os = None
    
    def __str__(self):
        return f"Computer: CPU={self.cpu}, RAM={self.ram}, Storage={self.storage}, GPU={self.gpu}, OS={self.os}"

class ComputerBuilder:
    """Builder class."""
    
    def __init__(self):
        self.computer = Computer()
    
    def set_cpu(self, cpu):
        self.computer.cpu = cpu
        return self
    
    def set_ram(self, ram):
        self.computer.ram = ram
        return self
    
    def set_storage(self, storage):
        self.computer.storage = storage
        return self
    
    def set_gpu(self, gpu):
        self.computer.gpu = gpu
        return self
    
    def set_os(self, os):
        self.computer.os = os
        return self
    
    def build(self):
        return self.computer

class ComputerDirector:
    """Director class."""
    
    @staticmethod
    def build_gaming_pc(builder):
        return (builder
                .set_cpu("Intel i9")
                .set_ram("32GB DDR4")
                .set_storage("2TB SSD")
                .set_gpu("RTX 3080")
                .set_os("Windows 11")
                .build())
    
    @staticmethod
    def build_office_pc(builder):
        return (builder
                .set_cpu("Intel i5")
                .set_ram("16GB DDR4")
                .set_storage("512GB SSD")
                .set_gpu("Integrated")
                .set_os("Windows 11")
                .build())

# Usage
builder = ComputerBuilder()

gaming_pc = ComputerDirector.build_gaming_pc(builder)
office_pc = ComputerDirector.build_office_pc(ComputerBuilder())

print("Gaming PC:", gaming_pc)
print("Office PC:", office_pc)
```

##### Prototype Pattern - Object Cloning
```python
import copy

class Shape:
    """Prototype base class."""
    
    def __init__(self, color):
        self.color = color
    
    def clone(self):
        """Shallow clone."""
        return copy.copy(self)
    
    def deep_clone(self):
        """Deep clone."""
        return copy.deepcopy(self)

class Rectangle(Shape):
    def __init__(self, width, height, color):
        super().__init__(color)
        self.width = width
        self.height = height
    
    def __str__(self):
        return f"Rectangle({self.width}x{self.height}, {self.color})"

class Circle(Shape):
    def __init__(self, radius, color):
        super().__init__(color)
        self.radius = radius
    
    def __str__(self):
        return f"Circle(r={self.radius}, {self.color})"

class ShapeRegistry:
    """Registry for shape prototypes."""
    
    def __init__(self):
        self.prototypes = {}
    
    def add_prototype(self, name, prototype):
        self.prototypes[name] = prototype
    
    def get_prototype(self, name):
        return self.prototypes[name].clone()
    
    def get_deep_prototype(self, name):
        return self.prototypes[name].deep_clone()

# Usage
registry = ShapeRegistry()

# Add prototypes
registry.add_prototype("red_rectangle", Rectangle(10, 5, "red"))
registry.add_prototype("blue_circle", Circle(7, "blue"))

# Clone shapes
rect1 = registry.get_prototype("red_rectangle")
rect2 = registry.get_prototype("red_rectangle")
rect2.color = "green"  # Only affects rect2

circle1 = registry.get_deep_prototype("blue_circle")

print("Original rectangle:", registry.prototypes["red_rectangle"])
print("Cloned rectangle 1:", rect1)
print("Cloned rectangle 2:", rect2)
print("Deep cloned circle:", circle1)
```

#### Structural Patterns

##### Facade Pattern - Simplified Interface
```python
class CPU:
    def freeze(self):
        print("CPU: Freezing...")
    
    def jump(self, position):
        print(f"CPU: Jumping to {position}")
    
    def execute(self):
        print("CPU: Executing...")

class Memory:
    def load(self, position, data):
        print(f"Memory: Loading {data} at {position}")

class HardDrive:
    def read(self, lba, size):
        print(f"HardDrive: Reading {size} bytes from LBA {lba}")
        return "data"

class ComputerFacade:
    """Facade for computer components."""
    
    def __init__(self):
        self.cpu = CPU()
        self.memory = Memory()
        self.hard_drive = HardDrive()
    
    def start_computer(self):
        print("Starting computer...")
        self.cpu.freeze()
        self.memory.load(0, self.hard_drive.read(0, 1024))
        self.cpu.jump(0)
        self.cpu.execute()
        print("Computer started successfully!")

# Usage - simple interface
computer = ComputerFacade()
computer.start_computer()
```

##### Composite Pattern - Tree Structures
```python
class Component(ABC):
    """Component base class."""
    
    @abstractmethod
    def operation(self):
        pass
    
    @abstractmethod
    def add(self, component):
        pass
    
    @abstractmethod
    def remove(self, component):
        pass
    
    @abstractmethod
    def get_child(self, index):
        pass

class Leaf(Component):
    """Leaf component."""
    
    def __init__(self, name):
        self.name = name
    
    def operation(self):
        print(f"Leaf {self.name}: Performing operation")
    
    def add(self, component):
        raise NotImplementedError("Leaf cannot add components")
    
    def remove(self, component):
        raise NotImplementedError("Leaf cannot remove components")
    
    def get_child(self, index):
        raise NotImplementedError("Leaf has no children")

class Composite(Component):
    """Composite component."""
    
    def __init__(self, name):
        self.name = name
        self.children = []
    
    def operation(self):
        print(f"Composite {self.name}: Performing operation")
        for child in self.children:
            child.operation()
    
    def add(self, component):
        self.children.append(component)
    
    def remove(self, component):
        self.children.remove(component)
    
    def get_child(self, index):
        return self.children[index]

# Usage - file system example
root = Composite("root")
home = Composite("home")
user = Composite("user")

file1 = Leaf("document.txt")
file2 = Leaf("image.jpg")
file3 = Leaf("music.mp3")

user.add(file1)
user.add(file2)
home.add(user)
home.add(file3)
root.add(home)

print("File system structure:")
root.operation()
```

#### Behavioral Patterns

##### Command Pattern - Encapsulate Requests
```python
class Command(ABC):
    """Command interface."""
    
    @abstractmethod
    def execute(self):
        pass
    
    @abstractmethod
    def undo(self):
        pass

class Light:
    """Receiver class."""
    
    def __init__(self):
        self.is_on = False
    
    def turn_on(self):
        self.is_on = True
        print("Light is ON")
    
    def turn_off(self):
        self.is_on = False
        print("Light is OFF")

class LightOnCommand(Command):
    """Concrete command."""
    
    def __init__(self, light):
        self.light = light
    
    def execute(self):
        self.light.turn_on()
    
    def undo(self):
        self.light.turn_off()

class LightOffCommand(Command):
    """Concrete command."""
    
    def __init__(self, light):
        self.light = light
    
    def execute(self):
        self.light.turn_off()
    
    def undo(self):
        self.light.turn_on()

class RemoteControl:
    """Invoker class."""
    
    def __init__(self):
        self.command_history = []
    
    def execute_command(self, command):
        command.execute()
        self.command_history.append(command)
    
    def undo_last_command(self):
        if self.command_history:
            last_command = self.command_history.pop()
            last_command.undo()

# Usage
light = Light()
light_on = LightOnCommand(light)
light_off = LightOffCommand(light)

remote = RemoteControl()

remote.execute_command(light_on)   # Light is ON
remote.execute_command(light_off)  # Light is OFF
remote.undo_last_command()         # Light is ON (undo)
```

##### State Pattern - Object Behavior Changes
```python
class TrafficLightState(ABC):
    """State interface."""
    
    @abstractmethod
    def handle(self, context):
        pass

class RedLight(TrafficLightState):
    def handle(self, context):
        print("Red light: STOP")
        context.set_state(GreenLight())

class YellowLight(TrafficLightState):
    def handle(self, context):
        print("Yellow light: CAUTION")
        context.set_state(RedLight())

class GreenLight(TrafficLightState):
    def handle(self, context):
        print("Green light: GO")
        context.set_state(YellowLight())

class TrafficLight:
    """Context class."""
    
    def __init__(self):
        self.state = RedLight()
    
    def set_state(self, state):
        self.state = state
    
    def change(self):
        self.state.handle(self)

# Usage
traffic_light = TrafficLight()

for _ in range(6):
    traffic_light.change()
```

### When to Use OOP - Decision Framework

#### Use OOP When:

1. **Complex Domain Models**
   - Real-world entities with complex relationships
   - Business logic that changes frequently
   - Need to model inheritance hierarchies

2. **Large-Scale Applications**
   - Multiple developers working on the same codebase
   - Long-term maintenance requirements
   - Need for extensibility and modularity

3. **Code Reusability**
   - Similar objects with shared behavior
   - Need to create multiple instances of similar objects
   - Want to leverage inheritance and polymorphism

4. **Data Encapsulation**
   - Need to protect data integrity
   - Complex data validation requirements
   - Want to hide implementation details

#### Avoid OOP When:

1. **Simple Scripts**
   - Small, one-time programs
   - Simple data processing tasks
   - Prototyping and experimentation

2. **Performance-Critical Code**
   - Real-time systems with strict timing requirements
   - Embedded systems with limited memory
   - High-performance computing applications

3. **Functional Programming Better Suited**
   - Heavy mathematical computations
   - Data transformation pipelines
   - Immutable data processing

4. **Simple Data Storage**
   - Basic CRUD operations
   - Simple data structures
   - No complex relationships

### OOP Anti-Patterns to Avoid

#### 1. God Object (God Class)
```python
# Bad: Single class doing everything
class Application:
    def __init__(self):
        self.users = []
        self.products = []
        self.orders = []
    
    def add_user(self, user):
        # User management logic
        pass
    
    def process_payment(self, order):
        # Payment processing logic
        pass
    
    def generate_report(self):
        # Report generation logic
        pass
    
    def send_email(self, recipient, message):
        # Email sending logic
        pass

# Good: Separate responsibilities
class UserService:
    def add_user(self, user):
        pass

class PaymentService:
    def process_payment(self, order):
        pass

class ReportService:
    def generate_report(self):
        pass

class EmailService:
    def send_email(self, recipient, message):
        pass
```

#### 2. Anemic Domain Model
```python
# Bad: Objects with no behavior
class User:
    def __init__(self, name, email):
        self.name = name
        self.email = email
        # Only data, no behavior

class UserService:
    def validate_user(self, user):
        # All logic in service class
        pass
    
    def save_user(self, user):
        pass

# Good: Rich domain model
class User:
    def __init__(self, name, email):
        self.name = name
        self.email = email
    
    def is_valid(self):
        return len(self.name) > 0 and '@' in self.email
    
    def change_email(self, new_email):
        if '@' not in new_email:
            raise ValueError("Invalid email")
        self.email = new_email
```

#### 3. Circular Dependencies
```python
# Bad: Circular dependency
class A:
    def __init__(self):
        self.b = B(self)

class B:
    def __init__(self, a):
        self.a = a

# Good: Dependency injection
class A:
    def __init__(self, b):
        self.b = b

class B:
    def __init__(self):
        pass
```

### Testing Object-Oriented Code

#### Unit Testing Classes
```python
import unittest
from unittest.mock import Mock, patch

class TestUser(unittest.TestCase):
    def setUp(self):
        self.user = User("John Doe", "john@example.com")
    
    def test_user_creation(self):
        self.assertEqual(self.user.name, "John Doe")
        self.assertEqual(self.user.email, "john@example.com")
    
    def test_email_validation(self):
        with self.assertRaises(ValueError):
            self.user.change_email("invalid-email")
    
    def test_valid_email_change(self):
        self.user.change_email("john.doe@example.com")
        self.assertEqual(self.user.email, "john.doe@example.com")

class TestPaymentProcessor(unittest.TestCase):
    def setUp(self):
        self.processor = CreditCardProcessor()
    
    @patch('some_payment_gateway.charge')
    def test_successful_payment(self, mock_charge):
        mock_charge.return_value = {'status': 'success', 'transaction_id': '123'}
        
        result = self.processor.process_payment(100.0)
        self.assertTrue(result)
        mock_charge.assert_called_once_with(100.0)

if __name__ == '__main__':
    unittest.main()
```

### Summary

Object-Oriented Programming is a powerful paradigm for building complex, maintainable software systems. The four pillars - Encapsulation, Inheritance, Polymorphism, and Abstraction - provide the foundation for creating well-structured code.

Design patterns offer proven solutions to common design problems, while SOLID principles guide the creation of flexible, maintainable systems. Understanding when to use OOP versus other paradigms is crucial for making appropriate technology choices.

The key to mastering OOP is practice: implementing classes with proper encapsulation, designing inheritance hierarchies thoughtfully, applying design patterns appropriately, and following SOLID principles consistently. With experience, these concepts become intuitive, leading to cleaner, more maintainable, and extensible software systems.

## Comprehensive Exercises

### Basic OOP Mastery
1. **Class Design**: Create a `BankAccount` class with proper encapsulation
2. **Inheritance Hierarchy**: Design a vehicle inheritance hierarchy
3. **Polymorphism**: Implement a shape drawing system with polymorphism
4. **Abstract Classes**: Create an abstract `Animal` class with concrete implementations

### Design Patterns Implementation
5. **Singleton**: Implement a configuration manager
6. **Factory**: Create a vehicle factory for different types
7. **Observer**: Build a weather monitoring system
8. **Strategy**: Implement different sorting strategies
9. **Decorator**: Add features to a coffee ordering system
10. **Command**: Create an undo/redo system for text editing

### SOLID Principles Application
11. **SRP**: Refactor a god class into smaller, focused classes
12. **OCP**: Extend a system without modifying existing code
13. **LSP**: Ensure proper substitutability in inheritance hierarchies
14. **ISP**: Break down fat interfaces into smaller, specific ones
15. **DIP**: Refactor tight coupling to use dependency injection

### Real-World Applications
16. **Library Management System**: Books, members, borrowing with OOP design
17. **E-commerce System**: Products, shopping cart, orders with proper encapsulation
18. **Game Character System**: Characters with different abilities using inheritance
19. **File System Simulator**: Directories and files with composite pattern
20. **Task Management Application**: Projects, tasks, users with observer pattern

### Advanced Challenges
21. **Custom Collections**: Implement your own list, set, and map classes
22. **Expression Evaluator**: Build a calculator with proper operator precedence
23. **State Machine**: Implement a traffic light or vending machine
24. **Plugin Architecture**: Create an extensible system using factories
25. **Domain Modeling**: Design classes for a complex business domain

Remember: OOP is about modeling real-world concepts in code. Focus on creating classes that represent meaningful entities with proper relationships, encapsulation, and behavior. Practice designing systems that are easy to understand, maintain, and extend.

## Further Reading and Resources

### Classic Books
- **"Design Patterns: Elements of Reusable Object-Oriented Software"** by Gang of Four
- **"Clean Code: A Handbook of Agile Software Craftsmanship"** by Robert C. Martin
- **"Head First Design Patterns"** by Eric Freeman and Elisabeth Robson
- **"Refactoring: Improving the Design of Existing Code"** by Martin Fowler

### Advanced Topics
- **"Domain-Driven Design"** by Eric Evans
- **"Patterns of Enterprise Application Architecture"** by Martin Fowler
- **"Object-Oriented Analysis and Design with Applications"** by Grady Booch

### Online Resources
- **Refactoring.Guru**: Design patterns and refactoring techniques
- **SourceMaking**: Design patterns with examples
- **OODesign**: Object-oriented design principles
- **SOLID Principles**: In-depth explanations

### Communities
- **Stack Overflow**: OOP design questions
- **Reddit r/programming**: Design discussions
- **Software Engineering Stack Exchange**: Architecture questions
- **Design Patterns Google Group**: Pattern discussions

Mastering Object-Oriented Programming requires understanding both the principles and their practical application. Focus on writing clean, maintainable code that follows established patterns and principles. With practice, OOP becomes a natural way to structure complex software systems.
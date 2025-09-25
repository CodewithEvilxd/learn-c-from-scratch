# 11. Advanced Topics - Building Production-Ready Applications

## Introduction

This comprehensive chapter explores advanced programming concepts essential for building robust, scalable, and production-ready applications. We'll dive deep into error handling strategies, file system operations, database design and optimization, networking protocols and architectures, concurrent and parallel programming, memory management techniques, security best practices, testing methodologies, and performance optimization. These topics bridge the gap between academic programming knowledge and real-world software development.

## Advanced Error Handling and Resilience

### Comprehensive Exception Handling Patterns

#### Exception Hierarchy and Custom Exceptions

```python
class ApplicationError(Exception):
    """Base exception for application-specific errors."""
    pass

class ValidationError(ApplicationError):
    """Raised when input validation fails."""
    def __init__(self, field, value, message=None):
        self.field = field
        self.value = value
        self.message = message or f"Invalid value for {field}: {value}"
        super().__init__(self.message)

class DatabaseError(ApplicationError):
    """Raised when database operations fail."""
    def __init__(self, operation, details=None):
        self.operation = operation
        self.details = details
        message = f"Database operation '{operation}' failed"
        if details:
            message += f": {details}"
        super().__init__(message)

class NetworkError(ApplicationError):
    """Raised when network operations fail."""
    def __init__(self, url, status_code=None, message=None):
        self.url = url
        self.status_code = status_code
        self.message = message or f"Network request to {url} failed"
        if status_code:
            self.message += f" (HTTP {status_code})"
        super().__init__(self.message)

# Usage
def validate_user_data(user_data):
    if not user_data.get('email'):
        raise ValidationError('email', user_data.get('email'))
    if '@' not in user_data['email']:
        raise ValidationError('email', user_data['email'], 'Invalid email format')

def save_user_to_db(user_data):
    try:
        validate_user_data(user_data)
        # Simulate database operation
        if user_data['email'] == 'error@example.com':
            raise DatabaseError('insert_user', 'Connection timeout')
        print(f"User {user_data['email']} saved successfully")
    except ValidationError as e:
        print(f"Validation failed: {e}")
        raise
    except DatabaseError as e:
        print(f"Database error: {e}")
        # Could implement retry logic here
        raise

# Robust error handling with context
def process_user_registration(user_data):
    try:
        save_user_to_db(user_data)
        send_welcome_email(user_data['email'])
        return True
    except ValidationError:
        # Log validation errors but don't retry
        log_error("Validation failed for user registration")
        return False
    except (DatabaseError, NetworkError) as e:
        # Log and potentially retry for transient errors
        log_error(f"Transient error in user registration: {e}")
        # Could implement exponential backoff retry
        return False
    except Exception as e:
        # Catch-all for unexpected errors
        log_error(f"Unexpected error in user registration: {e}")
        return False
    finally:
        # Always executed - cleanup resources
        cleanup_temp_files()

def send_welcome_email(email):
    # Simulate network operation
    if email == 'network_error@example.com':
        raise NetworkError('smtp.gmail.com', 500)
    print(f"Welcome email sent to {email}")

def log_error(message):
    print(f"ERROR: {message}")

def cleanup_temp_files():
    print("Cleaning up temporary files")

# Usage examples
process_user_registration({'email': 'user@example.com'})  # Success
process_user_registration({'email': 'invalid'})  # Validation error
process_user_registration({'email': 'error@example.com'})  # Database error
process_user_registration({'email': 'network_error@example.com'})  # Network error
```

#### Context Managers for Resource Management

```python
class DatabaseConnection:
    """Context manager for database connections."""
    
    def __init__(self, connection_string):
        self.connection_string = connection_string
        self.connection = None
    
    def __enter__(self):
        # Establish connection
        self.connection = f"Connected to {self.connection_string}"
        print(f"Opening database connection: {self.connection}")
        return self.connection
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        # Clean up connection
        print(f"Closing database connection: {self.connection}")
        self.connection = None
        
        # Handle exceptions if needed
        if exc_type:
            print(f"Exception occurred: {exc_val}")
            # Could implement rollback logic here
            return False  # Re-raise exception
        return True

# Usage
def perform_database_operation():
    with DatabaseConnection("postgresql://localhost/mydb") as conn:
        print(f"Performing operation with {conn}")
        # Simulate operation
        if random.choice([True, False]):  # Random failure for demo
            raise Exception("Database operation failed")
        print("Operation completed successfully")

# Multiple context managers
def complex_operation():
    with DatabaseConnection("db1") as db1, \
         DatabaseConnection("db2") as db2, \
         open("log.txt", "a") as log_file:
        
        print("Performing complex operation with multiple resources")
        log_file.write("Operation started\n")
        # Perform operations with db1, db2, and log_file
        log_file.write("Operation completed\n")

# Custom context manager decorator
from contextlib import contextmanager

@contextmanager
def transaction_scope(db_connection):
    """Context manager for database transactions."""
    try:
        print("Starting transaction")
        # Begin transaction
        yield db_connection
        print("Committing transaction")
        # Commit transaction
    except Exception as e:
        print(f"Rolling back transaction due to: {e}")
        # Rollback transaction
        raise
    finally:
        print("Transaction scope exited")

# Usage
with transaction_scope("my_db_connection") as conn:
    # Perform transactional operations
    print(f"Working with {conn}")
    # If exception occurs here, transaction rolls back
```

#### Circuit Breaker Pattern for Resilience

```python
import time
from enum import Enum

class CircuitState(Enum):
    CLOSED = "closed"      # Normal operation
    OPEN = "open"         # Failing, requests rejected
    HALF_OPEN = "half_open"  # Testing if service recovered

class CircuitBreaker:
    """Circuit breaker for fault tolerance."""
    
    def __init__(self, failure_threshold=5, recovery_timeout=60, expected_exception=Exception):
        self.failure_threshold = failure_threshold
        self.recovery_timeout = recovery_timeout
        self.expected_exception = expected_exception
        
        self.failure_count = 0
        self.last_failure_time = None
        self.state = CircuitState.CLOSED
    
    def call(self, func, *args, **kwargs):
        """Execute function with circuit breaker protection."""
        if self.state == CircuitState.OPEN:
            if self._should_attempt_reset():
                self.state = CircuitState.HALF_OPEN
            else:
                raise Exception("Circuit breaker is OPEN")
        
        try:
            result = func(*args, **kwargs)
            self._on_success()
            return result
        except self.expected_exception as e:
            self._on_failure()
            raise e
    
    def _should_attempt_reset(self):
        """Check if enough time has passed to attempt reset."""
        if self.last_failure_time is None:
            return True
        return time.time() - self.last_failure_time >= self.recovery_timeout
    
    def _on_success(self):
        """Handle successful call."""
        if self.state == CircuitState.HALF_OPEN:
            self.state = CircuitState.CLOSED
            self.failure_count = 0
            print("Circuit breaker reset to CLOSED")
    
    def _on_failure(self):
        """Handle failed call."""
        self.failure_count += 1
        self.last_failure_time = time.time()
        
        if self.failure_count >= self.failure_threshold:
            self.state = CircuitState.OPEN
            print(f"Circuit breaker opened after {self.failure_count} failures")
        elif self.state == CircuitState.HALF_OPEN:
            self.state = CircuitState.OPEN
            print("Circuit breaker opened during HALF_OPEN state")

# Usage
def unreliable_service():
    """Simulate an unreliable service."""
    import random
    if random.random() < 0.7:  # 70% failure rate
        raise ConnectionError("Service temporarily unavailable")
    return "Service response"

circuit_breaker = CircuitBreaker(failure_threshold=3, recovery_timeout=10)

# Test the circuit breaker
for i in range(10):
    try:
        result = circuit_breaker.call(unreliable_service)
        print(f"Call {i+1}: Success - {result}")
    except Exception as e:
        print(f"Call {i+1}: Failed - {e}")
    
    time.sleep(1)  # Wait between calls

print(f"Final circuit state: {circuit_breaker.state.value}")
```

## Error Handling

Error handling prevents programs from crashing and provides graceful recovery from unexpected situations.

### Types of Errors

1. **Syntax Errors**: Code structure problems (detected at compile time)
2. **Runtime Errors**: Occur during execution (e.g., division by zero)
3. **Logical Errors**: Code runs but produces wrong results

### Exception Handling

**Python:**
```python
try:
    # Code that might raise an exception
    result = 10 / 0
except ZeroDivisionError:
    print("Cannot divide by zero!")
except Exception as e:
    print(f"An error occurred: {e}")
else:
    print("No errors occurred")
finally:
    print("This always executes")
```

**Java:**
```java
try {
    int result = 10 / 0;
} catch (ArithmeticException e) {
    System.out.println("Cannot divide by zero!");
} catch (Exception e) {
    System.out.println("An error occurred: " + e.getMessage());
} finally {
    System.out.println("This always executes");
}
```

### Custom Exceptions

**Python:**
```python
class InsufficientFundsError(Exception):
    pass

def withdraw(balance, amount):
    if amount > balance:
        raise InsufficientFundsError("Not enough funds")
    return balance - amount

try:
    withdraw(100, 150)
except InsufficientFundsError as e:
    print(e)
```

## Advanced File I/O and Data Persistence

### Comprehensive File Operations

#### File Modes and Operations

```python
# File mode reference
"""
'r'  - read (default)
'w'  - write (truncates file)
'x'  - exclusive creation (fails if file exists)
'a'  - append
'b'  - binary mode
't'  - text mode (default)
'+'  - read and write
"""

# Advanced file reading techniques
def read_file_advanced(filename, mode='r', encoding='utf-8'):
    """Advanced file reading with multiple techniques."""
    
    # Method 1: Read entire file
    with open(filename, mode, encoding=encoding) as f:
        content = f.read()
        print(f"Entire file content:\n{content}")
    
    # Method 2: Read line by line
    with open(filename, mode, encoding=encoding) as f:
        for line_num, line in enumerate(f, 1):
            print(f"Line {line_num}: {line.rstrip()}")
    
    # Method 3: Read specific number of characters
    with open(filename, mode, encoding=encoding) as f:
        chunk = f.read(100)  # Read first 100 characters
        print(f"First 100 chars: {chunk}")
    
    # Method 4: Read all lines into list
    with open(filename, mode, encoding=encoding) as f:
        lines = f.readlines()
        print(f"Total lines: {len(lines)}")
        print(f"First line: {lines[0].rstrip()}")
    
    # Method 5: Read with seek and tell
    with open(filename, mode, encoding=encoding) as f:
        print(f"File size: {f.seek(0, 2)} bytes")  # Seek to end
        f.seek(0)  # Back to beginning
        print(f"Current position: {f.tell()}")

# Advanced writing techniques
def write_file_advanced(filename, data, mode='w', encoding='utf-8'):
    """Advanced file writing with different modes."""
    
    # Write with automatic newline handling
    with open(filename, mode, encoding=encoding) as f:
        if isinstance(data, list):
            f.writelines(line + '\n' for line in data)
        else:
            f.write(str(data))
    
    # Append mode
    with open(filename, 'a', encoding=encoding) as f:
        f.write(f"\nAppended at {time.strftime('%Y-%m-%d %H:%M:%S')}")
    
    # Exclusive creation (fails if file exists)
    try:
        with open(filename + '.new', 'x', encoding=encoding) as f:
            f.write("This file was created exclusively")
    except FileExistsError:
        print("File already exists, cannot create exclusively")

# Binary file operations
def binary_file_operations():
    """Demonstrate binary file operations."""
    
    # Write binary data
    data = bytes([0x48, 0x65, 0x6C, 0x6C, 0x6F])  # "Hello" in bytes
    with open('binary_file.bin', 'wb') as f:
        f.write(data)
        f.write(b' World!')  # Direct bytes
    
    # Read binary data
    with open('binary_file.bin', 'rb') as f:
        binary_content = f.read()
        print(f"Binary content: {binary_content}")
        print(f"As string: {binary_content.decode('utf-8')}")

# File system operations
import os
import shutil
from pathlib import Path

def file_system_operations():
    """Comprehensive file system operations."""
    
    # Create directory
    os.makedirs('test_directory/subdir', exist_ok=True)
    
    # Write test files
    for i in range(3):
        with open(f'test_directory/file_{i}.txt', 'w') as f:
            f.write(f'Content of file {i}\n')
    
    # List directory contents
    print("Directory contents:")
    for item in os.listdir('test_directory'):
        item_path = os.path.join('test_directory', item)
        if os.path.isfile(item_path):
            size = os.path.getsize(item_path)
            print(f"File: {item} ({size} bytes)")
        else:
            print(f"Directory: {item}")
    
    # File information
    test_file = 'test_directory/file_0.txt'
    if os.path.exists(test_file):
        stat = os.stat(test_file)
        print(f"File info: size={stat.st_size}, modified={stat.st_mtime}")
    
    # Copy and move files
    shutil.copy('test_directory/file_0.txt', 'test_directory/file_0_copy.txt')
    shutil.move('test_directory/file_1.txt', 'test_directory/subdir/file_1_moved.txt')
    
    # Remove files and directories
    os.remove('test_directory/file_0_copy.txt')
    shutil.rmtree('test_directory/subdir')
    
    # Path operations with pathlib
    path = Path('test_directory/file_2.txt')
    print(f"Path: {path}")
    print(f"Name: {path.name}")
    print(f"Stem: {path.stem}")
    print(f"Suffix: {path.suffix}")
    print(f"Parent: {path.parent}")
    print(f"Exists: {path.exists()}")
    print(f"Is file: {path.is_file()}")

# CSV file processing
import csv

def csv_operations():
    """Advanced CSV file operations."""
    
    # Writing CSV
    data = [
        ['Name', 'Age', 'City'],
        ['Alice', 25, 'New York'],
        ['Bob', 30, 'San Francisco'],
        ['Charlie', 35, 'Chicago']
    ]
    
    with open('people.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(data)
    
    # Reading CSV
    with open('people.csv', 'r', newline='') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)  # Skip header
        print(f"Header: {header}")
        
        for row in reader:
            name, age, city = row
            print(f"{name} is {age} years old and lives in {city}")
    
    # CSV with dictionaries
    people = [
        {'name': 'Alice', 'age': 25, 'city': 'New York'},
        {'name': 'Bob', 'age': 30, 'city': 'San Francisco'}
    ]
    
    with open('people_dict.csv', 'w', newline='') as csvfile:
        fieldnames = ['name', 'age', 'city']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(people)
    
    with open('people_dict.csv', 'r', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            print(f"{row['name']} ({row['age']}) - {row['city']}")

# JSON file processing
import json

def json_operations():
    """Advanced JSON file operations."""
    
    # Complex data structure
    data = {
        'company': 'Tech Corp',
        'employees': [
            {
                'name': 'Alice',
                'age': 25,
                'skills': ['Python', 'JavaScript'],
                'projects': [
                    {'name': 'Web App', 'status': 'completed'},
                    {'name': 'API', 'status': 'in_progress'}
                ]
            },
            {
                'name': 'Bob',
                'age': 30,
                'skills': ['Java', 'C++'],
                'projects': [
                    {'name': 'Mobile App', 'status': 'completed'}
                ]
            }
        ],
        'metadata': {
            'created': '2024-01-01',
            'version': '1.0'
        }
    }
    
    # Write JSON with pretty printing
    with open('company_data.json', 'w') as jsonfile:
        json.dump(data, jsonfile, indent=2, sort_keys=True)
    
    # Read JSON
    with open('company_data.json', 'r') as jsonfile:
        loaded_data = json.load(jsonfile)
        print(f"Company: {loaded_data['company']}")
        print(f"Number of employees: {len(loaded_data['employees'])}")
        
        for employee in loaded_data['employees']:
            print(f"- {employee['name']}: {', '.join(employee['skills'])}")

# Configuration file handling
import configparser

def config_file_operations():
    """Handle configuration files."""
    
    config = configparser.ConfigParser()
    
    # Create configuration
    config['DATABASE'] = {
        'host': 'localhost',
        'port': '5432',
        'database': 'mydb',
        'user': 'admin',
        'password': 'secret'
    }
    
    config['APP'] = {
        'debug': 'true',
        'log_level': 'INFO',
        'max_connections': '100'
    }
    
    # Write configuration file
    with open('app_config.ini', 'w') as configfile:
        config.write(configfile)
    
    # Read configuration file
    config.read('app_config.ini')
    
    # Access configuration values
    db_host = config['DATABASE']['host']
    debug_mode = config.getboolean('APP', 'debug')
    max_conn = config.getint('APP', 'max_connections')
    
    print(f"Database host: {db_host}")
    print(f"Debug mode: {debug_mode}")
    print(f"Max connections: {max_conn}")

# File compression and archiving
import zipfile
import gzip

def compression_operations():
    """File compression and archiving."""
    
    # Create ZIP archive
    with zipfile.ZipFile('archive.zip', 'w', zipfile.ZIP_DEFLATED) as zipf:
        zipf.write('company_data.json')
        zipf.write('people.csv')
        zipf.write('app_config.ini')
    
    # List ZIP contents
    with zipfile.ZipFile('archive.zip', 'r') as zipf:
        print("ZIP archive contents:")
        for info in zipf.filelist:
            print(f"- {info.filename} ({info.file_size} bytes)")
    
    # Extract ZIP
    with zipfile.ZipFile('archive.zip', 'r') as zipf:
        zipf.extractall('extracted_files')
    
    # GZIP compression
    with open('large_text.txt', 'w') as f:
        f.write('This is a large text file. ' * 1000)
    
    with open('large_text.txt', 'rb') as f_in:
        with gzip.open('large_text.txt.gz', 'wb') as f_out:
            f_out.writelines(f_in)
    
    # Compare file sizes
    original_size = os.path.getsize('large_text.txt')
    compressed_size = os.path.getsize('large_text.txt.gz')
    compression_ratio = (1 - compressed_size / original_size) * 100
    
    print(f"Original size: {original_size} bytes")
    print(f"Compressed size: {compressed_size} bytes")
    print(f"Compression ratio: {compression_ratio:.1f}%")

# Temporary files and cleanup
import tempfile

def temporary_file_operations():
    """Working with temporary files."""
    
    # Create temporary file
    with tempfile.NamedTemporaryFile(mode='w+', suffix='.txt', delete=False) as temp_file:
        temp_file.write("This is temporary data\n")
        temp_file.write("It will be automatically cleaned up\n")
        temp_filename = temp_file.name
        print(f"Temporary file created: {temp_filename}")
    
    # Read temporary file
    with open(temp_filename, 'r') as f:
        content = f.read()
        print(f"Temporary file content:\n{content}")
    
    # Clean up
    os.unlink(temp_filename)
    print("Temporary file cleaned up")
    
    # Temporary directory
    with tempfile.TemporaryDirectory() as temp_dir:
        temp_file_path = os.path.join(temp_dir, 'temp_data.txt')
        with open(temp_file_path, 'w') as f:
            f.write("Data in temporary directory")
        
        print(f"Created file in temp directory: {temp_file_path}")
        print(f"Temp directory exists: {os.path.exists(temp_dir)}")
    
    # Temp directory automatically cleaned up
    print(f"Temp directory cleaned up: {not os.path.exists(temp_dir)}")

# File watching and monitoring
import time

def file_monitoring():
    """Monitor file changes."""
    
    def get_file_info(filepath):
        if os.path.exists(filepath):
            stat = os.stat(filepath)
            return {
                'size': stat.st_size,
                'modified': stat.st_mtime,
                'exists': True
            }
        return {'exists': False}
    
    filename = 'monitor_test.txt'
    
    # Create initial file
    with open(filename, 'w') as f:
        f.write("Initial content")
    
    initial_info = get_file_info(filename)
    print(f"Initial file state: {initial_info}")
    
    # Monitor for changes
    print("Monitoring file for 10 seconds...")
    for i in range(10):
        time.sleep(1)
        current_info = get_file_info(filename)
        
        if current_info != initial_info:
            print(f"File changed at second {i+1}: {current_info}")
            initial_info = current_info
    
    # Clean up
    os.remove(filename)

# Execute all file operations
if __name__ == "__main__":
    # Create sample file for demonstration
    with open('example.txt', 'w') as f:
        f.write("This is the first line.\n")
        f.write("This is the second line.\n")
        f.write("This is the third line.\n")
    
    print("=== File Reading Techniques ===")
    read_file_advanced('example.txt')
    
    print("\n=== File Writing Techniques ===")
    write_file_advanced('output.txt', ['Line 1', 'Line 2', 'Line 3'])
    
    print("\n=== Binary File Operations ===")
    binary_file_operations()
    
    print("\n=== File System Operations ===")
    file_system_operations()
    
    print("\n=== CSV Operations ===")
    csv_operations()
    
    print("\n=== JSON Operations ===")
    json_operations()
    
    print("\n=== Configuration Files ===")
    config_file_operations()
    
    print("\n=== Compression Operations ===")
    compression_operations()
    
    print("\n=== Temporary Files ===")
    temporary_file_operations()
    
    print("\n=== File Monitoring ===")
    file_monitoring()
```

## Advanced Database Design and Management

### Database Architecture and Design Principles

#### Database Types and Selection Criteria

```python
# Database type comparison
DATABASE_TYPES = {
    'Relational': {
        'examples': ['PostgreSQL', 'MySQL', 'SQLite', 'Oracle'],
        'use_cases': ['Financial data', 'E-commerce', 'CRM systems'],
        'strengths': ['ACID compliance', 'Complex queries', 'Data integrity'],
        'weaknesses': ['Scalability challenges', 'Schema rigidity']
    },
    'NoSQL': {
        'examples': ['MongoDB', 'Cassandra', 'Redis', 'CouchDB'],
        'use_cases': ['Big data', 'Real-time analytics', 'Content management'],
        'strengths': ['Horizontal scaling', 'Flexible schemas', 'High performance'],
        'weaknesses': ['Eventual consistency', 'Complex joins']
    },
    'Graph': {
        'examples': ['Neo4j', 'Amazon Neptune', 'ArangoDB'],
        'use_cases': ['Social networks', 'Recommendation systems', 'Fraud detection'],
        'strengths': ['Relationship modeling', 'Complex traversals', 'Pattern matching'],
        'weaknesses': ['Learning curve', 'Limited aggregation']
    },
    'Time-Series': {
        'examples': ['InfluxDB', 'TimescaleDB', 'OpenTSDB'],
        'use_cases': ['IoT data', 'Metrics collection', 'Financial trading'],
        'strengths': ['Time-based queries', 'Data compression', 'Retention policies'],
        'weaknesses': ['Limited general-purpose use']
    }
}

def recommend_database(requirements):
    """Recommend database type based on requirements."""
    recommendations = []
    
    if requirements.get('complex_relationships'):
        recommendations.append('Graph')
    if requirements.get('high_scalability'):
        recommendations.append('NoSQL')
    if requirements.get('time_series_data'):
        recommendations.append('Time-Series')
    if requirements.get('acid_compliance'):
        recommendations.append('Relational')
    
    return recommendations if recommendations else ['Relational']

# Usage
print("Database recommendations for social network:")
print(recommend_database({
    'complex_relationships': True,
    'high_scalability': True,
    'acid_compliance': False
}))

print("\nDatabase recommendations for banking system:")
print(recommend_database({
    'complex_relationships': False,
    'high_scalability': False,
    'acid_compliance': True
}))
```

#### Database Design Principles

```sql
-- Example: E-commerce database design
-- Following normalization principles

-- 1NF: Atomic values, no repeating groups
CREATE TABLE customers (
    customer_id INTEGER PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 2NF: No partial dependencies
CREATE TABLE products (
    product_id INTEGER PRIMARY KEY,
    product_name VARCHAR(100) NOT NULL,
    description TEXT,
    base_price DECIMAL(10,2) NOT NULL,
    category_id INTEGER,
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
);

CREATE TABLE categories (
    category_id INTEGER PRIMARY KEY,
    category_name VARCHAR(50) NOT NULL,
    description TEXT
);

-- 3NF: No transitive dependencies
CREATE TABLE orders (
    order_id INTEGER PRIMARY KEY,
    customer_id INTEGER NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    total_amount DECIMAL(10,2) NOT NULL,
    status VARCHAR(20) DEFAULT 'pending',
    shipping_address_id INTEGER,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (shipping_address_id) REFERENCES addresses(address_id)
);

CREATE TABLE addresses (
    address_id INTEGER PRIMARY KEY,
    customer_id INTEGER NOT NULL,
    street_address VARCHAR(255) NOT NULL,
    city VARCHAR(50) NOT NULL,
    state VARCHAR(50),
    postal_code VARCHAR(20),
    country VARCHAR(50) DEFAULT 'USA',
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- Denormalization for performance (careful use)
CREATE TABLE order_summary (
    order_id INTEGER PRIMARY KEY,
    customer_name VARCHAR(101), -- Denormalized: first_name + ' ' + last_name
    customer_email VARCHAR(100), -- Denormalized
    order_date TIMESTAMP,
    total_amount DECIMAL(10,2),
    status VARCHAR(20)
);
```

### Advanced SQL and Query Optimization

#### Complex Queries and Analytics

```sql
-- Window functions for analytics
SELECT
    product_name,
    category_name,
    sales_amount,
    ROW_NUMBER() OVER (PARTITION BY category_name ORDER BY sales_amount DESC) as category_rank,
    RANK() OVER (ORDER BY sales_amount DESC) as overall_rank,
    PERCENT_RANK() OVER (ORDER BY sales_amount) as percent_rank,
    LAG(sales_amount, 1) OVER (ORDER BY sales_date) as prev_sales,
    LEAD(sales_amount, 1) OVER (ORDER BY sales_date) as next_sales
FROM product_sales ps
JOIN products p ON ps.product_id = p.product_id
JOIN categories c ON p.category_id = c.category_id;

-- Recursive queries for hierarchical data
WITH RECURSIVE employee_hierarchy AS (
    -- Base case: top-level managers
    SELECT
        employee_id,
        manager_id,
        first_name || ' ' || last_name as full_name,
        0 as level,
        ARRAY[employee_id] as path
    FROM employees
    WHERE manager_id IS NULL
    
    UNION ALL
    
    -- Recursive case: subordinates
    SELECT
        e.employee_id,
        e.manager_id,
        e.first_name || ' ' || e.last_name,
        eh.level + 1,
        eh.path || e.employee_id
    FROM employees e
    JOIN employee_hierarchy eh ON e.manager_id = eh.employee_id
)
SELECT * FROM employee_hierarchy ORDER BY level, employee_id;

-- Advanced aggregation with grouping sets
SELECT
    COALESCE(category_name, 'ALL CATEGORIES') as category,
    COALESCE(region, 'ALL REGIONS') as region,
    SUM(sales_amount) as total_sales,
    AVG(sales_amount) as avg_sale,
    COUNT(*) as transaction_count
FROM sales s
LEFT JOIN products p ON s.product_id = p.product_id
LEFT JOIN categories c ON p.category_id = c.category_id
GROUP BY GROUPING SETS (
    (category_name, region),
    (category_name),
    (region),
    ()
)
ORDER BY category, region;

-- JSON operations in PostgreSQL
CREATE TABLE user_profiles (
    user_id INTEGER PRIMARY KEY,
    profile_data JSONB
);

-- Insert JSON data
INSERT INTO user_profiles (user_id, profile_data) VALUES
(1, '{"name": "Alice", "age": 30, "skills": ["Python", "JavaScript"], "preferences": {"theme": "dark", "notifications": true}}'),
(2, '{"name": "Bob", "age": 25, "skills": ["Java", "C++"], "preferences": {"theme": "light", "notifications": false}}');

-- Query JSON data
SELECT
    user_id,
    profile_data->>'name' as name,
    profile_data->>'age' as age,
    jsonb_array_length(profile_data->'skills') as skill_count,
    profile_data->'preferences'->>'theme' as theme
FROM user_profiles
WHERE profile_data->>'age'::integer > 26;

-- Update JSON data
UPDATE user_profiles
SET profile_data = jsonb_set(profile_data, '{preferences,notifications}', 'false'::jsonb)
WHERE profile_data->>'name' = 'Alice';
```

#### Python Database Integration with Advanced Features

```python
import sqlite3
import psycopg2  # For PostgreSQL
from contextlib import contextmanager
import time
import logging

# Set up logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class DatabaseManager:
    """Advanced database manager with connection pooling and error handling."""
    
    def __init__(self, db_type='sqlite', **db_config):
        self.db_type = db_type
        self.db_config = db_config
        self.connection_pool = []
        self.max_pool_size = db_config.get('max_pool_size', 10)
    
    @contextmanager
    def get_connection(self):
        """Context manager for database connections."""
        conn = None
        try:
            if self.connection_pool:
                conn = self.connection_pool.pop()
            else:
                conn = self._create_connection()
            
            yield conn
            
        except Exception as e:
            logger.error(f"Database error: {e}")
            if conn:
                conn.rollback()
            raise
        finally:
            if conn:
                if len(self.connection_pool) < self.max_pool_size:
                    self.connection_pool.append(conn)
                else:
                    conn.close()
    
    def _create_connection(self):
        """Create a new database connection."""
        if self.db_type == 'sqlite':
            return sqlite3.connect(**self.db_config)
        elif self.db_type == 'postgresql':
            return psycopg2.connect(**self.db_config)
        else:
            raise ValueError(f"Unsupported database type: {self.db_type}")
    
    def execute_query(self, query, params=None, fetch=True):
        """Execute a query with automatic connection management."""
        with self.get_connection() as conn:
            cursor = conn.cursor()
            
            start_time = time.time()
            cursor.execute(query, params or ())
            execution_time = time.time() - start_time
            
            logger.info(f"Query executed in {execution_time:.4f} seconds")
            
            if fetch:
                results = cursor.fetchall()
                return results
            else:
                conn.commit()
                return cursor.rowcount
    
    def execute_batch(self, queries):
        """Execute multiple queries in a batch."""
        with self.get_connection() as conn:
            cursor = conn.cursor()
            
            for query, params in queries:
                cursor.execute(query, params or ())
            
            conn.commit()
            return len(queries)

# Database schema management
class SchemaManager:
    """Manage database schema migrations."""
    
    def __init__(self, db_manager):
        self.db = db_manager
        self.db.execute_query("""
            CREATE TABLE IF NOT EXISTS schema_versions (
                version INTEGER PRIMARY KEY,
                applied_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                description TEXT
            )
        """, fetch=False)
    
    def apply_migration(self, version, description, migration_sql):
        """Apply a database migration."""
        # Check if migration already applied
        existing = self.db.execute_query(
            "SELECT version FROM schema_versions WHERE version = ?",
            (version,)
        )
        
        if existing:
            logger.info(f"Migration {version} already applied")
            return
        
        # Apply migration
        logger.info(f"Applying migration {version}: {description}")
        self.db.execute_query(migration_sql, fetch=False)
        
        # Record migration
        self.db.execute_query(
            "INSERT INTO schema_versions (version, description) VALUES (?, ?)",
            (version, description),
            fetch=False
        )
        
        logger.info(f"Migration {version} applied successfully")

# Data access layer
class UserRepository:
    """Repository pattern for user data access."""
    
    def __init__(self, db_manager):
        self.db = db_manager
    
    def create_user(self, user_data):
        """Create a new user."""
        query = """
            INSERT INTO users (username, email, password_hash, created_at)
            VALUES (?, ?, ?, CURRENT_TIMESTAMP)
        """
        self.db.execute_query(query, (
            user_data['username'],
            user_data['email'],
            user_data['password_hash']
        ), fetch=False)
        return self.db.execute_query("SELECT last_insert_rowid()")[0][0]
    
    def get_user_by_id(self, user_id):
        """Get user by ID."""
        query = "SELECT * FROM users WHERE id = ?"
        result = self.db.execute_query(query, (user_id,))
        return self._row_to_user(result[0]) if result else None
    
    def get_users_by_criteria(self, criteria, limit=50, offset=0):
        """Get users with flexible criteria."""
        conditions = []
        params = []
        
        if 'username' in criteria:
            conditions.append("username LIKE ?")
            params.append(f"%{criteria['username']}%")
        
        if 'email' in criteria:
            conditions.append("email = ?")
            params.append(criteria['email'])
        
        if 'created_after' in criteria:
            conditions.append("created_at > ?")
            params.append(criteria['created_after'])
        
        where_clause = " AND ".join(conditions) if conditions else "1=1"
        
        query = f"""
            SELECT * FROM users
            WHERE {where_clause}
            ORDER BY created_at DESC
            LIMIT ? OFFSET ?
        """
        
        results = self.db.execute_query(query, params + [limit, offset])
        return [self._row_to_user(row) for row in results]
    
    def update_user(self, user_id, updates):
        """Update user data."""
        set_parts = []
        params = []
        
        for field, value in updates.items():
            if field in ['username', 'email', 'password_hash']:
                set_parts.append(f"{field} = ?")
                params.append(value)
        
        if not set_parts:
            return False
        
        params.append(user_id)
        query = f"UPDATE users SET {', '.join(set_parts)} WHERE id = ?"
        
        self.db.execute_query(query, params, fetch=False)
        return True
    
    def delete_user(self, user_id):
        """Soft delete user."""
        query = "UPDATE users SET deleted_at = CURRENT_TIMESTAMP WHERE id = ?"
        self.db.execute_query(query, (user_id,), fetch=False)
        return True
    
    def _row_to_user(self, row):
        """Convert database row to user dictionary."""
        return {
            'id': row[0],
            'username': row[1],
            'email': row[2],
            'password_hash': row[3],
            'created_at': row[4],
            'deleted_at': row[5]
        }

# Transaction management
@contextmanager
def transaction(db_manager):
    """Context manager for database transactions."""
    with db_manager.get_connection() as conn:
        try:
            # Start transaction
            conn.execute("BEGIN TRANSACTION")
            yield conn
            conn.commit()
        except Exception as e:
            conn.rollback()
            logger.error(f"Transaction failed: {e}")
            raise

def transfer_money(db_manager, from_user_id, to_user_id, amount):
    """Transfer money between users with transaction safety."""
    with transaction(db_manager) as conn:
        # Check sender balance
        sender_balance = conn.execute(
            "SELECT balance FROM accounts WHERE user_id = ?",
            (from_user_id,)
        ).fetchone()
        
        if not sender_balance or sender_balance[0] < amount:
            raise ValueError("Insufficient funds")
        
        # Deduct from sender
        conn.execute(
            "UPDATE accounts SET balance = balance - ? WHERE user_id = ?",
            (amount, from_user_id)
        )
        
        # Add to receiver
        conn.execute(
            "UPDATE accounts SET balance = balance + ? WHERE user_id = ?",
            (amount, to_user_id)
        )
        
        # Log transaction
        conn.execute(
            "INSERT INTO transactions (from_user_id, to_user_id, amount, timestamp) VALUES (?, ?, ?, CURRENT_TIMESTAMP)",
            (from_user_id, to_user_id, amount)
        )

# Usage example
if __name__ == "__main__":
    # Initialize database
    db_config = {'database': ':memory:', 'check_same_thread': False}
    db_manager = DatabaseManager('sqlite', **db_config)
    
    # Set up schema
    schema_manager = SchemaManager(db_manager)
    
    # Apply migrations
    schema_manager.apply_migration(1, "Create users table", """
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            email TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            deleted_at TIMESTAMP
        )
    """)
    
    schema_manager.apply_migration(2, "Create accounts table", """
        CREATE TABLE accounts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            balance DECIMAL(10,2) DEFAULT 0.00,
            FOREIGN KEY (user_id) REFERENCES users(id)
        )
    """)
    
    schema_manager.apply_migration(3, "Create transactions table", """
        CREATE TABLE transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            from_user_id INTEGER NOT NULL,
            to_user_id INTEGER NOT NULL,
            amount DECIMAL(10,2) NOT NULL,
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (from_user_id) REFERENCES users(id),
            FOREIGN KEY (to_user_id) REFERENCES users(id)
        )
    """)
    
    # Use repository
    user_repo = UserRepository(db_manager)
    
    # Create users
    user1_id = user_repo.create_user({
        'username': 'alice',
        'email': 'alice@example.com',
        'password_hash': 'hashed_password_1'
    })
    
    user2_id = user_repo.create_user({
        'username': 'bob',
        'email': 'bob@example.com',
        'password_hash': 'hashed_password_2'
    })
    
    # Set up accounts
    db_manager.execute_query(
        "INSERT INTO accounts (user_id, balance) VALUES (?, ?)",
        (user1_id, 1000.00), fetch=False
    )
    
    db_manager.execute_query(
        "INSERT INTO accounts (user_id, balance) VALUES (?, ?)",
        (user2_id, 500.00), fetch=False
    )
    
    # Perform transaction
    try:
        transfer_money(db_manager, user1_id, user2_id, 200.00)
        print("Transfer successful")
    except ValueError as e:
        print(f"Transfer failed: {e}")
    
    # Query data
    users = user_repo.get_users_by_criteria({'username': 'alice'})
    print("Found users:", len(users))
    
    # Check balances
    balances = db_manager.execute_query("""
        SELECT u.username, a.balance
        FROM users u
        JOIN accounts a ON u.id = a.user_id
        WHERE u.deleted_at IS NULL
    """)
    
    print("Account balances:")
    for username, balance in balances:
        print(f"  {username}: ${balance:.2f}")
```
## Advanced Networking and Distributed Systems

### Network Architecture and Protocols

#### OSI Model and TCP/IP Stack

```python
# OSI Model layers with examples
OSI_MODEL = {
    7: {
        'name': 'Application Layer',
        'protocols': ['HTTP', 'HTTPS', 'FTP', 'SMTP', 'DNS'],
        'responsibility': 'User interface and application services',
        'examples': ['Web browsers', 'Email clients', 'File transfer apps']
    },
    6: {
        'name': 'Presentation Layer',
        'protocols': ['ASCII', 'EBCDIC', 'JPEG', 'MPEG', 'SSL/TLS'],
        'responsibility': 'Data translation, encryption, compression',
        'examples': ['Data format conversion', 'Encryption/decryption']
    },
    5: {
        'name': 'Session Layer',
        'protocols': ['NetBIOS', 'RPC', 'PPTP'],
        'responsibility': 'Session establishment, management, termination',
        'examples': ['Session tokens', 'Checkpointing']
    },
    4: {
        'name': 'Transport Layer',
        'protocols': ['TCP', 'UDP', 'SCTP'],
        'responsibility': 'End-to-end communication, error recovery, flow control',
        'examples': ['Connection-oriented vs connectionless communication']
    },
    3: {
        'name': 'Network Layer',
        'protocols': ['IP', 'ICMP', 'OSPF', 'BGP'],
        'responsibility': 'Logical addressing, routing, path determination',
        'examples': ['IP addressing', 'Router operations']
    },
    2: {
        'name': 'Data Link Layer',
        'protocols': ['Ethernet', 'Wi-Fi', 'PPP', 'HDLC'],
        'responsibility': 'Physical addressing, error detection, media access control',
        'examples': ['MAC addresses', 'Frame transmission']
    },
    1: {
        'name': 'Physical Layer',
        'protocols': ['USB', 'Ethernet cables', 'Fiber optics', 'Radio waves'],
        'responsibility': 'Bit transmission, physical media specifications',
        'examples': ['Cable standards', 'Signal encoding']
    }
}

def explain_network_layer(layer_number):
    """Explain a specific OSI model layer."""
    if layer_number in OSI_MODEL:
        layer = OSI_MODEL[layer_number]
        print(f"Layer {layer_number}: {layer['name']}")
        print(f"Protocols: {', '.join(layer['protocols'])}")
        print(f"Responsibility: {layer['responsibility']}")
        print(f"Examples: {', '.join(layer['examples'])}")
        print()
    else:
        print(f"Invalid layer number: {layer_number}")

# TCP/IP model comparison
TCP_IP_MODEL = {
    'Application': [7, 6, 5],  # Combines top 3 OSI layers
    'Transport': [4],          # Same as OSI layer 4
    'Internet': [3],           # Same as OSI layer 3
    'Network Access': [2, 1]   # Combines bottom 2 OSI layers
}

print("OSI Model Layers:")
for layer_num in range(7, 0, -1):
    explain_network_layer(layer_num)

print("TCP/IP Model vs OSI Model:")
for tcp_layer, osi_layers in TCP_IP_MODEL.items():
    print(f"{tcp_layer}: OSI layers {osi_layers}")
```

#### Advanced HTTP and REST API Design

```python
import requests
import json
import time
from functools import wraps
import logging

# Set up logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class APIClient:
    """Advanced HTTP client with retry logic, authentication, and error handling."""
    
    def __init__(self, base_url, api_key=None, timeout=30, max_retries=3):
        self.base_url = base_url.rstrip('/')
        self.api_key = api_key
        self.timeout = timeout
        self.max_retries = max_retries
        self.session = requests.Session()
        
        # Set default headers
        self.session.headers.update({
            'User-Agent': 'AdvancedAPIClient/1.0',
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        })
        
        if api_key:
            self.session.headers['Authorization'] = f'Bearer {api_key}'
    
    def _should_retry(self, response, attempt):
        """Determine if request should be retried."""
        if attempt >= self.max_retries:
            return False
        
        # Retry on server errors, timeouts, or rate limits
        if response.status_code in [500, 502, 503, 504]:
            return True
        
        if response.status_code == 429:  # Rate limited
            retry_after = response.headers.get('Retry-After')
            if retry_after:
                time.sleep(int(retry_after))
            return True
        
        return False
    
    def request(self, method, endpoint, **kwargs):
        """Make HTTP request with retry logic."""
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        kwargs.setdefault('timeout', self.timeout)
        
        for attempt in range(self.max_retries + 1):
            try:
                logger.info(f"Making {method} request to {url} (attempt {attempt + 1})")
                response = self.session.request(method, url, **kwargs)
                
                if response.status_code == 200:
                    return response
                
                if self._should_retry(response, attempt):
                    wait_time = 2 ** attempt  # Exponential backoff
                    logger.warning(f"Request failed (status {response.status_code}), retrying in {wait_time}s")
                    time.sleep(wait_time)
                    continue
                
                # Don't retry
                response.raise_for_status()
                
            except requests.exceptions.RequestException as e:
                if attempt < self.max_retries:
                    wait_time = 2 ** attempt
                    logger.warning(f"Request failed: {e}, retrying in {wait_time}s")
                    time.sleep(wait_time)
                    continue
                raise e
        
        raise Exception(f"Request failed after {self.max_retries + 1} attempts")
    
    def get(self, endpoint, params=None, **kwargs):
        """GET request."""
        return self.request('GET', endpoint, params=params, **kwargs)
    
    def post(self, endpoint, data=None, json=None, **kwargs):
        """POST request."""
        if json:
            kwargs['json'] = json
        elif data:
            kwargs['data'] = json.dumps(data) if isinstance(data, dict) else data
        return self.request('POST', endpoint, **kwargs)
    
    def put(self, endpoint, data=None, json=None, **kwargs):
        """PUT request."""
        if json:
            kwargs['json'] = json
        elif data:
            kwargs['data'] = json.dumps(data) if isinstance(data, dict) else data
        return self.request('PUT', endpoint, **kwargs)
    
    def delete(self, endpoint, **kwargs):
        """DELETE request."""
        return self.request('DELETE', endpoint, **kwargs)

class RESTAPI:
    """REST API design with proper HTTP methods and status codes."""
    
    def __init__(self):
        self.resources = {}
        self.next_id = 1
    
    def create_resource(self, resource_type, data):
        """Create a new resource (POST)."""
        resource_id = self.next_id
        self.next_id += 1
        
        if resource_type not in self.resources:
            self.resources[resource_type] = {}
        
        self.resources[resource_type][resource_id] = {
            'id': resource_id,
            'data': data,
            'created_at': time.time(),
            'updated_at': time.time()
        }
        
        return self.resources[resource_type][resource_id], 201  # Created
    
    def get_resource(self, resource_type, resource_id=None):
        """Retrieve resource(s) (GET)."""
        if resource_type not in self.resources:
            return None, 404  # Not Found
        
        if resource_id is None:
            # Return all resources of this type
            return list(self.resources[resource_type].values()), 200
        
        if resource_id not in self.resources[resource_type]:
            return None, 404
        
        return self.resources[resource_type][resource_id], 200
    
    def update_resource(self, resource_type, resource_id, data):
        """Update a resource (PUT/PATCH)."""
        if resource_type not in self.resources or resource_id not in self.resources[resource_type]:
            return None, 404
        
        resource = self.resources[resource_type][resource_id]
        resource['data'].update(data)
        resource['updated_at'] = time.time()
        
        return resource, 200
    
    def delete_resource(self, resource_type, resource_id):
        """Delete a resource (DELETE)."""
        if resource_type not in self.resources or resource_id not in self.resources[resource_type]:
            return None, 404
        
        deleted_resource = self.resources[resource_type][resource_id]
        del self.resources[resource_type][resource_id]
        
        return deleted_resource, 200

# WebSocket implementation for real-time communication
import asyncio
import websockets
import json

class WebSocketServer:
    """Simple WebSocket server for real-time communication."""
    
    def __init__(self):
        self.clients = set()
    
    async def register(self, websocket):
        """Register a new client."""
        self.clients.add(websocket)
        logger.info(f"Client connected. Total clients: {len(self.clients)}")
    
    async def unregister(self, websocket):
        """Unregister a client."""
        self.clients.remove(websocket)
        logger.info(f"Client disconnected. Total clients: {len(self.clients)}")
    
    async def send_to_all(self, message):
        """Send message to all connected clients."""
        if self.clients:
            await asyncio.gather(
                *[client.send(message) for client in self.clients],
                return_exceptions=True
            )
    
    async def handler(self, websocket, path):
        """Handle WebSocket connections."""
        await self.register(websocket)
        try:
            async for message in websocket:
                data = json.loads(message)
                logger.info(f"Received message: {data}")
                
                # Echo message to all clients
                response = {
                    'type': 'echo',
                    'original': data,
                    'timestamp': time.time()
                }
                await self.send_to_all(json.dumps(response))
                
        except websockets.exceptions.ConnectionClosed:
            logger.info("Connection closed")
        finally:
            await self.unregister(websocket)
    
    async def start_server(self, host='localhost', port=8765):
        """Start the WebSocket server."""
        server = await websockets.serve(self.handler, host, port)
        logger.info(f"WebSocket server started on ws://{host}:{port}")
        await server.wait_closed()

class WebSocketClient:
    """Simple WebSocket client."""
    
    def __init__(self, uri):
        self.uri = uri
    
    async def connect_and_listen(self):
        """Connect to server and listen for messages."""
        try:
            async with websockets.connect(self.uri) as websocket:
                logger.info("Connected to WebSocket server")
                
                # Send a test message
                test_message = {'type': 'test', 'message': 'Hello from client!'}
                await websocket.send(json.dumps(test_message))
                
                # Listen for responses
                async for message in websocket:
                    data = json.loads(message)
                    logger.info(f"Received: {data}")
                    
        except Exception as e:
            logger.error(f"WebSocket client error: {e}")

# DNS resolution and network utilities
import socket
import ipaddress

def network_utilities():
    """Demonstrate network utility functions."""
    
    # DNS resolution
    hostname = "www.google.com"
    try:
        ip_address = socket.gethostbyname(hostname)
        print(f"{hostname} resolves to {ip_address}")
        
        # Reverse DNS lookup
        hostname_reverse = socket.gethostbyaddr(ip_address)[0]
        print(f"{ip_address} resolves back to {hostname_reverse}")
        
    except socket.gaierror as e:
        print(f"DNS resolution failed: {e}")
    
    # IP address manipulation
    ip = ipaddress.ip_address("192.168.1.100")
    network = ipaddress.ip_network("192.168.1.0/24")
    
    print(f"IP address: {ip}")
    print(f"Is private: {ip.is_private}")
    print(f"Network: {network}")
    print(f"Network contains IP: {ip in network}")
    print(f"Network broadcast: {network.broadcast_address}")
    print(f"Network hostmask: {network.hostmask}")
    
    # Port scanning (basic)
    def scan_port(host, port):
        """Check if a port is open."""
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(1)
            result = sock.connect_ex((host, port))
            sock.close()
            return result == 0
        except:
            return False
    
    # Scan common ports
    common_ports = {
        21: "FTP",
        22: "SSH",
        23: "Telnet",
        25: "SMTP",
        53: "DNS",
        80: "HTTP",
        443: "HTTPS",
        3306: "MySQL",
        5432: "PostgreSQL"
    }
    
    target_host = "localhost"
    print(f"\nScanning ports on {target_host}:")
    for port, service in common_ports.items():
        is_open = scan_port(target_host, port)
        status = "OPEN" if is_open else "CLOSED"
        print(f"Port {port} ({service}): {status}")

# Usage examples
if __name__ == "__main__":
    # API client demonstration
    print("=== API Client Demo ===")
    client = APIClient("https://httpbin.org")
    
    try:
        # GET request
        response = client.get("/get", params={"test": "value"})
        print(f"GET response status: {response.status_code}")
        print(f"Response data: {response.json()['args']}")
        
        # POST request
        response = client.post("/post", json={"message": "Hello, API!"})
        print(f"POST response status: {response.status_code}")
        print(f"Echoed message: {response.json()['json']['message']}")
        
    except Exception as e:
        print(f"API request failed: {e}")
    
    # REST API demonstration
    print("\n=== REST API Demo ===")
    api = RESTAPI()
    
    # Create resources
    user1, status = api.create_resource("users", {"name": "Alice", "email": "alice@example.com"})
    print(f"Created user: {user1}, Status: {status}")
    
    user2, status = api.create_resource("users", {"name": "Bob", "email": "bob@example.com"})
    print(f"Created user: {user2}, Status: {status}")
    
    # Get resources
    users, status = api.get_resource("users")
    print(f"All users: {len(users)}, Status: {status}")
    
    # Update resource
    updated_user, status = api.update_resource("users", 1, {"email": "alice.smith@example.com"})
    print(f"Updated user: {updated_user['data']}, Status: {status}")
    
    # Delete resource
    deleted_user, status = api.delete_resource("users", 2)
    print(f"Deleted user: {deleted_user['data']['name']}, Status: {status}")
    
    # Network utilities
    print("\n=== Network Utilities ===")
    network_utilities()
    
    # WebSocket demo (commented out to avoid blocking)
    """
    print("\n=== WebSocket Demo ===")
    
    async def run_websocket_demo():
        server = WebSocketServer()
        client = WebSocketClient("ws://localhost:8765")
        
        # Run server and client concurrently
        await asyncio.gather(
            server.start_server(),
            client.connect_and_listen()
        )
    
    # Uncomment to run WebSocket demo
    # asyncio.run(run_websocket_demo())
    """
```
## Advanced Concurrency and Parallel Programming

### Concurrency Models and Patterns

#### Threading vs Multiprocessing vs AsyncIO

```python
import threading
import multiprocessing
import asyncio
import time
import concurrent.futures

# CPU-bound task (benefits from multiprocessing)
def cpu_intensive_task(n):
    """Simulate CPU-intensive computation."""
    result = 0
    for i in range(n):
        result += i ** 2
    return result

# I/O-bound task (benefits from threading/asyncio)
def io_bound_task(url, delay=1):
    """Simulate I/O-bound operation."""
    time.sleep(delay)  # Simulate network delay
    return f"Response from {url}"

# 1. Threading approach (good for I/O-bound tasks)
def threading_example():
    """Demonstrate threading for concurrent I/O operations."""
    print("=== Threading Example ===")

    urls = [f"http://example.com/{i}" for i in range(5)]

    def fetch_url(url):
        return io_bound_task(url, 0.5)

    start_time = time.time()

    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
        results = list(executor.map(fetch_url, urls))

    end_time = time.time()
    print(f"Threading completed in {end_time - start_time:.2f} seconds")
    print(f"Results: {len(results)} responses")

# 2. Multiprocessing approach (good for CPU-bound tasks)
def multiprocessing_example():
    """Demonstrate multiprocessing for CPU-intensive tasks."""
    print("\n=== Multiprocessing Example ===")

    numbers = [1000000] * 4  # 4 CPU-intensive tasks

    start_time = time.time()

    with multiprocessing.Pool(processes=4) as pool:
        results = pool.map(cpu_intensive_task, numbers)

    end_time = time.time()
    print(f"Multiprocessing completed in {end_time - start_time:.2f} seconds")
    print(f"Results: {results}")

# 3. AsyncIO approach (excellent for I/O-bound tasks)
async def async_example():
    """Demonstrate asyncio for concurrent I/O operations."""
    print("\n=== AsyncIO Example ===")

    async def async_io_task(name, delay):
        """Async version of I/O task."""
        await asyncio.sleep(delay)
        return f"Completed {name}"

    start_time = time.time()

    # Create multiple concurrent tasks
    tasks = [
        async_io_task(f"task_{i}", 0.5)
        for i in range(10)
    ]

    # Run all tasks concurrently
    results = await asyncio.gather(*tasks)

    end_time = time.time()
    print(f"AsyncIO completed in {end_time - start_time:.2f} seconds")
    print(f"Results: {len(results)} tasks completed")

# Thread synchronization
class ThreadSafeCounter:
    """Thread-safe counter using locks."""

    def __init__(self):
        self.value = 0
        self.lock = threading.Lock()

    def increment(self):
        with self.lock:
            self.value += 1

    def get_value(self):
        with self.lock:
            return self.value

def thread_synchronization_example():
    """Demonstrate thread synchronization."""
    print("\n=== Thread Synchronization Example ===")

    counter = ThreadSafeCounter()

    def worker(worker_id):
        for _ in range(1000):
            counter.increment()
        print(f"Worker {worker_id} completed")

    # Create multiple threads
    threads = []
    for i in range(5):
        t = threading.Thread(target=worker, args=(i,))
        threads.append(t)
        t.start()

    # Wait for all threads
    for t in threads:
        t.join()

    print(f"Final counter value: {counter.get_value()} (expected: 5000)")

# Run examples
if __name__ == "__main__":
    threading_example()
    multiprocessing_example()
    asyncio.run(async_example())
    thread_synchronization_example()
```

## Advanced Memory Management and Performance Optimization

### Memory Management Strategies

#### Automatic Memory Management (Garbage Collection)

```python
import gc
import sys
import psutil
import os

class MemoryMonitor:
    """Monitor memory usage in Python applications."""
    
    def __init__(self):
        self.process = psutil.Process(os.getpid())
    
    def get_memory_usage(self):
        """Get current memory usage."""
        memory_info = self.process.memory_info()
        return {
            'rss': memory_info.rss / 1024 / 1024,  # MB
            'vms': memory_info.vms / 1024 / 1024,  # MB
            'percent': self.process.memory_percent()
        }
    
    def print_memory_usage(self, label=""):
        """Print current memory usage."""
        mem = self.get_memory_usage()
        print(f"{label} Memory - RSS: {mem['rss']:.2f} MB, VMS: {mem['vms']:.2f} MB, Percent: {mem['percent']:.2f}%")

def demonstrate_gc():
    """Demonstrate garbage collection behavior."""
    print("=== Garbage Collection Demonstration ===")
    
    monitor = MemoryMonitor()
    monitor.print_memory_usage("Initial")
    
    # Create many objects
    objects = []
    for i in range(100000):
        objects.append({"id": i, "data": "x" * 100})
    
    monitor.print_memory_usage("After creating objects")
    
    # Delete references
    del objects
    monitor.print_memory_usage("After deleting references")
    
    # Force garbage collection
    collected = gc.collect()
    monitor.print_memory_usage("After garbage collection")
    print(f"Objects collected: {collected}")

# Reference counting and circular references
class Node:
    """Node that can create circular references."""
    
    def __init__(self, value):
        self.value = value
        self.next = None
    
    def __del__(self):
        print(f"Node {self.value} is being deleted")

def circular_reference_demo():
    """Demonstrate circular reference issue."""
    print("\n=== Circular Reference Demo ===")
    
    # Create circular reference
    node1 = Node(1)
    node2 = Node(2)
    node1.next = node2
    node2.next = node1
    
    print("Created circular reference")
    
    # Delete references
    del node1
    del node2
    
    print("References deleted, forcing garbage collection...")
    gc.collect()  # In Python, circular references are handled by gc
    
    print("Circular reference demo completed")

# Memory-efficient data structures
class MemoryEfficientList:
    """Memory-efficient list using __slots__."""
    
    __slots__ = ['_data', '_size', '_capacity']
    
    def __init__(self, initial_capacity=10):
        self._data = [None] * initial_capacity
        self._size = 0
        self._capacity = initial_capacity
    
    def append(self, item):
        if self._size >= self._capacity:
            self._resize(self._capacity * 2)
        self._data[self._size] = item
        self._size += 1
    
    def _resize(self, new_capacity):
        new_data = [None] * new_capacity
        for i in range(self._size):
            new_data[i] = self._data[i]
        self._data = new_data
        self._capacity = new_capacity
    
    def __getitem__(self, index):
        if 0 <= index < self._size:
            return self._data[index]
        raise IndexError("Index out of range")
    
    def __len__(self):
        return self._size

def memory_efficiency_comparison():
    """Compare memory usage of different data structures."""
    print("\n=== Memory Efficiency Comparison ===")
    
    monitor = MemoryMonitor()
    
    # Regular list
    monitor.print_memory_usage("Before regular list")
    regular_list = [{"id": i, "data": "x" * 50} for i in range(10000)]
    monitor.print_memory_usage("After regular list")
    
    del regular_list
    
    # Memory efficient list
    monitor.print_memory_usage("Before efficient list")
    efficient_list = MemoryEfficientList()
    for i in range(10000):
        efficient_list.append({"id": i, "data": "x" * 50})
    monitor.print_memory_usage("After efficient list")

# Manual memory management concepts (for educational purposes)
def manual_memory_concepts():
    """Demonstrate manual memory management concepts."""
    print("\n=== Manual Memory Management Concepts ===")
    
    # In languages like C, you manually manage memory
    print("Manual memory management requires:")
    print("1. Allocating memory with malloc/calloc")
    print("2. Using the allocated memory")
    print("3. Freeing memory with free() when done")
    print("4. Avoiding memory leaks (forgetting to free)")
    print("5. Avoiding dangling pointers (using freed memory)")
    print("6. Avoiding double-free errors")
    
    # Python's memory management is automatic
    print("\nPython handles memory automatically:")
    print("- Reference counting for most objects")
    print("- Garbage collection for circular references")
    print("- Memory pooling for small objects")
    print("- Automatic memory deallocation")

# Memory profiling and optimization
def memory_profiling():
    """Demonstrate memory profiling techniques."""
    print("\n=== Memory Profiling ===")
    
    try:
        import memory_profiler
        print("Memory profiler available")
        
        @memory_profiler.profile
        def memory_intensive_function():
            data = []
            for i in range(10000):
                data.append({"index": i, "value": "x" * 100})
            return data
        
        result = memory_intensive_function()
        print(f"Created {len(result)} objects")
        
    except ImportError:
        print("memory_profiler not available, install with: pip install memory-profiler")
        print("Alternative: Use tracemalloc for basic profiling")
        
        import tracemalloc
        
        tracemalloc.start()
        
        data = []
        for i in range(10000):
            data.append({"index": i, "value": "x" * 100})
        
        current, peak = tracemalloc.get_traced_memory()
        print(f"Current memory usage: {current / 1024 / 1024:.2f} MB")
        print(f"Peak memory usage: {peak / 1024 / 1024:.2f} MB")
        
        tracemalloc.stop()

# Caching and memoization for memory efficiency
from functools import lru_cache
import time

@lru_cache(maxsize=128)
def expensive_computation(n):
    """Expensive computation with caching."""
    time.sleep(0.1)  # Simulate expensive operation
    return n * n

def caching_demo():
    """Demonstrate caching benefits."""
    print("\n=== Caching Demonstration ===")
    
    monitor = MemoryMonitor()
    monitor.print_memory_usage("Before caching demo")
    
    # Without caching
    start_time = time.time()
    results1 = [expensive_computation(i % 10) for i in range(20)]  # Many repeated calls
    time1 = time.time() - start_time
    
    # With caching (should be faster for repeated values)
    expensive_computation.cache_clear()  # Clear cache
    start_time = time.time()
    results2 = [expensive_computation(i % 10) for i in range(20)]  # Same calls
    time2 = time.time() - start_time
    
    monitor.print_memory_usage("After caching demo")
    
    print(f"Without caching: {time1:.2f} seconds")
    print(f"With caching: {time2:.2f} seconds")
    print(f"Speedup: {time1/time2:.2f}x")
    print(f"Cache hits: {expensive_computation.cache_info().hits}")
    print(f"Cache misses: {expensive_computation.cache_info().misses}")

# Memory-mapped files for large data
def memory_mapped_files():
    """Demonstrate memory-mapped file operations."""
    print("\n=== Memory-Mapped Files ===")
    
    try:
        import mmap
        
        # Create a large file
        filename = 'large_data.dat'
        with open(filename, 'wb') as f:
            for i in range(1000000):
                f.write(f"Line {i}: {'x' * 50}\n".encode())
        
        # Memory map the file
        with open(filename, 'r+b') as f:
            # Map the entire file
            mm = mmap.mmap(f.fileno(), 0)
            
            # Read specific parts without loading entire file
            print("First line:", mm[:50].decode().strip())
            
            # Search in memory-mapped file
            search_term = b"Line 500000"
            pos = mm.find(search_term)
            if pos != -1:
                # Read around the found position
                start = max(0, pos - 20)
                end = min(len(mm), pos + len(search_term) + 20)
                print("Found at position", pos, ":", mm[start:end].decode())
            
            mm.close()
        
        # Clean up
        os.remove(filename)
        print("Memory-mapped file operations completed")
        
    except ImportError:
        print("mmap not available on this platform")

# Run memory management demonstrations
if __name__ == "__main__":
    demonstrate_gc()
    circular_reference_demo()
    memory_efficiency_comparison()
    manual_memory_concepts()
    memory_profiling()
    caching_demo()
    memory_mapped_files()
```

## Advanced Security and Cryptography

### Secure Coding Practices

#### Input Validation and Sanitization

```python
import re
import html
from typing import Union, List, Dict, Any

class InputValidator:
    """Comprehensive input validation and sanitization."""
    
    # Common validation patterns
    PATTERNS = {
        'email': r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$',
        'phone': r'^\+?1?[-.\s]?\(?([0-9]{3})\)?[-.\s]?([0-9]{3})[-.\s]?([0-9]{4})$',
        'zipcode': r'^\d{5}(-\d{4})?$',
        'credit_card': r'^\d{4}[\s-]?\d{4}[\s-]?\d{4}[\s-]?\d{4}$',
        'url': r'^https?://[^\s/$.?#].[^\s]*$',
        'username': r'^[a-zA-Z0-9_-]{3,20}$',
        'password': r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$'
    }
    
    @staticmethod
    def validate_email(email: str) -> bool:
        """Validate email address."""
        return bool(re.match(InputValidator.PATTERNS['email'], email.strip()))
    
    @staticmethod
    def validate_password(password: str) -> Dict[str, Any]:
        """Validate password strength."""
        result = {
            'valid': False,
            'strength': 'weak',
            'issues': []
        }
        
        if len(password) < 8:
            result['issues'].append('Password too short (minimum 8 characters)')
        
        if not re.search(r'[a-z]', password):
            result['issues'].append('Missing lowercase letter')
        
        if not re.search(r'[A-Z]', password):
            result['issues'].append('Missing uppercase letter')
        
        if not re.search(r'\d', password):
            result['issues'].append('Missing digit')
        
        if not re.search(r'[@$!%*?&]', password):
            result['issues'].append('Missing special character')
        
        if not result['issues']:
            result['valid'] = True
            # Calculate strength
            score = 0
            if len(password) >= 12:
                score += 1
            if re.search(r'[a-z]', password):
                score += 1
            if re.search(r'[A-Z]', password):
                score += 1
            if re.search(r'\d', password):
                score += 1
            if re.search(r'[@$!%*?&]', password):
                score += 1
            
            if score >= 4:
                result['strength'] = 'strong'
            elif score >= 3:
                result['strength'] = 'medium'
        
        return result
    
    @staticmethod
    def sanitize_html(text: str) -> str:
        """Sanitize HTML input to prevent XSS."""
        return html.escape(text, quote=True)
    
    @staticmethod
    def sanitize_sql(value: Union[str, int, float]) -> str:
        """Basic SQL sanitization (use parameterized queries instead)."""
        if isinstance(value, str):
            # Remove dangerous characters (basic approach)
            return re.sub(r'[;\'\"\\]', '', value)
        return str(value)
    
    @staticmethod
    def validate_and_sanitize_input(data: Dict[str, Any], schema: Dict[str, Dict]) -> Dict[str, Any]:
        """Validate and sanitize input data against a schema."""
        sanitized = {}
        
        for field, rules in schema.items():
            if field not in data:
                if rules.get('required', False):
                    raise ValueError(f"Required field '{field}' is missing")
                continue
            
            value = data[field]
            field_type = rules.get('type', str)
            
            # Type conversion and validation
            try:
                if field_type == 'int':
                    value = int(value)
                elif field_type == 'float':
                    value = float(value)
                elif field_type == 'bool':
                    value = bool(value)
                elif field_type == 'str':
                    value = str(value)
                
                # Range validation
                if 'min' in rules and value < rules['min']:
                    raise ValueError(f"Value for '{field}' below minimum {rules['min']}")
                if 'max' in rules and value > rules['max']:
                    raise ValueError(f"Value for '{field}' above maximum {rules['max']}")
                
                # Pattern validation
                if 'pattern' in rules:
                    if not re.match(rules['pattern'], str(value)):
                        raise ValueError(f"Value for '{field}' doesn't match required pattern")
                
                # Custom validation
                if 'validator' in rules:
                    if not rules['validator'](value):
                        raise ValueError(f"Custom validation failed for '{field}'")
                
                # Sanitization
                if rules.get('sanitize', False):
                    if isinstance(value, str):
                        value = InputValidator.sanitize_html(value)
                
                sanitized[field] = value
                
            except (ValueError, TypeError) as e:
                raise ValueError(f"Validation error for field '{field}': {e}")
        
        return sanitized

# Usage examples
def security_validation_demo():
    """Demonstrate security validation."""
    print("=== Security Validation Demo ===")
    
    # Email validation
    emails = ["user@example.com", "invalid-email", "user@.com", ""]
    for email in emails:
        is_valid = InputValidator.validate_email(email)
        print(f"'{email}' is valid: {is_valid}")
    
    # Password validation
    passwords = ["weak", "Stronger123!", "VeryStrongPass123!@#"]
    for pwd in passwords:
        result = InputValidator.validate_password(pwd)
        print(f"Password '{pwd}': {result['strength']} - {'Valid' if result['valid'] else 'Invalid'}")
        if result['issues']:
            print(f"  Issues: {', '.join(result['issues'])}")
    
    # Input sanitization and validation
    schema = {
        'username': {
            'type': 'str',
            'pattern': r'^[a-zA-Z0-9_-]{3,20}$',
            'required': True,
            'sanitize': True
        },
        'age': {
            'type': 'int',
            'min': 13,
            'max': 120,
            'required': True
        },
        'email': {
            'type': 'str',
            'validator': InputValidator.validate_email,
            'required': True
        }
    }
    
    test_data = [
        {'username': 'valid_user', 'age': 25, 'email': 'user@example.com'},
        {'username': 'u', 'age': 10, 'email': 'invalid'},
        {'username': '<script>alert("xss")</script>', 'age': 30, 'email': 'user@example.com'}
    ]
    
    for i, data in enumerate(test_data):
        try:
            sanitized = InputValidator.validate_and_sanitize_input(data, schema)
            print(f"Test {i+1} passed: {sanitized}")
        except ValueError as e:
            print(f"Test {i+1} failed: {e}")

### SQL Injection Prevention and Secure Database Access

```python
import sqlite3
from contextlib import contextmanager
import hashlib
import secrets
import bcrypt

class SecureDatabase:
    """Secure database access with injection prevention."""
    
    def __init__(self, db_path):
        self.db_path = db_path
    
    @contextmanager
    def get_connection(self):
        """Secure database connection with proper cleanup."""
        conn = None
        try:
            conn = sqlite3.connect(self.db_path)
            conn.execute("PRAGMA foreign_keys = ON")  # Enable foreign key constraints
            yield conn
        except Exception as e:
            if conn:
                conn.rollback()
            raise e
        finally:
            if conn:
                conn.close()
    
    def execute_secure_query(self, query, params=None):
        """Execute query with parameterized statements."""
        with self.get_connection() as conn:
            cursor = conn.cursor()
            
            # Always use parameterized queries
            cursor.execute(query, params or ())
            
            if query.strip().upper().startswith(('SELECT', 'PRAGMA')):
                return cursor.fetchall()
            else:
                conn.commit()
                return cursor.rowcount
    
    def create_secure_tables(self):
        """Create tables with security considerations."""
        queries = [
            """
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                email TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL,
                salt TEXT NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                last_login TIMESTAMP,
                failed_attempts INTEGER DEFAULT 0,
                locked_until TIMESTAMP,
                active BOOLEAN DEFAULT 1
            )
            """,
            """
            CREATE TABLE IF NOT EXISTS sessions (
                session_id TEXT PRIMARY KEY,
                user_id INTEGER NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                expires_at TIMESTAMP NOT NULL,
                ip_address TEXT,
                user_agent TEXT,
                FOREIGN KEY (user_id) REFERENCES users(id)
            )
            """
        ]
        
        for query in queries:
            self.execute_secure_query(query)
    
    def hash_password(self, password, salt=None):
        """Secure password hashing with salt."""
        if salt is None:
            salt = secrets.token_hex(16)  # Generate random salt
        
        # Use bcrypt for secure hashing
        try:
            import bcrypt
            hashed = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt())
            return hashed.decode('utf-8'), salt
        except ImportError:
            # Fallback to hashlib with salt
            combined = salt + password
            hashed = hashlib.sha256(combined.encode('utf-8')).hexdigest()
            return hashed, salt
    
    def verify_password(self, password, stored_hash, salt):
        """Verify password against stored hash."""
        try:
            import bcrypt
            return bcrypt.checkpw(password.encode('utf-8'), stored_hash.encode('utf-8'))
        except ImportError:
            # Fallback verification
            combined = salt + password
            return hashlib.sha256(combined.encode('utf-8')).hexdigest() == stored_hash
    
    def register_user(self, username, email, password):
        """Secure user registration."""
        # Validate inputs
        if not InputValidator.validate_email(email):
            raise ValueError("Invalid email address")
        
        if not re.match(r'^[a-zA-Z0-9_-]{3,20}$', username):
            raise ValueError("Invalid username")
        
        pwd_validation = InputValidator.validate_password(password)
        if not pwd_validation['valid']:
            raise ValueError(f"Password too weak: {', '.join(pwd_validation['issues'])}")
        
        # Hash password
        password_hash, salt = self.hash_password(password)
        
        # Insert user
        query = """
        INSERT INTO users (username, email, password_hash, salt)
        VALUES (?, ?, ?, ?)
        """
        
        try:
            self.execute_secure_query(query, (username, email, password_hash, salt))
            return True
        except sqlite3.IntegrityError as e:
            if "username" in str(e):
                raise ValueError("Username already exists")
            elif "email" in str(e):
                raise ValueError("Email already registered")
            raise
    
    def authenticate_user(self, username_or_email, password):
        """Secure user authentication with brute force protection."""
        # Get user data
        query = """
        SELECT id, password_hash, salt, failed_attempts, locked_until, active
        FROM users
        WHERE (username = ? OR email = ?) AND active = 1
        """
        
        result = self.execute_secure_query(query, (username_or_email, username_or_email))
        
        if not result:
            # Don't reveal if user exists or not
            raise ValueError("Invalid username/email or password")
        
        user_id, stored_hash, salt, failed_attempts, locked_until, active = result[0]
        
        # Check if account is locked
        if locked_until and locked_until > time.time():
            raise ValueError("Account is temporarily locked due to too many failed attempts")
        
        # Verify password
        if self.verify_password(password, stored_hash, salt):
            # Successful login - reset failed attempts
            self.execute_secure_query(
                "UPDATE users SET failed_attempts = 0, last_login = CURRENT_TIMESTAMP WHERE id = ?",
                (user_id,)
            )
            return user_id
        else:
            # Failed login - increment attempts
            new_attempts = failed_attempts + 1
            
            # Lock account after 5 failed attempts
            lock_until = None
            if new_attempts >= 5:
                lock_until = time.time() + 900  # Lock for 15 minutes
            
            self.execute_secure_query(
                "UPDATE users SET failed_attempts = ?, locked_until = ? WHERE id = ?",
                (new_attempts, lock_until, user_id)
            )
            
            raise ValueError("Invalid username/email or password")
    
    def create_session(self, user_id, ip_address=None, user_agent=None):
        """Create secure session."""
        session_id = secrets.token_urlsafe(32)
        expires_at = time.time() + 86400  # 24 hours
        
        query = """
        INSERT INTO sessions (session_id, user_id, expires_at, ip_address, user_agent)
        VALUES (?, ?, ?, ?, ?)
        """
        
        self.execute_secure_query(query, (session_id, user_id, expires_at, ip_address, user_agent))
        return session_id
    
    def validate_session(self, session_id):
        """Validate session and return user_id if valid."""
        query = """
        SELECT user_id FROM sessions
        WHERE session_id = ? AND expires_at > ? AND user_id IN (
            SELECT id FROM users WHERE active = 1
        )
        """
        
        result = self.execute_secure_query(query, (session_id, time.time()))
        return result[0][0] if result else None

# Cryptography basics
class CryptoUtils:
    """Basic cryptographic utilities."""
    
    @staticmethod
    def generate_key(length=32):
        """Generate a random key."""
        return secrets.token_bytes(length)
    
    @staticmethod
    def hash_data(data, algorithm='sha256'):
        """Hash data using specified algorithm."""
        if isinstance(data, str):
            data = data.encode('utf-8')
        
        if algorithm == 'sha256':
            return hashlib.sha256(data).hexdigest()
        elif algorithm == 'md5':
            return hashlib.md5(data).hexdigest()
        else:
            raise ValueError(f"Unsupported hash algorithm: {algorithm}")
    
    @staticmethod
    def simple_encrypt(text, key):
        """Simple XOR encryption (not secure for production)."""
        if isinstance(text, str):
            text = text.encode('utf-8')
        if isinstance(key, str):
            key = key.encode('utf-8')
        
        encrypted = bytearray()
        for i, byte in enumerate(text):
            encrypted.append(byte ^ key[i % len(key)])
        
        return encrypted.hex()
    
    @staticmethod
    def simple_decrypt(encrypted_hex, key):
        """Simple XOR decryption."""
        encrypted = bytes.fromhex(encrypted_hex)
        if isinstance(key, str):
            key = key.encode('utf-8')
        
        decrypted = bytearray()
        for i, byte in enumerate(encrypted):
            decrypted.append(byte ^ key[i % len(key)])
        
        return decrypted.decode('utf-8')

# Security demonstration
def security_demo():
    """Comprehensive security demonstration."""
    print("=== Security Demonstration ===")
    
    # Input validation
    security_validation_demo()
    
    # Secure database operations
    print("\n=== Secure Database Demo ===")
    db = SecureDatabase(':memory:')
    db.create_secure_tables()
    
    try:
        # Register users
        db.register_user("alice", "alice@example.com", "SecurePass123!")
        db.register_user("bob", "bob@example.com", "AnotherPass456!")
        
        # Authenticate users
        alice_id = db.authenticate_user("alice", "SecurePass123!")
        print(f"Alice authenticated with ID: {alice_id}")
        
        # Create session
        session_id = db.create_session(alice_id, "192.168.1.100", "Mozilla/5.0")
        print(f"Session created: {session_id[:16]}...")
        
        # Validate session
        validated_user = db.validate_session(session_id)
        print(f"Session validation successful for user: {validated_user}")
        
    except ValueError as e:
        print(f"Security error: {e}")
    
    # Cryptography demo
    print("\n=== Cryptography Demo ===")
    message = "This is a secret message"
    key = "my_secret_key"
    
    encrypted = CryptoUtils.simple_encrypt(message, key)
    decrypted = CryptoUtils.simple_decrypt(encrypted, key)
    
    print(f"Original: {message}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
    print(f"Decryption successful: {message == decrypted}")
    
    # Hashing demo
    hash_value = CryptoUtils.hash_data("password123")
    print(f"SHA256 hash of 'password123': {hash_value}")

if __name__ == "__main__":
    import time
    security_demo()
```
## Comprehensive Testing and Quality Assurance

### Testing Pyramid and Test Types

#### Unit Testing - Foundation of Testing

```python
import unittest
import pytest
from unittest.mock import Mock, patch, MagicMock
import tempfile
import os
import json

# Calculator class to test
class Calculator:
    def __init__(self):
        self.history = []
    
    def add(self, a, b):
        result = a + b
        self.history.append(f"{a} + {b} = {result}")
        return result
    
    def divide(self, a, b):
        if b == 0:
            raise ValueError("Cannot divide by zero")
        result = a / b
        self.history.append(f"{a} / {b} = {result}")
        return result
    
    def get_history(self):
        return self.history.copy()

# Comprehensive unit tests
class TestCalculator(unittest.TestCase):
    """Comprehensive unit tests for Calculator class."""
    
    def setUp(self):
        """Set up test fixtures before each test."""
        self.calc = Calculator()
    
    def tearDown(self):
        """Clean up after each test."""
        pass
    
    # Basic functionality tests
    def test_add_positive_numbers(self):
        result = self.calc.add(2, 3)
        self.assertEqual(result, 5)
        self.assertIn("2 + 3 = 5", self.calc.get_history())
    
    def test_add_negative_numbers(self):
        result = self.calc.add(-5, -3)
        self.assertEqual(result, -8)
    
    def test_add_mixed_numbers(self):
        result = self.calc.add(10, -4)
        self.assertEqual(result, 6)
    
    def test_add_floats(self):
        result = self.calc.add(1.5, 2.5)
        self.assertAlmostEqual(result, 4.0)
    
    # Edge cases
    def test_add_zero(self):
        result = self.calc.add(0, 0)
        self.assertEqual(result, 0)
    
    def test_add_large_numbers(self):
        result = self.calc.add(999999, 999999)
        self.assertEqual(result, 1999998)
    
    # Division tests
    def test_divide_normal(self):
        result = self.calc.divide(10, 2)
        self.assertEqual(result, 5)
    
    def test_divide_with_remainder(self):
        result = self.calc.divide(7, 2)
        self.assertEqual(result, 3.5)
    
    def test_divide_by_zero(self):
        with self.assertRaises(ValueError) as context:
            self.calc.divide(10, 0)
        self.assertIn("Cannot divide by zero", str(context.exception))
    
    # History tests
    def test_history_tracking(self):
        self.calc.add(1, 2)
        self.calc.divide(8, 2)
        history = self.calc.get_history()
        self.assertEqual(len(history), 2)
        self.assertEqual(history[0], "1 + 2 = 3")
        self.assertEqual(history[1], "8 / 2 = 4.0")
    
    def test_history_isolation(self):
        """Test that history is properly isolated."""
        history1 = self.calc.get_history()
        self.calc.add(1, 1)
        history2 = self.calc.get_history()
        
        # Original history should not be affected
        self.assertEqual(len(history1), 0)
        self.assertEqual(len(history2), 1)
    
    # Parametrized tests
    def test_add_parametrized(self):
        test_cases = [
            (1, 2, 3),
            (0, 0, 0),
            (-1, 1, 0),
            (100, 200, 300),
            (1.5, 2.5, 4.0)
        ]
        
        for a, b, expected in test_cases:
            with self.subTest(a=a, b=b, expected=expected):
                result = self.calc.add(a, b)
                if isinstance(expected, float):
                    self.assertAlmostEqual(result, expected)
                else:
                    self.assertEqual(result, expected)

# Mocking and dependency injection
class UserService:
    def __init__(self, database=None, email_sender=None):
        self.database = database or Database()
        self.email_sender = email_sender or EmailSender()
    
    def create_user(self, username, email, password):
        # Validate inputs
        if not username or not email or not password:
            raise ValueError("All fields are required")
        
        # Check if user exists
        if self.database.user_exists(email):
            raise ValueError("User already exists")
        
        # Create user
        user_id = self.database.create_user(username, email, password)
        
        # Send welcome email
        self.email_sender.send_welcome_email(email, username)
        
        return user_id

class Database:
    def user_exists(self, email):
        # Simulate database check
        return False
    
    def create_user(self, username, email, password):
        # Simulate user creation
        return 123

class EmailSender:
    def send_welcome_email(self, email, username):
        # Simulate email sending
        print(f"Sending welcome email to {email}")

# Tests with mocking
class TestUserService(unittest.TestCase):
    def setUp(self):
        self.mock_db = Mock(spec=Database)
        self.mock_email = Mock(spec=EmailSender)
        self.service = UserService(self.mock_db, self.mock_email)
    
    def test_create_user_success(self):
        # Setup mocks
        self.mock_db.user_exists.return_value = False
        self.mock_db.create_user.return_value = 123
        
        # Execute
        result = self.service.create_user("alice", "alice@example.com", "password123")
        
        # Assert
        self.assertEqual(result, 123)
        self.mock_db.user_exists.assert_called_once_with("alice@example.com")
        self.mock_db.create_user.assert_called_once_with("alice", "alice@example.com", "password123")
        self.mock_email.send_welcome_email.assert_called_once_with("alice@example.com", "alice")
    
    def test_create_user_already_exists(self):
        # Setup mock
        self.mock_db.user_exists.return_value = True
        
        # Execute and assert
        with self.assertRaises(ValueError) as context:
            self.service.create_user("alice", "alice@example.com", "password123")
        
        self.assertIn("already exists", str(context.exception))
        self.mock_db.create_user.assert_not_called()
        self.mock_email.send_welcome_email.assert_not_called()
    
    def test_create_user_validation_error(self):
        with self.assertRaises(ValueError) as context:
            self.service.create_user("", "alice@example.com", "password123")
        
        self.assertIn("required", str(context.exception))
        self.mock_db.user_exists.assert_not_called()

# Integration tests
class TestUserServiceIntegration(unittest.TestCase):
    def setUp(self):
        # Use temporary database for integration tests
        self.temp_db = tempfile.NamedTemporaryFile(delete=False, suffix='.db')
        self.temp_db.close()
        
        # In a real scenario, you'd set up a test database
        self.service = UserService()
    
    def tearDown(self):
        # Clean up temporary database
        try:
            os.unlink(self.temp_db.name)
        except:
            pass
    
    def test_full_user_creation_workflow(self):
        """Test the complete user creation workflow."""
        # This would test the actual database and email sending
        # For demonstration, we'll use mocks
        pass

# Property-based testing with Hypothesis
try:
    import hypothesis
    from hypothesis import given, strategies as st
    
    class TestCalculatorHypothesis(unittest.TestCase):
        def setUp(self):
            self.calc = Calculator()
        
        @given(a=st.integers(), b=st.integers())
        def test_add_commutative(self, a, b):
            """Test that addition is commutative: a + b = b + a"""
            result1 = self.calc.add(a, b)
            # Reset calculator for second test
            self.calc = Calculator()
            result2 = self.calc.add(b, a)
            self.assertEqual(result1, result2)
        
        @given(a=st.floats(allow_nan=False, allow_infinity=False),
               b=st.floats(allow_nan=False, allow_infinity=False))
        def test_add_associative(self, a, b):
            """Test that addition is associative: (a + b) + c = a + (b + c)"""
            c = 1.0  # Fixed value for simplicity
            result1 = self.calc.add(self.calc.add(a, b), c)
            self.calc = Calculator()
            result2 = self.calc.add(a, self.calc.add(b, c))
            self.assertAlmostEqual(result1, result2, places=5)

except ImportError:
    print("Hypothesis not available for property-based testing")

# Test fixtures and setup
class DatabaseTestCase(unittest.TestCase):
    """Base class for database-related tests."""
    
    def setUp(self):
        # Create test database
        self.test_db = tempfile.NamedTemporaryFile(delete=False, suffix='.db')
        self.test_db.close()
        # Initialize test database schema
    
    def tearDown(self):
        # Clean up test database
        try:
            os.unlink(self.test_db.name)
        except:
            pass

# Performance testing
import time
import cProfile
import pstats

def performance_test():
    """Demonstrate performance testing."""
    calc = Calculator()
    
    # Time a large number of operations
    start_time = time.time()
    for i in range(10000):
        calc.add(i, i+1)
    end_time = time.time()
    
    print(f"10,000 additions took {end_time - start_time:.4f} seconds")
    print(f"Average time per operation: {(end_time - start_time) / 10000 * 1000:.4f} ms")
    
    # Profile the code
    profiler = cProfile.Profile()
    profiler.enable()
    
    calc = Calculator()
    for i in range(1000):
        calc.add(i, i+1)
    
    profiler.disable()
    stats = pstats.Stats(profiler).sort_stats('cumulative')
    print("\nTop 5 most time-consuming functions:")
    stats.print_stats(5)

# Test coverage and quality metrics
def test_coverage_demo():
    """Demonstrate test coverage concepts."""
    print("=== Test Coverage Concepts ===")
    print("1. Statement Coverage: Every line of code executed at least once")
    print("2. Branch Coverage: Every branch (if/else) executed")
    print("3. Path Coverage: Every possible path through the code")
    print("4. Function Coverage: Every function called")
    print("5. Condition Coverage: Every boolean condition evaluated")
    
    # Tools for measuring coverage:
    # - coverage.py for Python
    # - JaCoCo for Java
    # - Istanbul for JavaScript
    
    print("\nTo measure coverage, run:")
    print("coverage run -m pytest")
    print("coverage report")
    print("coverage html  # Generate HTML report")

# Behavior-Driven Development (BDD) with pytest-bdd
def bdd_demo():
    """Demonstrate BDD testing concepts."""
    print("=== Behavior-Driven Development ===")
    print("BDD focuses on business behavior rather than implementation")
    print("Uses natural language scenarios:")
    print()
    print("Feature: User Authentication")
    print("  Scenario: Successful login")
    print("    Given a user with valid credentials")
    print("    When they attempt to log in")
    print("    Then they should be granted access")
    print()
    print("Tools: pytest-bdd, Cucumber, SpecFlow")

# Continuous Integration testing
def ci_testing_demo():
    """Demonstrate CI/CD testing concepts."""
    print("=== Continuous Integration Testing ===")
    print("1. Automated testing on every code change")
    print("2. Multiple test environments (dev, staging, prod)")
    print("3. Parallel test execution")
    print("4. Test result reporting and notifications")
    print("5. Code quality gates (coverage, linting, security)")
    
    print("\nCI Tools: Jenkins, GitHub Actions, GitLab CI, Travis CI")

# Load testing concepts
def load_testing_demo():
    """Demonstrate load testing concepts."""
    print("=== Load Testing ===")
    print("Tests application performance under load")
    print("- Concurrent users: 100, 1000, 10000")
    print("- Response time requirements")
    print("- Throughput measurements")
    print("- Resource utilization monitoring")
    
    print("\nTools: JMeter, Locust, Gatling, Artillery")

# Run comprehensive testing demonstration
if __name__ == "__main__":
    # Run unit tests
    print("=== Running Unit Tests ===")
    unittest.main(argv=[''], exit=False, verbosity=2)
    
    # Performance testing
    print("\n=== Performance Testing ===")
    performance_test()
    
    # Coverage and quality concepts
    test_coverage_demo()
    bdd_demo()
    ci_testing_demo()
    load_testing_demo()
```

## Comprehensive Best Practices and Production Readiness

### Code Quality and Maintainability

#### Clean Code Principles

```python
# Bad: Unclear, unmaintainable code
def calc(x,y,z,a,b,c):return x+y+z+a+b+c  # Hard to understand

# Good: Clear, self-documenting code
def calculate_total_score(math_score, science_score, english_score,
                         history_score, art_score, physical_education_score):
    """Calculate the total score from all subjects.

    Args:
        math_score: Score in mathematics (0-100)
        science_score: Score in science (0-100)
        english_score: Score in English (0-100)
        history_score: Score in history (0-100)
        art_score: Score in art (0-100)
        physical_education_score: Score in physical education (0-100)

    Returns:
        Total score across all subjects
    """
    total = (math_score + science_score + english_score +
             history_score + art_score + physical_education_score)
    return total

# Bad: Deep nesting, complex logic
def process_data(data):
    result = []
    for item in data:
        if item['status'] == 'active':
            if item['type'] == 'premium':
                if item['score'] > 80:
                    result.append(item)
    return result

# Good: Early returns, guard clauses
def process_data(data):
    result = []
    for item in data:
        if item['status'] != 'active':
            continue
        if item['type'] != 'premium':
            continue
        if item['score'] <= 80:
            continue
        result.append(item)
    return result

# Even better: Extract conditions to functions
def is_active_premium_high_score(item):
    return (item['status'] == 'active' and
            item['type'] == 'premium' and
            item['score'] > 80)

def process_data(data):
    return [item for item in data if is_active_premium_high_score(item)]
```

#### Code Organization and Architecture

```python
# Proper project structure
"""
my_project/
├── src/
│   ├── __init__.py
│   ├── main.py
│   ├── config.py
│   ├── database/
│   │   ├── __init__.py
│   │   ├── models.py
│   │   └── connection.py
│   ├── services/
│   │   ├── __init__.py
│   │   ├── user_service.py
│   │   └── email_service.py
│   └── utils/
│       ├── __init__.py
│       └── helpers.py
├── tests/
│   ├── __init__.py
│   ├── test_user_service.py
│   └── test_email_service.py
├── docs/
│   ├── README.md
│   └── API.md
├── requirements.txt
├── setup.py
└── .env.example
"""

# Configuration management
import os
from typing import Optional

class Config:
    """Application configuration with environment variable support."""
    
    # Database settings
    DATABASE_URL: str = os.getenv('DATABASE_URL', 'sqlite:///app.db')
    DB_POOL_SIZE: int = int(os.getenv('DB_POOL_SIZE', '10'))
    
    # API settings
    API_HOST: str = os.getenv('API_HOST', 'localhost')
    API_PORT: int = int(os.getenv('API_PORT', '8000'))
    API_DEBUG: bool = os.getenv('API_DEBUG', 'false').lower() == 'true'
    
    # Security settings
    SECRET_KEY: str = os.getenv('SECRET_KEY', 'change-this-in-production')
    JWT_EXPIRATION: int = int(os.getenv('JWT_EXPIRATION', '3600'))
    
    # External services
    EMAIL_API_KEY: Optional[str] = os.getenv('EMAIL_API_KEY')
    STRIPE_SECRET_KEY: Optional[str] = os.getenv('STRIPE_SECRET_KEY')
    
    @classmethod
    def validate_config(cls):
        """Validate that all required configuration is present."""
        required_vars = ['SECRET_KEY']
        missing = [var for var in required_vars if not getattr(cls, var)]
        
        if missing:
            raise ValueError(f"Missing required environment variables: {missing}")
        
        if cls.API_DEBUG and not cls.SECRET_KEY.startswith('dev-'):
            print("WARNING: Using debug mode with production secret key")

# Dependency injection container
class Container:
    """Simple dependency injection container."""
    
    def __init__(self):
        self._services = {}
        self._singletons = {}
    
    def register(self, interface, implementation, singleton=True):
        """Register a service implementation."""
        self._services[interface] = (implementation, singleton)
    
    def resolve(self, interface):
        """Resolve a service instance."""
        if interface not in self._services:
            raise ValueError(f"No registration for {interface}")
        
        implementation, singleton = self._services[interface]
        
        if singleton:
            if interface not in self._singletons:
                self._singletons[interface] = implementation()
            return self._singletons[interface]
        else:
            return implementation()

# Usage
container = Container()

# Register services
container.register('database', lambda: DatabaseConnection(Config.DATABASE_URL))
container.register('user_service', lambda: UserService(container.resolve('database')))
container.register('email_service', lambda: EmailService(Config.EMAIL_API_KEY))

# Resolve services
user_service = container.resolve('user_service')
email_service = container.resolve('email_service')
```

### Performance Optimization Techniques

#### Profiling and Benchmarking

```python
import time
import cProfile
import pstats
from functools import wraps
import memory_profiler
import tracemalloc

def timing_decorator(func):
    """Decorator to measure function execution time."""
    @wraps(func)
    def wrapper(*args, **kwargs):
        start_time = time.perf_counter()
        result = func(*args, **kwargs)
        end_time = time.perf_counter()
        execution_time = end_time - start_time
        print(f"{func.__name__} executed in {execution_time:.4f} seconds")
        return result
    return wrapper

def memory_usage_decorator(func):
    """Decorator to measure memory usage."""
    @wraps(func)
    def wrapper(*args, **kwargs):
        tracemalloc.start()
        start_snapshot = tracemalloc.take_snapshot()
        
        result = func(*args, **kwargs)
        
        end_snapshot = tracemalloc.take_snapshot()
        tracemalloc.stop()
        
        stats = end_snapshot.compare_to(start_snapshot, 'lineno')
        total_memory = sum(stat.size_diff for stat in stats)
        print(f"{func.__name__} used {total_memory / 1024:.2f} KB of memory")
        
        return result
    return wrapper

@timing_decorator
@memory_usage_decorator
def optimize_this_function():
    """Function to optimize."""
    data = []
    for i in range(100000):
        data.append({
            'id': i,
            'value': i * 2,
            'description': f'Item number {i}'
        })
    return data

# Algorithm optimization examples
def fibonacci_inefficient(n):
    """Inefficient recursive Fibonacci."""
    if n <= 1:
        return n
    return fibonacci_inefficient(n-1) + fibonacci_inefficient(n-2)

def fibonacci_efficient(n):
    """Efficient iterative Fibonacci."""
    if n <= 1:
        return n
    
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

def fibonacci_memoized(n, memo={}):
    """Memoized recursive Fibonacci."""
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    
    memo[n] = fibonacci_memoized(n-1, memo) + fibonacci_memoized(n-2, memo)
    return memo[n]

# Database optimization
def optimize_database_queries():
    """Database query optimization techniques."""
    print("=== Database Optimization ===")
    
    optimizations = [
        "1. Use indexes on frequently queried columns",
        "2. Avoid SELECT * - specify needed columns",
        "3. Use prepared statements to prevent re-parsing",
        "4. Implement connection pooling",
        "5. Use database-specific optimizations (views, stored procedures)",
        "6. Implement proper caching strategies",
        "7. Use pagination for large result sets",
        "8. Monitor query performance with EXPLAIN",
        "9. Normalize data appropriately (avoid over-normalization)",
        "10. Use appropriate data types and constraints"
    ]
    
    for opt in optimizations:
        print(opt)

# Caching strategies
from functools import lru_cache
import time

class Cache:
    """Simple in-memory cache with TTL."""
    
    def __init__(self):
        self._cache = {}
    
    def set(self, key, value, ttl_seconds=None):
        """Set cache value with optional TTL."""
        expiry = time.time() + ttl_seconds if ttl_seconds else None
        self._cache[key] = {'value': value, 'expiry': expiry}
    
    def get(self, key):
        """Get cache value if not expired."""
        if key not in self._cache:
            return None
        
        item = self._cache[key]
        if item['expiry'] and time.time() > item['expiry']:
            del self._cache[key]
            return None
        
        return item['value']
    
    def clear(self):
        """Clear all cache entries."""
        self._cache.clear()

@lru_cache(maxsize=128)
def expensive_api_call(user_id):
    """Simulate expensive API call with caching."""
    time.sleep(0.1)  # Simulate network delay
    return f"User data for {user_id}"

# Web optimization techniques
def web_optimization_tips():
    """Web application optimization tips."""
    print("=== Web Optimization Tips ===")
    
    tips = [
        "1. Minimize HTTP requests (combine files, use sprites)",
        "2. Use CDN for static assets",
        "3. Enable compression (gzip)",
        "4. Optimize images and media files",
        "5. Use browser caching headers",
        "6. Minimize CSS and JavaScript",
        "7. Use lazy loading for images",
        "8. Implement pagination for large datasets",
        "9. Use database query optimization",
        "10. Implement proper error handling and logging"
    ]
    
    for tip in tips:
        print(tip)

### Deployment and DevOps

#### Containerization with Docker

```dockerfile
# Dockerfile example
FROM python:3.9-slim

# Set working directory
WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Copy requirements first for better caching
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy application code
COPY . .

# Create non-root user
RUN useradd --create-home --shell /bin/bash app \
    && chown -R app:app /app
USER app

# Expose port
EXPOSE 8000

# Health check
HEALTHCHECK --interval=30s --timeout=30s --start-period=5s --retries=3 \
    CMD curl -f http://localhost:8000/health || exit 1

# Run application
CMD ["python", "main.py"]
```

#### CI/CD Pipeline Example

```yaml
# .github/workflows/ci-cd.yml
name: CI/CD Pipeline

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    services:
      postgres:
        image: postgres:13
        env:
          POSTGRES_PASSWORD: postgres
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Set up Python
      uses: actions/setup-python@v2
      with:
        python-version: '3.9'
    
    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install -r requirements.txt
        pip install -r requirements-dev.txt
    
    - name: Run tests
      run: pytest --cov=src --cov-report=xml
    
    - name: Upload coverage
      uses: codecov/codecov-action@v2
    
    - name: Run linting
      run: flake8 src tests
    
    - name: Security scan
      run: bandit -r src
    
  deploy:
    needs: test
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Build Docker image
      run: docker build -t myapp:${{ github.sha }} .
    
    - name: Push to registry
      run: |
        echo ${{ secrets.DOCKER_PASSWORD }} | docker login -u ${{ secrets.DOCKER_USERNAME }} --password-stdin
        docker tag myapp:${{ github.sha }} myregistry/myapp:latest
        docker push myregistry/myapp:latest
    
    - name: Deploy to production
      run: |
        # Deployment commands here
        echo "Deploying to production..."
```

### Monitoring and Observability

#### Logging Best Practices

```python
import logging
import logging.config
import json
from datetime import datetime
import sys

class StructuredLogger:
    """Structured logging with JSON output."""
    
    def __init__(self, name, level=logging.INFO):
        self.logger = logging.getLogger(name)
        self.logger.setLevel(level)
        
        # Remove existing handlers
        for handler in self.logger.handlers[:]:
            self.logger.removeHandler(handler)
        
        # Add structured handler
        handler = logging.StreamHandler(sys.stdout)
        formatter = StructuredFormatter()
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)
    
    def info(self, message, **kwargs):
        self.logger.info(message, extra=kwargs)
    
    def error(self, message, exc_info=None, **kwargs):
        self.logger.error(message, exc_info=exc_info, extra=kwargs)
    
    def warning(self, message, **kwargs):
        self.logger.warning(message, extra=kwargs)
    
    def debug(self, message, **kwargs):
        self.logger.debug(message, extra=kwargs)

class StructuredFormatter(logging.Formatter):
    """JSON formatter for structured logging."""
    
    def format(self, record):
        log_entry = {
            'timestamp': datetime.utcnow().isoformat(),
            'level': record.levelname,
            'logger': record.name,
            'message': record.getMessage(),
            'module': record.module,
            'function': record.funcName,
            'line': record.lineno
        }
        
        # Add any extra fields
        if hasattr(record, '__dict__'):
            for key, value in record.__dict__.items():
                if key not in ['name', 'msg', 'args', 'levelname', 'levelno',
                             'pathname', 'filename', 'module', 'exc_info',
                             'exc_text', 'stack_info', 'lineno', 'funcName',
                             'created', 'msecs', 'relativeCreated', 'thread',
                             'threadName', 'processName', 'process', 'message']:
                    log_entry[key] = value
        
        return json.dumps(log_entry)

# Usage
logger = StructuredLogger('myapp')

def user_login(user_id, ip_address):
    logger.info("User logged in",
               user_id=user_id,
               ip_address=ip_address,
               event_type="authentication")

def process_payment(amount, user_id):
    try:
        # Process payment logic
        logger.info("Payment processed successfully",
                   amount=amount,
                   user_id=user_id,
                   currency="USD")
    except Exception as e:
        logger.error("Payment processing failed",
                    amount=amount,
                    user_id=user_id,
                    error=str(e),
                    exc_info=True)

# Metrics and monitoring
class MetricsCollector:
    """Simple metrics collection."""
    
    def __init__(self):
        self.metrics = {}
    
    def increment(self, name, value=1, tags=None):
        """Increment a counter metric."""
        key = (name, tuple(sorted(tags.items())) if tags else None)
        if key not in self.metrics:
            self.metrics[key] = 0
        self.metrics[key] += value
    
    def gauge(self, name, value, tags=None):
        """Set a gauge metric."""
        key = (name, tuple(sorted(tags.items())) if tags else None)
        self.metrics[key] = value
    
    def timing(self, name, duration, tags=None):
        """Record timing metric."""
        # In real implementation, you'd send to monitoring system
        logger.info(f"Timing: {name} took {duration:.4f}s",
                   metric_name=name,
                   duration=duration,
                   **(tags or {}))
    
    def report(self):
        """Report all metrics."""
        for (name, tags), value in self.metrics.items():
            tag_str = f"{{{', '.join(f'{k}={v}' for k, v in (tags or []))}}}" if tags else ""
            print(f"{name}{tag_str}: {value}")

# Usage
metrics = MetricsCollector()

def handle_request(endpoint, user_id):
    start_time = time.time()
    
    try:
        # Simulate request processing
        time.sleep(0.01)
        
        metrics.increment('requests_total', tags={'endpoint': endpoint, 'status': 'success'})
        metrics.timing('request_duration', time.time() - start_time,
                      tags={'endpoint': endpoint})
        
        logger.info("Request processed",
                   endpoint=endpoint,
                   user_id=user_id,
                   duration=time.time() - start_time)
        
    except Exception as e:
        metrics.increment('requests_total', tags={'endpoint': endpoint, 'status': 'error'})
        logger.error("Request failed",
                    endpoint=endpoint,
                    user_id=user_id,
                    error=str(e))

# Run demonstrations
if __name__ == "__main__":
    print("=== Performance Optimization Demo ===")
    optimize_this_function()
    
    print("\n=== Algorithm Comparison ===")
    n = 30
    start = time.time()
    result1 = fibonacci_inefficient(n)
    time1 = time.time() - start
    
    start = time.time()
    result2 = fibonacci_efficient(n)
    time2 = time.time() - start
    
    start = time.time()
    result3 = fibonacci_memoized(n)
    time3 = time.time() - start
    
    print(f"Fibonacci({n}):")
    print(f"Inefficient: {result1} in {time1:.4f}s")
    print(f"Efficient: {result2} in {time2:.4f}s")
    print(f"Memoized: {result3} in {time3:.4f}s")
    
    optimize_database_queries()
    web_optimization_tips()
    
    print("\n=== Logging and Monitoring Demo ===")
    user_login("user123", "192.168.1.100")
    process_payment(99.99, "user123")
    
    handle_request("/api/users", "user123")
    handle_request("/api/orders", "user456")
    
    print("\n=== Metrics Report ===")
    metrics.report()
```

## Summary

Advanced programming encompasses a wide range of skills and knowledge areas essential for building production-ready, scalable, and maintainable software systems. From robust error handling and comprehensive testing to performance optimization and deployment automation, these concepts form the foundation of modern software development.

Key takeaways include:
- **Error handling**: Implement comprehensive exception handling with proper logging and recovery mechanisms
- **File I/O**: Master various file operations, binary data handling, and efficient data persistence
- **Database design**: Understand normalization, indexing, query optimization, and secure database access
- **Networking**: Learn HTTP protocols, REST API design, WebSocket communication, and network utilities
- **Concurrency**: Apply threading, multiprocessing, and async programming for performance gains
- **Memory management**: Implement efficient memory usage, garbage collection understanding, and profiling
- **Security**: Apply input validation, secure database queries, authentication, and cryptography
- **Testing**: Use comprehensive testing strategies including unit, integration, and performance testing
- **Best practices**: Follow clean code principles, proper architecture, and production readiness

These advanced topics transform basic programming knowledge into professional software development expertise. Practice implementing these concepts in real projects, contribute to open-source software, and continuously learn about emerging technologies and best practices.

## Comprehensive Exercises and Projects

### Error Handling and Resilience
1. **Circuit Breaker**: Implement a circuit breaker pattern for API calls
2. **Retry Mechanism**: Build an exponential backoff retry system
3. **Custom Exceptions**: Create a comprehensive exception hierarchy for a banking application
4. **Error Recovery**: Implement automatic error recovery for file processing

### File and Data Processing
5. **CSV Processor**: Build a robust CSV file processor with error handling and validation
6. **Binary File Editor**: Create a hex editor for binary file manipulation
7. **Configuration Manager**: Implement a multi-format configuration file manager (JSON, YAML, INI)
8. **Data Compressor**: Build a file compression utility with multiple algorithms

### Database Applications
9. **User Management System**: Complete user CRUD with authentication and authorization
10. **E-commerce Database**: Design and implement a product catalog with search and filtering
11. **Analytics Dashboard**: Build a database-backed analytics system with caching
12. **Migration System**: Create a database migration framework

### Networking Projects
13. **REST API Server**: Build a complete REST API with authentication and rate limiting
14. **WebSocket Chat**: Implement a real-time chat application
15. **HTTP Client Library**: Create a comprehensive HTTP client with retry logic
16. **Network Scanner**: Build a port scanner and network discovery tool

### Concurrent Applications
17. **Web Crawler**: Multi-threaded web crawler with politeness and rate limiting
18. **Image Processor**: Concurrent image processing pipeline
19. **Task Scheduler**: Distributed task scheduler with worker processes
20. **Chat Server**: Multi-client chat server with rooms and private messaging

### Security Projects
21. **Password Manager**: Secure password storage and generation
22. **Authentication System**: JWT-based authentication with refresh tokens
23. **Encryption Tool**: File encryption/decryption utility
24. **Security Scanner**: Basic vulnerability scanner for web applications

### Testing and Quality Assurance
25. **Test Framework**: Build a custom testing framework with fixtures and mocking
26. **Load Testing Tool**: Create a simple load testing utility
27. **Code Coverage Tool**: Implement basic code coverage measurement
28. **CI/CD Pipeline**: Set up automated testing and deployment

### Performance and Optimization
29. **Cache System**: Implement various caching strategies (LRU, TTL, distributed)
30. **Profiling Tool**: Build a code profiling and optimization tool
31. **Memory Analyzer**: Create a memory usage analysis tool
32. **Database Optimizer**: Implement query optimization and indexing tools

### Real-World Applications
33. **Blog Platform**: Full-featured blog with users, posts, comments, and admin panel
34. **Task Manager**: Project management tool with teams, tasks, and progress tracking
35. **File Sharing Service**: Secure file upload/download with user management
36. **API Gateway**: Microservices API gateway with authentication and rate limiting
37. **Monitoring Dashboard**: Application monitoring with metrics and alerting
38. **Content Management System**: Flexible CMS with plugins and themes

### Advanced Challenges
39. **Distributed System**: Build a simple distributed key-value store
40. **Compiler**: Create a basic interpreter for a custom programming language
41. **Game Engine**: Develop a simple 2D game engine with physics and rendering
42. **Machine Learning Pipeline**: Build an end-to-end ML model training and deployment system
43. **Blockchain**: Implement a basic blockchain with mining and transactions
44. **IoT Platform**: Create an IoT device management platform
45. **Real-time Analytics**: Build a real-time data processing and analytics system

Remember: The best way to master these advanced concepts is through hands-on practice. Start with small projects and gradually build more complex systems. Learn from open-source projects, contribute to communities, and stay updated with industry best practices. Programming is a continuous learning journey - embrace the challenges and enjoy the process!

## Essential Resources and Further Reading

### Books
- **"Clean Code"** by Robert C. Martin - Code quality and best practices
- **"The Pragmatic Programmer"** by Andrew Hunt and David Thomas - Professional development
- **"Design Patterns"** by Gang of Four - Software design patterns
- **"Code Complete"** by Steve McConnell - Comprehensive programming guide
- **"Effective Java"** by Joshua Bloch - Java best practices
- **"Python Cookbook"** by David Beazley - Python advanced techniques

### Online Learning Platforms
- **Coursera**: Advanced computer science courses from top universities
- **edX**: Professional development and certification courses
- **Udacity**: Nanodegree programs for career advancement
- **Pluralsight**: Technology skill development platform
- **O'Reilly Learning**: Comprehensive tech learning platform

### Documentation and References
- **MDN Web Docs**: Comprehensive web development documentation
- **Python Documentation**: Official Python language reference
- **Java Documentation**: Oracle's Java documentation
- **Microsoft Docs**: .NET and Azure documentation
- **AWS Documentation**: Cloud computing services
- **Docker Documentation**: Containerization platform

### Communities and Forums
- **Stack Overflow**: Programming Q&A and problem solving
- **Reddit**: r/programming, r/learnprogramming, r/coding
- **GitHub**: Open source collaboration and learning
- **Dev.to**: Developer blogging and community
- **Hacker News**: Technology news and discussion
- **Discord Servers**: Real-time coding communities

### Tools and Technologies
- **Version Control**: Git, GitHub, GitLab
- **IDEs**: Visual Studio Code, PyCharm, IntelliJ IDEA
- **Containerization**: Docker, Kubernetes
- **Cloud Platforms**: AWS, Azure, Google Cloud
- **Monitoring**: Prometheus, Grafana, ELK Stack
- **CI/CD**: Jenkins, GitHub Actions, GitLab CI

### Career Development
- **LinkedIn Learning**: Professional skill development
- **LeetCode**: Algorithm and interview preparation
- **HackerRank**: Coding challenges and skill assessment
- **CodeChef**: Competitive programming platform
- **Interviewing.io**: Anonymous technical interview practice

Mastering these advanced topics will transform you from a beginner programmer into a professional software developer capable of building complex, production-ready applications. Focus on understanding core concepts deeply, practicing regularly, and staying curious about new technologies and methodologies. The programming world is vast and constantly evolving - embrace lifelong learning as your superpower!
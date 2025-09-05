# 🔤 Lesson 9: Strings in C
## Character Arrays and String Operations

---

## 🎯 Learning Objectives

- Understand string declaration and initialization
- Master standard string functions
- Learn manual string implementations
- Understand string manipulation techniques
- Handle common string pitfalls

---

## 📖 Strings Kya Hain C Mein?

**Strings** C mein character arrays hote hain jo null character (`'\0'`) se terminate hote hain. Other languages ki tarah C mein built-in string type nahi hota - strings character arrays ke through implement kiye jate hain.

### **String ki Characteristics**
- **Null-terminated**: `'\0'` (ASCII 0) se end hote hain
- **Character arrays**: `char` arrays ke form mein store hote hain
- **Mutable**: Modify kar sakte hain (some languages ki tarah nahi)
- **No bounds checking**: Programmer ki responsibility

### **String ke Types**
- **Character Arrays**: Fixed size, stack pe allocate
- **String Literals**: Read-only, data section mein
- **Dynamic Strings**: Runtime pe allocate, flexible size
- **Pointer to Char**: String ko point karne ke liye

---

## 📝 String Declaration and Initialization

### **String Declaration**
```c
// Method 1: Fixed size
char str1[20];

// Method 2: Size determined by initializer
char str2[] = "Hello";

// Method 3: Pointer to char
char *str3;
```

### **String Initialization**
```c
#include <stdio.h>

int main() {
    // Method 1: Character array with initialization
    char greeting[] = "Hello, World!";
    printf("Greeting: %s\n", greeting);

    // Method 2: Character by character
    char name[10];
    name[0] = 'J';
    name[1] = 'o';
    name[2] = 'h';
    name[3] = 'n';
    name[4] = '\0';  // Null terminator
    printf("Name: %s\n", name);

    // Method 3: Using pointers
    char *message = "Welcome to C Programming";
    printf("Message: %s\n", message);

    // Method 4: Multi-line strings
    char poem[] = "Roses are red,\n"
                  "Violets are blue,\n"
                  "C programming is fun,\n"
                  "And so are you!";
    printf("%s\n", poem);

    return 0;
}
```

### **Reading Strings from User**
```c
#include <stdio.h>

int main() {
    char name[50];
    char sentence[100];

    // Method 1: scanf (stops at whitespace)
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);

    // Method 2: fgets (reads entire line)
    printf("Enter a sentence: ");
    getchar();  // Consume newline from previous input
    fgets(sentence, sizeof(sentence), stdin);
    printf("You said: %s", sentence);

    return 0;
}
```

---

## 🛠️ Standard String Functions

### **String Length (`strlen`)**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World!";
    int length = strlen(str);

    printf("String: %s\n", str);
    printf("Length: %d\n", length);

    // Manual length calculation
    int manual_length = 0;
    while (str[manual_length] != '\0') {
        manual_length++;
    }
    printf("Manual length: %d\n", manual_length);

    return 0;
}
```

### **String Copy (`strcpy`, `strncpy`)**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    // strcpy - Copy entire string
    strcpy(destination, source);
    printf("Copied string: %s\n", destination);

    // strncpy - Copy limited characters
    char partial[10];
    strncpy(partial, source, 5);
    partial[5] = '\0';  // Manually add null terminator
    printf("Partial copy: %s\n", partial);

    return 0;
}
```

### **String Concatenation (`strcat`, `strncat`)**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[20] = "Hello";
    char str2[] = " World!";

    // strcat - Concatenate strings
    strcat(str1, str2);
    printf("Concatenated: %s\n", str1);

    // strncat - Concatenate limited characters
    char str3[20] = "Hello";
    strncat(str3, " Beautiful World!", 10);
    printf("Limited concat: %s\n", str3);

    return 0;
}
```

### **String Comparison (`strcmp`, `strncmp`)**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    char str4[] = "hello";

    // strcmp - Compare strings
    printf("str1 vs str2: %d\n", strcmp(str1, str2));  // 0 (equal)
    printf("str1 vs str3: %d\n", strcmp(str1, str3));  // Negative (str1 < str3)
    printf("str1 vs str4: %d\n", strcmp(str1, str4));  // Negative (case sensitive)

    // Practical usage
    if (strcmp(str1, str2) == 0) {
        printf("Strings are equal\n");
    } else {
        printf("Strings are different\n");
    }

    return 0;
}
```

### **Other Useful Functions**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World!";
    char search[] = "World";

    // strchr - Find first occurrence of character
    char *pos = strchr(str, 'W');
    if (pos != NULL) {
        printf("Found 'W' at position: %ld\n", pos - str);
    }

    // strstr - Find substring
    char *substr = strstr(str, search);
    if (substr != NULL) {
        printf("Found '%s' at position: %ld\n", search, substr - str);
    }

    // strrev - Reverse string (not standard, manual implementation needed)
    char reversed[20];
    strcpy(reversed, str);
    int len = strlen(reversed);
    for (int i = 0; i < len / 2; i++) {
        char temp = reversed[i];
        reversed[i] = reversed[len - 1 - i];
        reversed[len - 1 - i] = temp;
    }
    printf("Reversed: %s\n", reversed);

    return 0;
}
```

---

## 🔧 Manual String Implementations

### **Manual `strlen`**
```c
#include <stdio.h>

// Manual string length function
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    char str[] = "Hello, World!";
    printf("Length: %d\n", my_strlen(str));
    return 0;
}
```

### **Manual `strcpy`**
```c
#include <stdio.h>

// Manual string copy function
char* my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Add null terminator
    return dest;
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    my_strcpy(destination, source);
    printf("Copied: %s\n", destination);

    return 0;
}
```

### **Manual `strcmp`**
```c
#include <stdio.h>

// Manual string comparison function
int my_strcmp(const char *str1, const char *str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    // If one string is longer than the other
    return str1[i] - str2[i];
}

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    printf("str1 vs str2: %d\n", my_strcmp(str1, str2));
    printf("str1 vs str3: %d\n", my_strcmp(str1, str3));

    return 0;
}
```

### **Manual `strcat`**
```c
#include <stdio.h>

// Manual string concatenation function
char* my_strcat(char *dest, const char *src) {
    int dest_len = 0;

    // Find end of destination string
    while (dest[dest_len] != '\0') {
        dest_len++;
    }

    // Copy source to end of destination
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }

    dest[dest_len + i] = '\0';  // Add null terminator
    return dest;
}

int main() {
    char str1[20] = "Hello";
    char str2[] = " World!";

    my_strcat(str1, str2);
    printf("Concatenated: %s\n", str1);

    return 0;
}
```

---

## 🔄 String Manipulation Techniques

### **String Reversal**
```c
#include <stdio.h>
#include <string.h>

// Method 1: Using two pointers
void reverse_string(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Method 2: Using recursion
void reverse_recursive(char *str, int start, int end) {
    if (start >= end) return;

    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    reverse_recursive(str, start + 1, end - 1);
}

int main() {
    char str[] = "Hello, World!";

    printf("Original: %s\n", str);

    reverse_string(str);
    printf("Reversed: %s\n", str);

    return 0;
}
```

### **Substring Search**
```c
#include <stdio.h>
#include <string.h>

// Manual substring search
char* my_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') return (char*)haystack;

    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (haystack[i + j] == needle[j] && needle[j] != '\0') {
            j++;
        }
        if (needle[j] == '\0') {
            return (char*)&haystack[i];
        }
    }
    return NULL;
}

int main() {
    char text[] = "Hello, World! Welcome to C programming.";
    char pattern[] = "World";

    char *result = my_strstr(text, pattern);
    if (result != NULL) {
        printf("Found '%s' at position: %ld\n", pattern, result - text);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}
```

### **Palindrome Check**
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Check if string is palindrome (case insensitive)
int is_palindrome(const char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        // Skip non-alphanumeric characters
        while (start < end && !isalnum(str[start])) start++;
        while (start < end && !isalnum(str[end])) end--;

        // Compare characters (case insensitive)
        if (tolower(str[start]) != tolower(str[end])) {
            return 0;  // Not palindrome
        }

        start++;
        end--;
    }

    return 1;  // Palindrome
}

int main() {
    char str1[] = "A man, a plan, a canal: Panama";
    char str2[] = "race a car";

    printf("'%s' is %s\n", str1, is_palindrome(str1) ? "palindrome" : "not palindrome");
    printf("'%s' is %s\n", str2, is_palindrome(str2) ? "palindrome" : "not palindrome");

    return 0;
}
```

### **Word Count**
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Count words in a string
int count_words(const char *str) {
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }

    return count;
}

int main() {
    char text[] = "This is a sample text with multiple words.";

    printf("Text: %s\n", text);
    printf("Word count: %d\n", count_words(text));

    return 0;
}
```

### **Advanced String Algorithms**

#### **KMP (Knuth-Morris-Pratt) Pattern Matching**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compute prefix table for KMP
void compute_prefix_table(const char *pattern, int *prefix, int m) {
    int len = 0;
    prefix[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefix[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = prefix[len - 1];
            } else {
                prefix[i] = 0;
                i++;
            }
        }
    }
}

// KMP search algorithm
int kmp_search(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int *prefix = (int*)malloc(m * sizeof(int));
    compute_prefix_table(pattern, prefix, m);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            free(prefix);
            return i - j; // Pattern found
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }

    free(prefix);
    return -1; // Pattern not found
}

int main() {
    char text[] = "AABAACAADAABAABA";
    char pattern[] = "AABA";

    int result = kmp_search(text, pattern);
    if (result != -1) {
        printf("Pattern found at index %d\n", result);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}
```

#### **String Compression (Run Length Encoding)**
```c
#include <stdio.h>
#include <string.h>

// Compress string using run length encoding
void compress_string(const char *str, char *result) {
    int len = strlen(str);
    int i = 0;
    int j = 0;

    while (i < len) {
        char current = str[i];
        int count = 0;

        // Count consecutive occurrences
        while (i < len && str[i] == current) {
            count++;
            i++;
        }

        // Add character and count to result
        result[j++] = current;

        if (count > 1) {
            // Convert count to string
            char count_str[10];
            sprintf(count_str, "%d", count);
            strcpy(&result[j], count_str);
            j += strlen(count_str);
        }
    }

    result[j] = '\0';
}

// Decompress run length encoded string
void decompress_string(const char *compressed, char *result) {
    int i = 0;
    int j = 0;

    while (compressed[i] != '\0') {
        char ch = compressed[i++];
        int count = 0;

        // Read count (if present)
        while (compressed[i] >= '0' && compressed[i] <= '9') {
            count = count * 10 + (compressed[i] - '0');
            i++;
        }

        if (count == 0) count = 1; // No count means 1

        // Expand character
        for (int k = 0; k < count; k++) {
            result[j++] = ch;
        }
    }

    result[j] = '\0';
}

int main() {
    char original[] = "aaabbbcccaaa";
    char compressed[50];
    char decompressed[50];

    compress_string(original, compressed);
    printf("Original: %s\n", original);
    printf("Compressed: %s\n", compressed);

    decompress_string(compressed, decompressed);
    printf("Decompressed: %s\n", decompressed);

    return 0;
}
```

#### **Longest Common Substring**
```c
#include <stdio.h>
#include <string.h>

// Find length of longest common substring
int longest_common_substring(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int max_length = 0;

    // Create DP table
    int dp[len1 + 1][len2 + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return max_length;
}

int main() {
    char str1[] = "ABCDGH";
    char str2[] = "ACDGHR";

    int length = longest_common_substring(str1, str2);
    printf("Length of longest common substring: %d\n", length);

    return 0;
}
```

#### **String Permutation Check**
```c
#include <stdio.h>
#include <string.h>

// Check if one string is permutation of another
int is_permutation(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) return 0;

    // Count frequency of characters
    int count[256] = {0};

    for (int i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) return 0;
    }

    return 1;
}

int main() {
    char str1[] = "listen";
    char str2[] = "silent";

    if (is_permutation(str1, str2)) {
        printf("'%s' and '%s' are permutations\n", str1, str2);
    } else {
        printf("'%s' and '%s' are not permutations\n", str1, str2);
    }

    return 0;
}
```

#### **Anagram Detection**
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Sort string for anagram comparison
void sort_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// Check if two strings are anagrams
int are_anagrams(const char *str1, const char *str2) {
    char sorted1[100], sorted2[100];

    // Remove spaces and convert to lowercase
    int j = 0;
    for (int i = 0; str1[i]; i++) {
        if (!isspace(str1[i])) {
            sorted1[j++] = tolower(str1[i]);
        }
    }
    sorted1[j] = '\0';

    j = 0;
    for (int i = 0; str2[i]; i++) {
        if (!isspace(str2[i])) {
            sorted2[j++] = tolower(str2[i]);
        }
    }
    sorted2[j] = '\0';

    // Sort both strings
    sort_string(sorted1);
    sort_string(sorted2);

    // Compare sorted strings
    return strcmp(sorted1, sorted2) == 0;
}

int main() {
    char str1[] = "listen";
    char str2[] = "silent";

    if (are_anagrams(str1, str2)) {
        printf("'%s' and '%s' are anagrams\n", str1, str2);
    } else {
        printf("'%s' and '%s' are not anagrams\n", str1, str2);
    }

    return 0;
}
```

#### **Text Tokenization**
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Simple tokenizer
char** tokenize(const char *text, int *num_tokens) {
    char *copy = strdup(text);
    char **tokens = NULL;
    *num_tokens = 0;

    char *token = strtok(copy, " \t\n.,!?");

    while (token != NULL) {
        (*num_tokens)++;
        tokens = realloc(tokens, *num_tokens * sizeof(char*));
        tokens[*num_tokens - 1] = strdup(token);
        token = strtok(NULL, " \t\n.,!?");
    }

    free(copy);
    return tokens;
}

int main() {
    char text[] = "Hello, world! This is a test.";
    int num_tokens;

    char **tokens = tokenize(text, &num_tokens);

    printf("Original text: %s\n", text);
    printf("Tokens (%d):\n", num_tokens);

    for (int i = 0; i < num_tokens; i++) {
        printf("  %d: %s\n", i + 1, tokens[i]);
        free(tokens[i]);
    }

    free(tokens);
    return 0;
}
```

#### **String Pattern Matching with Wildcards**
```c
#include <stdio.h>
#include <string.h>

// Wildcard pattern matching (* and ?)
int wildcard_match(const char *text, const char *pattern) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    // DP table
    int dp[text_len + 1][pattern_len + 1];
    memset(dp, 0, sizeof(dp));

    // Empty pattern matches empty text
    dp[0][0] = 1;

    // Handle patterns starting with *
    for (int j = 1; j <= pattern_len; j++) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for (int i = 1; i <= text_len; i++) {
        for (int j = 1; j <= pattern_len; j++) {
            if (pattern[j - 1] == '*') {
                // * can match zero or more characters
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if (pattern[j - 1] == '?' || text[i - 1] == pattern[j - 1]) {
                // ? matches any single character or exact match
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    return dp[text_len][pattern_len];
}

int main() {
    char text[] = "aaabbb";
    char pattern[] = "a*b*";

    if (wildcard_match(text, pattern)) {
        printf("'%s' matches pattern '%s'\n", text, pattern);
    } else {
        printf("'%s' does not match pattern '%s'\n", text, pattern);
    }

    return 0;
}
```

---

## 🔢 Character Classification and Conversion

### **Character Functions**
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char ch = 'A';

    // Character classification
    printf("isalpha('%c'): %d\n", ch, isalpha(ch));    // 1 (true)
    printf("isdigit('%c'): %d\n", ch, isdigit(ch));    // 0 (false)
    printf("islower('%c'): %d\n", ch, islower(ch));    // 0 (false)
    printf("isupper('%c'): %d\n", ch, isupper(ch));    // 1 (true)

    // Character conversion
    printf("tolower('%c'): %c\n", ch, tolower(ch));    // 'a'
    printf("toupper('%c'): %c\n", 'b', toupper('b')); // 'B'

    return 0;
}
```

### **String Case Conversion**
```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Convert string to uppercase
void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

// Convert string to lowercase
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

int main() {
    char text[] = "Hello, World!";

    printf("Original: %s\n", text);

    to_uppercase(text);
    printf("Uppercase: %s\n", text);

    to_lowercase(text);
    printf("Lowercase: %s\n", text);

    return 0;
}
```

---

## ⚠️ Common String Mistakes

### **1. Buffer Overflow**
```c
#include <stdio.h>

int main() {
    char buffer[10];

    // Dangerous: No bounds checking
    strcpy(buffer, "This is a very long string that will overflow");

    // Safe: Use strncpy
    char safe_buffer[10];
    strncpy(safe_buffer, "This is safe", sizeof(safe_buffer) - 1);
    safe_buffer[sizeof(safe_buffer) - 1] = '\0';

    printf("Safe buffer: %s\n", safe_buffer);

    return 0;
}
```

### **2. Forgetting Null Terminator**
```c
#include <stdio.h>

int main() {
    char str[10];

    // Wrong: No null terminator
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    // Missing: str[5] = '\0';

    printf("String: %s\n", str);  // Undefined behavior

    // Correct
    str[5] = '\0';
    printf("Correct string: %s\n", str);

    return 0;
}
```

### **3. String Literal Modification**
```c
#include <stdio.h>

int main() {
    char *str = "Hello, World!";

    // Wrong: Trying to modify string literal
    // str[0] = 'h';  // Runtime error!

    // Correct: Use character array
    char str2[] = "Hello, World!";
    str2[0] = 'h';  // OK
    printf("%s\n", str2);

    return 0;
}
```

### **4. scanf Buffer Issues**
```c
#include <stdio.h>

int main() {
    char name[20];

    // Wrong: No width specifier
    // scanf("%s", name);  // Can overflow!

    // Correct: Specify width
    scanf("%19s", name);  // Leaves space for null terminator

    printf("Name: %s\n", name);

    return 0;
}
```

---

## 🎯 Best Practices

### **1. Always Check Bounds**
```c
// ✅ Safe string operations
char dest[20];
char src[] = "Very long string that might overflow";

strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

### **2. Use String Literals Carefully**
```c
// ✅ Prefer const for string literals
const char *message = "This cannot be modified";

// ❌ Avoid modifying string literals
char *bad_message = "Don't modify this";  // Dangerous
```

### **3. Handle User Input Safely**
```c
// ✅ Safe input reading
char buffer[100];
if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    // Remove trailing newline
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Input: %s\n", buffer);
}
```

### **4. Use Meaningful String Names**
```c
// ✅ Descriptive names
char user_name[50];
char email_address[100];
char phone_number[15];

// ❌ Generic names
char a[50];
char b[100];
char c[15];
```

---

## 📝 Practice Exercises

### **Exercise 1: String Operations**
Create functions for:
- Count vowels and consonants
- Remove all whitespace
- Replace substring
- Count word frequency

### **Exercise 2: String Algorithms**
Implement:
- String compression (aaabbb → a3b3)
- Longest common substring
- String permutation check
- Anagram detection

### **Exercise 3: Text Processing**
Build:
- Simple text editor
- Word frequency counter
- CSV parser
- Basic encryption/decryption

### **Exercise 4: Advanced Strings**
Create:
- String tokenizer
- Pattern matching
- Text formatting utilities
- String validation functions

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
How are strings represented in C?
a) Built-in string type
b) Character arrays with null terminator
c) Linked list of characters
d) Special string objects

### **Question 2:**
What is the null terminator in C strings?
a) `\n`
b) `\0`
c) `\t`
d) `NULL`

### **Question 3:**
Which function is used to find string length?
a) `strlen()`
b) `strlength()`
c) `stringlen()`
d) `length()`

### **Question 4:**
What does `strcmp()` return when strings are equal?
a) 1
b) 0
c) -1
d) Length of string

### **Question 5:**
Which is safer for copying strings?
a) `strcpy()`
b) `strncpy()`
c) Both are equally safe
d) Neither is safe

---

## 🔗 Additional Resources

### **String Algorithms**
- [String Searching Algorithms](https://en.wikipedia.org/wiki/String_searching_algorithm)
- [Pattern Matching](https://en.wikipedia.org/wiki/Pattern_matching)
- [Text Processing](https://en.wikipedia.org/wiki/Text_processing)

### **Further Reading**
- [Strings in C](https://en.cppreference.com/w/c/string)
- [String Functions](https://www.programiz.com/c-programming/c-strings)
- [Character Handling](https://en.cppreference.com/w/c/string/byte)

---

## 🎯 Next Steps

**Excellent work!** You've mastered:
- ✅ String declaration and initialization
- ✅ Standard string functions
- ✅ Manual string implementations
- ✅ String manipulation techniques
- ✅ Common string pitfalls

**Next Lesson Preview:**
- Pointers fundamentals
- Pointer arithmetic
- Pointers to arrays and strings
- Dynamic memory allocation

---

**🚀 Ready to explore pointers?**

[⬅️ Previous: Arrays](08_Arrays.md) | [Next: Pointers ➡️](10_Pointers.md)
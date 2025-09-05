# 📦 **Project 19: Simple File Compression in C**
## 🎯 **Run-Length Encoding with Huffman Coding Basics**

---

## 📋 **Project Overview**

**English:** A simple file compression utility in C that implements Run-Length Encoding (RLE) and basic Huffman coding for text file compression with decompression capabilities and compression ratio analysis.

**Hinglish:** Ek simple file compression utility jo C mein hai, jisme Run-Length Encoding (RLE) aur basic Huffman coding implement kiya gaya hai for text file compression with decompression capabilities aur compression ratio analysis ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Data compression algorithms
- File I/O for binary data
- Bit manipulation
- Memory-efficient data structures
- Algorithm optimization

✅ **Compression Concepts:**
- Run-length encoding
- Huffman coding basics
- Compression ratios
- Data encoding/decoding
- File format handling

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Compression algorithms | Handles encoding and decoding logic |
| **File System** | Binary file operations | Reading/writing compressed data |
| **Bit Operations** | Data packing | Efficient bit manipulation |
| **Dynamic Memory** | Tree structures | Huffman tree construction |

---

## 📁 **Project Structure**

```
FileCompression/
├── include/
│   ├── rle.h
│   ├── huffman.h
│   ├── compression.h
├── src/
│   ├── rle.c
│   ├── huffman.c
│   ├── compression.c
│   └── main.c
├── data/
│   └── sample.txt
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Run-Length Encoding (RLE)**

```c
// rle.h
#ifndef RLE_H
#define RLE_H

// RLE functions
int compress_rle(const char *input_file, const char *output_file);
int decompress_rle(const char *input_file, const char *output_file);
double get_rle_ratio(const char *original_file, const char *compressed_file);

#endif
```

```c
// rle.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

// Compress using Run-Length Encoding
int compress_rle(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "wb");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    char current_char;
    int count = 1;
    char prev_char = fgetc(input);

    if (prev_char == EOF) {
        fclose(input);
        fclose(output);
        return 1; // Empty file
    }

    while ((current_char = fgetc(input)) != EOF) {
        if (current_char == prev_char && count < 255) {
            count++;
        } else {
            // Write count and character
            fputc(count, output);
            fputc(prev_char, output);

            prev_char = current_char;
            count = 1;
        }
    }

    // Write last run
    fputc(count, output);
    fputc(prev_char, output);

    fclose(input);
    fclose(output);
    return 1;
}

// Decompress RLE data
int decompress_rle(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    while (!feof(input)) {
        int count = fgetc(input);
        if (count == EOF) break;

        char character = fgetc(input);
        if (character == EOF) break;

        // Write character 'count' times
        for (int i = 0; i < count; i++) {
            fputc(character, output);
        }
    }

    fclose(input);
    fclose(output);
    return 1;
}

// Calculate compression ratio
double get_rle_ratio(const char *original_file, const char *compressed_file) {
    FILE *orig = fopen(original_file, "r");
    FILE *comp = fopen(compressed_file, "rb");

    if (!orig || !comp) {
        if (orig) fclose(orig);
        if (comp) fclose(comp);
        return 0.0;
    }

    fseek(orig, 0, SEEK_END);
    long orig_size = ftell(orig);

    fseek(comp, 0, SEEK_END);
    long comp_size = ftell(comp);

    fclose(orig);
    fclose(comp);

    if (orig_size == 0) return 0.0;

    return (double)comp_size / orig_size;
}
```

### **2. Basic Huffman Coding**

```c
// huffman.h
#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_TREE_HT 100

// Huffman tree node
typedef struct HuffmanNode {
    char data;
    unsigned freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// Huffman functions
int compress_huffman(const char *input_file, const char *output_file);
int decompress_huffman(const char *input_file, const char *output_file);
double get_huffman_ratio(const char *original_file, const char *compressed_file);

// Helper functions
HuffmanNode* create_node(char data, unsigned freq);
void calculate_frequency(const char *text, int *freq);
HuffmanNode* build_huffman_tree(int *freq);
void generate_codes(HuffmanNode* root, char *code, int top, char codes[256][MAX_TREE_HT]);
void free_huffman_tree(HuffmanNode* root);

#endif
```

```c
// huffman.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "huffman.h"

// Priority queue for Huffman tree
typedef struct {
    HuffmanNode **array;
    int size;
} MinHeap;

// Create Huffman node
HuffmanNode* create_node(char data, unsigned freq) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Calculate character frequencies
void calculate_frequency(const char *text, int *freq) {
    for (int i = 0; text[i] != '\0'; i++) {
        freq[(unsigned char)text[i]]++;
    }
}

// Build Huffman tree
HuffmanNode* build_huffman_tree(int *freq) {
    // Create leaf nodes
    HuffmanNode *left, *right, *top;
    HuffmanNode **nodes = (HuffmanNode**)malloc(256 * sizeof(HuffmanNode*));

    int node_count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            nodes[node_count++] = create_node((char)i, freq[i]);
        }
    }

    // Build tree using simple selection sort approach
    while (node_count > 1) {
        // Find two minimum frequency nodes
        int min1 = 0, min2 = 1;
        if (nodes[min2]->freq < nodes[min1]->freq) {
            min1 = 1;
            min2 = 0;
        }

        for (int i = 2; i < node_count; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        // Create new internal node
        left = nodes[min1];
        right = nodes[min2];
        top = create_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        // Remove used nodes and add new node
        nodes[min1] = top;
        nodes[min2] = nodes[node_count - 1];
        node_count--;
    }

    HuffmanNode *root = nodes[0];
    free(nodes);
    return root;
}

// Generate Huffman codes
void generate_codes(HuffmanNode* root, char *code, int top, char codes[256][MAX_TREE_HT]) {
    if (root->left) {
        code[top] = '0';
        generate_codes(root->left, code, top + 1, codes);
    }

    if (root->right) {
        code[top] = '1';
        generate_codes(root->right, code, top + 1, codes);
    }

    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(codes[(unsigned char)root->data], code);
    }
}

// Compress using Huffman coding
int compress_huffman(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "wb");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 0;
    }

    // Read entire file
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *text = (char*)malloc(file_size + 1);
    fread(text, 1, file_size, input);
    text[file_size] = '\0';

    // Calculate frequencies
    int freq[256] = {0};
    calculate_frequency(text, freq);

    // Build Huffman tree
    HuffmanNode *root = build_huffman_tree(freq);

    // Generate codes
    char codes[256][MAX_TREE_HT];
    memset(codes, 0, sizeof(codes));
    char code[MAX_TREE_HT];
    generate_codes(root, code, 0, codes);

    // Write frequency table (simplified)
    fwrite(freq, sizeof(int), 256, output);

    // Compress text
    unsigned char buffer = 0;
    int bit_count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char *code_str = codes[(unsigned char)text[i]];

        for (int j = 0; code_str[j] != '\0'; j++) {
            buffer = (buffer << 1) | (code_str[j] - '0');
            bit_count++;

            if (bit_count == 8) {
                fputc(buffer, output);
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    // Write remaining bits
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        fputc(buffer, output);
    }

    free(text);
    free_huffman_tree(root);
    fclose(input);
    fclose(output);
    return 1;
}

// Free Huffman tree
void free_huffman_tree(HuffmanNode* root) {
    if (!root) return;
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}

// Calculate Huffman compression ratio
double get_huffman_ratio(const char *original_file, const char *compressed_file) {
    FILE *orig = fopen(original_file, "r");
    FILE *comp = fopen(compressed_file, "rb");

    if (!orig || !comp) {
        if (orig) fclose(orig);
        if (comp) fclose(comp);
        return 0.0;
    }

    fseek(orig, 0, SEEK_END);
    long orig_size = ftell(orig);

    fseek(comp, 0, SEEK_END);
    long comp_size = ftell(comp);

    fclose(orig);
    fclose(comp);

    if (orig_size == 0) return 0.0;

    return (double)comp_size / orig_size;
}
```

### **3. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "rle.h"
#include "huffman.h"

void display_menu() {
    printf("\n=== File Compression Tool ===\n");
    printf("1. Compress with RLE\n");
    printf("2. Decompress RLE\n");
    printf("3. Compress with Huffman\n");
    printf("4. Show Compression Ratios\n");
    printf("5. Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

int main() {
    char input_file[256], output_file[256];
    int choice;

    printf("File Compression Tool\n");
    printf("=====================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // RLE Compression
                printf("Enter input filename: ");
                scanf(" %s", input_file);
                printf("Enter output filename: ");
                scanf(" %s", output_file);

                if (compress_rle(input_file, output_file)) {
                    printf("RLE compression successful!\n");

                    double ratio = get_rle_ratio(input_file, output_file);
                    printf("Compression ratio: %.2f\n", ratio);
                } else {
                    printf("RLE compression failed!\n");
                }
                break;
            }

            case 2: {
                // RLE Decompression
                printf("Enter compressed filename: ");
                scanf(" %s", input_file);
                printf("Enter output filename: ");
                scanf(" %s", output_file);

                if (decompress_rle(input_file, output_file)) {
                    printf("RLE decompression successful!\n");
                } else {
                    printf("RLE decompression failed!\n");
                }
                break;
            }

            case 3: {
                // Huffman Compression
                printf("Enter input filename: ");
                scanf(" %s", input_file);
                printf("Enter output filename: ");
                scanf(" %s", output_file);

                if (compress_huffman(input_file, output_file)) {
                    printf("Huffman compression successful!\n");

                    double ratio = get_huffman_ratio(input_file, output_file);
                    printf("Compression ratio: %.2f\n", ratio);
                } else {
                    printf("Huffman compression failed!\n");
                }
                break;
            }

            case 4: {
                // Show ratios
                printf("Enter original filename: ");
                scanf(" %s", input_file);
                printf("Enter compressed filename: ");
                scanf(" %s", output_file);

                double rle_ratio = get_rle_ratio(input_file, output_file);
                double huffman_ratio = get_huffman_ratio(input_file, output_file);

                printf("\nCompression Analysis:\n");
                printf("RLE Ratio: %.2f\n", rle_ratio);
                printf("Huffman Ratio: %.2f\n", huffman_ratio);

                if (rle_ratio < huffman_ratio) {
                    printf("RLE performed better!\n");
                } else {
                    printf("Huffman performed better!\n");
                }
                break;
            }

            case 5:
                printf("Thank you for using File Compression Tool!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Compression Algorithms**
- ✅ Run-Length Encoding (RLE)
- ✅ Basic Huffman coding
- ✅ Compression ratio calculation
- ✅ File compression/decompression
- ✅ Performance comparison

### **Technical Features**
- ✅ Binary file handling
- ✅ Bit manipulation
- ✅ Memory-efficient algorithms
- ✅ Error handling
- ✅ User-friendly interface

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "File Compression Tool - RLE and Huffman Coding in C"
- **Hinglish:** "File Compression Tool - RLE and Huffman Coding in C"

### **Slide 2: What We Built**
- ✅ Complete file compression utility
- ✅ Run-Length Encoding implementation
- ✅ Basic Huffman coding
- ✅ Compression ratio analysis
- ✅ File compression and decompression

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HuffmanNode {
    char data;
    unsigned freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// Core functions
int compress_rle(const char *input_file, const char *output_file);
int decompress_rle(const char *input_file, const char *output_file);
int compress_huffman(const char *input_file, const char *output_file);
HuffmanNode* build_huffman_tree(int *freq);
double get_compression_ratio(const char *original, const char *compressed);
```

### **Slide 4: Compression Algorithms**
```c
// Run-Length Encoding
int compress_rle(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "wb");

    char current_char, prev_char = fgetc(input);
    int count = 1;

    while ((current_char = fgetc(input)) != EOF) {
        if (current_char == prev_char && count < 255) {
            count++;
        } else {
            fputc(count, output);
            fputc(prev_char, output);
            prev_char = current_char;
            count = 1;
        }
    }

    // Write final run
    fputc(count, output);
    fputc(prev_char, output);
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ Data compression algorithms
- ✅ File I/O operations
- ✅ Bit manipulation
- ✅ Memory management
- ✅ Algorithm implementation

### **Compression Concepts:**
- ✅ Run-length encoding
- ✅ Huffman coding
- ✅ Compression ratios
- ✅ Data encoding/decoding
- ✅ Performance analysis

---

## 📞 **Contact & Support**

**Project Developer:** Compression Algorithms Student
**Email:** compression@studentproject.com
**GitHub:** https://github.com/c-compression/file-compression

---

**📦 This file compression tool demonstrates data compression algorithms and file processing techniques in C, perfect for understanding data compression and storage optimization.**
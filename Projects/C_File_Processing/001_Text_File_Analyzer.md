# 📊 Text File Analyzer
## Comprehensive text analysis with statistics and insights

---

## 📋 Project Overview

This project implements a comprehensive text file analyzer in C that processes text files to extract various statistics, perform word analysis, generate reports, and provide insights about the content. It demonstrates file I/O, string processing, and data analysis techniques.

## 🎯 Learning Objectives

- Understand file processing techniques
- Learn text analysis algorithms
- Practice string manipulation
- Implement data structures for analysis
- Learn report generation

## 🛠️ Technical Requirements

- **Language**: C (Standard C99 or later)
- **Libraries**: Standard C libraries
- **Platform**: Cross-platform
- **Compiler**: GCC, MinGW, or MSVC

## 📁 Project Structure

```
text_analyzer/
├── src/
│   ├── main.c           # Main program with menu
│   ├── analyzer.c       # Core analysis functions
│   ├── file_io.c        # File input/output
│   ├── statistics.c     # Statistical calculations
│   └── report.c         # Report generation
├── include/
│   ├── analyzer.h
│   ├── file_io.h
│   ├── statistics.h
│   └── report.h
├── sample_texts/
│   ├── sample1.txt
│   └── sample2.txt
├── Makefile
└── README.md
```

## 🚀 Implementation Steps

### **Step 1: Core Data Structures**

```c
// analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 10000
#define MAX_SENTENCES 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} WordFrequency;

typedef struct {
    char** words;
    int word_count;
    int unique_words;
    WordFrequency* word_freq;
    int sentence_count;
    int paragraph_count;
    int char_count;
    int char_count_no_spaces;
    int line_count;
    double avg_word_length;
    double avg_sentence_length;
} TextStats;

// Function prototypes
TextStats* analyze_text(const char* text);
void free_text_stats(TextStats* stats);
void print_text_stats(const TextStats* stats);
char** split_into_words(const char* text, int* word_count);
int count_sentences(const char* text);
int count_paragraphs(const char* text);

#endif
```

```c
// analyzer.c
#include "analyzer.h"

TextStats* analyze_text(const char* text) {
    if (!text) return NULL;

    TextStats* stats = (TextStats*)malloc(sizeof(TextStats));
    if (!stats) return NULL;

    // Initialize stats
    stats->word_count = 0;
    stats->unique_words = 0;
    stats->sentence_count = 0;
    stats->paragraph_count = 0;
    stats->char_count = strlen(text);
    stats->char_count_no_spaces = 0;
    stats->line_count = 0;
    stats->avg_word_length = 0.0;
    stats->avg_sentence_length = 0.0;
    stats->words = NULL;
    stats->word_freq = NULL;

    // Count characters without spaces
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (!isspace(text[i])) {
            stats->char_count_no_spaces++;
        }
        if (text[i] == '\n') {
            stats->line_count++;
        }
    }

    // Split text into words
    stats->words = split_into_words(text, &stats->word_count);

    if (stats->word_count > 0) {
        // Calculate average word length
        int total_word_length = 0;
        for (int i = 0; i < stats->word_count; i++) {
            total_word_length += strlen(stats->words[i]);
        }
        stats->avg_word_length = (double)total_word_length / stats->word_count;

        // Count unique words and frequencies
        stats->word_freq = (WordFrequency*)malloc(stats->word_count * sizeof(WordFrequency));
        if (stats->word_freq) {
            // Simple frequency counting (can be optimized with hash table)
            stats->unique_words = 0;
            for (int i = 0; i < stats->word_count; i++) {
                bool found = false;
                for (int j = 0; j < stats->unique_words; j++) {
                    if (strcasecmp(stats->words[i], stats->word_freq[j].word) == 0) {
                        stats->word_freq[j].frequency++;
                        found = true;
                        break;
                    }
                }
                if (!found && stats->unique_words < MAX_WORDS) {
                    strcpy(stats->word_freq[stats->unique_words].word, stats->words[i]);
                    stats->word_freq[stats->unique_words].frequency = 1;
                    stats->unique_words++;
                }
            }
        }
    }

    // Count sentences and paragraphs
    stats->sentence_count = count_sentences(text);
    stats->paragraph_count = count_paragraphs(text);

    // Calculate average sentence length
    if (stats->sentence_count > 0) {
        stats->avg_sentence_length = (double)stats->word_count / stats->sentence_count;
    }

    return stats;
}

void free_text_stats(TextStats* stats) {
    if (stats) {
        if (stats->words) {
            for (int i = 0; i < stats->word_count; i++) {
                free(stats->words[i]);
            }
            free(stats->words);
        }
        if (stats->word_freq) {
            free(stats->word_freq);
        }
        free(stats);
    }
}

char** split_into_words(const char* text, int* word_count) {
    char** words = NULL;
    *word_count = 0;
    char* text_copy = strdup(text);
    if (!text_copy) return NULL;

    char* token = strtok(text_copy, " \t\n\r.,;:!?\"'()-");
    while (token && *word_count < MAX_WORDS) {
        // Skip empty tokens
        if (strlen(token) > 0) {
            words = (char**)realloc(words, (*word_count + 1) * sizeof(char*));
            if (words) {
                words[*word_count] = strdup(token);
                if (words[*word_count]) {
                    (*word_count)++;
                }
            }
        }
        token = strtok(NULL, " \t\n\r.,;:!?\"'()-");
    }

    free(text_copy);
    return words;
}

int count_sentences(const char* text) {
    int count = 0;
    bool in_sentence = false;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (!isspace(text[i]) && !ispunct(text[i])) {
            in_sentence = true;
        } else if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && in_sentence) {
            count++;
            in_sentence = false;
        }
    }

    return count > 0 ? count : 1; // At least one sentence
}

int count_paragraphs(const char* text) {
    int count = 1; // At least one paragraph

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n' && (i == 0 || text[i-1] == '\n')) {
            count++;
        }
    }

    return count;
}
```

### **Step 2: File I/O Operations**

```c
// file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include "analyzer.h"

char* read_text_file(const char* filename);
int write_analysis_report(const char* filename, const TextStats* stats);
void print_text_stats(const TextStats* stats);

#endif
```

```c
// file_io.c
#include "file_io.h"

char* read_text_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        fclose(file);
        return NULL;
    }

    // Allocate memory for text
    char* text = (char*)malloc(file_size + 1);
    if (!text) {
        fclose(file);
        return NULL;
    }

    // Read file content
    size_t bytes_read = fread(text, 1, file_size, file);
    text[bytes_read] = '\0';

    fclose(file);
    return text;
}

int write_analysis_report(const char* filename, const TextStats* stats) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error creating report file");
        return -1;
    }

    fprintf(file, "Text Analysis Report\n");
    fprintf(file, "===================\n\n");

    fprintf(file, "Basic Statistics:\n");
    fprintf(file, "----------------\n");
    fprintf(file, "Total characters: %d\n", stats->char_count);
    fprintf(file, "Characters (no spaces): %d\n", stats->char_count_no_spaces);
    fprintf(file, "Total words: %d\n", stats->word_count);
    fprintf(file, "Unique words: %d\n", stats->unique_words);
    fprintf(file, "Sentences: %d\n", stats->sentence_count);
    fprintf(file, "Paragraphs: %d\n", stats->paragraph_count);
    fprintf(file, "Lines: %d\n", stats->line_count);
    fprintf(file, "Average word length: %.2f\n", stats->avg_word_length);
    fprintf(file, "Average sentence length: %.2f words\n", stats->avg_sentence_length);

    fprintf(file, "\nWord Frequency Analysis:\n");
    fprintf(file, "-----------------------\n");
    for (int i = 0; i < stats->unique_words && i < 20; i++) {
        fprintf(file, "%s: %d\n", stats->word_freq[i].word, stats->word_freq[i].frequency);
    }

    fclose(file);
    return 0;
}

void print_text_stats(const TextStats* stats) {
    printf("\n=== Text Analysis Results ===\n");
    printf("Total characters: %d\n", stats->char_count);
    printf("Characters (excluding spaces): %d\n", stats->char_count_no_spaces);
    printf("Total words: %d\n", stats->word_count);
    printf("Unique words: %d\n", stats->unique_words);
    printf("Sentences: %d\n", stats->sentence_count);
    printf("Paragraphs: %d\n", stats->paragraph_count);
    printf("Lines: %d\n", stats->line_count);
    printf("Average word length: %.2f characters\n", stats->avg_word_length);
    printf("Average sentence length: %.2f words\n", stats->avg_sentence_length);

    printf("\nTop 10 Most Frequent Words:\n");
    printf("----------------------------\n");
    for (int i = 0; i < stats->unique_words && i < 10; i++) {
        printf("%d. %s (%d times)\n", i + 1,
               stats->word_freq[i].word, stats->word_freq[i].frequency);
    }
}
```

### **Step 3: Main Program**

```c
// main.c
#include "analyzer.h"
#include "file_io.h"

void display_menu(void) {
    printf("\n=== Text File Analyzer ===\n");
    printf("1. Analyze text file\n");
    printf("2. Analyze text from input\n");
    printf("3. Generate analysis report\n");
    printf("4. Show word frequency\n");
    printf("5. Find specific word\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    TextStats* current_stats = NULL;
    char filename[256];
    int choice;

    printf("Text File Analyzer\n");
    printf("==================\n");

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: // Analyze file
                printf("Enter filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';

                char* text = read_text_file(filename);
                if (text) {
                    if (current_stats) free_text_stats(current_stats);
                    current_stats = analyze_text(text);
                    free(text);

                    if (current_stats) {
                        printf("File analyzed successfully!\n");
                        print_text_stats(current_stats);
                    } else {
                        printf("Analysis failed!\n");
                    }
                } else {
                    printf("Failed to read file!\n");
                }
                break;

            case 2: // Analyze input text
                printf("Enter text to analyze (press Ctrl+D to end):\n");
                char* input_text = NULL;
                size_t input_size = 0;
                ssize_t input_len;

                FILE* input_stream = fopen("/dev/stdin", "r");
                if ((input_len = getline(&input_text, &input_size, input_stream)) != -1) {
                    if (current_stats) free_text_stats(current_stats);
                    current_stats = analyze_text(input_text);
                    free(input_text);

                    if (current_stats) {
                        printf("Text analyzed successfully!\n");
                        print_text_stats(current_stats);
                    }
                }
                break;

            case 3: // Generate report
                if (!current_stats) {
                    printf("No analysis data available. Analyze a file first.\n");
                    break;
                }

                printf("Enter report filename: ");
                scanf("%s", filename);

                if (write_analysis_report(filename, current_stats) == 0) {
                    printf("Report generated successfully: %s\n", filename);
                } else {
                    printf("Failed to generate report!\n");
                }
                break;

            case 4: // Show word frequency
                if (!current_stats) {
                    printf("No analysis data available. Analyze a file first.\n");
                    break;
                }

                printf("\nWord Frequency Analysis:\n");
                printf("=======================\n");
                for (int i = 0; i < current_stats->unique_words; i++) {
                    printf("%s: %d\n",
                           current_stats->word_freq[i].word,
                           current_stats->word_freq[i].frequency);
                }
                break;

            case 5: // Find specific word
                if (!current_stats) {
                    printf("No analysis data available. Analyze a file first.\n");
                    break;
                }

                printf("Enter word to search: ");
                char search_word[MAX_WORD_LENGTH];
                scanf("%s", search_word);

                bool found = false;
                for (int i = 0; i < current_stats->unique_words; i++) {
                    if (strcasecmp(search_word, current_stats->word_freq[i].word) == 0) {
                        printf("Word '%s' found %d times\n",
                               search_word, current_stats->word_freq[i].frequency);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    printf("Word '%s' not found in the text\n", search_word);
                }
                break;

            case 0:
                printf("Exiting...\n");
                if (current_stats) free_text_stats(current_stats);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
```

## 🎯 Key Features

### **✅ Core Analysis Features**
- [x] Character and word counting
- [x] Sentence and paragraph detection
- [x] Word frequency analysis
- [x] Average calculations
- [x] File I/O operations

### **✅ Advanced Features**
- [x] Report generation
- [x] Word search functionality
- [x] Memory management
- [x] Error handling
- [x] Interactive menu system

### **🚀 Extensions**
- [ ] Sentiment analysis
- [ ] Readability metrics
- [ ] Language detection
- [ ] Keyword extraction
- [ ] Text summarization
- [ ] Plagiarism detection

## 🧪 Testing and Usage

### **Sample Usage**
```bash
# Compile the program
gcc -o text_analyzer main.c analyzer.c file_io.c

# Analyze a file
./text_analyzer
# Choose option 1
# Enter filename: sample.txt

# Generate report
# Choose option 3
# Enter report filename: analysis_report.txt
```

### **Sample Input File**
```
This is a sample text file.
It contains multiple sentences and paragraphs.

The quick brown fox jumps over the lazy dog.
This sentence contains all letters of the alphabet.

Programming in C is fun and educational.
Learning data structures and algorithms is important.
```

## 📊 Technical Learning Outcomes

### **File Processing Skills**
- Text file reading and writing
- Memory management for large files
- Error handling for file operations
- Buffer management
- File format handling

### **Text Analysis Techniques**
- String tokenization
- Pattern recognition
- Statistical calculations
- Data structure usage
- Algorithm implementation

## 🚀 Advanced Extensions

### **Readability Analysis**
```c
double calculate_flesch_reading_ease(const TextStats* stats) {
    // Implement Flesch Reading Ease formula
    double words_per_sentence = (double)stats->word_count / stats->sentence_count;
    double syllables_per_word = calculate_average_syllables(stats);

    return 206.835 - 1.015 * words_per_sentence - 84.6 * syllables_per_word;
}
```

### **Keyword Extraction**
```c
char** extract_keywords(const TextStats* stats, int num_keywords) {
    // Extract most frequent words as keywords
    // Remove stop words and apply TF-IDF scoring
}
```

## 📖 References

- **"Natural Language Processing with Python"** by Bird et al.
- **"Speech and Language Processing"** by Jurafsky & Martin
- **Text Analysis techniques** - Stanford NLP Group
- **File I/O in C** - GNU C Library documentation

## 🎯 Real-World Applications

- **Content Analysis**: Blog posts, articles, documents
- **SEO Optimization**: Keyword analysis for websites
- **Educational Tools**: Reading level assessment
- **Quality Assurance**: Document validation
- **Research**: Text mining and analysis

---

**📊 This project demonstrates comprehensive text analysis and file processing in C!**
# 📝 **Project 15: Advanced Text File Analyzer in C**
## 🎯 **Comprehensive Text Analysis with Statistical Reports**

---

## 📋 **Project Overview**

**English:** An advanced text file analyzer in C that performs comprehensive text analysis including word frequency, character statistics, readability metrics, and generates detailed analysis reports.

**Hinglish:** Ek advanced text file analyzer jo C mein bana hai, jisme comprehensive text analysis karta hai including word frequency, character statistics, readability metrics, aur detailed analysis reports generate karta hai.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- File I/O operations
- String processing algorithms
- Data structure implementation
- Statistical analysis
- Report generation

✅ **Text Processing:**
- Word frequency analysis
- Character classification
- Readability calculations
- Pattern recognition
- Text statistics

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Text processing core | Handles file operations and analysis |
| **File System** | Text file reading | Large file processing capabilities |
| **String Library** | Text manipulation | Word and character processing |
| **Math Library** | Statistical calculations | Readability and frequency analysis |

---

## 📁 **Project Structure**

```
TextAnalyzer/
├── include/
│   ├── analyzer.h
│   ├── statistics.h
│   ├── wordfreq.h
│   └── report.h
├── src/
│   ├── analyzer.c
│   ├── statistics.c
│   ├── wordfreq.c
│   ├── report.c
│   └── main.c
├── data/
│   └── sample.txt
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Text Analysis Engine**

```c
// analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 10000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} WordFreq;

typedef struct {
    int total_characters;
    int total_words;
    int total_sentences;
    int total_paragraphs;
    int alphabetic_chars;
    int numeric_chars;
    int special_chars;
    int whitespace_chars;
    int unique_words;
    double avg_word_length;
    double avg_sentence_length;
} TextStats;

// Analysis functions
TextStats analyze_text(const char *filename);
int read_file_content(const char *filename, char **content, long *size);
void process_text(const char *text, TextStats *stats, WordFreq *word_freq, int *word_count);

#endif
```

```c
// analyzer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "analyzer.h"

// Analyze text file
TextStats analyze_text(const char *filename) {
    TextStats stats = {0};
    WordFreq word_freq[MAX_WORDS];
    int word_count = 0;

    char *content = NULL;
    long file_size = 0;

    if (!read_file_content(filename, &content, &file_size)) {
        return stats;
    }

    process_text(content, &stats, word_freq, &word_count);

    // Calculate averages
    if (stats.total_words > 0) {
        stats.avg_word_length = (double)stats.alphabetic_chars / stats.total_words;
    }

    if (stats.total_sentences > 0) {
        stats.avg_sentence_length = (double)stats.total_words / stats.total_sentences;
    }

    // Count unique words
    stats.unique_words = word_count;

    free(content);
    return stats;
}

// Read file content
int read_file_content(const char *filename, char **content, long *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory
    *content = (char*)malloc(*size + 1);
    if (!*content) {
        fclose(file);
        return 0;
    }

    // Read file
    size_t bytes_read = fread(*content, 1, *size, file);
    (*content)[bytes_read] = '\0';

    fclose(file);
    return 1;
}

// Process text content
void process_text(const char *text, TextStats *stats, WordFreq *word_freq, int *word_count) {
    char word[MAX_WORD_LENGTH];
    int word_index = 0;
    int in_word = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        stats->total_characters++;

        // Character classification
        if (isalpha(c)) {
            stats->alphabetic_chars++;
        } else if (isdigit(c)) {
            stats->numeric_chars++;
        } else if (isspace(c)) {
            stats->whitespace_chars++;
            if (c == '\n') {
                stats->total_paragraphs++;
            }
        } else {
            stats->special_chars++;
        }

        // Sentence detection
        if (c == '.' || c == '!' || c == '?') {
            stats->total_sentences++;
        }

        // Word processing
        if (isalnum(c)) {
            if (!in_word) {
                in_word = 1;
                word_index = 0;
                stats->total_words++;
            }
            if (word_index < MAX_WORD_LENGTH - 1) {
                word[word_index++] = tolower(c);
            }
        } else {
            if (in_word) {
                word[word_index] = '\0';
                in_word = 0;

                // Add to word frequency
                if (word_index > 0) {
                    add_word_frequency(word_freq, word, word_count);
                }
            }
        }
    }

    // Handle last word
    if (in_word) {
        word[word_index] = '\0';
        add_word_frequency(word_freq, word, word_count);
    }
}
```

### **2. Word Frequency Analysis**

```c
// wordfreq.h
#ifndef WORDFREQ_H
#define WORDFREQ_H

#include "analyzer.h"

// Word frequency functions
void add_word_frequency(WordFreq *word_freq, const char *word, int *word_count);
void sort_word_frequency(WordFreq *word_freq, int word_count);
void print_top_words(WordFreq *word_freq, int word_count, int top_n);

#endif
```

```c
// wordfreq.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordfreq.h"

// Add word to frequency list
void add_word_frequency(WordFreq *word_freq, const char *word, int *word_count) {
    // Check if word already exists
    for (int i = 0; i < *word_count; i++) {
        if (strcmp(word_freq[i].word, word) == 0) {
            word_freq[i].frequency++;
            return;
        }
    }

    // Add new word
    if (*word_count < MAX_WORDS) {
        strcpy(word_freq[*word_count].word, word);
        word_freq[*word_count].frequency = 1;
        (*word_count)++;
    }
}

// Sort words by frequency
void sort_word_frequency(WordFreq *word_freq, int word_count) {
    for (int i = 0; i < word_count - 1; i++) {
        for (int j = 0; j < word_count - i - 1; j++) {
            if (word_freq[j].frequency < word_freq[j + 1].frequency) {
                WordFreq temp = word_freq[j];
                word_freq[j] = word_freq[j + 1];
                word_freq[j + 1] = temp;
            }
        }
    }
}

// Print top N words
void print_top_words(WordFreq *word_freq, int word_count, int top_n) {
    printf("\n=== Top %d Words ===\n", top_n);
    for (int i = 0; i < word_count && i < top_n; i++) {
        printf("%d. %s (%d times)\n", i + 1, word_freq[i].word, word_freq[i].frequency);
    }
}
```

### **3. Readability Analysis**

```c
// statistics.h
#ifndef STATISTICS_H
#define STATISTICS_H

#include "analyzer.h"

// Readability metrics
double calculate_flesch_reading_ease(TextStats stats);
double calculate_flesch_kincaid_grade_level(TextStats stats);
double calculate_automated_readability_index(TextStats stats);
void print_readability_metrics(TextStats stats);

#endif
```

```c
// statistics.c
#include <stdio.h>
#include <math.h>
#include "statistics.h"

// Flesch Reading Ease
double calculate_flesch_reading_ease(TextStats stats) {
    if (stats.total_sentences == 0 || stats.total_words == 0) return 0;

    double asl = (double)stats.total_words / stats.total_sentences; // Average sentence length
    double asw = (double)stats.alphabetic_chars / stats.total_words; // Average syllables per word (simplified)

    return 206.835 - (1.015 * asl) - (84.6 * asw);
}

// Flesch-Kincaid Grade Level
double calculate_flesch_kincaid_grade_level(TextStats stats) {
    if (stats.total_sentences == 0 || stats.total_words == 0) return 0;

    double asl = (double)stats.total_words / stats.total_sentences;
    double asw = (double)stats.alphabetic_chars / stats.total_words;

    return (0.39 * asl) + (11.8 * asw) - 15.59;
}

// Automated Readability Index
double calculate_automated_readability_index(TextStats stats) {
    if (stats.total_sentences == 0 || stats.total_words == 0) return 0;

    double chars_per_word = (double)stats.total_characters / stats.total_words;
    double words_per_sentence = (double)stats.total_words / stats.total_sentences;

    return (4.71 * chars_per_word) + (0.5 * words_per_sentence) - 21.43;
}

// Print readability metrics
void print_readability_metrics(TextStats stats) {
    printf("\n=== Readability Analysis ===\n");

    double flesch = calculate_flesch_reading_ease(stats);
    printf("Flesch Reading Ease: %.1f ", flesch);
    if (flesch >= 90) printf("(Very Easy)\n");
    else if (flesch >= 80) printf("(Easy)\n");
    else if (flesch >= 70) printf("(Fairly Easy)\n");
    else if (flesch >= 60) printf("(Standard)\n");
    else if (flesch >= 50) printf("(Fairly Difficult)\n");
    else if (flesch >= 30) printf("(Difficult)\n");
    else printf("(Very Difficult)\n");

    double grade_level = calculate_flesch_kincaid_grade_level(stats);
    printf("Flesch-Kincaid Grade Level: %.1f\n", grade_level);

    double ari = calculate_automated_readability_index(stats);
    printf("Automated Readability Index: %.1f\n", ari);
}
```

### **4. Report Generation**

```c
// report.h
#ifndef REPORT_H
#define REPORT_H

#include "analyzer.h"
#include "wordfreq.h"

// Report functions
void generate_analysis_report(const char *filename, TextStats stats, WordFreq *word_freq, int word_count);
void print_summary_stats(TextStats stats);

#endif
```

```c
// report.c
#include <stdio.h>
#include "report.h"

// Generate comprehensive analysis report
void generate_analysis_report(const char *filename, TextStats stats, WordFreq *word_freq, int word_count) {
    printf("\n========================================\n");
    printf("    TEXT ANALYSIS REPORT\n");
    printf("========================================\n");
    printf("File: %s\n", filename);
    printf("----------------------------------------\n");

    print_summary_stats(stats);
    print_top_words(word_freq, word_count, 10);
    print_readability_metrics(stats);

    printf("\n========================================\n");
}

// Print summary statistics
void print_summary_stats(TextStats stats) {
    printf("\n=== Summary Statistics ===\n");
    printf("Total Characters: %d\n", stats.total_characters);
    printf("Total Words: %d\n", stats.total_words);
    printf("Total Sentences: %d\n", stats.total_sentences);
    printf("Total Paragraphs: %d\n", stats.total_paragraphs);
    printf("Unique Words: %d\n", stats.unique_words);
    printf("Average Word Length: %.1f characters\n", stats.avg_word_length);
    printf("Average Sentence Length: %.1f words\n", stats.avg_sentence_length);

    printf("\n=== Character Breakdown ===\n");
    printf("Alphabetic: %d (%.1f%%)\n", stats.alphabetic_chars,
           (double)stats.alphabetic_chars / stats.total_characters * 100);
    printf("Numeric: %d (%.1f%%)\n", stats.numeric_chars,
           (double)stats.numeric_chars / stats.total_characters * 100);
    printf("Special: %d (%.1f%%)\n", stats.special_chars,
           (double)stats.special_chars / stats.total_characters * 100);
    printf("Whitespace: %d (%.1f%%)\n", stats.whitespace_chars,
           (double)stats.whitespace_chars / stats.total_characters * 100);
}
```

### **5. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "analyzer.h"
#include "wordfreq.h"
#include "report.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    printf("Text File Analyzer\n");
    printf("==================\n");
    printf("Analyzing file: %s\n", filename);

    // Analyze text
    TextStats stats = analyze_text(filename);

    if (stats.total_characters == 0) {
        printf("Error: Could not analyze file or file is empty!\n");
        return 1;
    }

    // Generate word frequency data
    WordFreq word_freq[MAX_WORDS];
    int word_count = 0;

    char *content = NULL;
    long file_size = 0;

    if (read_file_content(filename, &content, &file_size)) {
        process_text(content, &stats, word_freq, &word_count);
        sort_word_frequency(word_freq, word_count);
        free(content);
    }

    // Generate report
    generate_analysis_report(filename, stats, word_freq, word_count);

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Text Analysis**
- ✅ Character frequency analysis
- ✅ Word frequency counting
- ✅ Sentence and paragraph detection
- ✅ Character classification
- ✅ Statistical calculations

### **Advanced Features**
- ✅ Readability metrics (Flesch, ARI)
- ✅ Word frequency ranking
- ✅ Detailed reporting
- ✅ Large file processing
- ✅ Comprehensive statistics

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Advanced Text File Analyzer - Comprehensive Text Analysis"
- **Hinglish:** "Advanced Text File Analyzer - Comprehensive Text Analysis"

### **Slide 2: What We Built**
- ✅ Complete text analysis system
- ✅ Word frequency analysis
- ✅ Readability assessment
- ✅ Statistical reporting
- ✅ Large file processing capabilities

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int total_characters;
    int total_words;
    int total_sentences;
    int alphabetic_chars;
    int unique_words;
    double avg_word_length;
} TextStats;

// Core functions
TextStats analyze_text(const char *filename);
int read_file_content(const char *filename, char **content, long *size);
void process_text(const char *text, TextStats *stats);
double calculate_flesch_reading_ease(TextStats stats);
```

### **Slide 4: Analysis Algorithms**
```c
// Text processing algorithm
void process_text(const char *text, TextStats *stats) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        stats->total_characters++;

        if (isalpha(c)) stats->alphabetic_chars++;
        else if (isdigit(c)) stats->numeric_chars++;
        else if (isspace(c)) stats->whitespace_chars++;
        else stats->special_chars++;

        // Word and sentence detection
        if (c == '.' || c == '!' || c == '?') stats->total_sentences++;
    }
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ File I/O operations
- ✅ String processing
- ✅ Data structure implementation
- ✅ Statistical analysis
- ✅ Algorithm development

### **Text Processing:**
- ✅ Natural language processing basics
- ✅ Readability analysis
- ✅ Frequency analysis
- ✅ Text statistics
- ✅ Report generation

---

## 📞 **Contact & Support**

**Project Developer:** Text Processing Student
**Email:** textanalysis@studentproject.com
**GitHub:** https://github.com/c-text/text-analyzer

---

**📝 This text analyzer demonstrates advanced file processing and natural language analysis concepts in C, perfect for understanding text mining and computational linguistics fundamentals.**
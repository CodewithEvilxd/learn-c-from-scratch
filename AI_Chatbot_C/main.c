/*
 * AI Chatbot in C - Main Entry Point
 * A sophisticated conversational AI implemented in pure C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "headers/chatbot.h"
#include "headers/nlp.h"
#include "headers/memory.h"
#include "headers/knowledge.h"
#include "headers/personality.h"
#include "headers/utils.h"

#define MAX_INPUT 1024
#define MAX_RESPONSE 2048

// Global chatbot instance
Chatbot* chatbot = NULL;

// Function prototypes
void print_banner(void);
void print_help(void);
void interactive_mode(void);
void process_command_line_args(int argc, char* argv[]);
void cleanup(void);

int main(int argc, char* argv[]) {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Process command line arguments
    process_command_line_args(argc, argv);

    // Initialize chatbot
    printf("🤖 Initializing AI Chatbot...\n");

    chatbot = chatbot_create();
    if (!chatbot) {
        fprintf(stderr, "❌ Failed to initialize chatbot\n");
        return EXIT_FAILURE;
    }

    // Load knowledge base
    if (!knowledge_load(chatbot->knowledge_base, "data/knowledge_base.txt")) {
        printf("⚠️  Warning: Could not load knowledge base\n");
    }

    // Load conversation memory
    if (!memory_load(chatbot->memory, "data/memory.db")) {
        printf("ℹ️  Starting with empty conversation memory\n");
    }

    printf("✅ AI Chatbot initialized successfully!\n\n");

    // Print banner
    print_banner();

    // Check for command line mode
    if (argc > 1) {
        // Command line mode - process single input
        char input[MAX_INPUT];
        strcpy(input, argv[1]);

        char response[MAX_RESPONSE];
        chatbot_process_input(chatbot, input, response, sizeof(response));

        printf("🤖 %s\n", response);
    } else {
        // Interactive mode
        interactive_mode();
    }

    // Cleanup
    cleanup();

    return EXIT_SUCCESS;
}

void print_banner(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    🤖 AI CHATBOT in C                       ║\n");
    printf("║                                                              ║\n");
    printf("║  A sophisticated conversational AI implemented in pure C    ║\n");
    printf("║                                                              ║\n");
    printf("║  Features:                                                   ║\n");
    printf("║  • Natural Language Processing                              ║\n");
    printf("║  • Conversation Memory                                      ║\n");
    printf("║  • Multiple Personalities                                   ║\n");
    printf("║  • Mathematical Calculations                                ║\n");
    printf("║  • Games & Entertainment                                    ║\n");
    printf("║  • Learning Capabilities                                    ║\n");
    printf("║                                                              ║\n");
    printf("║  Type 'help' for commands or 'quit' to exit                 ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

void print_help(void) {
    printf("\n============================================================================================\n");
    printf("📚 AI CHATBOT HELP - AVAILABLE COMMANDS\n");
    printf("============================================================================================\n\n");

    printf("🤖 GENERAL COMMANDS:\n");
    printf("  help              - Show this help message\n");
    printf("  quit/exit         - Exit the chatbot\n");
    printf("  status            - Show system status\n");
    printf("  clear             - Clear the screen\n");
    printf("  history           - Show conversation history\n\n");

    printf("🎭 PERSONALITY COMMANDS:\n");
    printf("  personality friendly     - Switch to friendly mode\n");
    printf("  personality professional - Switch to professional mode\n");
    printf("  personality witty        - Switch to witty mode\n");
    printf("  personality creative     - Switch to creative mode\n\n");

    printf("🧠 MEMORY COMMANDS:\n");
    printf("  remember [key] [value]   - Remember something\n");
    printf("  recall [key]            - Recall remembered information\n");
    printf("  forget [key]            - Forget something\n");
    printf("  memory                  - Show all memories\n\n");

    printf("🧮 CALCULATION COMMANDS:\n");
    printf("  calculate [expression]   - Calculate mathematical expression\n");
    printf("  Examples: calculate 2+3*4, calculate sin(30), calculate sqrt(16)\n\n");

    printf("🎮 GAME COMMANDS:\n");
    printf("  play game               - Start a game\n");
    printf("  guess number            - Play number guessing game\n");
    printf("  rock paper scissors     - Play rock-paper-scissors\n");
    printf("  math quiz               - Take a math quiz\n\n");

    printf("📚 KNOWLEDGE COMMANDS:\n");
    printf("  learn [question] [answer] - Teach the chatbot something new\n");
    printf("  what is [topic]         - Ask about a topic\n");
    printf("  explain [concept]       - Get detailed explanation\n\n");

    printf("💡 CONVERSATION TIPS:\n");
    printf("  • Use natural language: 'What's the weather like?'\n");
    printf("  • Be specific: 'Calculate 15 * 23 + 45'\n");
    printf("  • Ask questions: 'How do I create a function?'\n");
    printf("  • Give commands: 'Set a reminder for tomorrow'\n");
    printf("  • Have fun: 'Tell me a joke' or 'Play a game'\n\n");

    printf("============================================================================================\n\n");
}

void interactive_mode(void) {
    char input[MAX_INPUT];
    char response[MAX_RESPONSE];

    printf("🤖 Hello! I'm your AI assistant. How can I help you today?\n");
    printf("💡 Type 'help' for available commands or 'quit' to exit.\n\n");

    while (1) {
        printf("👤 You: ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Convert to lowercase for easier processing
        for (char* p = input; *p; ++p) {
            *p = tolower(*p);
        }

        // Check for exit commands
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0 ||
            strcmp(input, "bye") == 0 || strcmp(input, "goodbye") == 0) {
            printf("🤖 Goodbye! It was great chatting with you!\n");
            break;
        }

        // Check for help command
        if (strcmp(input, "help") == 0) {
            print_help();
            continue;
        }

        // Check for clear command
        if (strcmp(input, "clear") == 0) {
            system("cls || clear");  // Works on both Windows and Unix
            print_banner();
            continue;
        }

        // Process input through chatbot
        chatbot_process_input(chatbot, input, response, sizeof(response));

        printf("🤖 %s\n\n", response);
    }
}

void process_command_line_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("AI Chatbot in C\n\n");
            printf("Usage:\n");
            printf("  %s                    - Interactive mode\n", argv[0]);
            printf("  %s \"message\"         - Process single message\n", argv[0]);
            printf("  %s --help             - Show this help\n", argv[0]);
            printf("  %s --version          - Show version\n", argv[0]);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            printf("AI Chatbot in C v1.0.0\n");
            printf("Built with pure C programming language\n");
            exit(EXIT_SUCCESS);
        }
    }
}

void cleanup(void) {
    if (chatbot) {
        // Save conversation memory
        if (!memory_save(chatbot->memory, "data/memory.db")) {
            printf("⚠️  Warning: Could not save conversation memory\n");
        }

        // Save knowledge base
        if (!knowledge_save(chatbot->knowledge_base, "data/knowledge_base.txt")) {
            printf("⚠️  Warning: Could not save knowledge base\n");
        }

        // Destroy chatbot
        chatbot_destroy(chatbot);
        chatbot = NULL;
    }

    printf("🧹 Cleanup completed. Thank you for using AI Chatbot!\n");
}
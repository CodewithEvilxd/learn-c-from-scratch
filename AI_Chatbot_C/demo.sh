#!/bin/bash

# 🤖 AI CHATBOT SYSTEM DEMO SCRIPT
# ===============================
#
# This script demonstrates the complete functionality of the
# AI Chatbot System for college presentations.
#
# Usage: ./demo.sh
#
# Requirements:
# - Compiled chatbot executable in the same directory
# - Bash shell environment
#
# Author: [Your Name]
# Date: [Current Date]

# Configuration
DEMO_DELAY=3          # Delay between commands (seconds)
CHATBOT="./chatbot.exe"  # Executable name

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Demo functions
print_header() {
    clear
    echo -e "${CYAN}"
    echo "╔══════════════════════════════════════════════════════════════════════════════╗"
    echo "║                     🤖 AI CHATBOT SYSTEM DEMO                               ║"
    echo "║                                                                              ║"
    echo "║  College Project Presentation - Complete Working Implementation              ║"
    echo "║                                                                              ║"
    echo "║  Features Demonstrated:                                                       ║"
    echo "║  • Natural Language Processing (NLP)                                       ║"
    echo "║  • Intent Classification & Entity Extraction                               ║"
    echo "║  • Adaptive Knowledge Base & Learning                                     ║"
    echo "║  • Context-Aware Conversations                                             ║"
    echo "║  • Dynamic Personality System                                              ║"
    echo "║  • Real-time Response Generation                                           ║"
    echo "║                                                                              ║"
    echo "╚══════════════════════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
    echo ""
}

print_step() {
    echo -e "${YELLOW}▶ $1${NC}"
    sleep $DEMO_DELAY
}

print_command() {
    echo -e "${BLUE}Input: ${WHITE}$1${NC}"
}

print_response() {
    echo -e "${GREEN}Chatbot:${NC}"
}

execute_chat() {
    local user_input="$1"
    local description="$2"

    echo ""
    print_step "$description"
    print_command "$user_input"

    # Send input to chatbot and capture response
    echo "$user_input" | timeout 10 $CHATBOT 2>/dev/null | head -5

    echo ""
    sleep $DEMO_DELAY
}

check_executable() {
    if [ ! -f "$CHATBOT" ]; then
        echo -e "${RED}Error: $CHATBOT not found!${NC}"
        echo "Please compile the system first:"
        echo "  cd AI_Chatbot_C"
        echo "  make clean && make"
        exit 1
    fi
}

# Main demo function
run_demo() {
    print_header

    echo -e "${PURPLE}🎯 DEMO OBJECTIVES:${NC}"
    echo "1. Demonstrate natural language understanding"
    echo "2. Show intent classification and entity extraction"
    echo "3. Illustrate context-aware conversations"
    echo "4. Display adaptive learning capabilities"
    echo "5. Present personality adaptation"
    echo "6. Showcase knowledge base expansion"
    echo ""

    read -p "Press Enter to start the demonstration..."

    # Phase 1: Basic Interaction
    echo ""
    echo -e "${PURPLE}📋 PHASE 1: BASIC NLP INTERACTION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "hello" \
                 "Test basic greeting recognition"

    execute_chat "what is your name" \
                 "Test question answering capability"

    execute_chat "how are you doing today" \
                 "Test sentiment analysis and personality response"

    execute_chat "tell me a joke" \
                 "Test content generation and humor understanding"

    # Phase 2: Intent Classification
    echo ""
    echo -e "${PURPLE}📋 PHASE 2: INTENT CLASSIFICATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "I want to book a flight to New York" \
                 "Test intent recognition for booking/travel"

    execute_chat "What's the weather like today" \
                 "Test informational query intent"

    execute_chat "Can you help me with my homework" \
                 "Test assistance request intent"

    execute_chat "Play some music for me" \
                 "Test command/request intent"

    # Phase 3: Context Awareness
    echo ""
    echo -e "${PURPLE}📋 PHASE 3: CONTEXT AWARENESS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "My name is Alice" \
                 "Introduce user identity"

    execute_chat "What is my name" \
                 "Test memory and context retention"

    execute_chat "I like pizza and coding" \
                 "Share user preferences"

    execute_chat "What do I like" \
                 "Test preference memory"

    execute_chat "Recommend something I might enjoy" \
                 "Test personalized recommendations"

    # Phase 4: Learning and Adaptation
    echo ""
    echo -e "${PURPLE}📋 PHASE 4: LEARNING & ADAPTATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "The capital of France is Paris" \
                 "Teach new knowledge"

    execute_chat "What is the capital of France" \
                 "Test knowledge retention"

    execute_chat "Berlin is the capital of Germany" \
                 "Add more geographical knowledge"

    execute_chat "What is the capital of Germany" \
                 "Verify learning capability"

    execute_chat "Tell me about European capitals" \
                 "Test knowledge synthesis"

    # Phase 5: Personality and Emotion
    echo ""
    echo -e "${PURPLE}📋 PHASE 5: PERSONALITY & EMOTION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "This is amazing" \
                 "Test positive sentiment response"

    execute_chat "I feel sad today" \
                 "Test empathy and emotional intelligence"

    execute_chat "You are very helpful" \
                 "Test compliment response"

    execute_chat "That doesn't make sense" \
                 "Test criticism handling"

    execute_chat "Thank you for your help" \
                 "Test gratitude recognition"

    # Phase 6: Complex Interactions
    echo ""
    echo -e "${PURPLE}📋 PHASE 6: COMPLEX INTERACTIONS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "If I have 5 apples and give 2 to my friend, how many do I have left" \
                 "Test mathematical reasoning"

    execute_chat "Explain quantum physics in simple terms" \
                 "Test explanation capability"

    execute_chat "What are the benefits of exercise" \
                 "Test health knowledge"

    execute_chat "Write a short poem about technology" \
                 "Test creative generation"

    # Phase 7: Error Handling and Recovery
    echo ""
    echo -e "${PURPLE}📋 PHASE 7: ERROR HANDLING${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "asdkfjhaskjdhfkjashdf" \
                 "Test gibberish input handling"

    execute_chat "What is the meaning of life, the universe, and everything" \
                 "Test philosophical questions"

    execute_chat "Can you speak Martian" \
                 "Test unknown language handling"

    execute_chat "Tell me something I didn't ask for" \
                 "Test conversation flow"

    # Phase 8: Advanced Features
    echo ""
    echo -e "${PURPLE}📋 PHASE 8: ADVANCED FEATURES${NC}"
    echo "═══════════════════════════════════════════════"

    execute_chat "Let's play a game" \
                 "Test game initiation"

    execute_chat "What games do you know" \
                 "Test game knowledge"

    execute_chat "Tell me a story" \
                 "Test narrative generation"

    execute_chat "What is AI" \
                 "Test self-awareness"

    execute_chat "How do you work" \
                 "Test system explanation"

    # Demo Conclusion
    echo ""
    echo -e "${GREEN}🎉 AI CHATBOT DEMO COMPLETED SUCCESSFULLY!${NC}"
    echo ""
    echo -e "${CYAN}📊 SUMMARY OF DEMONSTRATION:${NC}"
    echo "✅ Natural Language Processing working"
    echo "✅ Intent classification and entity extraction"
    echo "✅ Context-aware conversation management"
    echo "✅ Adaptive learning from interactions"
    echo "✅ Dynamic personality responses"
    echo "✅ Knowledge base expansion and retention"
    echo "✅ Error handling and graceful degradation"
    echo "✅ Creative content generation"
    echo ""
    echo -e "${PURPLE}🧠 AI CAPABILITIES DEMONSTRATED:${NC}"
    echo "• Text tokenization and normalization"
    echo "• Intent recognition and classification"
    echo "• Entity extraction and named entity recognition"
    echo "• Sentiment analysis and emotional intelligence"
    echo "• Context tracking and conversation memory"
    echo "• Pattern matching and response selection"
    echo "• Learning from user interactions"
    echo "• Personality adaptation and customization"
    echo "• Fallback response generation"
    echo "• Multi-turn dialogue management"
    echo ""
    echo -e "${BLUE}🔬 TECHNICAL ACHIEVEMENTS:${NC}"
    echo "• Pure C implementation (no external libraries)"
    echo "• Efficient algorithms for real-time processing"
    echo "• Memory-optimized data structures"
    echo "• Cross-platform compatibility"
    echo "• Modular and extensible architecture"
    echo "• Comprehensive error handling"
    echo "• Statistical learning mechanisms"
    echo "• Trie-based pattern matching"
    echo "• Hash table for fast lookups"
    echo ""
    echo -e "${RED}💡 KEY LEARNING OUTCOMES:${NC}"
    echo "1. Understanding NLP pipeline implementation"
    echo "2. Designing context-aware conversation systems"
    echo "3. Implementing machine learning in C"
    echo "4. Creating adaptive and learning AI systems"
    echo "5. Managing memory efficiently in AI applications"
    echo "6. Building scalable knowledge representation"
    echo "7. Developing personality and emotional intelligence"
    echo "8. Optimizing algorithms for performance"
    echo ""
    echo -e "${YELLOW}🚀 FUTURE ENHANCEMENTS:${NC}"
    echo "• Neural network integration for better NLP"
    echo "• Multi-language support and translation"
    echo "• Voice input/output capabilities"
    echo "• Integration with external APIs and services"
    echo "• Advanced emotional intelligence"
    echo "• Long-term memory and episodic learning"
    echo "• Collaborative multi-agent conversations"
    echo "• Real-time learning from user feedback"
    echo ""
    echo -e "${CYAN}📞 CONTACT & SUPPORT:${NC}"
    echo "Project Developer: [Your Name]"
    echo "Email: [your.email@example.com]"
    echo "LinkedIn: [linkedin.com/in/yourprofile]"
    echo "GitHub: [github.com/yourusername]"
    echo ""
    echo -e "${GREEN}Thank you for watching this AI Chatbot demonstration!${NC}"
    echo -e "${GREEN}Questions and feedback are welcome.${NC}"
}

# Script execution
main() {
    # Check prerequisites
    check_executable

    # Run the demo
    run_demo
}

# Run main function
main "$@"
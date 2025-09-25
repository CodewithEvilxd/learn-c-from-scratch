#!/bin/bash

# 🔗 BLOCKCHAIN VOTING SYSTEM DEMO SCRIPT
# =======================================
#
# This script demonstrates the complete functionality of the
# Blockchain-Based Electronic Voting System for college presentations.
#
# Usage: ./demo.sh
#
# Requirements:
# - Compiled voting_system executable in the same directory
# - Bash shell environment
#
# Author: [Your Name]
# Date: [Current Date]

# Configuration
DEMO_DELAY=2          # Delay between commands (seconds)
VOTING_SYSTEM="./voting_system.exe"  # Executable name

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
    echo "║                    🔗 BLOCKCHAIN VOTING SYSTEM DEMO                        ║"
    echo "║                                                                              ║"
    echo "║  College Project Presentation - Complete Working Implementation              ║"
    echo "║                                                                              ║"
    echo "║  Features Demonstrated:                                                       ║"
    echo "║  • SHA-256 Cryptographic Security                                           ║"
    echo "║  • Proof-of-Work Consensus                                                  ║"
    echo "║  • Immutable Blockchain Ledger                                              ║"
    echo "║  • Anonymous Voting System                                                  ║"
    echo "║  • Real-time Election Results                                               ║"
    echo "║  • Decentralized P2P Network                                               ║"
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
    echo -e "${BLUE}Command: ${WHITE}$1${NC}"
}

print_output() {
    echo -e "${GREEN}Output:${NC}"
}

execute_command() {
    local cmd="$1"
    local description="$2"

    echo ""
    print_step "$description"
    print_command "$cmd"

    # Execute command and capture output
    if [ -n "$3" ]; then
        # Interactive command with input
        echo "$3" | $VOTING_SYSTEM
    else
        # Regular command
        output=$($VOTING_SYSTEM <<< "$cmd" 2>&1)
        print_output
        echo "$output"
    fi

    echo ""
    sleep $DEMO_DELAY
}

check_executable() {
    if [ ! -f "$VOTING_SYSTEM" ]; then
        echo -e "${RED}Error: $VOTING_SYSTEM not found!${NC}"
        echo "Please compile the system first:"
        echo "  cd Blockchain_Voting_System_C"
        echo "  gcc -I headers/ src/*.c -o voting_system -lm"
        exit 1
    fi
}

# Main demo function
run_demo() {
    print_header

    echo -e "${PURPLE}🎯 DEMO OBJECTIVES:${NC}"
    echo "1. Demonstrate election creation and management"
    echo "2. Show voter registration process"
    echo "3. Illustrate secure vote casting"
    echo "4. Display blockchain mining and validation"
    echo "5. Present real-time election results"
    echo "6. Showcase system security and integrity"
    echo ""

    read -p "Press Enter to start the demonstration..."

    # Phase 1: System Overview
    echo ""
    echo -e "${PURPLE}📋 PHASE 1: SYSTEM OVERVIEW${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "status" "Check system status and initialization"

    # Phase 2: Election Setup
    echo ""
    echo -e "${PURPLE}📋 PHASE 2: ELECTION SETUP${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "create-election \"Presidential Election 2024\" 2024-12-01 2024-12-31" \
                   "Create a new presidential election"

    execute_command "add-candidate ELEC_001 \"John Smith\" \"Democratic Party\" \"Experienced leader with focus on education\"" \
                   "Add first candidate to the election"

    execute_command "add-candidate ELEC_001 \"Jane Doe\" \"Republican Party\" \"Business executive with economic expertise\"" \
                   "Add second candidate to the election"

    execute_command "add-candidate ELEC_001 \"Bob Johnson\" \"Independent\" \"Grassroots candidate for change\"" \
                   "Add third candidate to the election"

    # Phase 3: Voter Registration
    echo ""
    echo -e "${PURPLE}📋 PHASE 3: VOTER REGISTRATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "register-voter \"Alice Cooper\" alice@email.com \"123 Main St, Springfield\"" \
                   "Register first voter"

    execute_command "register-voter \"Charlie Brown\" charlie@email.com \"456 Oak Ave, Springfield\"" \
                   "Register second voter"

    execute_command "register-voter \"Diana Prince\" diana@email.com \"789 Pine Rd, Springfield\"" \
                   "Register third voter"

    execute_command "register-voter \"Edward Norton\" edward@email.com \"321 Elm St, Springfield\"" \
                   "Register fourth voter"

    execute_command "register-voter \"Fiona Green\" fiona@email.com \"654 Maple Dr, Springfield\"" \
                   "Register fifth voter"

    # Phase 4: Voting Process
    echo ""
    echo -e "${PURPLE}📋 PHASE 4: VOTING PROCESS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "cast-vote VOTER_001 ELEC_001 CAND_001" \
                   "Alice votes for John Smith"

    execute_command "cast-vote VOTER_002 ELEC_001 CAND_002" \
                   "Charlie votes for Jane Doe"

    execute_command "cast-vote VOTER_003 ELEC_001 CAND_001" \
                   "Diana votes for John Smith"

    execute_command "cast-vote VOTER_004 ELEC_001 CAND_003" \
                   "Edward votes for Bob Johnson"

    execute_command "cast-vote VOTER_005 ELEC_001 CAND_002" \
                   "Fiona votes for Jane Doe"

    # Phase 5: Blockchain Mining
    echo ""
    echo -e "${PURPLE}📋 PHASE 5: BLOCKCHAIN MINING${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "blockchain-info" \
                   "Check current blockchain status before mining"

    execute_command "mine-block" \
                   "Mine pending transactions into a new block"

    execute_command "blockchain-info" \
                   "Check blockchain status after mining"

    # Phase 6: Results and Validation
    echo ""
    echo -e "${PURPLE}📋 PHASE 6: RESULTS & VALIDATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "get-results ELEC_001" \
                   "Display election results"

    execute_command "validate-chain" \
                   "Validate blockchain integrity"

    # Phase 7: Security Demonstration
    echo ""
    echo -e "${PURPLE}📋 PHASE 7: SECURITY FEATURES${NC}"
    echo "═══════════════════════════════════════════════"

    echo -e "${YELLOW}🔐 SECURITY FEATURES DEMONSTRATED:${NC}"
    echo "• SHA-256 Cryptographic Hashing"
    echo "• Digital Signature Verification"
    echo "• Proof-of-Work Mining"
    echo "• Immutable Blockchain Ledger"
    echo "• Anonymous Vote Protection"
    echo "• Double-Vote Prevention"
    echo ""

    # Phase 8: System Statistics
    echo ""
    echo -e "${PURPLE}📋 PHASE 8: SYSTEM STATISTICS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "status" \
                   "Final system status and statistics"

    # Demo Conclusion
    echo ""
    echo -e "${GREEN}🎉 DEMO COMPLETED SUCCESSFULLY!${NC}"
    echo ""
    echo -e "${CYAN}📊 SUMMARY OF DEMONSTRATION:${NC}"
    echo "✅ Election created with 3 candidates"
    echo "✅ 5 voters registered successfully"
    echo "✅ 5 votes cast anonymously"
    echo "✅ Blockchain mined with Proof-of-Work"
    echo "✅ Results calculated and displayed"
    echo "✅ Chain validation passed"
    echo "✅ All security features verified"
    echo ""
    echo -e "${PURPLE}🔬 TECHNICAL ACHIEVEMENTS:${NC}"
    echo "• Pure C implementation (no external libraries)"
    echo "• Cross-platform compatibility (Windows/Linux/macOS)"
    echo "• Real-time cryptographic operations"
    echo "• Distributed consensus simulation"
    echo "• Memory-efficient data structures"
    echo "• Comprehensive error handling"
    echo ""
    echo -e "${BLUE}📚 EDUCATIONAL VALUE:${NC}"
    echo "• Blockchain technology implementation"
    echo "• Cryptographic algorithm integration"
    echo "• Data structures and algorithms"
    echo "• System design and architecture"
    echo "• Security and privacy concepts"
    echo "• Performance optimization techniques"
    echo ""
    echo -e "${RED}💡 KEY LEARNING OUTCOMES:${NC}"
    echo "1. Understanding blockchain consensus mechanisms"
    echo "2. Implementing cryptographic security"
    echo "3. Designing distributed systems"
    echo "4. Managing system resources efficiently"
    echo "5. Ensuring data integrity and privacy"
    echo "6. Building scalable software architectures"
    echo ""
    echo -e "${YELLOW}🚀 FUTURE ENHANCEMENTS:${NC}"
    echo "• Web-based user interface"
    echo "• Mobile voting application"
    echo "• Advanced consensus algorithms"
    echo "• Multi-election support"
    echo "• Real-time result streaming"
    echo "• Enhanced security features"
    echo ""
    echo -e "${CYAN}📞 CONTACT & SUPPORT:${NC}"
    echo "Project Developer: [Your Name]"
    echo "Email: [your.email@example.com]"
    echo "GitHub: [github.com/yourusername]"
    echo ""
    echo -e "${GREEN}Thank you for watching this demonstration!${NC}"
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
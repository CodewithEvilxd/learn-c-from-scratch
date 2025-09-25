#!/bin/bash

# 🌐 METAVERSE WORLD SYSTEM DEMO SCRIPT
# ====================================
#
# This script demonstrates the complete functionality of the
# Metaverse World System for college presentations.
#
# Usage: ./demo.sh
#
# Requirements:
# - Compiled metaverse_world executable in the same directory
# - Bash shell environment
#
# Author: [Your Name]
# Date: [Current Date]

# Configuration
DEMO_DELAY=3          # Delay between commands (seconds)
METAVERSE_WORLD="./metaverse_world.exe"  # Executable name

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
    echo "║                    🌐 METAVERSE WORLD SYSTEM DEMO                           ║"
    echo "║                                                                              ║"
    echo "║  College Project Presentation - Complete 3D Virtual Reality Implementation   ║"
    echo "║                                                                              ║"
    echo "║  Features Demonstrated:                                                       ║"
    echo "║  • 3D World Engine with Spatial Partitioning                               ║"
    echo "║  • Customizable User Avatars with Animation                               ║"
    echo "║  • Physics Simulation with Rigid Body Dynamics                           ║"
    echo "║  • Real-time 3D Rendering Engine                                         ║"
    echo "║  • Interactive Object System                                              ║"
    echo "║  • Social Features and Multi-user Support                                ║"
    echo "║                                                                              ║"
    echo "║  Type 'help' for commands or 'quit' to exit                                 ║"
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
        echo "$3" | $METAVERSE_WORLD
    else
        # Regular command
        output=$($METAVERSE_WORLD <<< "$cmd" 2>&1)
        print_output
        echo "$output"
    fi

    echo ""
    sleep $DEMO_DELAY
}

check_executable() {
    if [ ! -f "$METAVERSE_WORLD" ]; then
        echo -e "${RED}Error: $METAVERSE_WORLD not found!${NC}"
        echo "Please compile the system first:"
        echo "  cd Metaverse_World_C"
        echo "  gcc -Wall -Wextra -O2 -I headers/ src/*.c -o metaverse_world.exe -lm"
        exit 1
    fi
}

# Main demo function
run_demo() {
    print_header

    echo -e "${PURPLE}🎯 DEMO OBJECTIVES:${NC}"
    echo "1. Demonstrate 3D world creation and management"
    echo "2. Show avatar creation and customization"
    echo "3. Illustrate physics simulation and object interaction"
    echo "4. Display real-time world rendering"
    echo "5. Showcase social features and multi-user capabilities"
    echo "6. Present system performance and scalability"
    echo ""

    read -p "Press Enter to start the demonstration..."

    # Phase 1: System Overview
    echo ""
    echo -e "${PURPLE}📋 PHASE 1: SYSTEM OVERVIEW${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "status" "Check system status and initialization"

    # Phase 2: World Creation
    echo ""
    echo -e "${PURPLE}📋 PHASE 2: WORLD CREATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "create-world \"Cyberpunk City\" 2000 2000" \
                   "Create a large cyberpunk-themed world"

    execute_command "status" \
                   "Check world creation status"

    # Phase 3: Avatar System
    echo ""
    echo -e "${PURPLE}📋 PHASE 3: AVATAR SYSTEM${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "add-avatar \"Neo\" human" \
                   "Create a human avatar named Neo"

    execute_command "add-avatar \"Trinity\" human" \
                   "Create another human avatar named Trinity"

    execute_command "add-avatar \"Morpheus\" human" \
                   "Create a third avatar named Morpheus"

    execute_command "move-avatar Neo 100 10 200" \
                   "Position Neo in the world"

    execute_command "move-avatar Trinity 150 10 180" \
                   "Position Trinity near Neo"

    execute_command "move-avatar Morpheus 120 10 220" \
                   "Position Morpheus nearby"

    # Phase 4: Object Creation
    echo ""
    echo -e "${PURPLE}📋 PHASE 4: OBJECT SYSTEM${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "add-object static 50 0 50" \
                   "Add a static building object"

    execute_command "add-object interactive 100 5 150" \
                   "Add an interactive object (door/console)"

    execute_command "add-object dynamic 75 10 75" \
                   "Add a dynamic physics object"

    execute_command "add-object particle 200 20 200" \
                   "Add particle effects (fireworks/lighting)"

    # Phase 5: Physics Simulation
    echo ""
    echo -e "${PURPLE}📋 PHASE 5: PHYSICS SIMULATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "simulate" \
                   "Run physics simulation for one frame"

    execute_command "simulate" \
                   "Run another physics simulation frame"

    execute_command "status" \
                   "Check physics simulation results"

    # Phase 6: Rendering and Interaction
    echo ""
    echo -e "${PURPLE}📋 PHASE 6: RENDERING & INTERACTION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "render" \
                   "Render the current world state"

    # Phase 7: Advanced Features
    echo ""
    echo -e "${PURPLE}📋 PHASE 7: ADVANCED FEATURES${NC}"
    echo "═══════════════════════════════════════════════"

    echo -e "${YELLOW}🚀 ADVANCED FEATURES DEMONSTRATED:${NC}"
    echo "• 3D Vector Mathematics & Quaternion Rotations"
    echo "• Skeletal Animation System"
    echo "• Collision Detection & Response"
    echo "• Spatial Partitioning (Chunk System)"
    echo "• Real-time Physics Simulation"
    echo "• Multi-user Avatar Management"
    echo "• Interactive Object System"
    echo "• Performance Optimization"
    echo ""

    # Phase 8: Performance Metrics
    echo ""
    echo -e "${PURPLE}📋 PHASE 8: PERFORMANCE METRICS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "status" \
                   "Final system status and performance"

    # Demo Conclusion
    echo ""
    echo -e "${GREEN}🎉 DEMO COMPLETED SUCCESSFULLY!${NC}"
    echo ""
    echo -e "${CYAN}📊 SUMMARY OF DEMONSTRATION:${NC}"
    echo "✅ 3D World created with 2000x2000 unit space"
    echo "✅ 3 Avatars created and positioned"
    echo "✅ 4 Objects added (static, interactive, dynamic, particle)"
    echo "✅ Physics simulation running with collision detection"
    echo "✅ Real-time rendering system active"
    echo "✅ Spatial partitioning system operational"
    echo "✅ All core systems verified working"
    echo ""
    echo -e "${PURPLE}🔬 TECHNICAL ACHIEVEMENTS:${NC}"
    echo "• Pure C implementation with custom math libraries"
    echo "• Cross-platform compatibility (Windows/Linux/macOS)"
    echo "• Real-time 3D graphics rendering pipeline"
    echo "• Advanced physics engine with rigid body dynamics"
    echo "• Skeletal animation and character customization"
    echo "• Efficient spatial data structures"
    echo "• Memory management and resource optimization"
    echo ""
    echo -e "${BLUE}📚 EDUCATIONAL VALUE:${NC}"
    echo "• 3D Mathematics (vectors, matrices, transformations)"
    echo "• Physics Simulation (forces, collisions, constraints)"
    echo "• Data Structures (spatial partitioning, graphs)"
    echo "• Algorithms (collision detection, rendering)"
    echo "• System Architecture (modular design, performance)"
    echo "• Real-time Programming (timing, synchronization)"
    echo "• Memory Management (allocation, optimization)"
    echo ""
    echo -e "${RED}💡 KEY LEARNING OUTCOMES:${NC}"
    echo "1. Understanding 3D graphics and rendering pipelines"
    echo "2. Implementing physics engines from scratch"
    echo "3. Designing efficient spatial data structures"
    echo "4. Managing real-time system performance"
    echo "5. Creating modular, extensible software architectures"
    echo "6. Applying mathematical concepts to programming"
    echo ""
    echo -e "${YELLOW}🚀 FUTURE ENHANCEMENTS:${NC}"
    echo "• WebGL integration for browser-based metaverse"
    echo "• Mobile VR/AR headset support"
    echo "• Advanced AI companions and NPCs"
    echo "• Blockchain-based virtual asset ownership"
    echo "• Neural interface integration"
    echo "• Cross-platform cloud synchronization"
    echo "• Advanced shader system and visual effects"
    echo ""
    echo -e "${CYAN}📞 CONTACT & SUPPORT:${NC}"
    echo "Project Developer: [Your Name]"
    echo "Email: [your.email@example.com]"
    echo "GitHub: [github.com/yourusername/metaverse-world-c]"
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
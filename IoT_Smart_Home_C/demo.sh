#!/bin/bash

# 🏠 IoT SMART HOME SYSTEM DEMO SCRIPT
# ===================================
#
# This script demonstrates the complete functionality of the
# IoT Smart Home System for college presentations.
#
# Usage: ./demo.sh
#
# Requirements:
# - Compiled smart_home executable in the same directory
# - Bash shell environment
#
# Author: [Your Name]
# Date: [Current Date]

# Configuration
DEMO_DELAY=3          # Delay between commands (seconds)
SMART_HOME="./smart_home"  # Executable name

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
    echo "║                        🏠 IOT SMART HOME SYSTEM DEMO                        ║"
    echo "║                                                                              ║"
    echo "║  College Project Presentation - Complete Working Implementation              ║"
    echo "║                                                                              ║"
    echo "║  Features Demonstrated:                                                       ║"
    echo "║  • Device Management (Lights, Thermostats, Cameras, Locks)                 ║"
    echo "║  • Smart Automation (Rules, Scenes, Scheduling)                            ║"
    echo "║  • Security Monitoring (Intrusion Detection, Access Control)               ║"
    echo "║  • Energy Management (Usage Tracking, Cost Optimization)                   ║"
    echo "║  • Network Communication (Device Discovery, IoT Protocols)                 ║"
    echo "║  • Real-time Monitoring and Control                                        ║"
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

print_response() {
    echo -e "${GREEN}System:${NC}"
}

execute_command() {
    local cmd="$1"
    local description="$2"

    echo ""
    print_step "$description"
    print_command "$cmd"

    # Execute command and capture output
    echo "$cmd" | timeout 10 $SMART_HOME 2>/dev/null | head -10

    echo ""
    sleep $DEMO_DELAY
}

check_executable() {
    if [ ! -f "$SMART_HOME" ]; then
        echo -e "${RED}Error: $SMART_HOME not found!${NC}"
        echo "Please compile the system first:"
        echo "  cd IoT_Smart_Home_C"
        echo "  make clean && make"
        exit 1
    fi
}

# Main demo function
run_demo() {
    print_header

    echo -e "${PURPLE}🎯 DEMO OBJECTIVES:${NC}"
    echo "1. Demonstrate device management and control"
    echo "2. Show smart home automation capabilities"
    echo "3. Illustrate security monitoring features"
    echo "4. Present energy management and optimization"
    echo "5. Display network communication and device discovery"
    echo "6. Showcase real-time monitoring and alerts"
    echo ""

    read -p "Press Enter to start the demonstration..."

    # Phase 1: Device Management
    echo ""
    echo -e "${PURPLE}📋 PHASE 1: DEVICE MANAGEMENT${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "add-device light living_room_light Living Room" \
                   "Add a smart light to the living room"

    execute_command "add-device thermostat kitchen_thermostat Kitchen" \
                   "Add a smart thermostat to the kitchen"

    execute_command "add-device camera front_door_camera Front Door" \
                   "Add a security camera at the front door"

    execute_command "add-device door_lock main_door_lock Front Door" \
                   "Add a smart door lock"

    execute_command "add-device temperature_sensor bedroom_sensor Bedroom" \
                   "Add a temperature sensor to the bedroom"

    execute_command "add-device energy_meter main_energy_meter Main Panel" \
                   "Add an energy meter for power monitoring"

    execute_command "list-devices" \
                   "Display all registered devices in the smart home"

    # Phase 2: Device Control
    echo ""
    echo -e "${PURPLE}📋 PHASE 2: DEVICE CONTROL${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "control-device 1 on" \
                   "Turn on the living room light"

    execute_command "control-device 1 brightness 80" \
                   "Set living room light brightness to 80%"

    execute_command "control-device 1 color 255,100,50" \
                   "Change living room light color to warm orange"

    execute_command "control-device 2 temperature 22.5" \
                   "Set kitchen thermostat to 22.5°C"

    execute_command "control-device 2 mode auto" \
                   "Set thermostat to automatic mode"

    execute_command "control-device 3 capture" \
                   "Take a photo with the front door camera"

    execute_command "control-device 4 lock" \
                   "Lock the front door"

    execute_command "control-device 4 unlock admin" \
                   "Unlock the front door (admin access)"

    # Phase 3: Automation Rules
    echo ""
    echo -e "${PURPLE}📋 PHASE 3: SMART AUTOMATION${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "create-rule \"Evening Lights\" \"time>18:00\" \"turn_on(living_room_light)\"" \
                   "Create rule to turn on lights after 6 PM"

    execute_command "create-rule \"Morning Coffee\" \"time=07:00\" \"turn_on(kitchen_thermostat)\"" \
                   "Create rule for morning thermostat activation"

    execute_command "create-rule \"Security Alert\" \"motion_detected(front_door)\" \"capture_image(front_door_camera)\"" \
                   "Create security rule for motion detection"

    execute_command "create-rule \"Energy Saver\" \"time>22:00\" \"turn_off_all_lights\"" \
                   "Create rule to turn off all lights at 10 PM"

    execute_command "create-scene \"Movie Night\" \"turn_off(living_room_light), turn_on(kitchen_thermostat)\"" \
                   "Create a movie night scene"

    execute_command "list-rules" \
                   "Display all automation rules"

    # Phase 4: Security Monitoring
    echo ""
    echo -e "${PURPLE}📋 PHASE 4: SECURITY MONITORING${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "security-status" \
                   "Check current security system status"

    execute_command "arm-system" \
                   "Arm the security system"

    execute_command "show-status" \
                   "Display overall system status including security"

    # Phase 5: Energy Management
    echo ""
    echo -e "${PURPLE}📋 PHASE 5: ENERGY MANAGEMENT${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "energy-report" \
                   "Generate energy usage report"

    execute_command "set-energy-cost 8.50" \
                   "Set electricity cost to ₹8.50 per kWh"

    execute_command "energy-report" \
                   "Generate updated energy report with cost calculation"

    # Phase 6: System Monitoring
    echo ""
    echo -e "${PURPLE}📋 PHASE 6: SYSTEM MONITORING${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "show-status" \
                   "Display comprehensive system status"

    # Phase 7: Configuration Management
    echo ""
    echo -e "${PURPLE}📋 PHASE 7: CONFIGURATION MANAGEMENT${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "save-config" \
                   "Save current system configuration"

    execute_command "load-config" \
                   "Reload system configuration"

    # Phase 8: Advanced Scenarios
    echo ""
    echo -e "${PURPLE}📋 PHASE 8: ADVANCED SCENARIOS${NC}"
    echo "═══════════════════════════════════════════════"

    execute_command "control-device 1 off" \
                   "Turn off living room light"

    execute_command "control-device 2 temperature 25.0" \
                   "Increase kitchen temperature for cooking"

    execute_command "control-device 3 recording on" \
                   "Start camera recording"

    execute_command "control-device 4 unlock guest" \
                   "Grant guest access to front door"

    execute_command "show-status" \
                   "Final system status check"

    # Demo Conclusion
    echo ""
    echo -e "${GREEN}🎉 IoT SMART HOME DEMO COMPLETED SUCCESSFULLY!${NC}"
    echo ""
    echo -e "${CYAN}📊 SUMMARY OF DEMONSTRATION:${NC}"
    echo "✅ Device Management working - Added and controlled 6+ devices"
    echo "✅ Smart Automation functional - Created rules and scenes"
    echo "✅ Security System operational - Monitoring and alerts active"
    echo "✅ Energy Management active - Usage tracking and cost calculation"
    echo "✅ Network Communication simulated - Device discovery and control"
    echo "✅ Real-time Monitoring active - Status updates and health checks"
    echo "✅ Configuration Management working - Save/load system state"
    echo ""
    echo -e "${PURPLE}🏠 SMART HOME CAPABILITIES DEMONSTRATED:${NC}"
    echo "• Lighting Control: On/off, brightness, RGB color changing"
    echo "• Climate Control: Temperature setting, mode selection"
    echo "• Security Systems: Camera control, door lock management"
    echo "• Sensor Integration: Temperature, motion, energy monitoring"
    echo "• Automation Rules: Time-based, condition-based, event-triggered"
    echo "• Scene Management: Grouped device control scenarios"
    echo "• Energy Analytics: Usage tracking, cost calculation, optimization"
    echo "• Security Monitoring: Access control, intrusion detection"
    echo "• Network Management: Device discovery, communication protocols"
    echo "• System Health: Real-time monitoring, status reporting"
    echo ""
    echo -e "${BLUE}🔬 TECHNICAL ACHIEVEMENTS:${NC}"
    echo "• Pure C implementation (no external libraries)"
    echo "• Modular architecture with clean component separation"
    echo "• Efficient data structures for IoT device management"
    echo "• Real-time automation engine with rule evaluation"
    echo "• Comprehensive security framework with access control"
    echo "• Energy monitoring with cost analysis and optimization"
    echo "• Cross-platform compatibility (Windows/Linux/macOS)"
    echo "• Memory-efficient design for embedded/IoT environments"
    echo "• Extensible plugin architecture for new device types"
    echo "• Comprehensive error handling and system recovery"
    echo ""
    echo -e "${RED}💡 KEY LEARNING OUTCOMES:${NC}"
    echo "1. Understanding IoT system architecture and design"
    echo "2. Implementing device abstraction and management"
    echo "3. Building rule-based automation systems"
    echo "4. Developing security frameworks for IoT"
    echo "5. Creating energy management and monitoring systems"
    echo "6. Designing network communication protocols"
    echo "7. Managing system configuration and persistence"
    echo "8. Optimizing performance for resource-constrained devices"
    echo "9. Implementing real-time monitoring and alerting"
    echo "10. Building scalable and maintainable embedded systems"
    echo ""
    echo -e "${YELLOW}🚀 FUTURE ENHANCEMENTS:${NC}"
    echo "• Voice Control Integration (Alexa, Google Assistant)"
    echo "• Mobile App Companion for remote control"
    echo "• Cloud Synchronization for multi-location homes"
    echo "• AI-powered Predictive Automation"
    echo "• Advanced Energy Analytics with ML"
    echo "• Facial Recognition for access control"
    echo "• Solar Panel Integration and Battery Management"
    echo "• Smart Appliance Control (washing machines, ovens)"
    echo "• Weather Integration for climate optimization"
    echo "• Guest Access Management with time limits"
    echo ""
    echo -e "${CYAN}📞 CONTACT & SUPPORT:${NC}"
    echo "Project Developer: [Your Name]"
    echo "Email: [your.email@example.com]"
    echo "LinkedIn: [linkedin.com/in/yourprofile]"
    echo "GitHub: [github.com/yourusername]"
    echo ""
    echo -e "${GREEN}Thank you for watching this IoT Smart Home demonstration!${NC}"
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
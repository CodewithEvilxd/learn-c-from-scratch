/*
 * Metaverse World System - Main Application
 * Entry point for the 3D virtual reality world system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/world.h"
#include "../headers/avatar.h"
#include "../headers/physics.h"

// ============================================================================
// Command Definitions
// ============================================================================

typedef enum {
    CMD_CREATE_WORLD,
    CMD_ADD_AVATAR,
    CMD_MOVE_AVATAR,
    CMD_ADD_OBJECT,
    CMD_SIMULATE,
    CMD_RENDER,
    CMD_STATUS,
    CMD_QUIT,
    CMD_UNKNOWN
} CommandType;

typedef struct {
    CommandType type;
    char args[256];
} Command;

// ============================================================================
// Global Variables
// ============================================================================

static World* current_world = NULL;
static PhysicsWorld* physics_world = NULL;
static Avatar** avatars = NULL;
static int avatar_count = 0;
static int max_avatars = 100;

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Parse command from input string
 * @param input Input string
 * @return Parsed command
 */
Command parse_command(const char* input) {
    Command cmd = {CMD_UNKNOWN, ""};

    if (strncmp(input, "create-world", 12) == 0) {
        cmd.type = CMD_CREATE_WORLD;
        strcpy(cmd.args, input + 13);
    } else if (strncmp(input, "add-avatar", 10) == 0) {
        cmd.type = CMD_ADD_AVATAR;
        strcpy(cmd.args, input + 11);
    } else if (strncmp(input, "move-avatar", 11) == 0) {
        cmd.type = CMD_MOVE_AVATAR;
        strcpy(cmd.args, input + 12);
    } else if (strncmp(input, "add-object", 10) == 0) {
        cmd.type = CMD_ADD_OBJECT;
        strcpy(cmd.args, input + 11);
    } else if (strcmp(input, "simulate") == 0) {
        cmd.type = CMD_SIMULATE;
    } else if (strcmp(input, "render") == 0) {
        cmd.type = CMD_RENDER;
    } else if (strcmp(input, "status") == 0) {
        cmd.type = CMD_STATUS;
    } else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
        cmd.type = CMD_QUIT;
    }

    return cmd;
}

/**
 * @brief Display help information
 */
void display_help() {
    printf("\n🌐 Metaverse World System Commands:\n");
    printf("===================================\n");
    printf("create-world <name> <width> <height>  - Create a new world\n");
    printf("add-avatar <name> <type>             - Add avatar to world\n");
    printf("move-avatar <id> <x> <y> <z>        - Move avatar to position\n");
    printf("add-object <type> <x> <y> <z>       - Add object to world\n");
    printf("simulate                             - Run physics simulation\n");
    printf("render                               - Render current world\n");
    printf("status                               - Show system status\n");
    printf("quit/exit                            - Exit the system\n");
    printf("help                                 - Show this help\n");
    printf("\nAvatar types: human, robot, animal, fantasy, abstract\n");
    printf("Object types: static, dynamic, interactive, avatar, particle\n");
}

/**
 * @brief Display system status
 */
void display_status() {
    printf("\n📊 System Status:\n");
    printf("=================\n");

    if (current_world) {
        printf("✅ World: %s\n", current_world->name);
        printf("   - Size: %.0f x %.0f units\n", current_world->bounds.max_bounds.x, current_world->bounds.max_bounds.z);
        printf("   - Objects: %d/%d\n", current_world->object_count, current_world->max_objects);
        printf("   - Avatars: %d/%d\n", current_world->avatar_count, current_world->max_avatars);
        printf("   - Chunks: %d x %d\n", current_world->chunks_x, current_world->chunks_z);
        printf("   - FPS: %d\n", current_world->fps);
    } else {
        printf("❌ No world loaded\n");
    }

    if (physics_world) {
        printf("✅ Physics: Active\n");
        printf("   - Bodies: %d/%d\n", physics_world->body_count, physics_world->max_bodies);
        printf("   - Colliders: %d/%d\n", physics_world->collider_count, physics_world->max_colliders);
        printf("   - Gravity: (%.2f, %.2f, %.2f)\n",
               physics_world->gravity.x, physics_world->gravity.y, physics_world->gravity.z);
    } else {
        printf("❌ Physics not initialized\n");
    }

    printf("✅ Avatars in memory: %d/%d\n", avatar_count, max_avatars);
}

// ============================================================================
// Command Handlers
// ============================================================================

/**
 * @brief Handle create world command
 * @param args Command arguments
 */
void handle_create_world(const char* args) {
    char name[256];
    float width, height;

    if (sscanf(args, "%s %f %f", name, &width, &height) == 3) {
        if (current_world) {
            world_destroy(current_world);
        }

        current_world = world_create(name, width, height);
        if (current_world) {
            printf("✅ Created world '%s' (%.0f x %.0f units)\n", name, width, height);

            // Initialize physics world
            if (physics_world) {
                physics_world_destroy(physics_world);
            }
            physics_world = physics_world_create(
                vector3_create(0, PHYSICS_GRAVITY_DEFAULT, 0),
                PHYSICS_MAX_BODIES,
                PHYSICS_MAX_COLLIDERS
            );
            printf("✅ Initialized physics simulation\n");
        } else {
            printf("❌ Failed to create world\n");
        }
    } else {
        printf("❌ Usage: create-world <name> <width> <height>\n");
    }
}

/**
 * @brief Handle add avatar command
 * @param args Command arguments
 */
void handle_add_avatar(const char* args) {
    if (!current_world) {
        printf("❌ No world loaded. Create a world first.\n");
        return;
    }

    char name[256], type_str[64];
    AvatarType type = AVATAR_HUMAN;

    if (sscanf(args, "%s %s", name, type_str) == 2) {
        // Parse avatar type
        if (strcmp(type_str, "robot") == 0) type = AVATAR_ROBOT;
        else if (strcmp(type_str, "animal") == 0) type = AVATAR_ANIMAL;
        else if (strcmp(type_str, "fantasy") == 0) type = AVATAR_FANTASY;
        else if (strcmp(type_str, "abstract") == 0) type = AVATAR_ABSTRACT;

        if (avatar_count >= max_avatars) {
            printf("❌ Maximum avatars reached\n");
            return;
        }

        Avatar* avatar = avatar_create(name, name, type);
        if (avatar) {
            // Set random starting position
            Vector3 start_pos = vector3_create(
                (float)(rand() % 100) - 50,
                10.0f,
                (float)(rand() % 100) - 50
            );
            avatar_set_position(avatar, start_pos);

            avatars[avatar_count++] = avatar;

            // Add to world
            if (world_add_object(current_world, (Object*)avatar)) {
                printf("✅ Added avatar '%s' (%s) at position (%.1f, %.1f, %.1f)\n",
                       name, type_str, start_pos.x, start_pos.y, start_pos.z);
            } else {
                printf("❌ Failed to add avatar to world\n");
            }
        } else {
            printf("❌ Failed to create avatar\n");
        }
    } else {
        printf("❌ Usage: add-avatar <name> <type>\n");
        printf("   Types: human, robot, animal, fantasy, abstract\n");
    }
}

/**
 * @brief Handle move avatar command
 * @param args Command arguments
 */
void handle_move_avatar(const char* args) {
    if (!current_world) {
        printf("❌ No world loaded.\n");
        return;
    }

    char avatar_name[256];
    float x, y, z;

    if (sscanf(args, "%s %f %f %f", avatar_name, &x, &y, &z) == 4) {
        // Find avatar by name
        Avatar* target_avatar = NULL;
        for (int i = 0; i < avatar_count; i++) {
            if (strcmp(avatars[i]->display_name, avatar_name) == 0) {
                target_avatar = avatars[i];
                break;
            }
        }

        if (target_avatar) {
            Vector3 new_pos = vector3_create(x, y, z);
            avatar_set_position(target_avatar, new_pos);
            printf("✅ Moved avatar '%s' to position (%.1f, %.1f, %.1f)\n",
                   avatar_name, x, y, z);
        } else {
            printf("❌ Avatar '%s' not found\n", avatar_name);
        }
    } else {
        printf("❌ Usage: move-avatar <name> <x> <y> <z>\n");
    }
}

/**
 * @brief Handle add object command
 * @param args Command arguments
 */
void handle_add_object(const char* args) {
    if (!current_world) {
        printf("❌ No world loaded.\n");
        return;
    }

    char type_str[64];
    float x, y, z;
    ObjectType type = OBJECT_STATIC;

    if (sscanf(args, "%s %f %f %f", type_str, &x, &y, &z) == 4) {
        // Parse object type
        if (strcmp(type_str, "dynamic") == 0) type = OBJECT_DYNAMIC;
        else if (strcmp(type_str, "interactive") == 0) type = OBJECT_INTERACTIVE;
        else if (strcmp(type_str, "particle") == 0) type = OBJECT_PARTICLE;
        else if (strcmp(type_str, "light") == 0) type = OBJECT_LIGHT;
        else if (strcmp(type_str, "trigger") == 0) type = OBJECT_TRIGGER;
        else if (strcmp(type_str, "portal") == 0) type = OBJECT_PORTAL;

        Object* object = object_create(type);
        if (object) {
            Vector3 position = vector3_create(x, y, z);
            object_set_position(object, position);

            if (world_add_object(current_world, object)) {
                printf("✅ Added %s object at position (%.1f, %.1f, %.1f)\n",
                       type_str, x, y, z);
            } else {
                printf("❌ Failed to add object to world\n");
                object_destroy(object);
            }
        } else {
            printf("❌ Failed to create object\n");
        }
    } else {
        printf("❌ Usage: add-object <type> <x> <y> <z>\n");
        printf("   Types: static, dynamic, interactive, particle, light, trigger, portal\n");
    }
}

/**
 * @brief Handle simulate command
 */
void handle_simulate() {
    if (!current_world || !physics_world) {
        printf("❌ World and physics not initialized\n");
        return;
    }

    // Run physics simulation for one frame
    physics_world_update(physics_world, PHYSICS_FIXED_TIMESTEP);
    world_update(current_world, PHYSICS_FIXED_TIMESTEP);

    printf("✅ Ran physics simulation (%.3f seconds)\n", PHYSICS_FIXED_TIMESTEP);
    printf("   - Collision checks: %d\n", physics_world->collision_checks);
    printf("   - Constraints solved: %d\n", physics_world->constraints_solved);
}

/**
 * @brief Handle render command
 */
void handle_render() {
    if (!current_world) {
        printf("❌ No world loaded\n");
        return;
    }

    // Simple text-based rendering
    printf("\n🌍 World Render: %s\n", current_world->name);
    printf("===================\n");

    // Render avatars
    printf("👥 Avatars:\n");
    for (int i = 0; i < avatar_count; i++) {
        Avatar* avatar = avatars[i];
        printf("   - %s: (%.1f, %.1f, %.1f) [%s]\n",
               avatar->display_name,
               avatar->position.x, avatar->position.y, avatar->position.z,
               avatar->online ? "online" : "offline");
    }

    // Render objects
    printf("📦 Objects: %d total\n", current_world->object_count);

    printf("✅ Rendered world at %d FPS\n", current_world->fps);
}

// ============================================================================
// Main Application
// ============================================================================

/**
 * @brief Initialize the system
 */
void initialize_system() {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Allocate avatar array
    avatars = (Avatar**)malloc(max_avatars * sizeof(Avatar*));
    if (!avatars) {
        printf("❌ Failed to allocate avatar memory\n");
        exit(1);
    }

    printf("🚀 Metaverse World System initialized\n");
    printf("Type 'help' for commands or 'quit' to exit\n");
}

/**
 * @brief Cleanup system resources
 */
void cleanup_system() {
    // Destroy avatars
    for (int i = 0; i < avatar_count; i++) {
        if (avatars[i]) {
            avatar_destroy(avatars[i]);
        }
    }
    free(avatars);

    // Destroy physics world
    if (physics_world) {
        physics_world_destroy(physics_world);
    }

    // Destroy world
    if (current_world) {
        world_destroy(current_world);
    }

    printf("🧹 System cleanup completed\n");
}

/**
 * @brief Main application entry point
 */
int main(int argc, char* argv[]) {
    // Display banner
    printf("🌐 METAVERSE WORLD SYSTEM\n");
    printf("========================\n");
    printf("A comprehensive 3D virtual reality world system in pure C\n");
    printf("Features: 3D worlds, avatars, physics, networking, social features\n\n");

    // Initialize system
    initialize_system();

    // Main command loop
    char input[512];
    bool running = true;

    while (running) {
        printf("\nmetaverse> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Parse and execute command
        Command cmd = parse_command(input);

        switch (cmd.type) {
            case CMD_CREATE_WORLD:
                handle_create_world(cmd.args);
                break;

            case CMD_ADD_AVATAR:
                handle_add_avatar(cmd.args);
                break;

            case CMD_MOVE_AVATAR:
                handle_move_avatar(cmd.args);
                break;

            case CMD_ADD_OBJECT:
                handle_add_object(cmd.args);
                break;

            case CMD_SIMULATE:
                handle_simulate();
                break;

            case CMD_RENDER:
                handle_render();
                break;

            case CMD_STATUS:
                display_status();
                break;

            case CMD_QUIT:
                running = false;
                break;

            default:
                if (strcmp(input, "help") == 0) {
                    display_help();
                } else {
                    printf("❌ Unknown command: %s\n", input);
                    printf("Type 'help' for available commands\n");
                }
                break;
        }
    }

    // Cleanup and exit
    cleanup_system();
    printf("👋 Thank you for using Metaverse World System!\n");

    return 0;
}
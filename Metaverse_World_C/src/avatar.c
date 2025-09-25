/*
 * Metaverse World System - Avatar Implementation
 * User avatar management, animation, and customization
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../headers/avatar.h"
#include "../headers/world.h"

// ============================================================================
// Avatar Management Implementation
// ============================================================================

Avatar* avatar_create(const char* user_id, const char* display_name, AvatarType type) {
    Avatar* avatar = (Avatar*)malloc(sizeof(Avatar));
    if (!avatar) return NULL;

    // Initialize basic properties
    strncpy(avatar->user_id, user_id, sizeof(avatar->user_id) - 1);
    avatar->user_id[sizeof(avatar->user_id) - 1] = '\0';

    strncpy(avatar->display_name, display_name, sizeof(avatar->display_name) - 1);
    avatar->display_name[sizeof(avatar->display_name) - 1] = '\0';

    avatar->type = type;
    avatar->state = AVATAR_IDLE;

    // Initialize position and movement
    avatar->position = vector3_create(0, 0, 0);
    avatar->rotation = quaternion_identity();
    avatar->velocity = vector3_create(0, 0, 0);
    avatar->acceleration = vector3_create(0, 0, 0);

    // Physical properties
    avatar->mass = 70.0f; // Average human mass in kg
    avatar->height = 1.75f; // Average human height in meters
    avatar->grounded = true;
    avatar->flying = false;

    // Interaction
    avatar->held_object = NULL;
    avatar->interacting = false;
    avatar->look_direction = vector3_create(0, 0, 1);

    // Social features
    strcpy(avatar->status_message, "Available");
    avatar->online = true;
    avatar->last_seen = (uint64_t)time(NULL);

    // Skeletal animation (simplified)
    avatar->skeleton = skeleton_create(type);
    avatar->animations = NULL;
    avatar->animation_count = 0;
    avatar->anim_state.current_animation = NULL;
    avatar->anim_state.current_time = 0.0f;
    avatar->anim_state.blend_weight = 1.0f;
    avatar->anim_state.playing = false;
    avatar->anim_state.paused = false;

    // Customization
    avatar->customization = avatar_customization_create(type);

    // Inventory
    avatar->inventory = inventory_create(50, 50.0f); // 50 slots, 50kg capacity

    // Gesture recognition
    avatar->current_gesture.name[0] = '\0';
    avatar->current_gesture.joint_count = 0;
    avatar->current_gesture.confidence = 0.0f;
    avatar->gesture_enabled = true;

    // Network sync
    avatar->last_sync = (uint64_t)time(NULL);
    avatar->needs_sync = false;

    // Performance
    avatar->render_distance = 100.0f;
    avatar->lod_level = 0;

    return avatar;
}

void avatar_destroy(Avatar* avatar) {
    if (!avatar) return;

    // Destroy skeleton
    if (avatar->skeleton) {
        skeleton_destroy(avatar->skeleton);
    }

    // Destroy animations
    for (int i = 0; i < avatar->animation_count; i++) {
        if (avatar->animations[i]) {
            animation_destroy(avatar->animations[i]);
        }
    }
    free(avatar->animations);

    // Destroy customization
    if (avatar->customization) {
        avatar_customization_destroy(avatar->customization);
    }

    // Destroy inventory
    if (avatar->inventory) {
        inventory_destroy(avatar->inventory);
    }

    free(avatar);
}

void avatar_update(Avatar* avatar, float delta_time) {
    if (!avatar) return;

    // Update animation
    if (avatar->anim_state.playing && !avatar->anim_state.paused) {
        avatar->anim_state.current_time += delta_time * avatar->anim_state.blend_weight;

        // Loop animation if needed
        if (avatar->anim_state.current_animation &&
            avatar->anim_state.current_time >= avatar->anim_state.current_animation->duration) {
            if (avatar->anim_state.current_animation->loop) {
                avatar->anim_state.current_time = 0.0f;
            } else {
                avatar->anim_state.playing = false;
            }
        }
    }

    // Update physics (simplified)
    if (!avatar->grounded && !avatar->flying) {
        // Apply gravity
        avatar->acceleration.y -= 9.81f;
    }

    // Update velocity and position
    avatar->velocity = vector3_add(avatar->velocity,
        vector3_multiply(avatar->acceleration, delta_time));
    avatar->position = vector3_add(avatar->position,
        vector3_multiply(avatar->velocity, delta_time));

    // Reset acceleration
    avatar->acceleration = vector3_create(0, 0, 0);

    // Ground collision (simplified)
    if (avatar->position.y < 0) {
        avatar->position.y = 0;
        avatar->velocity.y = 0;
        avatar->grounded = true;
    }

    // Update gesture recognition (simplified)
    if (avatar->gesture_enabled) {
        // Simulate gesture detection based on movement
        if (vector3_magnitude(avatar->velocity) > 2.0f) {
            strcpy(avatar->current_gesture.name, "running");
            avatar->current_gesture.confidence = 0.9f;
        } else if (avatar->velocity.y > 1.0f) {
            strcpy(avatar->current_gesture.name, "jumping");
            avatar->current_gesture.confidence = 0.8f;
        } else {
            strcpy(avatar->current_gesture.name, "standing");
            avatar->current_gesture.confidence = 0.7f;
        }
    }

    avatar->last_sync = (uint64_t)time(NULL);
}

void avatar_set_position(Avatar* avatar, Vector3 position) {
    if (!avatar) return;
    avatar->position = position;
    avatar->needs_sync = true;
}

void avatar_set_rotation(Avatar* avatar, Quaternion rotation) {
    if (!avatar) return;
    avatar->rotation = quaternion_normalize(rotation);
    avatar->needs_sync = true;
}

void avatar_move(Avatar* avatar, Vector3 direction, float speed) {
    if (!avatar) return;

    // Normalize direction
    Vector3 normalized_dir = vector3_normalize(direction);

    // Apply movement
    Vector3 movement = vector3_multiply(normalized_dir, speed);
    avatar->velocity = vector3_add(avatar->velocity, movement);

    // Update state based on movement
    float speed_magnitude = vector3_magnitude(avatar->velocity);
    if (speed_magnitude > 3.0f) {
        avatar->state = AVATAR_RUNNING;
    } else if (speed_magnitude > 0.1f) {
        avatar->state = AVATAR_WALKING;
    } else {
        avatar->state = AVATAR_IDLE;
    }

    avatar->needs_sync = true;
}

void avatar_rotate(Avatar* avatar, float pitch, float yaw, float roll) {
    if (!avatar) return;

    // Create rotation quaternion from Euler angles
    Quaternion rotation = quaternion_from_euler(pitch, yaw, roll);

    // Apply rotation
    avatar->rotation = quaternion_multiply(avatar->rotation, rotation);
    avatar->rotation = quaternion_normalize(avatar->rotation);

    avatar->needs_sync = true;
}

void avatar_jump(Avatar* avatar, float force) {
    if (!avatar || (!avatar->grounded && !avatar->flying)) return;

    avatar->velocity.y += force;
    avatar->grounded = false;
    avatar->state = AVATAR_JUMPING;

    avatar->needs_sync = true;
}

void avatar_set_state(Avatar* avatar, AvatarState state) {
    if (!avatar) return;
    avatar->state = state;
    avatar->needs_sync = true;
}

void avatar_play_animation(Avatar* avatar, const char* animation_name, bool loop) {
    if (!avatar) return;

    // Find animation by name
    for (int i = 0; i < avatar->animation_count; i++) {
        if (strcmp(avatar->animations[i]->name, animation_name) == 0) {
            avatar->anim_state.current_animation = avatar->animations[i];
            avatar->anim_state.current_time = 0.0f;
            avatar->anim_state.playing = true;
            avatar->anim_state.paused = false;
            avatar->anim_state.blend_weight = 1.0f;
            return;
        }
    }
}

void avatar_stop_animation(Avatar* avatar) {
    if (!avatar) return;
    avatar->anim_state.playing = false;
    avatar->anim_state.current_animation = NULL;
}

void avatar_customize(Avatar* avatar, AvatarCustomization* customization) {
    if (!avatar || !customization) return;

    // Copy customization data
    if (avatar->customization) {
        avatar_customization_destroy(avatar->customization);
    }
    avatar->customization = avatar_customization_create(customization->type);

    // Copy properties (simplified)
    avatar->customization->height = customization->height;
    avatar->customization->build = customization->build;

    avatar->needs_sync = true;
}

bool avatar_add_to_inventory(Avatar* avatar, void* item) {
    if (!avatar || !avatar->inventory) return false;
    return inventory_add_item(avatar->inventory, item, 1.0f); // 1kg default weight
}

bool avatar_remove_from_inventory(Avatar* avatar, void* item) {
    if (!avatar || !avatar->inventory) return false;
    return inventory_remove_item(avatar->inventory, item);
}

bool avatar_detect_gesture(Avatar* avatar, Gesture* gesture) {
    if (!avatar || !gesture) return false;

    // Copy current gesture data
    *gesture = avatar->current_gesture;
    return gesture->confidence > 0.5f;
}

void avatar_perform_gesture(Avatar* avatar, const char* gesture_name) {
    if (!avatar) return;

    // Set gesture manually
    strcpy(avatar->current_gesture.name, gesture_name);
    avatar->current_gesture.confidence = 1.0f;
    avatar->current_gesture.timestamp = (uint64_t)time(NULL);

    avatar->needs_sync = true;
}

void avatar_interact_with_object(Avatar* avatar, Object* object) {
    if (!avatar || !object) return;

    // Check distance for interaction
    float distance = vector3_distance(avatar->position, object->position);
    if (distance <= 3.0f) { // 3 meter interaction range
        avatar->interacting = true;
        avatar->held_object = object;
        object_interact(object, avatar);
    }
}

// ============================================================================
// Skeleton Implementation
// ============================================================================

Skeleton* skeleton_create(AvatarType type) {
    Skeleton* skeleton = (Skeleton*)malloc(sizeof(Skeleton));
    if (!skeleton) return NULL;

    // Create basic human skeleton (simplified)
    skeleton->bone_count = 15; // Basic bone count
    skeleton->bones = (Bone*)malloc(skeleton->bone_count * sizeof(Bone));
    skeleton->bind_poses = (Matrix4x4*)malloc(skeleton->bone_count * sizeof(Matrix4x4));

    if (!skeleton->bones || !skeleton->bind_poses) {
        free(skeleton->bones);
        free(skeleton->bind_poses);
        free(skeleton);
        return NULL;
    }

    // Initialize basic bone structure
    const char* bone_names[] = {
        "root", "spine", "chest", "neck", "head",
        "left_shoulder", "left_arm", "left_forearm", "left_hand",
        "right_shoulder", "right_arm", "right_forearm", "right_hand",
        "left_leg", "right_leg"
    };

    for (int i = 0; i < skeleton->bone_count; i++) {
        strcpy(skeleton->bones[i].name, bone_names[i]);
        skeleton->bones[i].position = vector3_create(0, 0, 0);
        skeleton->bones[i].rotation = quaternion_identity();
        skeleton->bones[i].scale = vector3_create(1, 1, 1);
        skeleton->bones[i].parent_index = (i == 0) ? -1 : 0; // Simple hierarchy

        // Identity bind pose
        skeleton->bind_poses[i].m[0][0] = 1; skeleton->bind_poses[i].m[0][1] = 0; skeleton->bind_poses[i].m[0][2] = 0; skeleton->bind_poses[i].m[0][3] = 0;
        skeleton->bind_poses[i].m[1][0] = 0; skeleton->bind_poses[i].m[1][1] = 1; skeleton->bind_poses[i].m[1][2] = 0; skeleton->bind_poses[i].m[1][3] = 0;
        skeleton->bind_poses[i].m[2][0] = 0; skeleton->bind_poses[i].m[2][1] = 0; skeleton->bind_poses[i].m[2][2] = 1; skeleton->bind_poses[i].m[2][3] = 0;
        skeleton->bind_poses[i].m[3][0] = 0; skeleton->bind_poses[i].m[3][1] = 0; skeleton->bind_poses[i].m[3][2] = 0; skeleton->bind_poses[i].m[3][3] = 1;
    }

    return skeleton;
}

void skeleton_destroy(Skeleton* skeleton) {
    if (!skeleton) return;

    free(skeleton->bones);
    free(skeleton->bind_poses);
    free(skeleton);
}

Bone* skeleton_get_bone(Skeleton* skeleton, const char* name) {
    if (!skeleton || !name) return NULL;

    for (int i = 0; i < skeleton->bone_count; i++) {
        if (strcmp(skeleton->bones[i].name, name) == 0) {
            return &skeleton->bones[i];
        }
    }

    return NULL;
}

void skeleton_calculate_transforms(Skeleton* skeleton, Matrix4x4* bone_transforms) {
    if (!skeleton || !bone_transforms) return;

    // Simplified: just copy bind poses
    for (int i = 0; i < skeleton->bone_count; i++) {
        bone_transforms[i] = skeleton->bind_poses[i];
    }
}

// ============================================================================
// Customization Implementation
// ============================================================================

AvatarCustomization* avatar_customization_create(AvatarType type) {
    AvatarCustomization* customization = (AvatarCustomization*)malloc(sizeof(AvatarCustomization));
    if (!customization) return NULL;

    customization->type = type;
    customization->height = 1.75f;
    customization->build = 0.5f; // Medium build

    // Default colors (RGBA)
    customization->skin_color = 0xFFDEB887;    // Tan
    customization->hair_color = 0xFF8B4513;    // Brown
    customization->eye_color = 0xFF000080;     // Blue

    // Default models
    strcpy(customization->face_model, "default_face.obj");
    strcpy(customization->hair_model, "default_hair.obj");
    strcpy(customization->body_model, "default_body.obj");

    // No clothing initially
    customization->clothing_items[0] = NULL;
    customization->clothing_count = 0;

    customization->accessories[0] = NULL;
    customization->accessory_count = 0;

    return customization;
}

void avatar_customization_destroy(AvatarCustomization* customization) {
    if (!customization) return;

    // Free clothing and accessory strings
    for (int i = 0; i < customization->clothing_count; i++) {
        free(customization->clothing_items[i]);
    }

    for (int i = 0; i < customization->accessory_count; i++) {
        free(customization->accessories[i]);
    }

    free(customization);
}

void avatar_customization_set_color(AvatarCustomization* customization,
                                   const char* color_type, uint32_t color) {
    if (!customization || !color_type) return;

    if (strcmp(color_type, "skin") == 0) {
        customization->skin_color = color;
    } else if (strcmp(color_type, "hair") == 0) {
        customization->hair_color = color;
    } else if (strcmp(color_type, "eye") == 0) {
        customization->eye_color = color;
    }
}

bool avatar_customization_add_clothing(AvatarCustomization* customization,
                                      const char* item_filename) {
    if (!customization || !item_filename ||
        customization->clothing_count >= 16) {
        return false;
    }

    customization->clothing_items[customization->clothing_count] =
        strdup(item_filename);
    if (!customization->clothing_items[customization->clothing_count]) {
        return false;
    }

    customization->clothing_count++;
    return true;
}

bool avatar_customization_add_accessory(AvatarCustomization* customization,
                                       const char* accessory_filename) {
    if (!customization || !accessory_filename ||
        customization->accessory_count >= 8) {
        return false;
    }

    customization->accessories[customization->accessory_count] =
        strdup(accessory_filename);
    if (!customization->accessories[customization->accessory_count]) {
        return false;
    }

    customization->accessory_count++;
    return true;
}

// ============================================================================
// Inventory Implementation
// ============================================================================

Inventory* inventory_create(int max_items, float max_weight) {
    Inventory* inventory = (Inventory*)malloc(sizeof(Inventory));
    if (!inventory) return NULL;

    inventory->items = (void**)malloc(max_items * sizeof(void*));
    if (!inventory->items) {
        free(inventory);
        return NULL;
    }

    inventory->item_count = 0;
    inventory->max_items = max_items;
    inventory->total_weight = 0.0f;
    inventory->max_weight = max_weight;

    // Initialize all slots to NULL
    for (int i = 0; i < max_items; i++) {
        inventory->items[i] = NULL;
    }

    return inventory;
}

void inventory_destroy(Inventory* inventory) {
    if (!inventory) return;

    free(inventory->items);
    free(inventory);
}

bool inventory_add_item(Inventory* inventory, void* item, float weight) {
    if (!inventory || !item || inventory->item_count >= inventory->max_items) {
        return false;
    }

    if (inventory->total_weight + weight > inventory->max_weight) {
        return false;
    }

    // Find empty slot
    for (int i = 0; i < inventory->max_items; i++) {
        if (inventory->items[i] == NULL) {
            inventory->items[i] = item;
            inventory->item_count++;
            inventory->total_weight += weight;
            return true;
        }
    }

    return false;
}

bool inventory_remove_item(Inventory* inventory, void* item) {
    if (!inventory || !item) return false;

    for (int i = 0; i < inventory->max_items; i++) {
        if (inventory->items[i] == item) {
            inventory->items[i] = NULL;
            inventory->item_count--;
            // Note: weight tracking would need item-specific weights
            return true;
        }
    }

    return false;
}

bool inventory_can_hold(Inventory* inventory, float weight) {
    if (!inventory) return false;
    return inventory->total_weight + weight <= inventory->max_weight &&
           inventory->item_count < inventory->max_items;
}

float inventory_get_total_weight(Inventory* inventory) {
    return inventory ? inventory->total_weight : 0.0f;
}

// ============================================================================
// Animation Implementation (Stub)
// ============================================================================

Animation* animation_create(const char* name, float duration) {
    Animation* animation = (Animation*)malloc(sizeof(Animation));
    if (!animation) return NULL;

    strncpy(animation->name, name, sizeof(animation->name) - 1);
    animation->name[sizeof(animation->name) - 1] = '\0';

    animation->keyframes = NULL;
    animation->keyframe_count = 0;
    animation->duration = duration;
    animation->loop = false;
    animation->speed = 1.0f;

    return animation;
}

void animation_destroy(Animation* animation) {
    if (!animation) return;

    if (animation->keyframes) {
        for (int i = 0; i < animation->keyframe_count; i++) {
            free(animation->keyframes[i].positions);
            free(animation->keyframes[i].rotations);
            free(animation->keyframes[i].scales);
        }
        free(animation->keyframes);
    }

    free(animation);
}

void animation_sample_pose(Animation* animation, float time,
                          Vector3* positions, Quaternion* rotations,
                          Vector3* scales) {
    // Simplified: return identity poses
    if (positions) *positions = vector3_create(0, 0, 0);
    if (rotations) *rotations = quaternion_identity();
    if (scales) *scales = vector3_create(1, 1, 1);
}

// ============================================================================
// Utility Functions
// ============================================================================

bool avatar_save_to_file(Avatar* avatar, const char* filename) {
    // Simplified: would implement full serialization
    FILE* file = fopen(filename, "w");
    if (!file) return false;

    fprintf(file, "AVATAR %s %s %d\n", avatar->user_id, avatar->display_name, avatar->type);
    fprintf(file, "POSITION %.2f %.2f %.2f\n", avatar->position.x, avatar->position.y, avatar->position.z);
    fprintf(file, "ONLINE %d\n", avatar->online);

    fclose(file);
    return true;
}

Avatar* avatar_load_from_file(const char* filename) {
    // Simplified: would implement full deserialization
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char line[256];
    char user_id[64], display_name[256];
    int type;

    if (fgets(line, sizeof(line), file) &&
        sscanf(line, "AVATAR %s %s %d", user_id, display_name, &type) == 3) {
        Avatar* avatar = avatar_create(user_id, display_name, (AvatarType)type);
        fclose(file);
        return avatar;
    }

    fclose(file);
    return NULL;
}

void avatar_get_statistics(Avatar* avatar, void* stats) {
    // Simplified statistics
    if (stats) {
        // Would fill statistics structure
    }
}

bool avatar_check_world_collision(Avatar* avatar, World* world) {
    // Simplified collision check
    if (!avatar || !world) return false;

    // Check if avatar is below terrain
    float terrain_height = world_get_terrain_height(world, avatar->position.x, avatar->position.z);
    return avatar->position.y < terrain_height;
}

void avatar_network_sync(Avatar* avatar, void* network_data) {
    if (!avatar) return;

    // Simplified network synchronization
    avatar->last_sync = (uint64_t)time(NULL);
    avatar->needs_sync = false;
}
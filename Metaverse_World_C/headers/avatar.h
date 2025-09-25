/*
 * Metaverse World System - Avatar Management Header
 * Defines structures and functions for user avatars,
 * animations, and character customization
 */

#ifndef METAVERSE_AVATAR_H
#define METAVERSE_AVATAR_H

#include <stdint.h>
#include <stdbool.h>
#include "world.h"

// Forward declarations
typedef struct Animation Animation;
typedef struct AvatarCustomization AvatarCustomization;
typedef struct Inventory Inventory;
typedef struct Gesture Gesture;

// ============================================================================
// Avatar Structures
// ============================================================================

/**
 * @brief Avatar body types
 */
typedef enum {
    AVATAR_HUMAN,                   // Human-like avatar
    AVATAR_ROBOT,                   // Robotic avatar
    AVATAR_ANIMAL,                  // Animal avatar
    AVATAR_FANTASY,                 // Fantasy creature
    AVATAR_ABSTRACT                 // Abstract geometric avatar
} AvatarType;

/**
 * @brief Avatar states
 */
typedef enum {
    AVATAR_IDLE,                    // Standing still
    AVATAR_WALKING,                 // Walking animation
    AVATAR_RUNNING,                 // Running animation
    AVATAR_JUMPING,                 // Jumping animation
    AVATAR_FLYING,                  // Flying animation
    AVATAR_SWIMMING,                // Swimming animation
    AVATAR_SITTING,                 // Sitting pose
    AVATAR_DANCING,                 // Dancing animation
    AVATAR_EMOTING                  // Emotional expression
} AvatarState;

/**
 * @brief Skeletal bone structure
 */
typedef struct {
    char name[64];                  // Bone name
    Vector3 position;               // Bone position
    Quaternion rotation;            // Bone rotation
    Vector3 scale;                  // Bone scale
    int parent_index;               // Parent bone index (-1 for root)
} Bone;

/**
 * @brief Skeletal structure for animation
 */
typedef struct {
    Bone* bones;                    // Array of bones
    int bone_count;                 // Number of bones
    Matrix4x4* bind_poses;          // Inverse bind pose matrices
} Skeleton;

/**
 * @brief Animation keyframe
 */
typedef struct {
    float time;                     // Time in seconds
    Vector3* positions;             // Bone positions at this keyframe
    Quaternion* rotations;          // Bone rotations at this keyframe
    Vector3* scales;                // Bone scales at this keyframe
} Keyframe;

/**
 * @brief Animation clip
 */
struct Animation {
    char name[128];                 // Animation name
    Keyframe* keyframes;            // Array of keyframes
    int keyframe_count;             // Number of keyframes
    float duration;                 // Animation duration in seconds
    bool loop;                      // Whether animation loops
    float speed;                    // Playback speed multiplier
};

/**
 * @brief Animation state
 */
typedef struct {
    Animation* current_animation;    // Currently playing animation
    float current_time;             // Current playback time
    float blend_weight;             // Blend weight for transitions
    bool playing;                   // Whether animation is playing
    bool paused;                    // Whether animation is paused
} AnimationState;

/**
 * @brief Avatar appearance customization
 */
struct AvatarCustomization {
    // Body characteristics
    AvatarType type;                // Avatar type
    float height;                   // Avatar height in meters
    float build;                    // Body build (slender to muscular)

    // Colors
    uint32_t skin_color;            // Skin color (RGBA)
    uint32_t hair_color;            // Hair color (RGBA)
    uint32_t eye_color;             // Eye color (RGBA)

    // Features
    char face_model[256];           // Face model filename
    char hair_model[256];           // Hair model filename
    char body_model[256];           // Body model filename

    // Clothing and accessories
    char* clothing_items[16];       // Array of clothing item filenames
    int clothing_count;             // Number of clothing items

    char* accessories[8];           // Array of accessory filenames
    int accessory_count;            // Number of accessories
};

/**
 * @brief Avatar inventory system
 */
struct Inventory {
    void** items;                   // Array of inventory items
    int item_count;                 // Number of items
    int max_items;                  // Maximum inventory capacity
    float total_weight;             // Total weight of all items
    float max_weight;               // Maximum carry weight
};

/**
 * @brief Gesture recognition data
 */
struct Gesture {
    char name[64];                  // Gesture name
    Vector3* joint_positions;       // Positions of body joints
    int joint_count;                // Number of joints tracked
    float confidence;               // Recognition confidence (0-1)
    uint64_t timestamp;             // When gesture was detected
};

/**
 * @brief Avatar main structure
 */
typedef struct Avatar {
    char user_id[64];               // Unique user identifier
    char display_name[256];         // Display name

    // Physical properties
    Vector3 position;               // Current position in world
    Quaternion rotation;            // Current rotation
    Vector3 velocity;               // Movement velocity
    Vector3 acceleration;           // Movement acceleration

    // Avatar data
    AvatarType type;                // Avatar type
    AvatarState state;              // Current state
    AvatarCustomization* customization; // Appearance customization

    // Skeletal animation
    Skeleton* skeleton;             // Avatar skeleton
    AnimationState anim_state;      // Current animation state
    Animation** animations;         // Available animations
    int animation_count;            // Number of animations

    // Physics properties
    float mass;                     // Avatar mass
    float height;                   // Avatar height
    bool grounded;                  // Whether avatar is on ground
    bool flying;                    // Whether avatar is flying

    // Interaction
    Object* held_object;            // Currently held object
    bool interacting;               // Whether avatar is interacting
    Vector3 look_direction;         // Direction avatar is looking

    // Social features
    char status_message[256];       // Status message
    bool online;                    // Whether user is online
    uint64_t last_seen;             // Last activity timestamp

    // Inventory
    Inventory* inventory;           // Avatar inventory

    // Gesture recognition
    Gesture current_gesture;        // Currently detected gesture
    bool gesture_enabled;           // Whether gesture recognition is enabled

    // Network synchronization
    uint64_t last_sync;             // Last synchronization timestamp
    bool needs_sync;                // Whether avatar needs synchronization

    // Performance metrics
    float render_distance;          // Maximum render distance
    int lod_level;                  // Level of detail for rendering
} Avatar;

// ============================================================================
// Avatar Management Functions
// ============================================================================

/**
 * @brief Create a new avatar
 * @param user_id Unique user identifier
 * @param display_name Display name
 * @param type Avatar type
 * @return Pointer to created avatar or NULL on failure
 */
Avatar* avatar_create(const char* user_id, const char* display_name, AvatarType type);

/**
 * @brief Destroy an avatar
 * @param avatar Avatar to destroy
 */
void avatar_destroy(Avatar* avatar);

/**
 * @brief Update avatar state
 * @param avatar Avatar to update
 * @param delta_time Time elapsed since last update
 */
void avatar_update(Avatar* avatar, float delta_time);

/**
 * @brief Set avatar position
 * @param avatar Target avatar
 * @param position New position
 */
void avatar_set_position(Avatar* avatar, Vector3 position);

/**
 * @brief Set avatar rotation
 * @param avatar Target avatar
 * @param rotation New rotation quaternion
 */
void avatar_set_rotation(Avatar* avatar, Quaternion rotation);

/**
 * @brief Move avatar in direction
 * @param avatar Target avatar
 * @param direction Movement direction
 * @param speed Movement speed
 */
void avatar_move(Avatar* avatar, Vector3 direction, float speed);

/**
 * @brief Rotate avatar
 * @param avatar Target avatar
 * @param pitch Pitch rotation in degrees
 * @param yaw Yaw rotation in degrees
 * @param roll Roll rotation in degrees
 */
void avatar_rotate(Avatar* avatar, float pitch, float yaw, float roll);

/**
 * @brief Make avatar jump
 * @param avatar Target avatar
 * @param force Jump force
 */
void avatar_jump(Avatar* avatar, float force);

/**
 * @brief Set avatar state
 * @param avatar Target avatar
 * @param state New avatar state
 */
void avatar_set_state(Avatar* avatar, AvatarState state);

/**
 * @brief Play animation on avatar
 * @param avatar Target avatar
 * @param animation_name Name of animation to play
 * @param loop Whether animation should loop
 */
void avatar_play_animation(Avatar* avatar, const char* animation_name, bool loop);

/**
 * @brief Stop current animation
 * @param avatar Target avatar
 */
void avatar_stop_animation(Avatar* avatar);

/**
 * @brief Customize avatar appearance
 * @param avatar Target avatar
 * @param customization New customization data
 */
void avatar_customize(Avatar* avatar, AvatarCustomization* customization);

/**
 * @brief Add item to avatar inventory
 * @param avatar Target avatar
 * @param item Item to add
 * @return Success status
 */
bool avatar_add_to_inventory(Avatar* avatar, void* item);

/**
 * @brief Remove item from avatar inventory
 * @param avatar Target avatar
 * @param item Item to remove
 * @return Success status
 */
bool avatar_remove_from_inventory(Avatar* avatar, void* item);

/**
 * @brief Detect gesture from avatar movement
 * @param avatar Target avatar
 * @param gesture Detected gesture output
 * @return True if gesture detected
 */
bool avatar_detect_gesture(Avatar* avatar, Gesture* gesture);

/**
 * @brief Perform gesture animation
 * @param avatar Target avatar
 * @param gesture_name Name of gesture to perform
 */
void avatar_perform_gesture(Avatar* avatar, const char* gesture_name);

/**
 * @brief Interact with object
 * @param avatar Avatar performing interaction
 * @param object Object to interact with
 */
void avatar_interact_with_object(Avatar* avatar, Object* object);

// ============================================================================
// Animation System Functions
// ============================================================================

/**
 * @brief Create animation from file
 * @param filename Animation file path
 * @return Pointer to loaded animation or NULL on failure
 */
Animation* animation_load_from_file(const char* filename);

/**
 * @brief Create animation programmatically
 * @param name Animation name
 * @param duration Animation duration in seconds
 * @return Pointer to created animation or NULL on failure
 */
Animation* animation_create(const char* name, float duration);

/**
 * @brief Destroy animation
 * @param animation Animation to destroy
 */
void animation_destroy(Animation* animation);

/**
 * @brief Add keyframe to animation
 * @param animation Target animation
 * @param time Keyframe time
 * @param positions Bone positions at keyframe
 * @param rotations Bone rotations at keyframe
 * @param scales Bone scales at keyframe
 * @param bone_count Number of bones
 */
void animation_add_keyframe(Animation* animation, float time,
                           Vector3* positions, Quaternion* rotations,
                           Vector3* scales, int bone_count);

/**
 * @brief Get animation pose at time
 * @param animation Source animation
 * @param time Time to sample
 * @param positions Output bone positions
 * @param rotations Output bone rotations
 * @param scales Output bone scales
 */
void animation_sample_pose(Animation* animation, float time,
                          Vector3* positions, Quaternion* rotations,
                          Vector3* scales);

// ============================================================================
// Skeleton Functions
// ============================================================================

/**
 * @brief Create skeleton for avatar type
 * @param type Avatar type
 * @return Pointer to created skeleton or NULL on failure
 */
Skeleton* skeleton_create(AvatarType type);

/**
 * @brief Destroy skeleton
 * @param skeleton Skeleton to destroy
 */
void skeleton_destroy(Skeleton* skeleton);

/**
 * @brief Get bone by name
 * @param skeleton Target skeleton
 * @param name Bone name
 * @return Pointer to bone or NULL if not found
 */
Bone* skeleton_get_bone(Skeleton* skeleton, const char* name);

/**
 * @brief Calculate bone transforms
 * @param skeleton Target skeleton
 * @param bone_transforms Output bone transformation matrices
 */
void skeleton_calculate_transforms(Skeleton* skeleton, Matrix4x4* bone_transforms);

// ============================================================================
// Customization Functions
// ============================================================================

/**
 * @brief Create default customization for avatar type
 * @param type Avatar type
 * @return Pointer to created customization or NULL on failure
 */
AvatarCustomization* avatar_customization_create(AvatarType type);

/**
 * @brief Destroy customization
 * @param customization Customization to destroy
 */
void avatar_customization_destroy(AvatarCustomization* customization);

/**
 * @brief Set customization color
 * @param customization Target customization
 * @param color_type Type of color to set
 * @param color Color value (RGBA)
 */
void avatar_customization_set_color(AvatarCustomization* customization,
                                   const char* color_type, uint32_t color);

/**
 * @brief Add clothing item to customization
 * @param customization Target customization
 * @param item_filename Clothing item filename
 * @return Success status
 */
bool avatar_customization_add_clothing(AvatarCustomization* customization,
                                      const char* item_filename);

/**
 * @brief Add accessory to customization
 * @param customization Target customization
 * @param accessory_filename Accessory filename
 * @return Success status
 */
bool avatar_customization_add_accessory(AvatarCustomization* customization,
                                       const char* accessory_filename);

// ============================================================================
// Inventory Functions
// ============================================================================

/**
 * @brief Create inventory for avatar
 * @param max_items Maximum number of items
 * @param max_weight Maximum carry weight
 * @return Pointer to created inventory or NULL on failure
 */
Inventory* inventory_create(int max_items, float max_weight);

/**
 * @brief Destroy inventory
 * @param inventory Inventory to destroy
 */
void inventory_destroy(Inventory* inventory);

/**
 * @brief Add item to inventory
 * @param inventory Target inventory
 * @param item Item to add
 * @param weight Item weight
 * @return Success status
 */
bool inventory_add_item(Inventory* inventory, void* item, float weight);

/**
 * @brief Remove item from inventory
 * @param inventory Target inventory
 * @param item Item to remove
 * @return Success status
 */
bool inventory_remove_item(Inventory* inventory, void* item);

/**
 * @brief Check if inventory can hold item
 * @param inventory Target inventory
 * @param weight Item weight
 * @return True if item can be added
 */
bool inventory_can_hold(Inventory* inventory, float weight);

/**
 * @brief Get inventory weight
 * @param inventory Target inventory
 * @return Total weight of all items
 */
float inventory_get_total_weight(Inventory* inventory);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Save avatar to file
 * @param avatar Avatar to save
 * @param filename Output filename
 * @return Success status
 */
bool avatar_save_to_file(Avatar* avatar, const char* filename);

/**
 * @brief Load avatar from file
 * @param filename Input filename
 * @return Pointer to loaded avatar or NULL on failure
 */
Avatar* avatar_load_from_file(const char* filename);

/**
 * @brief Get avatar statistics
 * @param avatar Target avatar
 * @param stats Output statistics structure
 */
void avatar_get_statistics(Avatar* avatar, void* stats);

/**
 * @brief Check avatar collision with world
 * @param avatar Target avatar
 * @param world World to check against
 * @return True if collision detected
 */
bool avatar_check_world_collision(Avatar* avatar, World* world);

/**
 * @brief Synchronize avatar across network
 * @param avatar Avatar to synchronize
 * @param network_data Network synchronization data
 */
void avatar_network_sync(Avatar* avatar, void* network_data);

#endif // METAVERSE_AVATAR_H
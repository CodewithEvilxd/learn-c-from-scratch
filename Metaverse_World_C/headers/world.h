/*
 * Metaverse World System - 3D World Management Header
 * Defines structures and functions for 3D world representation,
 * spatial partitioning, and world state management
 */

#ifndef METAVERSE_WORLD_H
#define METAVERSE_WORLD_H

#include <stdint.h>
#include <stdbool.h>

// Forward declarations
typedef struct Vector3 Vector3;
typedef struct Quaternion Quaternion;
typedef struct Matrix4x4 Matrix4x4;
typedef struct Object Object;
typedef struct Avatar Avatar;
typedef struct WorldChunk WorldChunk;

// ============================================================================
// 3D Mathematics Structures
// ============================================================================

/**
 * @brief 3D Vector structure for spatial coordinates
 */
struct Vector3 {
    float x, y, z;
};

/**
 * @brief Quaternion structure for 3D rotations
 */
struct Quaternion {
    float w, x, y, z;
};

/**
 * @brief 4x4 Matrix for transformations
 */
struct Matrix4x4 {
    float m[4][4];
};

// ============================================================================
// World and Spatial Structures
// ============================================================================

/**
 * @brief World chunk for spatial partitioning
 */
struct WorldChunk {
    int chunk_x, chunk_z;           // Chunk coordinates
    Vector3 position;               // World position
    Object** objects;               // Objects in this chunk
    int object_count;               // Number of objects
    int max_objects;                // Maximum objects per chunk
    bool loaded;                    // Whether chunk is loaded
    uint64_t last_accessed;         // Timestamp of last access
};

/**
 * @brief Terrain heightmap data
 */
typedef struct {
    int width, height;              // Terrain dimensions
    float* heights;                 // Height values
    float min_height, max_height;   // Height range
} Terrain;

/**
 * @brief World boundary and limits
 */
typedef struct {
    Vector3 min_bounds;             // Minimum world coordinates
    Vector3 max_bounds;             // Maximum world coordinates
    float world_scale;              // World scaling factor
} WorldBounds;

/**
 * @brief Main world structure
 */
typedef struct {
    char name[256];                 // World name
    char description[1024];         // World description

    // Spatial information
    WorldBounds bounds;             // World boundaries
    int chunk_size;                 // Size of each chunk
    WorldChunk*** chunks;           // 3D array of chunk pointers
    int chunks_x, chunks_z;         // Number of chunks in each direction

    // Terrain and environment
    Terrain* terrain;               // World terrain
    float gravity;                  // Gravity strength
    Vector3 wind_direction;         // Wind direction vector
    float wind_strength;            // Wind strength

    // Objects and entities
    Object** objects;               // All world objects
    int object_count;               // Number of objects
    int max_objects;                // Maximum objects

    Avatar** avatars;               // Active avatars
    int avatar_count;               // Number of active avatars
    int max_avatars;                // Maximum avatars

    // World state
    uint64_t world_time;            // World simulation time
    bool paused;                    // Whether world is paused
    float time_scale;               // Time scaling factor

    // Performance metrics
    int fps;                        // Current frames per second
    float frame_time;               // Time per frame in milliseconds
    int triangles_rendered;         // Number of triangles rendered
} World;

// ============================================================================
// Object System
// ============================================================================

/**
 * @brief Object types in the world
 */
typedef enum {
    OBJECT_STATIC,                  // Non-moving objects (buildings, trees)
    OBJECT_DYNAMIC,                 // Movable objects (vehicles, furniture)
    OBJECT_INTERACTIVE,             // Objects that can be interacted with
    OBJECT_AVATAR,                  // User avatars
    OBJECT_PARTICLE,                // Particle effects
    OBJECT_LIGHT,                   // Light sources
    OBJECT_TRIGGER,                 // Trigger zones
    OBJECT_PORTAL                   // Teleportation portals
} ObjectType;

/**
 * @brief Object physics properties
 */
typedef struct {
    float mass;                     // Object mass
    Vector3 velocity;               // Current velocity
    Vector3 acceleration;           // Current acceleration
    bool kinematic;                 // Whether object is kinematic
    float friction;                 // Friction coefficient
    float restitution;              // Bounciness factor
} PhysicsProperties;

/**
 * @brief World object structure
 */
struct Object {
    char id[64];                    // Unique object identifier
    char name[256];                 // Human-readable name

    ObjectType type;                // Object type
    Vector3 position;               // World position
    Quaternion rotation;            // Object rotation
    Vector3 scale;                  // Object scale

    // Visual properties
    char model_path[512];           // 3D model file path
    char texture_path[512];         // Texture file path
    bool visible;                   // Whether object is visible

    // Physics
    PhysicsProperties physics;      // Physics properties
    bool has_collision;             // Whether object has collision
    float bounding_radius;          // Collision bounding sphere radius

    // Interaction
    bool interactive;               // Whether object can be interacted with
    void* user_data;                // Custom user data
    void (*on_interact)(struct Object*, Avatar*); // Interaction callback

    // World linkage
    WorldChunk* chunk;              // Chunk containing this object
    uint64_t last_updated;          // Last update timestamp
};

// ============================================================================
// World Management Functions
// ============================================================================

/**
 * @brief Create a new world instance
 * @param name World name
 * @param width World width in units
 * @param height World height in units
 * @return Pointer to created world or NULL on failure
 */
World* world_create(const char* name, float width, float height);

/**
 * @brief Destroy a world instance
 * @param world World to destroy
 */
void world_destroy(World* world);

/**
 * @brief Update world simulation
 * @param world World to update
 * @param delta_time Time elapsed since last update
 */
void world_update(World* world, float delta_time);

/**
 * @brief Render the world (software rendering)
 * @param world World to render
 * @param camera_position Camera position
 * @param camera_rotation Camera rotation
 * @param viewport_width Viewport width
 * @param viewport_height Viewport height
 */
void world_render(World* world, Vector3 camera_position, Quaternion camera_rotation,
                 int viewport_width, int viewport_height);

/**
 * @brief Add object to world
 * @param world Target world
 * @param object Object to add
 * @return Success status
 */
bool world_add_object(World* world, Object* object);

/**
 * @brief Remove object from world
 * @param world Target world
 * @param object Object to remove
 * @return Success status
 */
bool world_remove_object(World* world, Object* object);

/**
 * @brief Find object by ID
 * @param world World to search
 * @param id Object ID to find
 * @return Pointer to object or NULL if not found
 */
Object* world_find_object(World* world, const char* id);

/**
 * @brief Get objects within radius
 * @param world World to search
 * @param center Center position
 * @param radius Search radius
 * @param objects Output array for found objects
 * @param max_objects Maximum objects to return
 * @return Number of objects found
 */
int world_get_objects_in_radius(World* world, Vector3 center, float radius,
                               Object** objects, int max_objects);

/**
 * @brief Load world chunk at coordinates
 * @param world Target world
 * @param chunk_x Chunk X coordinate
 * @param chunk_z Chunk Z coordinate
 * @return Pointer to loaded chunk or NULL on failure
 */
WorldChunk* world_load_chunk(World* world, int chunk_x, int chunk_z);

/**
 * @brief Unload world chunk
 * @param world Target world
 * @param chunk Chunk to unload
 */
void world_unload_chunk(World* world, WorldChunk* chunk);

/**
 * @brief Get terrain height at position
 * @param world World containing terrain
 * @param x X coordinate
 * @param z Z coordinate
 * @return Terrain height at position
 */
float world_get_terrain_height(World* world, float x, float z);

/**
 * @brief Check line of sight between two points
 * @param world World to check
 * @param start Start position
 * @param end End position
 * @return True if line of sight exists
 */
bool world_line_of_sight(World* world, Vector3 start, Vector3 end);

/**
 * @brief Perform raycast against world
 * @param world World to raycast
 * @param origin Ray origin
 * @param direction Ray direction (normalized)
 * @param max_distance Maximum ray distance
 * @param hit_info Output hit information
 * @return True if ray hit something
 */
bool world_raycast(World* world, Vector3 origin, Vector3 direction,
                  float max_distance, void* hit_info);

// ============================================================================
// Object Management Functions
// ============================================================================

/**
 * @brief Create a new object
 * @param type Object type
 * @return Pointer to created object or NULL on failure
 */
Object* object_create(ObjectType type);

/**
 * @brief Destroy an object
 * @param object Object to destroy
 */
void object_destroy(Object* object);

/**
 * @brief Set object position
 * @param object Target object
 * @param position New position
 */
void object_set_position(Object* object, Vector3 position);

/**
 * @brief Set object rotation
 * @param object Target object
 * @param rotation New rotation quaternion
 */
void object_set_rotation(Object* object, Quaternion rotation);

/**
 * @brief Set object scale
 * @param object Target object
 * @param scale New scale
 */
void object_set_scale(Object* object, Vector3 scale);

/**
 * @brief Move object by offset
 * @param object Target object
 * @param offset Movement offset
 */
void object_move(Object* object, Vector3 offset);

/**
 * @brief Rotate object by quaternion
 * @param object Target object
 * @param rotation Rotation quaternion
 */
void object_rotate(Object* object, Quaternion rotation);

/**
 * @brief Check collision between two objects
 * @param obj1 First object
 * @param obj2 Second object
 * @return True if objects collide
 */
bool object_check_collision(Object* obj1, Object* obj2);

/**
 * @brief Handle object interaction
 * @param object Object being interacted with
 * @param avatar Avatar performing interaction
 */
void object_interact(Object* object, Avatar* avatar);

// ============================================================================
// Vector Mathematics Functions
// ============================================================================

/**
 * @brief Create a 3D vector
 * @param x X component
 * @param y Y component
 * @param z Z component
 * @return Created vector
 */
Vector3 vector3_create(float x, float y, float z);

/**
 * @brief Add two vectors
 * @param a First vector
 * @param b Second vector
 * @return Result vector
 */
Vector3 vector3_add(Vector3 a, Vector3 b);

/**
 * @brief Subtract two vectors
 * @param a First vector
 * @param b Second vector
 * @return Result vector
 */
Vector3 vector3_subtract(Vector3 a, Vector3 b);

/**
 * @brief Multiply vector by scalar
 * @param v Vector
 * @param scalar Scalar value
 * @return Result vector
 */
Vector3 vector3_multiply(Vector3 v, float scalar);

/**
 * @brief Calculate dot product
 * @param a First vector
 * @param b Second vector
 * @return Dot product
 */
float vector3_dot(Vector3 a, Vector3 b);

/**
 * @brief Calculate cross product
 * @param a First vector
 * @param b Second vector
 * @return Cross product vector
 */
Vector3 vector3_cross(Vector3 a, Vector3 b);

/**
 * @brief Calculate vector magnitude
 * @param v Vector
 * @return Magnitude
 */
float vector3_magnitude(Vector3 v);

/**
 * @brief Normalize vector
 * @param v Vector to normalize
 * @return Normalized vector
 */
Vector3 vector3_normalize(Vector3 v);

/**
 * @brief Calculate distance between two points
 * @param a First point
 * @param b Second point
 * @return Distance
 */
float vector3_distance(Vector3 a, Vector3 b);

// ============================================================================
// Quaternion Functions
// ============================================================================

/**
 * @brief Create identity quaternion
 * @return Identity quaternion
 */
Quaternion quaternion_identity(void);

/**
 * @brief Create quaternion from Euler angles
 * @param pitch Pitch angle in degrees
 * @param yaw Yaw angle in degrees
 * @param roll Roll angle in degrees
 * @return Created quaternion
 */
Quaternion quaternion_from_euler(float pitch, float yaw, float roll);

/**
 * @brief Multiply two quaternions
 * @param a First quaternion
 * @param b Second quaternion
 * @return Result quaternion
 */
Quaternion quaternion_multiply(Quaternion a, Quaternion b);

/**
 * @brief Normalize quaternion
 * @param q Quaternion to normalize
 * @return Normalized quaternion
 */
Quaternion quaternion_normalize(Quaternion q);

/**
 * @brief Convert quaternion to Euler angles
 * @param q Quaternion
 * @param pitch Output pitch angle
 * @param yaw Output yaw angle
 * @param roll Output roll angle
 */
void quaternion_to_euler(Quaternion q, float* pitch, float* yaw, float* roll);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Generate unique object ID
 * @return Unique ID string
 */
const char* world_generate_object_id(void);

/**
 * @brief Save world to file
 * @param world World to save
 * @param filename Output filename
 * @return Success status
 */
bool world_save_to_file(World* world, const char* filename);

/**
 * @brief Load world from file
 * @param filename Input filename
 * @return Pointer to loaded world or NULL on failure
 */
World* world_load_from_file(const char* filename);

/**
 * @brief Get world statistics
 * @param world Target world
 * @param stats Output statistics structure
 */
void world_get_statistics(World* world, void* stats);

#endif // METAVERSE_WORLD_H
/*
 * Metaverse World System - 3D World Implementation
 * Core world management, spatial partitioning, and object handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../headers/world.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ============================================================================
// Vector3 Mathematics Implementation
// ============================================================================

Vector3 vector3_create(float x, float y, float z) {
    Vector3 v = {x, y, z};
    return v;
}

Vector3 vector3_add(Vector3 a, Vector3 b) {
    return vector3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 vector3_subtract(Vector3 a, Vector3 b) {
    return vector3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 vector3_multiply(Vector3 v, float scalar) {
    return vector3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vector3_dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 vector3_cross(Vector3 a, Vector3 b) {
    return vector3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float vector3_magnitude(Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 vector3_normalize(Vector3 v) {
    float mag = vector3_magnitude(v);
    if (mag > 0.0001f) {
        return vector3_multiply(v, 1.0f / mag);
    }
    return vector3_create(0, 0, 0);
}

float vector3_distance(Vector3 a, Vector3 b) {
    Vector3 diff = vector3_subtract(a, b);
    return vector3_magnitude(diff);
}

// ============================================================================
// Quaternion Mathematics Implementation
// ============================================================================

Quaternion quaternion_identity(void) {
    Quaternion q = {0, 0, 0, 1};
    return q;
}

Quaternion quaternion_from_euler(float pitch, float yaw, float roll) {
    // Convert degrees to radians
    pitch *= M_PI / 180.0f;
    yaw *= M_PI / 180.0f;
    roll *= M_PI / 180.0f;

    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

Quaternion quaternion_multiply(Quaternion a, Quaternion b) {
    Quaternion result;
    result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    return result;
}

Quaternion quaternion_normalize(Quaternion q) {
    float mag = sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    if (mag > 0.0001f) {
        q.w /= mag;
        q.x /= mag;
        q.y /= mag;
        q.z /= mag;
    }
    return q;
}

void quaternion_to_euler(Quaternion q, float* pitch, float* yaw, float* roll) {
    // Roll (x-axis rotation)
    float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    *roll = atan2f(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    float sinp = 2 * (q.w * q.y - q.z * q.x);
    if (fabsf(sinp) >= 1)
        *pitch = copysignf(M_PI / 2, sinp); // Use 90 degrees if out of range
    else
        *pitch = asinf(sinp);

    // Yaw (z-axis rotation)
    float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    *yaw = atan2f(siny_cosp, cosy_cosp);

    // Convert to degrees
    *pitch *= 180.0f / M_PI;
    *yaw *= 180.0f / M_PI;
    *roll *= 180.0f / M_PI;
}

// ============================================================================
// World Management Implementation
// ============================================================================

World* world_create(const char* name, float width, float height) {
    World* world = (World*)malloc(sizeof(World));
    if (!world) return NULL;

    // Initialize basic properties
    strncpy(world->name, name, sizeof(world->name) - 1);
    world->name[sizeof(world->name) - 1] = '\0';

    strcpy(world->description, "A virtual reality world");
    world->world_time = 0;
    world->paused = false;
    world->time_scale = 1.0f;
    world->fps = 60;
    world->frame_time = 16.67f; // 60 FPS
    world->triangles_rendered = 0;

    // Set up world bounds
    world->bounds.min_bounds = vector3_create(-width/2, -100, -height/2);
    world->bounds.max_bounds = vector3_create(width/2, 1000, height/2);
    world->bounds.world_scale = 1.0f;

    // Set up physics
    world->gravity = -9.81f;
    world->wind_direction = vector3_create(1, 0, 0);
    world->wind_strength = 0.0f;

    // Initialize terrain (simplified)
    world->terrain = NULL;

    // Set up chunk system
    world->chunk_size = 64; // 64x64 unit chunks
    world->chunks_x = (int)ceilf(width / world->chunk_size);
    world->chunks_z = (int)ceilf(height / world->chunk_size);

    // Allocate chunk grid
    world->chunks = (WorldChunk***)malloc(world->chunks_x * sizeof(WorldChunk**));
    if (!world->chunks) {
        free(world);
        return NULL;
    }

    for (int x = 0; x < world->chunks_x; x++) {
        world->chunks[x] = (WorldChunk**)malloc(world->chunks_z * sizeof(WorldChunk*));
        if (!world->chunks[x]) {
            // Cleanup on failure
            for (int i = 0; i < x; i++) {
                free(world->chunks[i]);
            }
            free(world->chunks);
            free(world);
            return NULL;
        }

        for (int z = 0; z < world->chunks_z; z++) {
            world->chunks[x][z] = NULL; // Chunks loaded on demand
        }
    }

    // Initialize object arrays
    world->objects = NULL;
    world->object_count = 0;
    world->max_objects = 10000;

    world->avatars = NULL;
    world->avatar_count = 0;
    world->max_avatars = 1000;

    return world;
}

void world_destroy(World* world) {
    if (!world) return;

    // Destroy chunks
    if (world->chunks) {
        for (int x = 0; x < world->chunks_x; x++) {
            if (world->chunks[x]) {
                for (int z = 0; z < world->chunks_z; z++) {
                    if (world->chunks[x][z]) {
                        // Note: Objects are destroyed separately
                        free(world->chunks[x][z]);
                    }
                }
                free(world->chunks[x]);
            }
        }
        free(world->chunks);
    }

    // Destroy terrain
    if (world->terrain) {
        if (world->terrain->heights) {
            free(world->terrain->heights);
        }
        free(world->terrain);
    }

    // Note: Objects and avatars are destroyed by their respective systems

    free(world);
}

void world_update(World* world, float delta_time) {
    if (!world || world->paused) return;

    // Update world time
    world->world_time += (uint64_t)(delta_time * 1000000); // microseconds

    // Update objects (simplified - real implementation would iterate through all objects)
    // This is where physics, AI, and other updates would happen

    // Update performance metrics
    static uint64_t last_time = 0;
    static int frame_count = 0;

    if (last_time == 0) {
        last_time = world->world_time;
    }

    frame_count++;
    if (world->world_time - last_time >= 1000000) { // Every second
        world->fps = frame_count;
        world->frame_time = 1000.0f / frame_count;
        frame_count = 0;
        last_time = world->world_time;
    }
}

void world_render(World* world, Vector3 camera_position, Quaternion camera_rotation,
                 int viewport_width, int viewport_height) {
    if (!world) return;

    // Simplified software rendering
    // In a real implementation, this would:
    // 1. Frustum culling
    // 2. Depth sorting
    // 3. Perspective projection
    // 4. Rasterization
    // 5. Texture mapping
    // 6. Lighting calculations

    world->triangles_rendered = world->object_count * 12; // Rough estimate
}

bool world_add_object(World* world, Object* object) {
    if (!world || !object || world->object_count >= world->max_objects) {
        return false;
    }

    // Expand object array if needed
    if (world->object_count == 0) {
        world->objects = (Object**)malloc(world->max_objects * sizeof(Object*));
        if (!world->objects) return false;
    }

    world->objects[world->object_count++] = object;

    // Assign to chunk
    int chunk_x = (int)((object->position.x - world->bounds.min_bounds.x) / world->chunk_size);
    int chunk_z = (int)((object->position.z - world->bounds.min_bounds.z) / world->chunk_size);

    chunk_x = chunk_x < 0 ? 0 : (chunk_x >= world->chunks_x ? world->chunks_x - 1 : chunk_x);
    chunk_z = chunk_z < 0 ? 0 : (chunk_z >= world->chunks_z ? world->chunks_z - 1 : chunk_z);

    // Load chunk if needed
    if (!world->chunks[chunk_x][chunk_z]) {
        world->chunks[chunk_x][chunk_z] = (WorldChunk*)malloc(sizeof(WorldChunk));
        if (!world->chunks[chunk_x][chunk_z]) return false;

        WorldChunk* new_chunk = world->chunks[chunk_x][chunk_z];
        new_chunk->chunk_x = chunk_x;
        new_chunk->chunk_z = chunk_z;
        new_chunk->position = vector3_create(
            world->bounds.min_bounds.x + chunk_x * world->chunk_size,
            0,
            world->bounds.min_bounds.z + chunk_z * world->chunk_size
        );
        new_chunk->objects = NULL;
        new_chunk->object_count = 0;
        new_chunk->max_objects = 100;
        new_chunk->loaded = true;
        new_chunk->last_accessed = world->world_time;
    }

    WorldChunk* chunk = world->chunks[chunk_x][chunk_z];
    object->chunk = chunk;

    return true;
}

bool world_remove_object(World* world, Object* object) {
    if (!world || !object) return false;

    // Find and remove from object array
    for (int i = 0; i < world->object_count; i++) {
        if (world->objects[i] == object) {
            // Shift remaining objects
            for (int j = i; j < world->object_count - 1; j++) {
                world->objects[j] = world->objects[j + 1];
            }
            world->object_count--;
            return true;
        }
    }

    return false;
}

Object* world_find_object(World* world, const char* id) {
    if (!world || !id) return NULL;

    for (int i = 0; i < world->object_count; i++) {
        if (strcmp(world->objects[i]->id, id) == 0) {
            return world->objects[i];
        }
    }

    return NULL;
}

int world_get_objects_in_radius(World* world, Vector3 center, float radius,
                               Object** objects, int max_objects) {
    if (!world || !objects || max_objects <= 0) return 0;

    int count = 0;
    for (int i = 0; i < world->object_count && count < max_objects; i++) {
        Object* obj = world->objects[i];
        if (vector3_distance(center, obj->position) <= radius) {
            objects[count++] = obj;
        }
    }

    return count;
}

WorldChunk* world_load_chunk(World* world, int chunk_x, int chunk_z) {
    if (!world || chunk_x < 0 || chunk_x >= world->chunks_x ||
        chunk_z < 0 || chunk_z >= world->chunks_z) {
        return NULL;
    }

    if (!world->chunks[chunk_x][chunk_z]) {
        // Create new chunk
        world->chunks[chunk_x][chunk_z] = (WorldChunk*)malloc(sizeof(WorldChunk));
        if (!world->chunks[chunk_x][chunk_z]) return NULL;

        WorldChunk* new_chunk = world->chunks[chunk_x][chunk_z];
        new_chunk->chunk_x = chunk_x;
        new_chunk->chunk_z = chunk_z;
        new_chunk->position = vector3_create(
            world->bounds.min_bounds.x + chunk_x * world->chunk_size,
            0,
            world->bounds.min_bounds.z + chunk_z * world->chunk_size
        );
        new_chunk->objects = NULL;
        new_chunk->object_count = 0;
        new_chunk->max_objects = 100;
        new_chunk->loaded = true;
        new_chunk->last_accessed = world->world_time;
    }

    return world->chunks[chunk_x][chunk_z];
}

void world_unload_chunk(World* world, WorldChunk* chunk) {
    if (!world || !chunk) return;

    // Find chunk in grid
    for (int x = 0; x < world->chunks_x; x++) {
        for (int z = 0; z < world->chunks_z; z++) {
            if (world->chunks[x][z] == chunk) {
                // Move objects to adjacent chunks or remove them
                // Simplified: just mark as unloaded
                chunk->loaded = false;
                chunk->last_accessed = world->world_time;
                return;
            }
        }
    }
}

float world_get_terrain_height(World* world, float x, float z) {
    // Simplified: return flat terrain
    return 0.0f;
}

bool world_line_of_sight(World* world, Vector3 start, Vector3 end) {
    // Simplified: always true (no obstacles)
    return true;
}

bool world_raycast(World* world, Vector3 origin, Vector3 direction,
                  float max_distance, void* hit_info) {
    // Simplified raycast implementation
    // In a real implementation, this would check against all objects
    return false;
}

// ============================================================================
// Object Management Implementation
// ============================================================================

Object* object_create(ObjectType type) {
    Object* object = (Object*)malloc(sizeof(Object));
    if (!object) return NULL;

    // Generate unique ID
    static int id_counter = 0;
    sprintf(object->id, "obj_%d", id_counter++);

    strcpy(object->name, "Object");
    object->type = type;
    object->position = vector3_create(0, 0, 0);
    object->rotation = quaternion_identity();
    object->scale = vector3_create(1, 1, 1);

    // Visual properties
    strcpy(object->model_path, "");
    strcpy(object->texture_path, "");
    object->visible = true;

    // Physics (simplified)
    object->physics.mass = 1.0f;
    object->physics.velocity = vector3_create(0, 0, 0);
    object->physics.acceleration = vector3_create(0, 0, 0);
    object->physics.kinematic = (type == OBJECT_STATIC);
    object->physics.friction = 0.5f;
    object->physics.restitution = 0.3f;

    // Collision
    object->has_collision = true;
    object->bounding_radius = 1.0f;

    // Interaction
    object->interactive = (type == OBJECT_INTERACTIVE);
    object->user_data = NULL;
    object->on_interact = NULL;

    // World linkage
    object->chunk = NULL;
    object->last_updated = 0;

    return object;
}

void object_destroy(Object* object) {
    if (!object) return;

    // Clean up user data if needed
    if (object->user_data) {
        free(object->user_data);
    }

    free(object);
}

void object_set_position(Object* object, Vector3 position) {
    if (!object) return;
    object->position = position;
    object->last_updated = (uint64_t)time(NULL);
}

void object_set_rotation(Object* object, Quaternion rotation) {
    if (!object) return;
    object->rotation = quaternion_normalize(rotation);
    object->last_updated = (uint64_t)time(NULL);
}

void object_set_scale(Object* object, Vector3 scale) {
    if (!object) return;
    object->scale = scale;
    object->last_updated = (uint64_t)time(NULL);
}

void object_move(Object* object, Vector3 offset) {
    if (!object) return;
    object->position = vector3_add(object->position, offset);
    object->last_updated = (uint64_t)time(NULL);
}

void object_rotate(Object* object, Quaternion rotation) {
    if (!object) return;
    object->rotation = quaternion_multiply(object->rotation, rotation);
    object->rotation = quaternion_normalize(object->rotation);
    object->last_updated = (uint64_t)time(NULL);
}

bool object_check_collision(Object* obj1, Object* obj2) {
    if (!obj1 || !obj2) return false;

    float distance = vector3_distance(obj1->position, obj2->position);
    float combined_radius = obj1->bounding_radius + obj2->bounding_radius;

    return distance <= combined_radius;
}

void object_interact(Object* object, Avatar* avatar) {
    if (!object || !avatar) return;

    // Call interaction callback if set
    if (object->on_interact) {
        object->on_interact(object, avatar);
    }
}

// ============================================================================
// Utility Functions Implementation
// ============================================================================

const char* world_generate_object_id(void) {
    static char id[65];
    static int counter = 0;

    sprintf(id, "world_obj_%d_%lu", counter++, (unsigned long)time(NULL));
    return id;
}

bool world_save_to_file(World* world, const char* filename) {
    // Simplified: would implement full serialization
    FILE* file = fopen(filename, "w");
    if (!file) return false;

    fprintf(file, "WORLD %s\n", world->name);
    fprintf(file, "BOUNDS %.2f %.2f %.2f %.2f %.2f %.2f\n",
            world->bounds.min_bounds.x, world->bounds.min_bounds.y, world->bounds.min_bounds.z,
            world->bounds.max_bounds.x, world->bounds.max_bounds.y, world->bounds.max_bounds.z);
    fprintf(file, "OBJECTS %d\n", world->object_count);

    fclose(file);
    return true;
}

World* world_load_from_file(const char* filename) {
    // Simplified: would implement full deserialization
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char line[256];
    if (fgets(line, sizeof(line), file)) {
        char name[256];
        if (sscanf(line, "WORLD %s", name) == 1) {
            // Create world with saved name
            World* world = world_create(name, 1000, 1000);
            fclose(file);
            return world;
        }
    }

    fclose(file);
    return NULL;
}

void world_get_statistics(World* world, void* stats) {
    // Simplified statistics
    if (stats) {
        // Would fill statistics structure
    }
}
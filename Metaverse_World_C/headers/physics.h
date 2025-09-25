/*
 * Metaverse World System - Physics Engine Header
 * Defines structures and functions for physics simulation,
 * collision detection, and rigid body dynamics
 */

#ifndef METAVERSE_PHYSICS_H
#define METAVERSE_PHYSICS_H

#include <stdint.h>
#include <stdbool.h>
#include "world.h"

// Forward declarations
typedef struct RigidBody RigidBody;
typedef struct Collider Collider;
typedef struct PhysicsWorld PhysicsWorld;
typedef struct RaycastHit RaycastHit;
typedef struct Joint Joint;

// ============================================================================
// Physics Constants and Configuration
// ============================================================================

#define PHYSICS_GRAVITY_DEFAULT -9.81f
#define PHYSICS_MAX_BODIES 10000
#define PHYSICS_MAX_COLLIDERS 50000
#define PHYSICS_MAX_CONSTRAINTS 1000
#define PHYSICS_FIXED_TIMESTEP 1.0f/60.0f
#define PHYSICS_MAX_ITERATIONS 10

/**
 * @brief Physics material properties
 */
typedef struct {
    float density;                  // Material density (kg/m³)
    float restitution;              // Bounciness (0-1)
    float static_friction;          // Static friction coefficient
    float dynamic_friction;         // Dynamic friction coefficient
} PhysicsMaterial;

/**
 * @brief Collision shape types
 */
typedef enum {
    COLLIDER_SPHERE,                // Spherical collider
    COLLIDER_BOX,                   // Box/AABB collider
    COLLIDER_CAPSULE,               // Capsule collider
    COLLIDER_MESH,                  // Triangle mesh collider
    COLLIDER_TERRAIN                // Heightfield terrain collider
} ColliderType;

// ============================================================================
// Rigid Body Physics
// ============================================================================

/**
 * @brief Rigid body structure for physics simulation
 */
struct RigidBody {
    // Identification
    char id[64];                    // Unique body identifier
    Object* attached_object;        // Attached world object

    // Physical properties
    float mass;                     // Body mass in kg
    Matrix4x4 inertia_tensor;       // Moment of inertia tensor
    PhysicsMaterial material;       // Material properties

    // State
    Vector3 position;               // Current position
    Quaternion rotation;            // Current rotation
    Vector3 linear_velocity;        // Linear velocity (m/s)
    Vector3 angular_velocity;       // Angular velocity (rad/s)

    // Forces and torques
    Vector3 force_accumulator;      // Accumulated forces
    Vector3 torque_accumulator;     // Accumulated torques

    // Collision
    Collider* collider;             // Collision shape
    bool kinematic;                 // Whether body is kinematic (unaffected by forces)
    bool sleeping;                  // Whether body is sleeping (optimization)

    // Simulation properties
    float linear_damping;           // Linear velocity damping
    float angular_damping;          // Angular velocity damping
    float gravity_scale;            // Gravity multiplier

    // Constraints and joints
    Joint** joints;                 // Connected joints
    int joint_count;                // Number of joints

    // Performance
    uint64_t last_updated;          // Last simulation update
    bool needs_update;              // Whether body needs physics update
};

/**
 * @brief Collision shape data
 */
typedef union {
    // Sphere collider
    struct {
        float radius;
    } sphere;

    // Box collider
    struct {
        Vector3 half_extents;       // Half extents of the box
    } box;

    // Capsule collider
    struct {
        float radius;
        float height;
    } capsule;

    // Mesh collider
    struct {
        Vector3* vertices;          // Triangle mesh vertices
        int* indices;               // Triangle indices
        int vertex_count;           // Number of vertices
        int triangle_count;         // Number of triangles
    } mesh;

    // Terrain collider
    struct {
        float* heights;             // Heightfield data
        int width, height;          // Terrain dimensions
        float scale;                // Height scale
    } terrain;
} ColliderShape;

/**
 * @brief Collision shape structure
 */
struct Collider {
    char id[64];                    // Unique collider identifier
    ColliderType type;              // Collider shape type
    ColliderShape shape;            // Shape-specific data

    // Transform (relative to rigid body)
    Vector3 offset;                 // Position offset
    Quaternion rotation;            // Rotation offset

    // Properties
    bool is_trigger;                // Whether this is a trigger volume
    uint32_t collision_mask;        // Collision layer mask
    PhysicsMaterial material;       // Surface material

    // Attached body
    RigidBody* body;                // Owning rigid body
};

// ============================================================================
// Collision Detection and Response
// ============================================================================

/**
 * @brief Collision contact point information
 */
typedef struct {
    Vector3 point;                  // Contact point in world space
    Vector3 normal;                 // Contact normal
    float penetration;              // Penetration depth
    float impulse;                  // Applied impulse
} ContactPoint;

/**
 * @brief Collision manifold (contact information)
 */
typedef struct {
    RigidBody* body_a;              // First colliding body
    RigidBody* body_b;              // Second colliding body
    ContactPoint* contacts;         // Contact points
    int contact_count;              // Number of contact points
    bool resolved;                  // Whether collision has been resolved
} CollisionManifold;

/**
 * @brief Raycast hit information
 */
struct RaycastHit {
    Vector3 point;                  // Hit point
    Vector3 normal;                 // Surface normal at hit point
    float distance;                 // Distance from ray origin to hit point
    RigidBody* body;                // Hit rigid body
    Collider* collider;             // Hit collider
    bool hit;                       // Whether ray hit something
};

// ============================================================================
// Constraints and Joints
// ============================================================================

/**
 * @brief Joint types
 */
typedef enum {
    JOINT_FIXED,                    // Fixed joint (no relative movement)
    JOINT_HINGE,                    // Hinge joint (rotates around axis)
    JOINT_BALL_SOCKET,              // Ball and socket joint (3DOF rotation)
    JOINT_SLIDER,                   // Slider joint (linear movement)
    JOINT_SPRING,                   // Spring joint (damped connection)
    JOINT_DISTANCE                  // Distance constraint
} JointType;

/**
 * @brief Joint definition data
 */
typedef union {
    // Fixed joint - no additional data needed

    // Hinge joint
    struct {
        Vector3 axis;               // Rotation axis
        float min_angle;            // Minimum rotation angle
        float max_angle;            // Maximum rotation angle
    } hinge;

    // Ball socket joint
    struct {
        float cone_limit;           // Cone angle limit (radians)
    } ball_socket;

    // Slider joint
    struct {
        Vector3 axis;               // Movement axis
        float min_distance;         // Minimum distance
        float max_distance;         // Maximum distance
    } slider;

    // Spring joint
    struct {
        float stiffness;            // Spring stiffness
        float damping;              // Spring damping
        float rest_length;          // Rest length
    } spring;

    // Distance joint
    struct {
        float distance;             // Target distance
        float tolerance;            // Distance tolerance
    } distance;
} JointData;

/**
 * @brief Physics joint structure
 */
struct Joint {
    char id[64];                    // Unique joint identifier
    JointType type;                 // Joint type
    JointData data;                 // Type-specific data

    // Connected bodies
    RigidBody* body_a;              // First body
    RigidBody* body_b;              // Second body

    // Anchor points (in local space of each body)
    Vector3 anchor_a;               // Anchor point on body A
    Vector3 anchor_b;               // Anchor point on body B

    // Joint properties
    bool enabled;                   // Whether joint is active
    float break_force;              // Force required to break joint
    float break_torque;             // Torque required to break joint
};

// ============================================================================
// Physics World and Simulation
// ============================================================================

/**
 * @brief Physics simulation world
 */
struct PhysicsWorld {
    // Bodies and colliders
    RigidBody** bodies;             // Array of rigid bodies
    int body_count;                 // Number of bodies
    int max_bodies;                 // Maximum bodies

    Collider** colliders;           // Array of colliders
    int collider_count;             // Number of colliders
    int max_colliders;              // Maximum colliders

    // Simulation settings
    Vector3 gravity;                // Gravity vector
    float fixed_timestep;           // Fixed simulation timestep
    int max_iterations;             // Maximum solver iterations
    bool paused;                    // Whether simulation is paused

    // Collision detection
    CollisionManifold* manifolds;   // Collision manifolds
    int manifold_count;             // Number of manifolds
    int max_manifolds;              // Maximum manifolds

    // Performance metrics
    float simulation_time;          // Time spent in simulation
    int collision_checks;           // Number of collision checks
    int constraints_solved;         // Number of constraints solved

    // Broad phase acceleration
    void* broad_phase;              // Broad phase collision detection
    void* narrow_phase;             // Narrow phase collision detection

    // Callbacks
    void (*on_collision)(CollisionManifold*); // Collision callback
    void (*on_trigger)(Collider*, Collider*); // Trigger callback
};

// ============================================================================
// Physics Engine Functions
// ============================================================================

/**
 * @brief Create physics world
 * @param gravity Gravity vector
 * @param max_bodies Maximum number of bodies
 * @param max_colliders Maximum number of colliders
 * @return Pointer to created physics world or NULL on failure
 */
PhysicsWorld* physics_world_create(Vector3 gravity, int max_bodies, int max_colliders);

/**
 * @brief Destroy physics world
 * @param world Physics world to destroy
 */
void physics_world_destroy(PhysicsWorld* world);

/**
 * @brief Update physics simulation
 * @param world Physics world to update
 * @param delta_time Time elapsed since last update
 */
void physics_world_update(PhysicsWorld* world, float delta_time);

/**
 * @brief Add rigid body to physics world
 * @param world Target physics world
 * @param body Rigid body to add
 * @return Success status
 */
bool physics_world_add_body(PhysicsWorld* world, RigidBody* body);

/**
 * @brief Remove rigid body from physics world
 * @param world Target physics world
 * @param body Rigid body to remove
 * @return Success status
 */
bool physics_world_remove_body(PhysicsWorld* world, RigidBody* body);

/**
 * @brief Add collider to physics world
 * @param world Target physics world
 * @param collider Collider to add
 * @return Success status
 */
bool physics_world_add_collider(PhysicsWorld* world, Collider* collider);

/**
 * @brief Remove collider from physics world
 * @param world Target physics world
 * @param collider Collider to remove
 * @return Success status
 */
bool physics_world_remove_collider(PhysicsWorld* world, Collider* collider);

/**
 * @brief Perform raycast against physics world
 * @param world Physics world to raycast
 * @param origin Ray origin
 * @param direction Ray direction (normalized)
 * @param max_distance Maximum ray distance
 * @param hit Output hit information
 * @return True if ray hit something
 */
bool physics_world_raycast(PhysicsWorld* world, Vector3 origin, Vector3 direction,
                          float max_distance, RaycastHit* hit);

/**
 * @brief Check collision between two colliders
 * @param collider_a First collider
 * @param collider_b Second collider
 * @param manifold Output collision manifold
 * @return True if collision detected
 */
bool physics_check_collision(Collider* collider_a, Collider* collider_b,
                           CollisionManifold* manifold);

// ============================================================================
// Rigid Body Functions
// ============================================================================

/**
 * @brief Create rigid body
 * @param mass Body mass in kg
 * @param position Initial position
 * @param rotation Initial rotation
 * @return Pointer to created rigid body or NULL on failure
 */
RigidBody* rigid_body_create(float mass, Vector3 position, Quaternion rotation);

/**
 * @brief Destroy rigid body
 * @param body Rigid body to destroy
 */
void rigid_body_destroy(RigidBody* body);

/**
 * @brief Apply force to rigid body
 * @param body Target rigid body
 * @param force Force vector
 * @param world_point Point in world space where force is applied
 */
void rigid_body_apply_force(RigidBody* body, Vector3 force, Vector3 world_point);

/**
 * @brief Apply impulse to rigid body
 * @param body Target rigid body
 * @param impulse Impulse vector
 * @param world_point Point in world space where impulse is applied
 */
void rigid_body_apply_impulse(RigidBody* body, Vector3 impulse, Vector3 world_point);

/**
 * @brief Apply torque to rigid body
 * @param body Target rigid body
 * @param torque Torque vector
 */
void rigid_body_apply_torque(RigidBody* body, Vector3 torque);

/**
 * @brief Set rigid body position
 * @param body Target rigid body
 * @param position New position
 */
void rigid_body_set_position(RigidBody* body, Vector3 position);

/**
 * @brief Set rigid body rotation
 * @param body Target rigid body
 * @param rotation New rotation
 */
void rigid_body_set_rotation(RigidBody* body, Quaternion rotation);

/**
 * @brief Get rigid body transform matrix
 * @param body Target rigid body
 * @return Transform matrix
 */
Matrix4x4 rigid_body_get_transform(RigidBody* body);

/**
 * @brief Put rigid body to sleep (optimization)
 * @param body Target rigid body
 */
void rigid_body_sleep(RigidBody* body);

/**
 * @brief Wake up rigid body
 * @param body Target rigid body
 */
void rigid_body_wake(RigidBody* body);

// ============================================================================
// Collider Functions
// ============================================================================

/**
 * @brief Create sphere collider
 * @param radius Sphere radius
 * @return Pointer to created collider or NULL on failure
 */
Collider* collider_create_sphere(float radius);

/**
 * @brief Create box collider
 * @param half_extents Half extents of the box
 * @return Pointer to created collider or NULL on failure
 */
Collider* collider_create_box(Vector3 half_extents);

/**
 * @brief Create capsule collider
 * @param radius Capsule radius
 * @param height Capsule height
 * @return Pointer to created collider or NULL on failure
 */
Collider* collider_create_capsule(float radius, float height);

/**
 * @brief Destroy collider
 * @param collider Collider to destroy
 */
void collider_destroy(Collider* collider);

/**
 * @brief Set collider as trigger
 * @param collider Target collider
 * @param is_trigger Whether collider is a trigger
 */
void collider_set_trigger(Collider* collider, bool is_trigger);

/**
 * @brief Update collider transform
 * @param collider Target collider
 * @param position New position
 * @param rotation New rotation
 */
void collider_update_transform(Collider* collider, Vector3 position, Quaternion rotation);

/**
 * @brief Get collider bounding box
 * @param collider Target collider
 * @param min Output minimum bounds
 * @param max Output maximum bounds
 */
void collider_get_bounds(Collider* collider, Vector3* min, Vector3* max);

// ============================================================================
// Joint Functions
// ============================================================================

/**
 * @brief Create fixed joint
 * @param body_a First body
 * @param body_b Second body
 * @param anchor Anchor point
 * @return Pointer to created joint or NULL on failure
 */
Joint* joint_create_fixed(RigidBody* body_a, RigidBody* body_b, Vector3 anchor);

/**
 * @brief Create hinge joint
 * @param body_a First body
 * @param body_b Second body
 * @param anchor Anchor point
 * @param axis Rotation axis
 * @return Pointer to created joint or NULL on failure
 */
Joint* joint_create_hinge(RigidBody* body_a, RigidBody* body_b, Vector3 anchor, Vector3 axis);

/**
 * @brief Create ball socket joint
 * @param body_a First body
 * @param body_b Second body
 * @param anchor Anchor point
 * @return Pointer to created joint or NULL on failure
 */
Joint* joint_create_ball_socket(RigidBody* body_a, RigidBody* body_b, Vector3 anchor);

/**
 * @brief Destroy joint
 * @param joint Joint to destroy
 */
void joint_destroy(Joint* joint);

/**
 * @brief Set joint break forces
 * @param joint Target joint
 * @param break_force Force required to break joint
 * @param break_torque Torque required to break joint
 */
void joint_set_break_forces(Joint* joint, float break_force, float break_torque);

/**
 * @brief Check if joint is broken
 * @param joint Target joint
 * @return True if joint is broken
 */
bool joint_is_broken(Joint* joint);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Calculate moment of inertia for sphere
 * @param mass Sphere mass
 * @param radius Sphere radius
 * @return Moment of inertia tensor
 */
Matrix4x4 physics_moment_of_inertia_sphere(float mass, float radius);

/**
 * @brief Calculate moment of inertia for box
 * @param mass Box mass
 * @param half_extents Box half extents
 * @return Moment of inertia tensor
 */
Matrix4x4 physics_moment_of_inertia_box(float mass, Vector3 half_extents);

/**
 * @brief Convert point from world space to local space
 * @param world_point Point in world space
 * @param body_transform Body transform matrix
 * @return Point in local space
 */
Vector3 physics_world_to_local(Vector3 world_point, Matrix4x4 body_transform);

/**
 * @brief Convert point from local space to world space
 * @param local_point Point in local space
 * @param body_transform Body transform matrix
 * @return Point in world space
 */
Vector3 physics_local_to_world(Vector3 local_point, Matrix4x4 body_transform);

/**
 * @brief Get physics world statistics
 * @param world Target physics world
 * @param stats Output statistics structure
 */
void physics_world_get_statistics(PhysicsWorld* world, void* stats);

/**
 * @brief Debug draw physics world
 * @param world Physics world to debug draw
 */
void physics_world_debug_draw(PhysicsWorld* world);

#endif // METAVERSE_PHYSICS_H
/*
 * Metaverse World System - Physics Engine Implementation
 * Rigid body dynamics, collision detection, and constraint solving
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "../headers/physics.h"

// ============================================================================
// Physics World Implementation
// ============================================================================

PhysicsWorld* physics_world_create(Vector3 gravity, int max_bodies, int max_colliders) {
    PhysicsWorld* world = (PhysicsWorld*)malloc(sizeof(PhysicsWorld));
    if (!world) return NULL;

    // Initialize properties
    world->gravity = gravity;
    world->fixed_timestep = PHYSICS_FIXED_TIMESTEP;
    world->max_iterations = PHYSICS_MAX_ITERATIONS;
    world->paused = false;

    // Allocate body arrays
    world->bodies = (RigidBody**)malloc(max_bodies * sizeof(RigidBody*));
    world->max_bodies = max_bodies;
    world->body_count = 0;

    world->colliders = (Collider**)malloc(max_colliders * sizeof(Collider*));
    world->max_colliders = max_colliders;
    world->collider_count = 0;

    // Initialize collision manifolds
    world->manifolds = (CollisionManifold*)malloc(PHYSICS_MAX_CONSTRAINTS * sizeof(CollisionManifold));
    world->max_manifolds = PHYSICS_MAX_CONSTRAINTS;
    world->manifold_count = 0;

    // Initialize broad phase (simplified)
    world->broad_phase = NULL;
    world->narrow_phase = NULL;

    // Initialize callbacks
    world->on_collision = NULL;
    world->on_trigger = NULL;

    // Initialize performance metrics
    world->simulation_time = 0.0f;
    world->collision_checks = 0;
    world->constraints_solved = 0;

    if (!world->bodies || !world->colliders || !world->manifolds) {
        physics_world_destroy(world);
        return NULL;
    }

    // Initialize arrays to NULL
    memset(world->bodies, 0, max_bodies * sizeof(RigidBody*));
    memset(world->colliders, 0, max_colliders * sizeof(Collider*));

    return world;
}

void physics_world_destroy(PhysicsWorld* world) {
    if (!world) return;

    // Destroy all bodies
    for (int i = 0; i < world->body_count; i++) {
        if (world->bodies[i]) {
            rigid_body_destroy(world->bodies[i]);
        }
    }
    free(world->bodies);

    // Destroy all colliders
    for (int i = 0; i < world->collider_count; i++) {
        if (world->colliders[i]) {
            collider_destroy(world->colliders[i]);
        }
    }
    free(world->colliders);

    // Free manifolds
    free(world->manifolds);

    free(world);
}

void physics_world_update(PhysicsWorld* world, float delta_time) {
    if (!world || world->paused) return;

    // Clamp delta time to prevent large jumps
    if (delta_time > 1.0f / 30.0f) {
        delta_time = 1.0f / 30.0f;
    }

    // Apply gravity to all bodies
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        if (body && !body->kinematic) {
            body->force_accumulator = vector3_add(body->force_accumulator,
                vector3_multiply(world->gravity, body->mass));
        }
    }

    // Integrate forces and update velocities
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        if (body && !body->kinematic) {
            // F = ma => a = F/m
            Vector3 acceleration = vector3_multiply(body->force_accumulator, 1.0f / body->mass);

            // Integrate acceleration
            body->linear_velocity = vector3_add(body->linear_velocity,
                vector3_multiply(acceleration, delta_time));

            // Apply damping
            body->linear_velocity = vector3_multiply(body->linear_velocity,
                1.0f - body->linear_damping * delta_time);

            // Clear force accumulator
            body->force_accumulator = vector3_create(0, 0, 0);
        }
    }

    // Integrate velocities and update positions
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        if (body && !body->kinematic) {
            // Integrate velocity
            body->position = vector3_add(body->position,
                vector3_multiply(body->linear_velocity, delta_time));

            // Update transform timestamp
            body->last_updated = (uint64_t)time(NULL);
        }
    }

    // Broad phase collision detection (simplified)
    world->collision_checks = 0;
    world->manifold_count = 0;

    for (int i = 0; i < world->body_count; i++) {
        for (int j = i + 1; j < world->body_count; j++) {
            RigidBody* body_a = world->bodies[i];
            RigidBody* body_b = world->bodies[j];

            if (!body_a || !body_b) continue;

            world->collision_checks++;

            // Check if bodies can collide
            if (body_a->kinematic && body_b->kinematic) continue;

            // Narrow phase collision detection
            CollisionManifold manifold = {0};
            if (physics_check_collision(body_a->collider, body_b->collider, &manifold)) {
                manifold.body_a = body_a;
                manifold.body_b = body_b;

                // Store manifold for resolution
                if (world->manifold_count < world->max_manifolds) {
                    world->manifolds[world->manifold_count++] = manifold;
                }

                // Call collision callback
                if (world->on_collision) {
                    world->on_collision(&manifold);
                }
            }
        }
    }

    // Resolve collisions (simplified)
    for (int i = 0; i < world->manifold_count; i++) {
        CollisionManifold* manifold = &world->manifolds[i];

        // Simple position correction
        if (manifold->contact_count > 0) {
            ContactPoint* contact = &manifold->contacts[0];

            // Separate bodies
            Vector3 correction = vector3_multiply(contact->normal, contact->penetration * 0.5f);

            if (!manifold->body_a->kinematic) {
                manifold->body_a->position = vector3_subtract(manifold->body_a->position, correction);
            }
            if (!manifold->body_b->kinematic) {
                manifold->body_b->position = vector3_add(manifold->body_b->position, correction);
            }

            // Apply impulse
            float impulse = contact->impulse;
            if (!manifold->body_a->kinematic) {
                manifold->body_a->linear_velocity = vector3_add(manifold->body_a->linear_velocity,
                    vector3_multiply(contact->normal, -impulse / manifold->body_a->mass));
            }
            if (!manifold->body_b->kinematic) {
                manifold->body_b->linear_velocity = vector3_add(manifold->body_b->linear_velocity,
                    vector3_multiply(contact->normal, impulse / manifold->body_b->mass));
            }
        }
    }

    world->constraints_solved = world->manifold_count;
}

bool physics_world_add_body(PhysicsWorld* world, RigidBody* body) {
    if (!world || !body || world->body_count >= world->max_bodies) {
        return false;
    }

    world->bodies[world->body_count++] = body;
    return true;
}

bool physics_world_remove_body(PhysicsWorld* world, RigidBody* body) {
    if (!world || !body) return false;

    for (int i = 0; i < world->body_count; i++) {
        if (world->bodies[i] == body) {
            // Shift remaining bodies
            for (int j = i; j < world->body_count - 1; j++) {
                world->bodies[j] = world->bodies[j + 1];
            }
            world->body_count--;
            return true;
        }
    }

    return false;
}

bool physics_world_add_collider(PhysicsWorld* world, Collider* collider) {
    if (!world || !collider || world->collider_count >= world->max_colliders) {
        return false;
    }

    world->colliders[world->collider_count++] = collider;
    return true;
}

bool physics_world_remove_collider(PhysicsWorld* world, Collider* collider) {
    if (!world || !collider) return false;

    for (int i = 0; i < world->collider_count; i++) {
        if (world->colliders[i] == collider) {
            // Shift remaining colliders
            for (int j = i; j < world->collider_count - 1; j++) {
                world->colliders[j] = world->colliders[j + 1];
            }
            world->collider_count--;
            return true;
        }
    }

    return false;
}

bool physics_world_raycast(PhysicsWorld* world, Vector3 origin, Vector3 direction,
                          float max_distance, RaycastHit* hit) {
    if (!world || !hit) return false;

    hit->hit = false;
    hit->distance = max_distance;
    hit->body = NULL;
    hit->collider = NULL;

    // Simplified raycast - check against all colliders
    for (int i = 0; i < world->collider_count; i++) {
        Collider* collider = world->colliders[i];
        if (!collider) continue;

        // Simple sphere-ray intersection (for sphere colliders)
        if (collider->type == COLLIDER_SPHERE) {
            Vector3 to_center = vector3_subtract(collider->body->position, origin);
            float distance_to_center = vector3_magnitude(to_center);

            if (distance_to_center <= collider->shape.sphere.radius) {
                // Ray origin is inside sphere
                hit->hit = true;
                hit->distance = 0.0f;
                hit->point = origin;
                hit->body = collider->body;
                hit->collider = collider;
                hit->normal = vector3_normalize(to_center);
                return true;
            }

            // Check ray-sphere intersection
            float projection = vector3_dot(to_center, direction);
            if (projection < 0) continue; // Sphere is behind ray

            Vector3 closest_point = vector3_add(origin,
                vector3_multiply(direction, projection));
            Vector3 to_closest = vector3_subtract(closest_point, collider->body->position);
            float distance_to_sphere = vector3_magnitude(to_closest);

            if (distance_to_sphere <= collider->shape.sphere.radius) {
                float distance_inside = sqrtf(collider->shape.sphere.radius * collider->shape.sphere.radius -
                                           distance_to_sphere * distance_to_sphere);
                float hit_distance = projection - distance_inside;

                if (hit_distance <= max_distance) {
                    hit->hit = true;
                    hit->distance = hit_distance;
                    hit->point = vector3_add(origin, vector3_multiply(direction, hit_distance));
                    hit->body = collider->body;
                    hit->collider = collider;
                    hit->normal = vector3_normalize(vector3_subtract(hit->point, collider->body->position));
                    return true;
                }
            }
        }
    }

    return hit->hit;
}

bool physics_check_collision(Collider* collider_a, Collider* collider_b,
                           CollisionManifold* manifold) {
    if (!collider_a || !collider_b || !manifold) return false;

    // Only handle sphere-sphere collisions for simplicity
    if (collider_a->type == COLLIDER_SPHERE && collider_b->type == COLLIDER_SPHERE) {
        Vector3 pos_a = vector3_add(collider_a->body->position, collider_a->offset);
        Vector3 pos_b = vector3_add(collider_b->body->position, collider_b->offset);

        float distance = vector3_distance(pos_a, pos_b);
        float combined_radius = collider_a->shape.sphere.radius + collider_b->shape.sphere.radius;

        if (distance < combined_radius) {
            // Collision detected
            manifold->contact_count = 1;
            manifold->contacts[0].point = vector3_add(pos_a,
                vector3_multiply(vector3_normalize(vector3_subtract(pos_b, pos_a)),
                collider_a->shape.sphere.radius));
            manifold->contacts[0].normal = vector3_normalize(vector3_subtract(pos_b, pos_a));
            manifold->contacts[0].penetration = combined_radius - distance;
            manifold->contacts[0].impulse = 0.0f; // Would calculate based on velocities

            return true;
        }
    }

    return false;
}

// ============================================================================
// Rigid Body Implementation
// ============================================================================

RigidBody* rigid_body_create(float mass, Vector3 position, Quaternion rotation) {
    RigidBody* body = (RigidBody*)malloc(sizeof(RigidBody));
    if (!body) return NULL;

    // Generate unique ID
    static int id_counter = 0;
    sprintf(body->id, "body_%d", id_counter++);

    // Attach to object (NULL initially)
    body->attached_object = NULL;

    // Physical properties
    body->mass = mass;
    // Identity inertia tensor for simplicity
    memset(&body->inertia_tensor, 0, sizeof(Matrix4x4));
    body->inertia_tensor.m[0][0] = 1.0f;
    body->inertia_tensor.m[1][1] = 1.0f;
    body->inertia_tensor.m[2][2] = 1.0f;
    body->inertia_tensor.m[3][3] = 1.0f;

    // Default material
    body->material.density = 1000.0f; // kg/m³
    body->material.restitution = 0.3f;
    body->material.static_friction = 0.6f;
    body->material.dynamic_friction = 0.4f;

    // State
    body->position = position;
    body->rotation = rotation;
    body->linear_velocity = vector3_create(0, 0, 0);
    body->angular_velocity = vector3_create(0, 0, 0);

    // Forces
    body->force_accumulator = vector3_create(0, 0, 0);
    body->torque_accumulator = vector3_create(0, 0, 0);

    // Collision
    body->collider = NULL;
    body->kinematic = false;
    body->sleeping = false;

    // Simulation properties
    body->linear_damping = 0.1f;
    body->angular_damping = 0.1f;
    body->gravity_scale = 1.0f;

    // Joints
    body->joints = NULL;
    body->joint_count = 0;

    // Performance
    body->last_updated = (uint64_t)time(NULL);
    body->needs_update = false;

    return body;
}

void rigid_body_destroy(RigidBody* body) {
    if (!body) return;

    // Destroy collider if owned by this body
    if (body->collider) {
        collider_destroy(body->collider);
    }

    free(body);
}

void rigid_body_apply_force(RigidBody* body, Vector3 force, Vector3 world_point) {
    if (!body || body->kinematic) return;

    body->force_accumulator = vector3_add(body->force_accumulator, force);

    // Calculate torque if point is not at center of mass
    Vector3 r = vector3_subtract(world_point, body->position);
    Vector3 torque = vector3_cross(r, force);
    body->torque_accumulator = vector3_add(body->torque_accumulator, torque);
}

void rigid_body_apply_impulse(RigidBody* body, Vector3 impulse, Vector3 world_point) {
    if (!body || body->kinematic) return;

    // Apply immediate velocity change
    body->linear_velocity = vector3_add(body->linear_velocity,
        vector3_multiply(impulse, 1.0f / body->mass));

    // Apply angular impulse
    Vector3 r = vector3_subtract(world_point, body->position);
    Vector3 angular_impulse = vector3_cross(r, impulse);
    // Simplified: would need to transform by inverse inertia tensor
    body->angular_velocity = vector3_add(body->angular_velocity, angular_impulse);
}

void rigid_body_apply_torque(RigidBody* body, Vector3 torque) {
    if (!body || body->kinematic) return;

    body->torque_accumulator = vector3_add(body->torque_accumulator, torque);
}

void rigid_body_set_position(RigidBody* body, Vector3 position) {
    if (!body) return;
    body->position = position;
    body->needs_update = true;
}

void rigid_body_set_rotation(RigidBody* body, Quaternion rotation) {
    if (!body) return;
    body->rotation = quaternion_normalize(rotation);
    body->needs_update = true;
}

Matrix4x4 rigid_body_get_transform(RigidBody* body) {
    Matrix4x4 transform = {0};

    if (!body) {
        // Return identity matrix
        transform.m[0][0] = 1; transform.m[1][1] = 1;
        transform.m[2][2] = 1; transform.m[3][3] = 1;
        return transform;
    }

    // Simplified: would build proper transformation matrix
    // For now, return identity
    transform.m[0][0] = 1; transform.m[1][1] = 1;
    transform.m[2][2] = 1; transform.m[3][3] = 1;

    return transform;
}

void rigid_body_sleep(RigidBody* body) {
    if (!body) return;
    body->sleeping = true;
    body->linear_velocity = vector3_create(0, 0, 0);
    body->angular_velocity = vector3_create(0, 0, 0);
}

void rigid_body_wake(RigidBody* body) {
    if (!body) return;
    body->sleeping = false;
}

// ============================================================================
// Collider Implementation
// ============================================================================

Collider* collider_create_sphere(float radius) {
    Collider* collider = (Collider*)malloc(sizeof(Collider));
    if (!collider) return NULL;

    // Generate unique ID
    static int id_counter = 0;
    sprintf(collider->id, "collider_%d", id_counter++);

    collider->type = COLLIDER_SPHERE;
    collider->shape.sphere.radius = radius;

    // Transform
    collider->offset = vector3_create(0, 0, 0);
    collider->rotation = quaternion_identity();

    // Properties
    collider->is_trigger = false;
    collider->collision_mask = 0xFFFFFFFF; // Collide with everything
    collider->material.density = 1000.0f;
    collider->material.restitution = 0.3f;
    collider->material.static_friction = 0.6f;
    collider->material.dynamic_friction = 0.4f;

    // Body
    collider->body = NULL;

    return collider;
}

void collider_destroy(Collider* collider) {
    if (!collider) return;

    // Free shape-specific data
    if (collider->type == COLLIDER_MESH) {
        free(collider->shape.mesh.vertices);
        free(collider->shape.mesh.indices);
    } else if (collider->type == COLLIDER_TERRAIN) {
        free(collider->shape.terrain.heights);
    }

    free(collider);
}

void collider_set_trigger(Collider* collider, bool is_trigger) {
    if (collider) {
        collider->is_trigger = is_trigger;
    }
}

void collider_update_transform(Collider* collider, Vector3 position, Quaternion rotation) {
    if (collider) {
        collider->offset = position;
        collider->rotation = rotation;
    }
}

void collider_get_bounds(Collider* collider, Vector3* min, Vector3* max) {
    if (!collider || !min || !max) return;

    switch (collider->type) {
        case COLLIDER_SPHERE: {
            float radius = collider->shape.sphere.radius;
            *min = vector3_create(-radius, -radius, -radius);
            *max = vector3_create(radius, radius, radius);
            break;
        }
        case COLLIDER_BOX: {
            Vector3 half = collider->shape.box.half_extents;
            *min = vector3_create(-half.x, -half.y, -half.z);
            *max = vector3_create(half.x, half.y, half.z);
            break;
        }
        default: {
            *min = vector3_create(0, 0, 0);
            *max = vector3_create(0, 0, 0);
            break;
        }
    }

    // Transform bounds by collider transform
    *min = vector3_add(*min, collider->offset);
    *max = vector3_add(*max, collider->offset);
}

// ============================================================================
// Utility Functions
// ============================================================================

Matrix4x4 physics_moment_of_inertia_sphere(float mass, float radius) {
    Matrix4x4 tensor = {0};
    float value = (2.0f / 5.0f) * mass * radius * radius;

    tensor.m[0][0] = value;
    tensor.m[1][1] = value;
    tensor.m[2][2] = value;
    tensor.m[3][3] = 1.0f;

    return tensor;
}

Matrix4x4 physics_moment_of_inertia_box(float mass, Vector3 half_extents) {
    Matrix4x4 tensor = {0};
    float x = half_extents.x * 2;
    float y = half_extents.y * 2;
    float z = half_extents.z * 2;

    tensor.m[0][0] = (1.0f / 12.0f) * mass * (y*y + z*z);
    tensor.m[1][1] = (1.0f / 12.0f) * mass * (x*x + z*z);
    tensor.m[2][2] = (1.0f / 12.0f) * mass * (x*x + y*y);
    tensor.m[3][3] = 1.0f;

    return tensor;
}

Vector3 physics_world_to_local(Vector3 world_point, Matrix4x4 body_transform) {
    // Simplified: assume identity transform
    return world_point;
}

Vector3 physics_local_to_world(Vector3 local_point, Matrix4x4 body_transform) {
    // Simplified: assume identity transform
    return local_point;
}

void physics_world_get_statistics(PhysicsWorld* world, void* stats) {
    // Simplified statistics
    if (stats) {
        // Would fill statistics structure
    }
}

void physics_world_debug_draw(PhysicsWorld* world) {
    if (!world) return;

    printf("Physics World Debug:\n");
    printf("- Bodies: %d/%d\n", world->body_count, world->max_bodies);
    printf("- Colliders: %d/%d\n", world->collider_count, world->max_colliders);
    printf("- Manifolds: %d/%d\n", world->manifold_count, world->max_manifolds);
    printf("- Collision checks: %d\n", world->collision_checks);
    printf("- Constraints solved: %d\n", world->constraints_solved);
}
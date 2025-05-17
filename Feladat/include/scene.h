#ifndef SCENE_H
#define SCENE_H
#define NUM_TREES 36 

#include "camera.h"
#include "snow.h"
#include "texture.h"


#include <obj/model.h>

typedef struct {
    float x, y;
    float rotation;
} TreeInstance;

typedef struct Scene
{
    Model cube;
    Material material;
    GLuint trunk_texture_id;
    GLuint crown_texture_id;
    Snow snow;
    TreeInstance trees[NUM_TREES];
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */

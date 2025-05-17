#ifndef SNOW_H
#define SNOW_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>

#define N_PARTICLES 500

typedef struct Particle {
  vec3 position;
  vec3 velocity;
  double lifetime;
} Particle;

typedef struct Snow {
  Model model;
  GLuint trunk_texture_id;
  GLuint crown_texture_id;
  Particle particles[N_PARTICLES];
} Snow;

/**
 * Initialize the particles of the snow.
 */
void init_snow(Snow* snow);

/**
 * Update the position of the particles.
 */
void update_snow(Snow* snow, double elapsed_time);

/**
 * Render the particles.
 */
void render_snow(const Snow* snow);

#endif /* SNOW_H */


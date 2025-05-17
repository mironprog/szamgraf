#include "snow.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <stdlib.h>

#define GRAVITY_Z -0.1
#define MAX_LIFETIME 3

void init_snow(Snow* snow)
{
    load_model(&(snow->model), "assets/models/cube.obj");
    
    snow->trunk_texture_id = load_texture("assets/textures/tree_trunk.png"); 
   
    snow->crown_texture_id = load_texture("assets/textures/tree_crown.png"); 


    for (int i = 0; i < N_PARTICLES; ++i) {
        snow->particles[i].position.x = 0;
        snow->particles[i].position.y = 0;
        snow->particles[i].position.z = 3;

        snow->particles[i].velocity.x = (double)(rand() % 2000 - 1000) / 3000;
        snow->particles[i].velocity.y = (double)(rand() % 2000 - 1000) / 3000;
        snow->particles[i].velocity.z = -0.2 - (double)(rand() % 1000) / 3000;

        snow->particles[i].lifetime = (double)(rand() % 3000) / 1000;
    }
}

void update_snow(Snow* snow, double elapsed_time)
{
    for (int i = 0; i < N_PARTICLES; ++i) {
        snow->particles[i].lifetime += elapsed_time;

        if (snow->particles[i].lifetime >= MAX_LIFETIME) {
            snow->particles[i].position.x = 0;
            snow->particles[i].position.y = 0;
            snow->particles[i].position.z = 3;

            snow->particles[i].velocity.x = (double)(rand() % 2000 - 1000) / 3000;
            snow->particles[i].velocity.y = (double)(rand() % 2000 - 1000) / 3000;
            snow->particles[i].velocity.z = -0.2 - (double)(rand() % 1000) / 3000;

            snow->particles[i].lifetime = 0;
        }

        snow->particles[i].velocity.z += (GRAVITY_Z * elapsed_time);
        snow->particles[i].position.x += snow->particles[i].velocity.x * elapsed_time;
        snow->particles[i].position.y += snow->particles[i].velocity.y * elapsed_time;
        snow->particles[i].position.z += snow->particles[i].velocity.z * elapsed_time;
    }
}

void render_snow(const Snow* snow)
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < N_PARTICLES; ++i) {
        glPushMatrix();
        glTranslated(
            snow->particles[i].position.x,
            snow->particles[i].position.y,
            snow->particles[i].position.z
        );
        glScaled(0.05, 0.05, 0.05); 
        draw_model(&(snow->model));
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

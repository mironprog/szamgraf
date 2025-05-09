#include "fire.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <stdlib.h>

#define GRAVITY_Z -0.1
#define MAX_LIFETIME 3

void init_explosion(Explosion* explosion)
{
    load_model(&(explosion->model), "assets/models/cube.obj");
    explosion->texture_id = load_texture("assets/textures/cube.png");

    for (int i = 0; i < N_PARTICLES; ++i) {
        explosion->particles[i].position.x = 0;
        explosion->particles[i].position.y = 0;
        explosion->particles[i].position.z = 3;

        explosion->particles[i].velocity.x = (double)(rand() % 2000 - 1000) / 3000; 
        explosion->particles[i].velocity.y = (double)(rand() % 2000 - 1000) / 3000;
        explosion->particles[i].velocity.z = -0.2 - (double)(rand() % 1000) / 3000; 

        explosion->particles[i].lifetime = (double)(rand() % 3000) / 1000;
    }
}

void update_explosion(Explosion* explosion, double elapsed_time)
{
    for (int i = 0; i < N_PARTICLES; ++i) {
        explosion->particles[i].lifetime += elapsed_time;
        if (explosion->particles[i].lifetime >= MAX_LIFETIME) {
            explosion->particles[i].position.x = 0;
            explosion->particles[i].position.y = 0;
            explosion->particles[i].position.z = 3;

            explosion->particles[i].velocity.x = (double)(rand() % 2000 - 1000) / 3000;
            explosion->particles[i].velocity.y = (double)(rand() % 2000 - 1000) / 3000;
            explosion->particles[i].velocity.z = -0.2 - (double)(rand() % 1000) / 3000;

            explosion->particles[i].lifetime = 0;
        }

        explosion->particles[i].velocity.z += (GRAVITY_Z * elapsed_time);
        explosion->particles[i].position.x += explosion->particles[i].velocity.x * elapsed_time;
        explosion->particles[i].position.y += explosion->particles[i].velocity.y * elapsed_time;
        explosion->particles[i].position.z += explosion->particles[i].velocity.z * elapsed_time;
    }
}

void render_explosion(const Explosion* explosion)
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);  // fehér hó

    for (int i = 0; i < N_PARTICLES; ++i) {
        glPushMatrix();
        glTranslated(
            explosion->particles[i].position.x,
            explosion->particles[i].position.y,
            explosion->particles[i].position.z
        );
        glScaled(0.05, 0.05, 0.05);  // kisebb hópelyhek
        draw_model(&(explosion->model));
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

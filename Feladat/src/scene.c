#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

#include "snow.h"

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "assets/models/tree.obj");
    scene->texture_id = load_texture("assets/textures/tree_trunk.png");

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    
    init_snow(&(scene->snow));

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    srand((unsigned int)time(NULL));

    int index = 0;
    for (float x = -5; x <= 5; x += 2.0f) {
        for (float y = -5; y <= 5; y += 2.0f) {
            scene->trees[index].x = x + (((float)(rand() % 100) / 100.0f) - 0.5f);
            scene->trees[index].y = y + (((float)(rand() % 100) / 100.0f) - 0.5f);
            index++;
        }
    }
}

void set_lighting()
{
    float ambient_light[] = { 5.0f, 6.0f, 7.0f, 1.0f };
    float diffuse_light[] = { 5.0f, 5.0f, 5.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double elapsed_time)
{
    update_snow(&(scene->snow), elapsed_time);
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_ground();
    render_snow(&(scene->snow));
    
    for (int i = 0; i < NUM_TREES; i++) {
        glPushMatrix();

        glTranslatef(scene->trees[i].x, scene->trees[i].y, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glScalef(0.2f, 0.2f, 0.2f);

        draw_model(&(scene->cube));

        glPopMatrix();
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_ground()
{
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS); 
    
    glColor3f(1.0f, 1.0f, 1.0f); 

    float ground_level = 0.0f;

    glVertex3f(-50.0f, -50.0f, ground_level);
    glVertex3f( 50.0f, -50.0f, ground_level); 
    glVertex3f( 50.0f, 50.0f, ground_level); 
    glVertex3f(-50.0f, 50.0f, ground_level); 

    glEnd(); 
}

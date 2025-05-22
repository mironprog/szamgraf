#include "camera.h"
#include "scene.h"

#include <GL/gl.h>

#include <math.h>

#define GRAVITY -9.8


void init_camera(Camera* camera)
{
    camera->height = 0.4;
    camera->radius = 0.3;

    camera->position.x = 2.0;
    camera->position.y = 2.0;
    camera->position.z = 0.0 + camera->height;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

static double dist_2d(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}


void update_camera(Camera* camera, const Scene* scene, double time)
{
    double angle;
    double side_angle;

    double next_x = camera->position.x;
    double next_y = camera->position.y;
    double next_z = camera->position.z;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    double delta_x_forward = cos(angle) * camera->speed.y * time;
    double delta_y_forward = sin(angle) * camera->speed.y * time;

    double delta_x_side = cos(side_angle) * camera->speed.x * time;
    double delta_y_side = sin(side_angle) * camera->speed.x * time;

    next_x += delta_x_forward + delta_x_side;
    next_y += delta_y_forward + delta_y_side;

    camera->speed.z += GRAVITY * time;

    next_z += camera->speed.z * time;

    const double ground_level = 0.0;

    if (next_z < ground_level + camera->height) {
        next_z = ground_level + camera->height;
        if (camera->speed.z < 0) {
            camera->speed.z = 0;
        }
    }
    
    const double tree_collision_radius = 0.2 * 0.8; 
    const double min_dist_between_centers = camera->radius + tree_collision_radius;

    for (int i = 0; i < NUM_TREES; ++i) { 
        double tree_x = scene->trees[i].x;
        double tree_y = scene->trees[i].y;

        double dist_to_tree_center = dist_2d(next_x, next_y, tree_x, tree_y);

        if (dist_to_tree_center < min_dist_between_centers) {
            double penetration_depth = min_dist_between_centers - dist_to_tree_center;

            double dir_x = next_x - tree_x;
            double dir_y = next_y - tree_y;

            if (dist_to_tree_center > 0) { 
                dir_x /= dist_to_tree_center;
                dir_y /= dist_to_tree_center;
            } else {
                dir_x = 1.0;
                dir_y = 0.0;
            }

            next_x += dir_x * penetration_depth;
            next_y += dir_y * penetration_depth;
        }
    }

    camera->position.x = next_x;
    camera->position.y = next_y;
    camera->position.z = next_z;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vert_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}


void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}



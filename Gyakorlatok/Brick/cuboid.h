#ifndef CUBOID_H
#define CUBOID_H

#include <stdbool.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct CUBOID
{
	double a;
	double b;
	double c;
} Cuboid;

/**
 * Set the data of the circle
 */
void set_cuboid_size(Cuboid* cuboid, double a, double b, double c);

/**
 * Calculate the area of the circle.
 */
double calc_cuboid_volume(const Cuboid* cuboid);
double calc_cuboid_surface(const Cuboid* cuboid);
double has_cube(const Cuboid* cuboid);
#endif // CIRCLE_H
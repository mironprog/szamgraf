#include "cuboid.h"

#include <stdbool.h> 
#include <math.h>

void set_cuboid_size(Cuboid* cuboid, double a, double b, double c)
{
    if(a > 0 && b > 0 && c > 0)
    {
	cuboid->a = a;
	cuboid->b = b;
    cuboid->c = c;
    }
  
}

double calc_cuboid_volume(const Cuboid* cuboid)
{
	double volume = cuboid->a * cuboid->b * cuboid->c;
	return volume;
}

double calc_cuboid_surface(const Cuboid* cuboid)
{
    double surface = 2 * (cuboid->a * cuboid->b + cuboid->a * cuboid->c + cuboid->b * cuboid->c);
    return surface;
}

double has_cube(const Cuboid* cuboid)
{
    double has_cube = 0;
    if(cuboid->a == cuboid->b || cuboid->a == cuboid->c || cuboid->b == cuboid->c)
    {
        has_cube = 1;
    }

    return has_cube;
}
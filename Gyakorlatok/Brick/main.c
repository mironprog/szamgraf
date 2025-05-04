#include "cuboid.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Cuboid cuboid;
	double volume;
	double surface;
    double hascube;

	set_cuboid_size(&cuboid, 5, 10, 8);
	volume = calc_cuboid_volume(&cuboid);
	surface = calc_cuboid_surface(&cuboid);
    hascube = has_cube(&cuboid);

	printf("The volume of the cuboid: %lf\n", volume);
	printf("The surface of the cuboid: %lf\n", surface);
    if(hascube == 1){
		printf("It has a square side.\n");
	}else{
		printf("It doesn't have a square side.\n");
	}
	return 0;
}
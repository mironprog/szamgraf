all:
	gcc -Iinclude/ -Imingwdev/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/snow.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o ice.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o ice -Wall -Wextra -Wpedantic

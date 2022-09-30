#include <stdio.h>
#include "mesh-library.h"

int main() {
	vec3f a = { 1, 1, 1 };
	vec3f b = { 1, -1, -1 };
	vec3f c = { -1, 1, -1 };
	vec3f d = { -1, -1, 1 };

	mesh tetrahedron;
	create_mesh(&tetrahedron, 4);
	add_triangle(&tetrahedron, a, b, c);
	add_triangle(&tetrahedron, a, c, d);
	add_triangle(&tetrahedron, a, d, b);
	add_triangle(&tetrahedron, d, c, b);

	printf("Tetrahedron mesh >>>\n");
	print_mesh(&tetrahedron);

	mesh icosahedron;

	float a0 = 1.0f;
	float b0 = 1.0f / tau();

	vec3f v1 = { 0, b0, -a0 };
	vec3f v2 = { b0, a0, 0 };
	vec3f v3 = { -b0, a0, 0 };
	vec3f v4 = { 0, b0, a0 };
	vec3f v5 = { 0, -b0, a0 };
	vec3f v6 = { -a0, 0, b0 };
	vec3f v7 = { 0, -b0, -a0 };
	vec3f v8 = { a0, 0, -b0 };
	vec3f v9 = { a0, 0, b0 };
	vec3f v10 = { -a0, 0, -b0 };
	vec3f v11 = { b0, -a0, 0 };
	vec3f v12 = {-b0, -a0, 0};

	create_mesh(&icosahedron, 20);
	add_triangle(&icosahedron, v3, v2, v1);
	add_triangle(&icosahedron, v2, v3, v4); 
	add_triangle(&icosahedron, v6, v5, v4); 
	add_triangle(&icosahedron, v5, v9, v4);
	add_triangle(&icosahedron, v8, v7, v1);
	add_triangle(&icosahedron, v7, v10, v1);
	add_triangle(&icosahedron, v12, v11, v5);
	add_triangle(&icosahedron, v11, v12, v7);
	add_triangle(&icosahedron, v10, v6, v3);
	add_triangle(&icosahedron, v6, v10, v12);
	add_triangle(&icosahedron, v9, v8, v2);
	add_triangle(&icosahedron, v8, v9, v11);
	add_triangle(&icosahedron, v3, v6, v4);
	add_triangle(&icosahedron, v9, v2, v4);
	add_triangle(&icosahedron, v10, v3, v1);
	add_triangle(&icosahedron, v2, v8, v1);
	add_triangle(&icosahedron, v12, v10, v7);
	add_triangle(&icosahedron, v8, v11, v7);
	add_triangle(&icosahedron, v6, v12, v5);
	add_triangle(&icosahedron, v11, v9, v5);

	printf("Icosahedron mesh >>>\n");
	print_mesh(&icosahedron);

	vec3f c0 = { -1, -1, -1 };
	vec3f c1 = { 1, -1, -1 };
	vec3f c2 = { -1, 1, -1 };
	vec3f c3 = { 1, 1, -1 };
	vec3f c4 = { -1, -1, 1 };
	vec3f c5 = { -1, 1, 1 };
	vec3f c6 = { 1, 1, 1 };
	vec3f c7 = { 1, -1, 1};

	mesh cube;
	create_mesh(&cube, 6);
	add_quad(&cube, c0, c1, c3, c2); 
	add_quad(&cube, c4, c5, c6, c7);
	add_quad(&cube, c1, c3, c6, c7);
	add_quad(&cube, c0, c2, c5, c4);
	add_quad(&cube, c2, c3, c6, c5);
	add_quad(&cube, c0, c1, c7, c4);

	printf("Cube mesh >>>\n");
	print_mesh(&cube);


	return 0;
}
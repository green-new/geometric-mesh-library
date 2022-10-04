#define GEOMETRIC_MESH_LIBRARY_IMPLEMENTATION_H
#include "mesh_library.h"

#include <stdio.h>

int main() {
	gml_vec3f a = { 1, 1, 1 };
	gml_vec3f b = { 1, -1, -1 };
	gml_vec3f c = { -1, 1, -1 };
	gml_vec3f d = { -1, -1, 1 };

	gml_mesh tetrahedron;
	gml_create_mesh(&tetrahedron, 4);
	gml_add_triangle(&tetrahedron, &a, &b, &c);
	gml_add_triangle(&tetrahedron, &a, &c, &d);
	gml_add_triangle(&tetrahedron, &a, &d, &b);
	gml_add_triangle(&tetrahedron, &d, &c, &b);

	printf("Tetrahedron mesh >>>\n");
	gml_print_mesh(&tetrahedron);

	gml_mesh icosahedron;

	float a0 = 1.0f;
	float b0 = 1.0f / gml_tau();

	gml_vec3f v1 = { 0, b0, -a0 };
	gml_vec3f v2 = { b0, a0, 0 };
	gml_vec3f v3 = { -b0, a0, 0 };
	gml_vec3f v4 = { 0, b0, a0 };
	gml_vec3f v5 = { 0, -b0, a0 };
	gml_vec3f v6 = { -a0, 0, b0 };
	gml_vec3f v7 = { 0, -b0, -a0 };
	gml_vec3f v8 = { a0, 0, -b0 };
	gml_vec3f v9 = { a0, 0, b0 };
	gml_vec3f v10 = { -a0, 0, -b0 };
	gml_vec3f v11 = { b0, -a0, 0 };
	gml_vec3f v12 = {-b0, -a0, 0};

	gml_create_mesh(&icosahedron, 12);
	gml_add_triangle(&icosahedron, &v3, &v2, &v1);
	gml_add_triangle(&icosahedron, &v2, &v3, &v4);
	gml_add_triangle(&icosahedron, &v6, &v5, &v4);
	gml_add_triangle(&icosahedron, &v5, &v9, &v4);
	gml_add_triangle(&icosahedron, &v8, &v7, &v1);
	gml_add_triangle(&icosahedron, &v7, &v10, &v1);
	gml_add_triangle(&icosahedron, &v12, &v11, &v5);
	gml_add_triangle(&icosahedron, &v11, &v12, &v7);
	gml_add_triangle(&icosahedron, &v10, &v6, &v3);
	gml_add_triangle(&icosahedron, &v6, &v10, &v12);
	gml_add_triangle(&icosahedron, &v9, &v8, &v2);
	gml_add_triangle(&icosahedron, &v8, &v9, &v11);
	gml_add_triangle(&icosahedron, &v3, &v6, &v4);
	gml_add_triangle(&icosahedron, &v9, &v2, &v4);
	gml_add_triangle(&icosahedron, &v10, &v3, &v1);
	gml_add_triangle(&icosahedron, &v2, &v8, &v1);
	gml_add_triangle(&icosahedron, &v12, &v10, &v7);
	gml_add_triangle(&icosahedron, &v8, &v11, &v7);
	gml_add_triangle(&icosahedron, &v6, &v12, &v5);
	gml_add_triangle(&icosahedron, &v11, &v9, &v5);

	printf("Icosahedron mesh >>>\n");
	gml_print_mesh(&icosahedron);

	gml_vec3f c0 = { -1, -1, -1 };
	gml_vec3f c1 = { 1, -1, -1 };
	gml_vec3f c2 = { -1, 1, -1 };
	gml_vec3f c3 = { 1, 1, -1 };
	gml_vec3f c4 = { -1, -1, 1 };
	gml_vec3f c5 = { -1, 1, 1 };
	gml_vec3f c6 = { 1, 1, 1 };
	gml_vec3f c7 = { 1, -1, 1};

	gml_mesh cube;
	gml_create_mesh(&cube, 8);
	gml_add_quad(&cube, &c0, &c1, &c3, &c2);
	gml_add_quad(&cube, &c4, &c5, &c6, &c7);
	gml_add_quad(&cube, &c1, &c3, &c6, &c7);
	gml_add_quad(&cube, &c0, &c2, &c5, &c4);
	gml_add_quad(&cube, &c2, &c3, &c6, &c5);
	gml_add_quad(&cube, &c0, &c1, &c7, &c4);

	printf("Cube mesh >>>\n");
	gml_print_mesh(&cube);

	gml_vec3f o0 = { 1, 0, 0 };
	gml_vec3f o1 = { -1, 0, 0 };
	gml_vec3f o2 = { 0, 1, 0 };
	gml_vec3f o3 = { 0, -1, 0 };
	gml_vec3f o4 = { 0, 0, 1 };
	gml_vec3f o5 = { 0, 0, -1 };
	gml_mesh octahedron;
	gml_create_mesh(&octahedron, 6);
	gml_add_triangle(&octahedron, &o0, &o2, &o4);
	gml_add_triangle(&octahedron, &o1, &o2, &o4);
	gml_add_triangle(&octahedron, &o1, &o2, &o5);
	gml_add_triangle(&octahedron, &o0, &o2, &o5);
	gml_add_triangle(&octahedron, &o0, &o3, &o5);
	gml_add_triangle(&octahedron, &o5, &o3, &o1);
	gml_add_triangle(&octahedron, &o1, &o3, &o4);
	gml_add_triangle(&octahedron, &o4, &o3, &o0);

	printf(">>> Octahedron mesh\n");
	gml_print_mesh(&octahedron);

	gml_mesh pyramid;
	gml_create_mesh(&pyramid, 6);
	gml_add_quad(&pyramid, &o0, &o4, &o1, &o5);
	gml_add_triangle(&pyramid, &o0, &o2, &o4);
	gml_add_triangle(&pyramid, &o4, &o2, &o1);
	gml_add_triangle(&pyramid, &o1, &o2, &o5);
	gml_add_triangle(&pyramid, &o5, &o2, &o0);

	printf(">>> Pyramid mesh\n");
	gml_print_mesh(&pyramid);

	return 0;
}
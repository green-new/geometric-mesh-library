/*
* Author: Tristen Woodruff
* Version: 1.0
* Date: October 3rd, 2022
* 
* This library uses doubly connected edge lists to design polygons which make up three dimensional meshes.
* This introduces triangulation techniques to break faces down into triangles for computer graphics rendering.
* 
* Sources:
* https://web.archive.org/web/20130531101356/http://www.emeyex.com/site/tuts/VertexNormals.pdf
* https://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
* http://www.holmes3d.net/graphics/dcel/
* https://cs.stackexchange.com/questions/2450/how-do-i-construct-a-doubly-connected-edge-list-given-a-set-of-line-segments
*/

#ifndef GEOMETRIC_MESH_LIBRARY
#define GEOMETRIC_MESH_LIBRARY
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* This library can only handle dodecahedron polygons as faces. */
#define GML_MAX_SIDES	12U

/* Maximum of faces for a three-dimensional mesh. */
#define GML_MAX_FACES	128U

#define GML_MAX_VERTICES 1024U

// V + E - F = 2

typedef struct gml_vec3f gml_vec3f;
typedef struct gml_vec2f gml_vec2f;
typedef struct gml_vertex gml_vertex;
typedef struct gml_halfedge gml_halfedge;
typedef struct gml_face gml_face;
typedef struct gml_mesh gml_mesh;

/* Normalizes the givern vec3f reference. */
void gml_normalize(gml_vec3f* normal);

/* Cross product. */
gml_vec3f gml_cross(const gml_vec3f* left, const gml_vec3f* right);

/* Subtracts two vec3s linearly. */
gml_vec3f gml_subtract(const gml_vec3f* left, const gml_vec3f* right);

/* Calculate all normals for the mesh (starting vertex). */
void calculate_smooth_normals(gml_vertex* P0);

/* Calculates the geometric normal for the face. */
void calculate_geometric_normal(gml_face* face);

/* Golden ratio (1.0f + sqrtf(5.0f)) / 2.0f.) */
float gml_tau();

// #ifdef GEOMETRIC_MESH_LIBRARY_IMPLEMENTATION_H

struct gml_vec3f {
	float			x, y, z;
};

struct gml_vec2f{
	float			u, v;
};

struct gml_vertex {
	gml_vec3f		pos;
	gml_vec3f		smooth_normal;
	gml_halfedge*	leaving;
};

struct gml_halfedge {
	gml_vertex*		origin;
	gml_halfedge*	twin;
	gml_face*		incident;
	gml_halfedge*	next;
	gml_halfedge*	prev;
};

struct gml_face {
	gml_halfedge*	inner;
	gml_vec3f		geometric_normal;
};

gml_halfedge const* INFINITY_EDGE = NULL;
gml_face const* INFINITY_PLANE = NULL;

void gml_normalize(gml_vec3f* normal) {
	float f = sqrtf((normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z));
	if (f <= 0.0f) {
		printf("[ERROR] normalize: Vector length is 0 and cannot be normalized\n");
		return;
	}
	normal->x = normal->x / f;
	normal->y = normal->y / f;
	normal->z = normal->z / f;
}

gml_vec3f gml_cross(const gml_vec3f* left, const gml_vec3f* right) {
	gml_vec3f v = {
		(left->y * right->z) - (left->z * right->y),
		(left->z * right->x) - (left->x * right->z),
		(left->x * right->y) - (left->y * right->x)
	};
	return v;
}

gml_vec3f gml_subtract(const gml_vec3f* left, const gml_vec3f* right) {
	gml_vec3f res = {
		(left->x - right->x),
		(left->y - right->y),
		(left->z - right->z)
	};
	return res;
}



float gml_tau() {
	return (1.0f + sqrtf(5.0f)) / 2.0f;
}

// #endif /* GEOMETRIC_MESH_LIBRARY_IMPLEMENTATION_H */

#endif /* GEOMETRIC_MESH_LIBRARY */
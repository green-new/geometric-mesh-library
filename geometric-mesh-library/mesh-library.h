#ifndef GEOMETRIC_MESH_LIBRARY
#define GEOMETRIC_MESH_LIBRARY
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x, y, z;
} gml_vec3f;

typedef struct {
	gml_vec3f pos;
	unsigned int index;
} gml_vertex;

typedef struct {
	gml_vec3f p0, p1, p2;
} gml_triangle;

typedef struct {
	gml_vec3f*		m_vertices;
	unsigned int*	m_indices;
	unsigned int    used_vertices;
	unsigned int    used_indices;
	unsigned int    n_vertices;
	unsigned int    n_indices;
} gml_mesh;

typedef struct {
	gml_vec3f* first;
	gml_vec3f* second;
} gml_edge;

/* Subtracts two vectors and returns by value a new gml_vec3f. */
gml_vec3f gml_subtract(const gml_vec3f* left, const gml_vec3f* right);

/* Returns by value a new gml_vec3f by cross product. */
gml_vec3f gml_cross_product(const gml_vec3f* left, const gml_vec3f* right);

/* Normalizes the given vector. */
void gml_normalize(gml_vec3f* normal);

/* Gets the normal of the given triangle (plane). */
gml_vec3f gml_get_normal(gml_vec3f q, gml_vec3f r, gml_vec3f s);

/* Initiates the given mesh pointer. init is the expected number of triangles. */
void gml_create_mesh(gml_mesh* m, unsigned int init);

/* Deletes the mesh and its elements. */
void gml_delete_mesh(gml_mesh* m);

int gml_contains(const gml_mesh* m, const gml_vec3f* v);

/* Generates an index for the given vertex.
If the vertex already exists, use that index. */
unsigned int gml_get_idx(const gml_mesh* m, const gml_vec3f* v);

/* Creates a face based on the given list of vertices.  */
void gml_add_face(gml_mesh* m, gml_vec3f* vs, unsigned int n_vs);

/* Adds a triangle to the mesh given 3 vectors. */
void gml_add_triangle(gml_mesh* m, gml_vec3f* x, gml_vec3f* y, gml_vec3f* z);

/* Adds a quad to the mesh given 4 vectors. It creates two triangles with identical normals with the 4 vectors. */
void gml_add_quad(gml_mesh* m, gml_vec3f* x, gml_vec3f* y, gml_vec3f* z, gml_vec3f* w);

/* Prints the elements of the mesh using printf. */
void gml_print_mesh(const gml_mesh* m);

/* Golden ratio (1.0f + sqrtf(5.0f)) / 2.0f.) */
float gml_tau();

#ifdef GEOMETRIC_MESH_LIBRARY_IMPLEMENTATION_H

gml_vec3f gml_subtract(const gml_vec3f* left, const gml_vec3f* right) {
	gml_vec3f res = {
		(left->x - right->x),
		(left->y - right->y),
		(left->z - right->z)
	};
	return res;
}

gml_vec3f gml_cross_product(const gml_vec3f* left, const gml_vec3f* right) {
	gml_vec3f v = {
		(left->y * right->z) - (left->z * right->y),
		(left->z * right->x) - (left->x * right->z),
		(left->x * right->y) - (left->y * right->x)
	};
	return v;
}

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

gml_vec3f gml_get_normal(gml_vec3f q, gml_vec3f r, gml_vec3f s) {
	gml_normalize(&q);
	gml_normalize(&r);
	gml_normalize(&s);
	gml_vec3f qr = gml_subtract(&r, &q);
	gml_vec3f qs = gml_subtract(&s, &q);
	gml_vec3f normal = gml_cross_product(&qr, &qs);
	gml_normalize(&normal);
	return normal;
}

void gml_create_mesh(gml_mesh* m, unsigned int init) {
	m->m_vertices = (gml_vec3f*)malloc(init * sizeof(gml_vec3f));
	m->m_indices = (unsigned int*)malloc(init * sizeof(unsigned int));
	m->n_vertices = init;
	m->n_indices = init;
	m->used_vertices = 0;
	m->used_indices = 0;
}

void gml_delete_mesh(gml_mesh* m) {
	free(m);
}

int gml_contains(const gml_mesh* m, const gml_vec3f* v) {
	for (unsigned int i = 0; i < m->used_vertices; i++) {
		if (m->m_vertices[i].x == v->x && m->m_vertices[i].y == v->y && m->m_vertices[i].z == v->z ) {
			return i;
		}
	}
	return -1;
}

unsigned int gml_get_idx(const gml_mesh* m, const gml_vec3f* v) {
	int j = gml_contains(m, v);
	if (j > -1) {
		return (unsigned int)j;
	}
	if (m->used_indices >= 1) {
		unsigned int largest = 0;
		for (unsigned int i = 0; i < m->used_indices; i++) {
			if (m->m_indices[i] > largest) {
				largest = m->m_indices[i];
			}
		}
		// return largest + 1;
		return largest + 1;
	}
	else {
		return 0; 
	}
}

void gml_add_face(gml_mesh* m, gml_vec3f vs[], unsigned int n_vs) {
	if (m == NULL) {
		printf("[ERROR] add_face: Mesh is null or uninitalized\n");
		return;
	}
	if (m->used_vertices + n_vs >= m->n_vertices) {
		m->n_vertices *= 2;
		gml_vec3f* buffer = (gml_vec3f*)realloc(m->m_vertices, m->n_vertices * sizeof(gml_vec3f));
		if (buffer == NULL) {
			printf("[ERROR] add_face: Error allocating memory for m_vertices\n");
			return;
		}
		m->m_vertices = buffer;
	}
	if (m->used_indices + n_vs >= m->n_indices) {
		m->n_indices *= 2;
		unsigned int* buffer = (unsigned int*)realloc(m->m_indices, m->n_indices * sizeof(unsigned int));
		if (buffer == NULL) {
			printf("[ERROR] add_face: Error allocating memory for m_indices\n");
			return;
		}
		m->m_indices = buffer;
	}
	for (unsigned int n = 0; n < n_vs; n++) {
		if (gml_contains(m, &vs[n]) == -1) {
			m->m_vertices[m->used_vertices++] = vs[n];
		}
	}
	for (unsigned int k = 0; k < n_vs - 2; k++) {
		m->m_indices[m->used_indices++] = (unsigned int)gml_get_idx(m, &vs[k]);
		m->m_indices[m->used_indices++] = (unsigned int)gml_get_idx(m, &vs[k + 1]);
		m->m_indices[m->used_indices++] = (unsigned int)gml_get_idx(m, &vs[k + 2]);
	}
}

void gml_add_triangle(gml_mesh* m, gml_vec3f* x, gml_vec3f* y, gml_vec3f* z) {
	// Don't Repeat Yourself
	gml_vec3f vs[3] = { *x, *y, *z };
	gml_add_face(m, vs, 3);
}

void gml_add_quad(gml_mesh* m, gml_vec3f* x, gml_vec3f* y, gml_vec3f* z, gml_vec3f* w) {
	// Don't Repeat Yourself
	gml_vec3f vs[4] = { *x, *y, *z, *w };
	gml_add_face(m, vs, 4);
}

void gml_print_mesh(const gml_mesh* m) {
	printf("Mesh [%p] has [%u] vertices\n", (void*)m, m->used_vertices);
	for (unsigned int i = 0; i < m->used_vertices; i++) {
		printf("Vertex [%d]\t--- (%.2f, %.2f, %.2f)\n", i, m->m_vertices[i].x, m->m_vertices[i].y, m->m_vertices[i].z);
	}
	for (unsigned int i = 0; i < m->used_indices; i++) {
		printf("Index [%d]\t--- %d\n", i, m->m_indices[i]);
	}
	printf("\n");
}

float gml_tau() {
	return (1.0f + sqrtf(5.0f)) / 2.0f;
}

#endif /* GEOMETRIC_MESH_LIBRARY_IMPLEMENTATION_H */

#endif /* GEOMETRIC_MESH_LIBRARY */
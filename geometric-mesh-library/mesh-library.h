#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float tau() {
	return (1.0f + sqrt(5.0f)) / 2.0f;
}

typedef struct {
	float x;
	float y;
	float z;
} vec3f;

typedef struct {
	vec3f points[3];
	vec3f normal;
} triangle;

typedef struct {
	triangle* m_triangles;
	unsigned int* m_indices;
	size_t used_triangles;
	size_t used_indices;
	size_t n_triangles;
	size_t n_indices;
} mesh;

vec3f subtract(const vec3f* left, const vec3f* right) {
	vec3f res = {
		(left->x - right->x),
		(left->y - right->y),
		(left->z - right->z)
	};
	return res;
}

vec3f cross_product(const vec3f* left, const vec3f* right) {
	vec3f v = {
		(left->y * right->z) - (left->z * right->y),
		(left->z * right->x) - (left->x * right->z),
		(left->x * right->y) - (left->y * right->x)
	};
	return v;
}

void normalize(vec3f* normal) {
	float f = sqrtf((normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z));
	if (f <= 0.0f) {
		printf("Issue with normalization");
		return;
	}
	normal->x = normal->x / f;
	normal->y = normal->y / f;
	normal->z = normal->z / f;
}

vec3f get_normal(vec3f q, vec3f r, vec3f s) {
	normalize(&q);
	normalize(&r);
	normalize(&s);
	vec3f qr = subtract(&r, &q);
	vec3f qs = subtract(&s, &q);
	vec3f normal = cross_product(&qr, &qs);
	normalize(&normal);
	return normal;
}

void create_mesh(mesh* m, size_t init) {
	m->m_triangles = malloc(init * sizeof(triangle));
	m->m_indices = malloc(init * sizeof(unsigned int) * 3);
	m->n_triangles = init;
	m->n_indices = init * 3;
	m->used_indices = 0;
	m->used_triangles = 0;
}

triangle build_triangle(vec3f x, vec3f y, vec3f z) {
	/*printf("(%.2f, %.2f, %.2f)\n", x.x, x.y, x.z);
	printf("(%.2f, %.2f, %.2f)\n", y.x, y.y, y.z);
	printf("(%.2f, %.2f, %.2f)\n", z.x, z.y, z.z);*/
	vec3f n = get_normal(x, y, z);
	triangle t = { x, y, z, n };
	return t;
}

unsigned int get_idx(const mesh* m, const vec3f* v) {
	for (int i = 0; i < m->n_triangles; i++) {
		for (int j = 0; j < 3; j++) {
			if (m->m_triangles[i].points[j].x == v->x &&
				m->m_triangles[i].points[j].y == v->y &&
				m->m_triangles[i].points[j].z == v->z
				) {
				return m->m_indices[(3 * i) + j];
			}
		}
	}
	if (m->used_indices >= 1) {
		unsigned int largest = 0;
		for (int i = 0; i < m->used_indices; i++) {
			if (m->m_indices[i] > largest) {
				largest = m->m_indices[i];
			}
		}
		return largest + 1;
	}
	else {
		return 0;
	}
}

void add_triangle(mesh* m, vec3f x, vec3f y, vec3f z) {
	if (m->used_triangles >= m->n_triangles) {
		m->n_triangles *= 2;
		triangle* buffer = (triangle*)realloc(m->m_triangles, m->n_triangles * sizeof(triangle));
		if (buffer == NULL) {
			printf("Error allocating memory for m_triangles");
			return;
		}
		m->m_triangles = buffer;
	}
	if (m->used_indices + 3 >= m->n_indices) {
		m->n_indices *= 2;
		unsigned int* buffer = (unsigned int*)realloc(m->m_indices, m->n_indices * sizeof(unsigned int));
		if (buffer == NULL) {
			printf("Error allocating memory for m_indices");
			return;
		}
		m->m_indices = buffer;
	}
	m->m_indices[m->used_indices++] = get_idx(m, &x);
	m->m_indices[m->used_indices++] = get_idx(m, &y);
	m->m_indices[m->used_indices++] = get_idx(m, &z);
	triangle t = build_triangle(x, y, z);
	m->m_triangles[m->used_triangles++] = t;
}

void add_quad(mesh* m, vec3f x, vec3f y, vec3f z, vec3f w) {
	add_triangle(m, x, y, z);
	add_triangle(m, x, z, w);
}

void print_mesh(mesh* m) {
	for (int i = 0; i < m->used_triangles; i++) {
		printf("Triangle [%d] --- (%.2f, %.2f, %.2f)\n", i, m->m_triangles[i].points[0].x, m->m_triangles[i].points[0].y, m->m_triangles[i].points[0].z);
		printf("Triangle [%d] --- (%.2f, %.2f, %.2f)\n", i, m->m_triangles[i].points[1].x, m->m_triangles[i].points[1].y, m->m_triangles[i].points[1].z);
		printf("Triangle [%d] --- (%.2f, %.2f, %.2f)\n\n", i, m->m_triangles[i].points[2].x, m->m_triangles[i].points[2].y, m->m_triangles[i].points[2].z);
	}
	for (int i = 0; i < m->used_triangles; i++) {
		printf("Normal [%d]   --- (%.2f, %.2f, %.2f)\n", i, m->m_triangles[i].normal.x, m->m_triangles[i].normal.y, m->m_triangles[i].normal.z);
	}
	for (int i = 0; i < m->used_indices; i++) {
		printf("Index [%d]	  --- %d\n", i, m->m_indices[i]);
	}
}
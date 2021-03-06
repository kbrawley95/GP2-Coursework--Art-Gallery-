#ifndef _CUBE_H
#define _CUBE_H

#include "common.h"
#include "Vertex.h"

using namespace glm;

static const Vertex cubeVerts[] = {
	//Front
	{ vec3(-10.0f, 10.0f, 10.0f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.3f,0.3f,0.3f) },// Top Left

	{ vec3(-10.0f, -10.0f, 10.0f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f),vec3(-0.3f,-0.3f,0.3f) },// Bottom Left

	{ vec3(10.0f, -10.0f, 10.0f),
	vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f),vec3(0.3f,-0.3f,0.3f) }, //Bottom Right

	{ vec3(10.0f, 10.0f, 10.0f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f),vec3(0.3f,0.3f,0.3f) },// Top Right


	//back
	{ vec3(-10.0f, 10.0f, -10.0f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f),vec3(-0.3f,0.3f,-0.3f) },// Top Left

	{ vec3(-10.0f, -10.0f, -10.0f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f),vec3(-0.3f,-0.3f,-0.3f) },// Bottom Left

	{ vec3(10.0f, -10.0f, -10.0f),
	vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f),vec3(0.3f,-0.3f,-0.3f) }, //Bottom Right

	{ vec3(10.0f, 10.0f, -10.0f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f),vec3(0.3f,0.3f,-0.3f) },// Top Right

};

static const int cubeIndices[] = {
	//front
	0, 2, 1,
	0, 3, 2,

	//left
	4, 1, 5,
	4, 0, 1,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 2, 5,
	6, 5, 2,

	//top
	4, 7, 0,
	0, 7, 3,

	//back
	4, 5, 6,
	4, 6, 7
};

static const int numberOfCubeIndices = 36;
static const int numberOfCubeVerts = 8;
#endif

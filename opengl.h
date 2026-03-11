

#ifndef OPENGL_H
#define OPENGL_H



#include <glad/glad.h>
#include <SDL2/SDL.h>



#define MAXIMUM_LIGHTS 128

#define ERROR(x) std::cout << x << " (" << (void*) this << ")" << std::endl

typedef struct Vector2
{

    float x;
    float y;

} Vector2;

typedef struct Vector3
{

    float x;
    float y;
    float z;

} Vector3;

typedef struct Transform
{

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

} Transform;

typedef struct vertex_t
{

    Vector3 position;
    Vector3 color;
    Vector2 texture_coordinates;


} vertex_t;

#endif
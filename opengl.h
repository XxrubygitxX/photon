

#ifndef OPENGL_H
#define OPENGL_H



#include <glad/glad.h>
#include <SDL2/SDL.h>



#define ERROR(x) std::cout << x << " (" << (void*) this << ")" << std::endl

typedef struct Vector3
{

    float x;
    float y;
    float z;

} Vector3;

#endif
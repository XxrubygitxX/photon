

#ifndef CAMERA_H
#define CAMERA_H


#include "opengl.h"

class CCamera
{

    public:

        Vector3 m_Position;
        Vector3 m_Direction;

        explicit CCamera();
        explicit CCamera(Vector3 p_Position, Vector3 p_Direction);
        virtual ~CCamera();

};

#endif
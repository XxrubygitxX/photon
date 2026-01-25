

#include "camera.h"




CCamera::CCamera()
{

    this->m_Position = {0.0f, 0.0f, 0.0f};
    this->m_Direction = {0.0f, 0.0f, 0.0f};

}

CCamera::CCamera(Vector3 p_Position, Vector3 p_Direction)
{

    this->m_Position = p_Position;
    this->m_Direction = p_Direction;

}

CCamera::~CCamera()
{

    

}
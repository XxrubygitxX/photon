

#ifndef TRANSFORM_H
#define TRANSFORM_H






#include "graphics.h"


class CTransform
{

    public:


        void Rotate(float p_X, float p_Y, float p_Z);
        void Rotate(Vector3 p_Amount);

        explicit CTransform();
        virtual ~CTransform();

    private:

        glm::vec3 m_Position;
        glm::quat m_Orientation;
        glm::vec3 m_Scale;

};

#endif
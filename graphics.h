

#ifndef GRAPHICS_H
#define GRAPHICS_H




#include <iostream>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include "shader.h"
#include "camera.h"
#include "image.h"





extern glm::vec3 g_CameraPosition;
extern glm::vec3 g_CameraRotation;
extern glm::vec3 g_CameraFront;
extern glm::vec3 g_CameraUp;

extern std::filesystem::path GetExecutableDir();



class CGraphicsSystem
{

    public:

        CWindow* m_Window;

        int Initialize(const windowparameters_t& p_WindowParameters);
        void Release();

        void Update();
        void Clear();

        void SetupProjection(unsigned int p_Shader);

        explicit CGraphicsSystem();
        virtual ~CGraphicsSystem();

};

#endif
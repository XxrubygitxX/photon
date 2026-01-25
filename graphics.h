

#ifndef GRAPHICS_H
#define GRAPHICS_H



#include <iostream>
#include <vector>
#include <filesystem>
#include "window.h"
#include "shader.h"
#include "camera.h"





extern std::filesystem::path GetExecutableDir();

class CGraphicsSystem
{

    public:

        CWindow* m_Window;

        CCamera* m_Camera;

        int Initialize(const windowparameters_t& p_WindowParameters);
        void Release();

        void Update();
        void Clear();

        explicit CGraphicsSystem();
        virtual ~CGraphicsSystem();

};

#endif
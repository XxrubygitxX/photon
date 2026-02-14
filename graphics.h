

#ifndef GRAPHICS_H
#define GRAPHICS_H



#include <iostream>
#include <vector>
#include <filesystem>
#include "window.h"
#include "shader.h"
#include "camera.h"







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
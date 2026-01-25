

#include "graphics.h"



CGraphicsSystem::CGraphicsSystem()
{

    this->m_Window = nullptr;

}

int CGraphicsSystem::Initialize(const windowparameters_t& p_WindowParameters)
{

    this->m_Window = new CWindow(p_WindowParameters);

    int return_value = this->m_Window->Initialize();

    if (return_value != 0)
    {

        ERROR("CGraphicsSystem ::  An error has occurred" << std::endl);

        return return_value;

    }

    this->m_Camera = new CCamera();

    return 0;

}

CGraphicsSystem::~CGraphicsSystem()
{

    this->Release();

}

void CGraphicsSystem::Update()
{

    SDL_GL_SwapWindow(this->m_Window->m_Window);

}

void CGraphicsSystem::Clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void CGraphicsSystem::Release()
{

    delete this->m_Window;
    this->m_Window = nullptr;

}
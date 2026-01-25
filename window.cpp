

#include "window.h"





CWindow::CWindow(const windowparameters_t& p_WindowParameters)
{

    this->m_Width = p_WindowParameters.width;
    this->m_Height = p_WindowParameters.height;
    this->m_X = p_WindowParameters.x;
    this->m_Y = p_WindowParameters.y;
    this->m_Fullscreen = p_WindowParameters.fullscreen;
    this->m_Active = false;

    this->m_Title = new char[p_WindowParameters.title_size]();

    this->m_BufferSize = p_WindowParameters.buffer_size;

    memcpy(this->m_Title, p_WindowParameters.title, p_WindowParameters.title_size);

}

CWindow::~CWindow()
{

    this->Release();

}

void CWindow::ChangeResolution(int p_Width, int p_Height)
{

    this->m_Width = p_Width;
    this->m_Height = p_Height;

}

void CWindow::SetFullscreen(bool p_Fullscreen)
{

    this->m_Fullscreen = p_Fullscreen;

}

void CWindow::ToggleFullscreen()
{

    this->m_Fullscreen = -this->m_Fullscreen;

}

void CWindow::SetPosition(int p_X, int p_Y)
{

    this->m_X = p_X;
    this->m_Y = p_Y;

}

int CWindow::Initialize()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    this->SetOpenGLAttributes();

    this->m_Window = SDL_CreateWindow(this->m_Title,
                                      this->m_X,
                                      this->m_Y,
                                      this->m_Width,
                                      this->m_Height,
                                      ((this->m_Fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN) | SDL_WINDOW_OPENGL);

    if (!this->m_Window) { ERROR("Could not create a window"); std::cout << SDL_GetError() << std::endl; return 1; }

    this->m_Context = SDL_GL_CreateContext(this->m_Window);

    if (!this->m_Context) { ERROR("Could not create an OpenGL context"); std::cout << SDL_GetError() << std::endl; return 1; }

    this->InitializeOpenGL();

    return 0;

}

void CWindow::Release()
{

    if (this->m_Window) { SDL_DestroyWindow(this->m_Window); this->m_Window = nullptr; }
    if (this->m_Context) { SDL_GL_DeleteContext(this->m_Context); this->m_Context = NULL; }

    if (this->m_Title) { delete[] this->m_Title; this->m_Title = nullptr; }

    SDL_Quit();

}

void CWindow::SetOpenGLAttributes()
{

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, this->m_BufferSize);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

}

void CWindow::InitializeOpenGL()
{

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}



#ifndef WINDOW_H
#define WINDOW_H



#include <iostream>
#include "opengl.h"

typedef struct windowparameters_t
{

    const char* title;
    const int width;
    const int height;
    const int x;
    const int y;
    const int title_size;
    const int buffer_size;
    const bool fullscreen;

} windowparameters_t;

class CWindow
{

    friend class CGraphicsSystem;

    public:

        void SetPosition(int p_X, int p_Y);
        void ChangeResolution(int p_Width, int p_Height);
        void SetFullscreen(bool p_Fullscreen);
        void ToggleFullscreen();

        int Initialize();
        void Release();

        void InitializeOpenGL();
        void SetOpenGLAttributes();

        explicit CWindow(const windowparameters_t& p_WindowParameters);
        virtual ~CWindow();

    private:

        SDL_Window* m_Window;
        SDL_GLContext m_Context;

        int m_Width;
        int m_Height;
        int m_X;
        int m_Y;
        int m_TitleSize;
        char* m_Title;
        bool m_Fullscreen;
        bool m_Active;
        int m_BufferSize;

};

#endif









#include <iostream>
#include <filesystem>
#include "opengl.h"
#include "graphics.h"






CGraphicsSystem* g_GraphicsSystem;



int main()
{

    float vertices[] = {
     1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
     1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
    0, 2, 1,
    0, 3, 2
    };

    unsigned int index_amount = sizeof(indices) / sizeof(indices[0]);

    const char* title = "Program";

    windowparameters_t windowparameters = {title, 800, 600, 100, 100, sizeof(title), 24, false};

    g_GraphicsSystem = new CGraphicsSystem();

    if (g_GraphicsSystem->Initialize(windowparameters) != 0)
    {

        delete g_GraphicsSystem;
        g_GraphicsSystem = nullptr;

        return 0;

    }

    CShader* shader = new CShader();

    shader->AddVertexShader((GetExecutableDir() / "vertex_shader.glsl").string().c_str());
    shader->AddFragmentShader((GetExecutableDir() / "fragment_shader.glsl").string().c_str());

    if (shader->Compile() != 0)
    {

        delete shader;
        shader = nullptr;

        delete g_GraphicsSystem;
        g_GraphicsSystem = nullptr;

        return 0;

    }


    if (shader->Link() != 0)
    {

        delete shader;
        shader = nullptr;

        delete g_GraphicsSystem;
        g_GraphicsSystem = nullptr;

        return 0;

    }

    unsigned int vertex_array_object;
    unsigned int vertex_buffer_object;
    unsigned int element_buffer_object;

    glGenBuffers(1, &vertex_buffer_object);
    glGenVertexArrays(1, &vertex_array_object);

    glGenBuffers(1, &element_buffer_object);

    glBindVertexArray(vertex_array_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    CImage* image = new CImage("texture.jpg");

    unsigned int texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->GetInfo().width, image->GetInfo().height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetImage());

    glGenerateMipmap(GL_TEXTURE_2D);

    bool active = true;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    g_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    g_CameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    g_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    g_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    const unsigned char* keyboard;
    
    long long current = SDL_GetPerformanceCounter();
    long long last = 0;
    float delta_time;

    float speed = 0.1f;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_Event event;

    while (active)
    {

        g_GraphicsSystem->Clear();

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {

                case SDL_QUIT:
                {

                    active = false;

                }

            }
            
        }

        last = current;
        current = SDL_GetPerformanceCounter();

        delta_time = (float) ((current - last) * 1000 / (float) SDL_GetPerformanceFrequency());

        keyboard = SDL_GetKeyboardState(NULL);

        if (keyboard[SDL_SCANCODE_W])
        {

            g_CameraPosition += g_CameraFront * speed * delta_time;

        }

        if (keyboard[SDL_SCANCODE_S])
        {

            g_CameraPosition += -g_CameraFront * speed * delta_time;

        }

        if (keyboard[SDL_SCANCODE_A])
        {

            g_CameraPosition += glm::normalize(glm::cross(g_CameraUp, g_CameraFront)) * speed * delta_time;

        }

        if (keyboard[SDL_SCANCODE_D])
        {

            g_CameraPosition += -glm::normalize(glm::cross(g_CameraUp, g_CameraFront)) * speed * delta_time;

        }

        g_GraphicsSystem->SetupProjection(shader->m_ShaderProgram);

        glUseProgram(shader->m_ShaderProgram);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(vertex_array_object);

        glDrawElements(GL_TRIANGLES, index_amount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        g_GraphicsSystem->Update();

    }

    delete image;
    image = nullptr;

    delete shader;
    shader = nullptr;

    delete g_GraphicsSystem;
    g_GraphicsSystem = nullptr;

    return 0;

}
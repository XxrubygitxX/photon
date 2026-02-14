




#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void CGraphicsSystem::SetupProjection(unsigned int p_Shader)
{

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    int model_location = glGetUniformLocation(p_Shader, "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

    int view_location = glGetUniformLocation(p_Shader, "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    int projection_location = glGetUniformLocation(p_Shader, "projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

}
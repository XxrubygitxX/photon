

#include "shader.h"





#ifdef __APPLE__

#include <mach-o/dyld.h>

#elif defined(_WIN32)

#include <windows.h>

#endif


std::filesystem::path GetExecutableDir()
{

#ifdef __APPLE__

    uint32_t size = 0;

    _NSGetExecutablePath(nullptr, &size);

    std::string path = std::string(size, '\0');

    _NSGetExecutablePath(path.data(), &size);

    return std::filesystem::weakly_canonical(path).parent_path();

#elif defined(_WIN32)

    char buffer[MAX_PATH];

    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    return std::filesystem::path(buffer).parent_path();

#else

    return std::filesystem::current_path();

#endif

}

static std::string get_file(std::ifstream& in)
{

    std::ostringstream sstr;
    sstr << in.rdbuf();

    return sstr.str();

}

CShader::CShader()
{

    this->m_VertexShaderCompiled = false;
    this->m_FragmentShaderCompiled = false;

}

CShader::CShader(const char* p_VertexPath, const char* p_FragmentPath)
{

    this->AddVertexShader(p_VertexPath);
    this->AddFragmentShader(p_FragmentPath);

}

CShader::~CShader()
{

    this->Release();

}

int CShader::Compile()
{

    int vertex_shader;
    int fragment_shader;

    int return_value = 0;

    if (this->m_VertexShaderFile.empty() || this->m_FragmentShaderFile.empty())
    {

        ERROR("CShader ::  Could not compile shader");

        return 1;

    }

    this->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertex_shader_file = this->m_VertexShaderFile.c_str();

    glShaderSource(this->m_VertexShader, 1, &vertex_shader_file, NULL);
    glCompileShader(this->m_VertexShader);

    glGetShaderiv(this->m_VertexShader, GL_COMPILE_STATUS, &vertex_shader);

    if (!vertex_shader)
    {

        ERROR("CShader ::  Vertex shader compilation failed");

        glDeleteShader(this->m_VertexShader);

        return_value = 1;

    } else { std::cout << "CShader ::  Vertex shader compiled successfully" << std::endl; }

    this->m_VertexShaderCompiled = (vertex_shader) ? true : false;

    const char* fragment_shader_file = this->m_FragmentShaderFile.c_str();

    glShaderSource(this->m_FragmentShader, 1, &fragment_shader_file, NULL);
    glCompileShader(this->m_FragmentShader);

    glGetShaderiv(this->m_FragmentShader, GL_COMPILE_STATUS, &fragment_shader);

    if (!fragment_shader)
    {

        ERROR("CShader ::  Fragment shader compilation failed");

        glDeleteShader(this->m_FragmentShader);

        return_value = 1;

    } else { std::cout << "CShader ::  Fragment shader compiled successfully" << std::endl; }

    this->m_FragmentShaderCompiled = (fragment_shader) ? true : false;

    return return_value;

}

int CShader::AddVertexShader(const char* p_Path)
{

    std::ifstream vertex_shader = std::ifstream(p_Path);

    if (vertex_shader.fail()) { ERROR("CShader ::  Could not open vertex shader " << p_Path); return 1; }

    this->m_VertexShaderFile = get_file(vertex_shader);

    return 0;

}

int CShader::AddFragmentShader(const char* p_Path)
{

    std::ifstream fragment_shader = std::ifstream(p_Path);

    if (fragment_shader.fail()) { ERROR("CShader ::  Could not open fragment shader " << p_Path); return 1; }

    this->m_FragmentShaderFile = get_file(fragment_shader);

    return 0;

}

int CShader::Link()
{

    int shader_program;

    if (!this->m_VertexShaderCompiled || !this->m_FragmentShaderCompiled)
    {

        ERROR("CShader ::  Could not link shaders");

        return 1;

    }

    this->m_ShaderProgram = glCreateProgram();

    glAttachShader(this->m_ShaderProgram, this->m_VertexShader);
    glAttachShader(this->m_ShaderProgram, this->m_FragmentShader);

    glLinkProgram(this->m_ShaderProgram);

    glGetProgramiv(this->m_ShaderProgram, GL_LINK_STATUS, &shader_program);

    if (!shader_program)
    {

        ERROR("CShader ::  Failed to link shaders");

        return 1;

    }

    glDeleteShader(this->m_VertexShader);
    glDeleteShader(this->m_FragmentShader);

    return 0;

}

void CShader::Release()
{

    if (this->m_ShaderProgramCreated) { glDeleteProgram(this->m_ShaderProgram); this->m_ShaderProgramCreated = false; }

}

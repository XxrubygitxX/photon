

#ifndef SHADER_H
#define SHADER_H




#include <iostream>
#include <fstream>
#include <sstream>
#include "opengl.h"

class CShader
{

    public:


        unsigned int m_ShaderProgram;

        int AddVertexShader(const char* p_Path);
        int AddFragmentShader(const char* p_Path);

        int Compile();
        int Link();

        void Release();

        explicit CShader();
        explicit CShader(const char* p_VertexPath, const char* p_FragmentPath);
        virtual ~CShader();

    private:


        unsigned int m_VertexShader;
        unsigned int m_FragmentShader;

        bool m_VertexShaderCompiled;
        bool m_FragmentShaderCompiled;
        bool m_ShaderLinked;
        bool m_ShaderProgramCreated;

        std::string m_VertexShaderFile;
        std::string m_FragmentShaderFile;

};

#endif


#ifndef MESH_H
#define MESH_H





#include <vector>
#include "opengl.h"



namespace Gfx
{

    enum class CallType : char
    {

        GFX_DRAW_BLEND = 0x00,
        GFX_DRAW_WIREFRAME = 0x01

    };

    enum class ShaderType : char
    {

        GFX_DEFAULT_SHADER,
        GFX_CUSTOM_SHADER

    };

    typedef struct GfxMesh
    {

        vertex_t* vertices;
        int* indices;
        int vertex_amount;
        int index_amount;

    } GfxMesh;

    typedef struct GfxCall
    {

        CallType call_type;
        ShaderType shader_type;
        GfxMesh* mesh;

    } GfxCall;

    class CMesh
    {

        public:


            GfxMesh* Cache();
            void Clear();

            CMesh(const vertex_t* p_Vertices, const int* p_Indices, int p_VertexAmount, int p_IndexAmount);
            virtual ~CMesh();

        private:

            
            GfxMesh* m_Instance;

            std::vector<vertex_t> m_Vertices;
            std::vector<int> m_Indices;

    };

}

#endif
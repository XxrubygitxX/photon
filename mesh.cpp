

#include "mesh.h"




Gfx::CMesh::CMesh(const vertex_t* p_Vertices, const int* p_Indices, int p_VertexAmount, int p_IndexAmount)
{



}

Gfx::CMesh::~CMesh()
{



}

Gfx::GfxMesh* Gfx::CMesh::Cache()
{

    if (this->m_Instance == nullptr)
    {

        this->m_Instance = new GfxMesh{this->m_Vertices.data(), this->m_Indices.data(), (int) this->m_Vertices.size(), (int) this->m_Indices.size()};

    }

    return this->m_Instance;

}

void Gfx::CMesh::Clear()
{

    if (this->m_Instance != nullptr)
    {

        delete this->m_Instance;
        this->m_Instance = nullptr;

    }

}
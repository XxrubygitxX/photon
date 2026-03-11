

#ifndef MODEL_H
#define MODEL_H




#include <vector>
#include "mesh.h"

class CModel
{

    public:


        CModel();
        virtual ~CModel();

    private:

        std::vector<Gfx::CMesh> m_Meshes;

};

#endif
#include "Vertex.h"

void lan::Vertex::InitNormal(std::vector<Vertex>& vertexs, std::vector<int>& indexs)
{
    for (int i = 0; i < indexs.size()-2; i+=3) {
        auto& vert0 = vertexs[indexs[i]];
        auto& vert1 = vertexs[indexs[i+1]];
        auto& vert2 = vertexs[indexs[i+2]];

        auto vec01 = vert1.Position - vert0.Position;
        auto vec02 = vert2.Position - vert0.Position;
        auto normal = Vector3F::cross(vec02, vec01);
        vert0.m_normal += normal;
        vert1.m_normal += normal;
        vert2.m_normal += normal;
    }
    for (unsigned int i = 0; i < vertexs.size(); i++) {
        vertexs[i].m_normal.normalized();
    }
}

#pragma once
#include"Vector3F.h"
#include"Vector2F.h"
#include<vector>
namespace lan {
    struct Vertex
    {
        Vector3F Position;
        Vector2F TexCoord;
        Vector3F m_normal;
        Vertex(Vector3F position, Vector2F texCoord) {
            Position = position;
            TexCoord = texCoord;
        }
        //给顶点数组生成法线，默认逆时针是正面
        static void InitNormal(std::vector<Vertex>& vertexs, std::vector<int>& indexs);
    };
}


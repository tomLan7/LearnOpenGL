#pragma once
#include"Vector3F.h"
#include"Vector2F.h"
namespace lan {
    struct Vertex
    {
        Vector3F Position;
        Vector2F TexCoord;
        Vertex(Vector3F position, Vector2F texCoord) {
            Position = position;
            TexCoord = texCoord;
        }
    };
}


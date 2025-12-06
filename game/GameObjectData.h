#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "glm/glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"

struct GameObjectData
{
    std::shared_ptr<VertexBuffer> objectVBO;
    std::shared_ptr<VertexArray> objectVAO;
    std::shared_ptr<IndexBuffer> objectIBO;
    BufferLayout bufferlayout;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    std::string texturePath = "";
    bool isCubeMap = false;
};

#endif
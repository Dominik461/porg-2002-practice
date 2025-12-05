#ifndef SHADERDEFINITIONPLAYER_H_
#define SHADERDEFINITIONPLAYER_H_

#include <string>

inline const std::string PLAYER_VERTEX_SHADER_SRC = R"(
    #version 460 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 tcoords;
    layout(location = 3) in vec3 color;

    
    uniform mat4 u_Model;
    uniform mat4 u_ViewProjection;


    out vec3 vertexColor;
    
    void main() {
        vec4 worldPos = u_Model * vec4(position, 1.0);
        gl_Position = u_ViewProjection * worldPos;
        vertexColor = color;
    }
)";

inline const std::string PLAYER_FRAGMENT_SHADER_SRC = R"(
    #version 460 core
    in vec3 vertexColor;
    out vec4 FragColor;
    
    void main() {
        FragColor = vec4(vertexColor, 1.0);
    }
)";

#endif
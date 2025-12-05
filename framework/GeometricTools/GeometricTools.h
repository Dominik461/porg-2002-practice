#ifndef GEOMETRICTOOLS_H_
#define GEOMETRICTOOLS_H_

#include <array>
#include <vector>
#include <iostream>

namespace GeometricTools
{
    constexpr std::array<float, 3 * 2> UnitTriangle2D = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f }; // [2,3]

    constexpr std::array<float, 3 * 2 * 2> UnitSquare2D = {
        // triangle 1
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f,
        // triganle 2
        0.5f, 0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f 
    }; // [2,6]

    constexpr std::array<float, 11 * 4> UnitSquare3DWithTexCoordsVertices = {
        // pos              // Normals        // T.C.     // Color
        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // close left
        -0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // far left
         0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // far right
         0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // close right
    };

    constexpr std::array<unsigned int, 3 * 2> UnitSquare3DWithTexCoordsIndices = {
        0, 1, 2,
        3, 0, 2,
    };

    constexpr std::array<float, 3 * 4 * 6> UnitCube3DVertices = {
        // front
        -0.5,  0.5,  0.5,
        -0.5, -0.5,  0.5,
        0.5, -0.5,  0.5,
        0.5,  0.5,  0.5,
        // back
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5,  0.5, -0.5,
        // left
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5,  0.5,
        -0.5,  0.5,  0.5,
        // right
        0.5,  0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5,  0.5,
        0.5,  0.5,  0.5,
        // top
        -0.5,  0.5,  0.5,
        -0.5,  0.5, -0.5,
        0.5,  0.5, -0.5,
        0.5,  0.5,  0.5,
        // bottom
        -0.5, -0.5,  0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5,  0.5,
    };

    constexpr std::array<int, 3 * 2 * 6> UnitCube3DIndices = {
        // first triangle    second triangle
            0, 1, 2,          2, 3, 0,       // front
            6, 5, 4,          4, 7, 6,       // back
            8, 9,10,         10,11, 8,       // left
           14,13,12,         12,15,14,       // right
           18,17,16,         16,19,18,       // top
           20,21,22,         22,23,20,       // bottom
    };

    // Cube with 24 vertices (each vertex repeated 3 times for each face it participates in)
    // Each vertex has: position (x,y,z) + normal (nx,ny,nz) = 6 floats
    constexpr std::array<float, 3 * 24 * 2> UnitCube3D24WNormals = {
        // FRONT FACE (normal: 0, 0, 1)
        // Positions          // Normals
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Bottom-left
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Bottom-right
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Top-right
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Top-left

        // BACK FACE (normal: 0, 0, -1)
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Top-left
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Top-right

        // TOP FACE (normal: 0, 1, 0)
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Front-left
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Front-right
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Back-right
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Back-left

        // BOTTOM FACE (normal: 0, -1, 0)
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Back-left
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Back-right
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Front-right
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Front-left

        // RIGHT FACE (normal: 1, 0, 0)
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Bottom-front
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Bottom-back
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Top-back
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Top-front

        // LEFT FACE (normal: -1, 0, 0)
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  // Bottom-back
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  // Bottom-front
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  // Top-front
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f   // Top-back
    };

    // Topology indices for 24-vertex cube (6 faces * 2 triangles * 3 vertices = 36 indices)
    constexpr std::array<unsigned int, 6 * 3 * 2> UnitCube3DTopologyTriangles24 = {
        // FRONT FACE
        0, 1, 2,    // Triangle 1
        2, 3, 0,    // Triangle 2

        // BACK FACE
        4, 5, 6,    // Triangle 1
        6, 7, 4,    // Triangle 2

        // TOP FACE
        8, 9, 10,   // Triangle 1
        10, 11, 8,  // Triangle 2

        // BOTTOM FACE
        12, 13, 14, // Triangle 1
        14, 15, 12, // Triangle 2

        // RIGHT FACE
        16, 17, 18, // Triangle 1
        18, 19, 16, // Triangle 2

        // LEFT FACE
        20, 21, 22, // Triangle 1
        22, 23, 20  // Triangle 2
    };


    /**
     * @brief Creates a UnitCube3D with an aspect ratio of width:height
     *
     * Generates a std::pair<std::array<float, 3 * 3 * 2 * 3 * 4* 6>, std::array<unsigned int, 3 * 2 * 6>>
     * Where std::array<float, 3 * 3 * 2 * 3 * 4 * 6> -> VBO (vertex positions (3), normals(3), tex  coords(2) and color (3))
     * Where std::array<unsigned int, 3 * 2 * 6> -> EBO (triangle indices)
     * Default values returns a cube
     *
     * @param width scale on X axis
     * @param height scale on Y axis
     * @return pair with VBO and EBO
     */
    inline std::pair<std::array<float, 11 * 4 * 6>, std::array<unsigned int, 3 * 2 * 6>> GetUnitCube3D(float width = 1.0f, float height = 1.0f)
    {
        std::array<float, 11 * 4 * 6> VBO = {
            // FRONT FACE (normal: 0, 0, 1)
            // Positions                           // Normals           // T.C.        // Color
            -0.5f / width, -0.5f / height,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-left
             0.5f / width, -0.5f / height,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-right
             0.5f / width,  0.5f / height,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-right
            -0.5f / width,  0.5f / height,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-left

            // BACK FACE (normal: 0, 0, -1)                                      
             0.5f / width, -0.5f / height, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-right
            -0.5f / width, -0.5f / height, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-left
            -0.5f / width,  0.5f / height, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-left
             0.5f / width,  0.5f / height, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-right

             // TOP FACE(normal: 0, 1, 0)                                         
             -0.5f / width,  0.5f / height,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Front-left
              0.5f / width,  0.5f / height,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Front-right
              0.5f / width,  0.5f / height, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Back-right
             -0.5f / width,  0.5f / height, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Back-left

             // BOTTOM FAE (normal: 0, -1, 0)                                     
             -0.5f / width, -0.5f / height, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Back-left
              0.5f / width, -0.5f / height, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Back-right
              0.5f / width, -0.5f / height,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Front-right
             -0.5f / width, -0.5f / height,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Front-left

             // RIGHT FACE (normal: 1, 0, 0)                                      
              0.5f / width, -0.5f / height,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-front
              0.5f / width, -0.5f / height, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-back
              0.5f / width,  0.5f / height, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-back
              0.5f / width,  0.5f / height,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-front

              // LEFT FACE(normal: -1, 0, 0)                                       
              -0.5f / width, -0.5f / height, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-back
              -0.5f / width, -0.5f / height,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // Bottom-front
              -0.5f / width,  0.5f / height,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-front
              -0.5f / width,  0.5f / height, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-back
        };

        std::array<unsigned int, 6 * 3 * 2> EBO = {
            // FRONT FACE
            0, 1, 2,    // Triangle 1
            2, 3, 0,    // Triangle 2

            // BACK FACE
            4, 5, 6,    // Triangle 1
            6, 7, 4,    // Triangle 2

            // TOP FACE
            8, 9, 10,   // Triangle 1
            10, 11, 8,  // Triangle 2

            // BOTTOM FACE
            12, 13, 14, // Triangle 1
            14, 15, 12, // Triangle 2

            // RIGHT FACE
            16, 17, 18, // Triangle 1
            18, 19, 16, // Triangle 2

            // LEFT FACE
            20, 21, 22, // Triangle 1
            22, 23, 20  // Triangle 2
        };

        return std::make_pair(VBO, EBO);
    }

    /**
     * @brief Creates a UnitGrid of dimension (divisionsX x divisionsY)
     *
     * Generates a std::pair<std::vector<float>, std::vector<int>>
     * Where std::vector<float> -> VBO (vertex positions)
     * Where std::vector<int> -> EBO (triangle indices)
     *
     * @param divisionsX Number of divisions along X axis
     * @param divisionsY Number of divisions along Y axis
     * @return pair with VBO and EBO
     */
    inline std::pair<std::vector<float>, std::vector<int>> GenerateUnitGrid2D(int divisionsX, int divisionsY)
    {
        std::vector<float> vertices;
        std::vector<int> indices;

        // Calculate spacing between tiles
        const float stepX = 1.0f / divisionsX;
        const float stepY = 1.0f / divisionsY;

        int vertexIndex = 0;

        // Create separate vertices for each tile (no sharing between tiles)
        for (int row = 0; row < divisionsY; ++row)
        {
            for (int col = 0; col < divisionsX; ++col)
            {
                // Calculate tile position
                float x = -0.5f + row * stepX;
                float y = 0.5f - col * stepY;

                // Create 4 vertices for this tile
                // Bottom-left
                vertices.insert(vertices.end(), { x, y - stepY });
                // Bottom-right
                vertices.insert(vertices.end(), { x + stepX, y - stepY });
                // Top-right
                vertices.insert(vertices.end(), { x + stepX, y });
                // Top-left
                vertices.insert(vertices.end(), { x, y });

                // Create indices for 2 triangles that form this tile
                // First triangle (bottom-left, bottom-right, top-left)
                indices.insert(indices.end(), { vertexIndex, vertexIndex + 1, vertexIndex + 3 });
                // Second triangle (bottom-right, top-right, top-left)
                indices.insert(indices.end(), { vertexIndex + 1, vertexIndex + 2, vertexIndex + 3 });

                vertexIndex += 4; // Move to next set of 4 vertices
            }
        }

        return std::make_pair(vertices, indices);
    }

    inline std::pair<std::vector<float>, std::vector<int>> GenerateUnitGrid2DWTCoords(int divisionsX, int divisionsY)
    {
        std::vector<float> vertices;
        std::vector<int> indices;

        // Calculate spacing between tiles
        const float stepX = 1.0f / divisionsX;
        const float stepY = 1.0f / divisionsY;

        float s, t;

        int vertexIndex = 0;

        // Create separate vertices for each tile (no sharing between tiles)
        for (int row = 0; row < divisionsY; ++row)
        {
            for (int col = 0; col < divisionsX; ++col)
            {
                // Calculate tile position
                float x = -0.5f + row * stepX;
                float y = 0.5f - col * stepY;

                // Create 4 vertices for this tile
                // Bottom-left
                s = 0.0f;
                t = 0.0f;
                vertices.insert(vertices.end(), { x, y - stepY, s, t });
                // Bottom-right
                s = 1.0f;
                t = 0.0f;
                vertices.insert(vertices.end(), { x + stepX, y - stepY, s, t });
                // Top-right
                s = 1.0f;
                t = 1.0f;
                vertices.insert(vertices.end(), { x + stepX, y, s, t });
                // Top-left
                s = 0.0f;
                t = 1.0f;
                vertices.insert(vertices.end(), { x, y, s, t });

                // Create indices for 2 triangles that form this tile
                // First triangle (bottom-left, bottom-right, top-left)
                indices.insert(indices.end(), { vertexIndex, vertexIndex + 1, vertexIndex + 3 });
                // Second triangle (bottom-right, top-right, top-left)
                indices.insert(indices.end(), { vertexIndex + 1, vertexIndex + 2, vertexIndex + 3 });

                vertexIndex += 4; // Move to next set of 4 vertices
            }
        }

        return std::make_pair(vertices, indices);
    }

}

#endif // !GEOMETRICTOOLS_H_
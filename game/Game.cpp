#include "Game.h"

Game::Game()
    : GLFWApplication("Exam Practice Application", "1.0"), m_window(nullptr),
    m_deltaTime(0.0f), m_lastFrameTime(0.0f), m_startTime(0.0f),
    m_renderer(nullptr)
{}

unsigned Game::init()
{   
    if (!getIsOpenGLInitialized())
        return 1;

    std::cout << "HEHEHEHEHE" << std::endl;
    m_window = getWindow();

    m_renderer = std::make_shared<Renderer>();

    createPlayer();
    createPlatforms();
    createFloor();
    createCamera();

    return 0;
}

unsigned Game::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        m_deltaTime = currentFrame - m_lastFrameTime;
        m_lastFrameTime = currentFrame;

        handleInput();

        movePlayer();

        m_renderer->draw(camera, m_floor->data, m_platformsData, m_player->data, m_deltaTime);

        // Swap buffers and poll events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    return 0;
}

void Game::shutdown()
{
}

void Game::createPlayer()
{
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 transform = glm::vec3(0.0f, 0.0f, 0.0f);
    float rotationDeg = 0.0f;

    auto cubeData = GeometricTools::GetUnitCube3D(1.0f, 1.0f);
    auto verticesData = cubeData.first;
    auto indicesData = cubeData.second;

    m_player = std::make_shared<Player>();

    m_player->data->modelMatrix = MatrixOperations::getTransformedMatrix(scale, rotationVec, rotationDeg, transform);

    // Create VAO and buffers using VertexBuffer and IndexBuffer classes
    m_player->data->objectIBO = std::make_shared<IndexBuffer>(indicesData.data(), indicesData.size());
    m_player->data->bufferlayout = BufferLayout({ {ShaderDataType::Float3, "position"}, {ShaderDataType::Float3, "normals"}, {ShaderDataType::Float2, "tcoords"}, {ShaderDataType::Float3, "color"} });

    m_player->data->objectVBO = std::make_shared<VertexBuffer>(verticesData.data(), verticesData.size() * sizeof(verticesData[0]));
    m_player->data->objectVBO->SetLayout(m_player->data->bufferlayout);

    m_player->data->objectVAO = std::make_shared<VertexArray>();
    m_player->data->objectVAO->Bind();
    m_player->data->objectVAO->SetIndexBuffer(m_player->data->objectIBO);
    m_player->data->objectVAO->AddVertexBuffer(m_player->data->objectVBO);

}

void Game::createPlatforms()
{
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
    
    float rotationDeg = 0.0f;

    for (int i = 0; i <= 1; i++)
    {
        glm::vec3 transform = glm::vec3(6.0f, 0.0f, 0.0f);
        std::shared_ptr<Platform> platform = std::make_shared<Platform>();

        auto& cubeData = GeometricTools::GetUnitCube3D(1.0f, 2.0f);
        auto& verticesData = cubeData.first;
        auto& indicesData = cubeData.second;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        platform->data->modelMatrix = MatrixOperations::getTransformedMatrix(scale, rotationVec, rotationDeg, transform);

        

        for (float data : verticesData)
        {
            vertices.push_back(data);
        }

        for (unsigned int data : indicesData)
        {
            indices.push_back(data);
        }

        // Create VAO and buffers using VertexBuffer and IndexBuffer classes
        platform->data->objectIBO = std::make_shared<IndexBuffer>(indices.data(), indices.size());
        platform->data->bufferlayout = BufferLayout({ {ShaderDataType::Float3, "position"}, {ShaderDataType::Float3, "normals"}, {ShaderDataType::Float2, "tcoords"}, {ShaderDataType::Float3, "color"} });

        platform->data->objectVBO = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(vertices[0]));
        platform->data->objectVBO->SetLayout(platform->data->bufferlayout);

        platform->data->objectVAO = std::make_shared<VertexArray>();
        platform->data->objectVAO->Bind();
        platform->data->objectVAO->SetIndexBuffer(platform->data->objectIBO);
        platform->data->objectVAO->AddVertexBuffer(platform->data->objectVBO);


        m_platforms.push_back(platform);
        m_platformsData.push_back(platform->data);

    }
}

void Game::createFloor()
{

    glm::vec3 scale = glm::vec3(4.0f);
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 transform = glm::vec3(0.0f, -3.0f, 0.0f);
    float rotationDeg = 0.0f;

    auto& verticesData = GeometricTools::UnitSquare3DWithTexCoordsVertices;
    auto& indicesData = GeometricTools::UnitSquare3DWithTexCoordsIndices;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    m_floor = std::make_shared<Floor>();

    m_floor->data->modelMatrix = MatrixOperations::getTransformedMatrix(scale, rotationVec, rotationDeg, transform);

    for(float data : verticesData)
    {
        vertices.push_back(data);
    }

    for(float data : indicesData)
    {
        indices.push_back(data);
    }

    // Create VAO and buffers using VertexBuffer and IndexBuffer classes
    m_floor->data->objectIBO = std::make_shared<IndexBuffer>(indices.data(), indices.size());
    m_floor->data->bufferlayout = BufferLayout({ {ShaderDataType::Float3, "position"}, {ShaderDataType::Float3, "normals"}, {ShaderDataType::Float2, "tcoords"}, {ShaderDataType::Float3, "color"} });
    m_floor->data->objectVBO = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(vertices[0]));
    m_floor->data->objectVBO->SetLayout(m_floor->data->bufferlayout);

    m_floor->data->objectVAO = std::make_shared<VertexArray>();
    m_floor->data->objectVAO->Bind();
    m_floor->data->objectVAO->SetIndexBuffer(m_floor->data->objectIBO);
    m_floor->data->objectVAO->AddVertexBuffer(m_floor->data->objectVBO);

}

void Game::createCamera()
{
    float fov = 45.0f;
    float aspectRatio = 1.0f;
    float nearPlane = 1.0f;
    float farPlane = 100.0f;

    glm::vec3 ori = { 0, 0, 0 };
    glm::vec3 up = { 0, 1, 0 };

    camera = PerspectiveCamera({ fov, float(WINDOW_WIDTH) , float(WINDOW_HEIGHT), nearPlane, farPlane }, cameraPos, ori, up);
}

void Game::updateCamera()
{
    cameraPos.x = m_player->moveDir.x;
    cameraPos.y = m_player->moveDir.y;

    camera.SetLookAt(m_player->moveDir);
    camera.SetPosition(cameraPos);
}

//Check if the player is touching ground
bool Game::checkCollison()
{
    if (m_player->isGrounded)
        m_player->isGrounded = false;

    return false;
}


void Game::handleInput()
{
    jump = false;
    // Exit when Q key is pressed
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
        return;
    }
    // Left
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_player->moveDir.x -= m_player->SPEED * m_deltaTime;
        checkCollison();
    }
    // Right
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_player->moveDir.x += m_player->SPEED * m_deltaTime;
        checkCollison();
    }
    // Up
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // Double speed for the jump
        m_player->moveDir.y += m_player->JUMPSPEED * m_deltaTime;
        jump = true;
        checkCollison();
    }


}


void Game::movePlayer()
{
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
    float rotationDeg = 0.0f;

    if (!m_player->isGrounded && !jump)
    {
        m_player->moveDir.y += GRAVITY * m_deltaTime;
    }

    m_player->data->modelMatrix = MatrixOperations::getTransformedMatrix(scale, rotationVec, rotationDeg, m_player->moveDir);
    std::cout << "........................................................" << std::endl;
    extractAxes(m_player->data->modelMatrix);

    // Update the camera position and where it should look at
    updateCamera();
}

// Just for checking matrix math
void Game::extractAxes(const glm::mat4& transform) {
    // Extract the basis vectors
    glm::vec3 right = glm::vec3(transform[0]);
    glm::vec3 up = glm::vec3(transform[1]);
    glm::vec3 forward = glm::vec3(transform[2]);
    glm::vec3 position = glm::vec3(transform[3]);

    std::cout << "Right (X-axis):   (" << right.x << ", " << right.y << ", " << right.z << ")\n";
    std::cout << "Up (Y-axis):      (" << up.x << ", " << up.y << ", " << up.z << ")\n";
    std::cout << "Forward (Z-axis): (" << forward.x << ", " << forward.y << ", " << forward.z << ")\n";
    std::cout << "Position:         (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
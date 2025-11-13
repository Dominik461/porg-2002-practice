#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GeometricTools.h>

#include <cstdlib>
#include <iostream>
#include <cmath>

const int WIDTH = 900;
const int HEIGHT = 900;
const char* TITLE = "Hello World";

// Shader sources
const std::string VERTEX_SHADER_SRC = R"(
    #version 430 core

    layout(location = 0) in vec2 position;
    layout(location = 1) in vec3 color;

    out vec3 vertexColor;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
        vertexColor = color;
    }
)";

const std::string FRAGMENT_SHADER_SRC = R"(
    #version 430 core

    in vec3 vertexColor;
    uniform vec3 backgroundColor;
    out vec4 color;
    
    void main()
    {
        color = vec4(vertexColor, 1.0);
    }
)";

const auto TRIANGLE = GeometricTools::UnitTriangle2D;
const auto SQUARE = GeometricTools::UnitSquare2D;

const float TRIANGLE_COLORS[3 * 3] = {
    // colors (initial values)
     1.0f, 0.0f, 0.0f, // bottom left - red
     0.0f, 1.0f, 0.0f,  // bottom right - green
     0.0f, 0.0f, 1.0f     // top - blue
};

const float SQUARE_COLORS[3 * 3 * 2] = {
    // colors (initial values)
    // triangle 1
     0.0f, 0.0f, 1.0f, // blue
     0.0f, 0.0f, 1.0f, // blue
     0.0f, 0.0f, 1.0f, // blue
     // triangle 2
     0.0f, 0.0f, 1.0f, // blue
     0.0f, 0.0f, 1.0f, // blue
     0.0f, 0.0f, 1.0f  // blue
};


bool initializeGLFW();
GLFWwindow* createWindow();
bool initializeGLAD();
GLuint compileShader(GLenum type, const std::string& source);
GLuint createShaderProgram();
void setupGeometry(GLuint VAOs[], GLuint VBOs[]);
void renderLoop(GLFWwindow* window, GLuint VAOs[], GLuint VBOs[], GLuint shaderProgram);
void cleanup(GLFWwindow* window);
void updateTriangleColorBuffer(GLuint VBO, float time);
void updateSquareColors(GLuint VBO, float time);

int main(int argc, char** argv)
{
    // GLFW initialization code (SECTION 2)
    if (!initializeGLFW())
        return EXIT_FAILURE;

    // OpenGL initialization code (SECTION 3)
    GLFWwindow* window = createWindow();
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    if (!initializeGLAD())
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // OpenGL data transfer code (SECTION 4)   
    GLuint VAOs[2], VBOs[4];
    setupGeometry(VAOs, VBOs);


    GLuint shaderProgram = createShaderProgram();
    if (shaderProgram == 0)
    {
        cleanup(window);
        return EXIT_FAILURE;
    }

    glUseProgram(shaderProgram);
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

    // Application loop code (SECTION 5)
    renderLoop(window, VAOs, VBOs, shaderProgram);

    // Termination code (SECTION 6)
    cleanup(window);
    // No more GLFW calls after this point

    return EXIT_SUCCESS;
}

/**
 * @brief Initializes the GLFW library.
 *
 * This function attempts to initialize the GLFW library, which is required for creating windows and contexts
 * for OpenGL. If initialization fails, an error message is printed to the standard error stream.
 *
 * @return true if GLFW was successfully initialized, false otherwise.
 */
bool initializeGLFW()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Creates and initializes a GLFW window with specified OpenGL context version.
 *
 * This function sets the OpenGL context version to 4.3 using glfwWindowHint,
 * creates a window with the given WIDTH, HEIGHT, and TITLE, and makes the context current.
 * If window creation fails, it prints an error message to std::cerr, terminates GLFW,
 * and returns nullptr.
 *
 * @return Pointer to the created GLFWwindow, or nullptr if creation fails.
 */
GLFWwindow* createWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}

/**
 * @brief Initializes the GLAD OpenGL loader.
 *
 * This function attempts to load all OpenGL function pointers using GLAD and GLFW.
 * It should be called after creating an OpenGL context with GLFW.
 *
 * @return true if GLAD was successfully initialized, false otherwise.
 */
bool initializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Compiles an OpenGL shader from source code.
 *
 * This function creates a shader object of the specified type, sets its source code,
 * and compiles it. If compilation fails, it prints the error log to std::cerr,
 * deletes the shader object, and returns 0.
 *
 * @param type The type of shader to compile (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
 * @param source The source code of the shader as a std::string.
 * @return GLuint The compiled shader object, or 0 if compilation failed.
 */
GLuint compileShader(GLenum type, const std::string& source)
{
    // Create a shader object of the specified type (vertex or fragment)
    GLuint shader = glCreateShader(type);

    // Set the shader source code
    const GLchar* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);

    // Compile the shader
    glCompileShader(shader);

    // Check if compilation was successful
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        // If compilation failed, retrieve and print the error log
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
            << infoLog << std::endl;
        // Delete the shader object to free resources
        glDeleteShader(shader);
        return 0;
    }
    // Return the compiled shader object
    return shader;
}

/**
 * @brief Creates and links an OpenGL shader program from predefined vertex and fragment shader sources.
 *
 * This function compiles the vertex and fragment shaders using the provided source code,
 * attaches them to a new shader program, and links the program. If compilation or linking fails,
 * it outputs an error message and cleans up any allocated resources.
 *
 * @return GLuint The handle to the created shader program, or 0 if an error occurred.
 */
GLuint createShaderProgram()
{
    // Compile the vertex shader from source
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, VERTEX_SHADER_SRC);
    if (vertexShader == 0)
        return 0; // Return 0 if compilation failed

    // Compile the fragment shader from source
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC);
    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader); // Clean up vertex shader if fragment fails
        return 0;
    }

    // Create a shader program and attach both shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check if linking was successful
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        // If linking failed, retrieve and print the error log
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n"
            << infoLog << std::endl;
        // Clean up shaders and program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        return 0;
    }

    // Shaders are no longer needed after linking, so delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Return the linked shader program
    return shaderProgram;
}

/**
 * @brief Initializes geometry data for rendering a triangle and a square using OpenGL.
 *
 * This function generates and configures three Vertex Array Objects (VAOs) and three Vertex Buffer Objects (VBOs)
 * for rendering one triangle and two triangles that together form a square. It sets up vertex attributes for
 * position (location = 0) and color (location = 1) for each geometry.
 *
 * @param VAOs Array of GLuint identifiers for the Vertex Array Objects. Must have space for at least 2 VAOs.
 * @param VBOs Array of GLuint identifiers for the Vertex Buffer Objects. Must have space for at least 4 VBOs.
 *
 * @note The vertex data arrays (TRIANGLE, TRIANGLE_COLORS, SQUARE, SQUARE_COLORS) must be defined elsewhere.
 *       Each vertex is expected to have 2 position floats (stride = 2 * sizeof(float) and each color is expected to have 3 color floats (stride = 3 * sizeof(float)).
 */
void setupGeometry(GLuint VAOs[], GLuint VBOs[])
{
    glGenVertexArrays(2, VAOs);
    glGenBuffers(4, VBOs);

    // Setup for the triangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TRIANGLE), TRIANGLE.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup for the triangle colors
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TRIANGLE_COLORS), TRIANGLE_COLORS, GL_DYNAMIC_DRAW);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Setup for square
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE), SQUARE.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup for the square colors
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_COLORS), SQUARE_COLORS, GL_DYNAMIC_DRAW);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

}

/**
 * @brief Main rendering loop for the OpenGL application.
 *
 * Continuously polls window events and renders the scene until the window is closed.
 * Dynamically updates the background color and the colors of the triangle and square
 * based on elapsed time, creating animated effects.
 *
 * @param window Pointer to the GLFW window.
 * @param VAOs Array of Vertex Array Object identifiers.
 *        VAOs[0] - triangle, VAOs[1] - square (two triangles).
 * @param VBOs Array of Vertex Buffer Object identifiers.
 *        VBOs[0] - triangle, VBOs[1] - triangle color, VBOs[2] - square (two triangles), VBOs[3] - square color.
 * @param shaderProgram OpenGL shader program identifier.
 */
void renderLoop(GLFWwindow* window, GLuint VAOs[], GLuint VBOs[], GLuint shaderProgram)
{
    GLint backgroundColorLocation = glGetUniformLocation(shaderProgram, "backgroundColor");

    float startTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - startTime;

        // Update background color
        float bgR = (sin(deltaTime * 0.3f) + 1.0f) * 0.5f;
        float bgG = (cos(deltaTime * 0.2f) + 1.0f) * 0.2f;
        float bgB = (sin(deltaTime * 0.4f + 1.0f) + 1.0f) * 0.3f;
        glClearColor(bgR, bgG, bgB, 1.0f);
        glUniform3f(backgroundColorLocation, bgR, bgG, bgB);

        // Update triangle colors
        updateTriangleColorBuffer(VBOs[1], deltaTime);

        // Update square colors
        updateSquareColors(VBOs[3], deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw square (two triangles)
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Draw triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }
}

/**
 * @brief Cleans up and terminates the GLFW window and context.
 *
 * This function destroys the provided GLFW window and terminates the GLFW library,
 * releasing all associated resources. It should be called before exiting the application
 * to ensure proper cleanup of GLFW resources.
 *
 * @param window Pointer to the GLFW window to be destroyed.
 */
void cleanup(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


/**
 * @brief Updates the color attributes for a triangle's vertices based on the elapsed time.
 *
 * This function animates the colors of a triangle by calculating new color values
 * for each vertex using the sine of the provided time parameter. The colors smoothly
 * transition over time, creating an animated effect. The updated vertex data is then
 * uploaded to the GPU using glBufferSubData.
 *
 * @param VBO The Vertex Buffer Object (VBO) identifier to update.
 * @param time The elapsed time value used to animate the colors.
 */
void updateTriangleColorBuffer(GLuint VBO, float time)
{
    float triangleColor[3 * 3] = {
        // animated colors
        float((sin(time) + 1.0f) * 0.5f), 0.0f, 0.0f,
        0.0f, float((sin(time + 2.0f) + 1.0f) * 0.5f), 0.0f,
        0.0f, 0.0f, float((sin(time + 4.0f) + 1.0f) * 0.5f)
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleColor), triangleColor);
}

/**
 * @brief Updates the color attributes of two square vertex buffers based on the given time.
 *
 * This function calculates RGB color values using trigonometric functions of the input time,
 * creating smooth color transitions. It then updates the vertex buffer object (VBO)
 * with new vertex data, where each vertex contains color attributes.
 *
 * @param VBO The OpenGL vertex buffer object with 2 triangles to form a square.
 * @param time The current time value used to animate the colors.
 */
void updateSquareColors(GLuint VBO, float time)
{
    // Calculate RGB color values using trigonometric functions for smooth animation
    float r = (cos(time * 0.4f) + 1.0f) * 0.5f;
    float g = (sin(time * 0.7f) + 1.0f) * 0.5f;
    float b = (sin(time * 0.3f + 1.5f) + 1.0f) * 0.5f;

    // Vertex data for the first triangle of the square (positions + animated color)
    float squareColor[3 * 3 * 2] = {
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b
    };

    // Update the vertex buffer for the first triangle of the square
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(squareColor), squareColor);
}
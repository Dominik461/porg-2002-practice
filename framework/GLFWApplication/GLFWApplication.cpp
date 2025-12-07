#include "GLFWApplication.h"

unsigned GLFWApplication::init()
{
    std::cout << "GLFWApplication::Init() called" << std::endl;
    return 0;
}

void GLFWApplication::shutdown()
{
    std::cout << "GLFWApplication::Shutdown() called" << std::endl;
}

unsigned GLFWApplication::run()
{
    std::cout << "GLFWApplication::run() called" << std::endl;
    return 0;
}

void GLFWApplication::initializeOpenGL()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, getName().c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL init complete" << std::endl;

    m_isOpenGLInitialized = true;
}
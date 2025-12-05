# Create the Lab5Application library
add_library(PracticeLib
    GameObjectData.h
    Game.cpp Game.h
)

# Include directories for the library
target_include_directories(PracticeLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/framework/GLFWApplication
    ${CMAKE_SOURCE_DIR}/framework/GeometricTools
    ${CMAKE_SOURCE_DIR}/framework/Rendering
    ${CMAKE_SOURCE_DIR}/framework/Projection
)

# Link Lab3Application with required dependencies
target_link_libraries(PracticeLib
    Renderer
    GLFWApplication
    GeometricTools
    Rendering
    Projection
    glad
    glfw
    stb
    glm
)

target_compile_definitions(PracticeLib PRIVATE
  TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/")

target_compile_definitions(PracticeLib PRIVATE STB_IMAGE_IMPLEMENTATION)

add_executable(Practice
    Main.cpp
)

# Link Lab3Test with the Lab3Application library
target_link_libraries(Practice
    PracticeLib
)

# Set output directory for the test executable
set_target_properties(Practice PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

#add_custom_command(
#  TARGET Practice POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy
#  ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/cube_texture.jpg
#  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/cube_texture.jpg
#)
#
#add_custom_command(
#  TARGET Practice POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy
#  ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/floor_texture.jpg
#  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/floor_texture.jpg
#)
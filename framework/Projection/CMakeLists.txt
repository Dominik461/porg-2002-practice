add_library(Projection Matrices.cpp Matrices.h)
add_library(Framework::Projection ALIAS Projection)
target_include_directories(Projection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Projection PUBLIC glad glfw glm)
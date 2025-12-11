cmake_minimum_required(VERSION 4.0)
project(NFA_Traversal_Steps)

set(CMAKE_CXX_STANDARD 20)



add_executable(NFA_Traversal_Steps
        src/main.cpp
        src/Tools/tinyfiledialogs.c
        src/Automatas/nfa.cpp  src/Automatas/state.cpp  src/Automatas/transition.cpp
        src/Renderer/renderer.cpp
)

target_include_directories(NFA_Traversal_Steps PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(NFA_Traversal_Steps PRIVATE RAYGUI_IMPLEMENTATION)
target_link_libraries(NFA_Traversal_Steps PRIVATE
        raylib
)

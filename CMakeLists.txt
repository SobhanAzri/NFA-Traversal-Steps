cmake_minimum_required(VERSION 4.0)
project(NFA_Traversal_Steps)

set(CMAKE_CXX_STANDARD 20)

add_executable(NFA_Traversal_Steps
        src/main.cpp
        src/Tools/tinyfiledialogs.cpp
        src/Automatas/nfa.cpp  src/Automatas/state.cpp  src/Automatas/transition.cpp
        src/Renderer/renderer.cpp
        include/Tools/fileLoader.h
        src/Tools/fileLoader.cpp
)

target_include_directories(NFA_Traversal_Steps PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(NFA_Traversal_Steps PROPERTIES
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_link_libraries(NFA_Traversal_Steps PRIVATE
        raylib
)

add_custom_command(TARGET NFA_Traversal_Steps POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:NFA_Traversal_Steps>/resources
)

cmake_minimum_required(VERSION 3.21)
project(PongGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/SFML)

add_executable(PongGame
    PongGame.cpp
    Game.cpp
    Game.h
    Paddle.h
    Ball.h
)

target_link_libraries(PongGame PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)

add_custom_command(TARGET PongGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Fonts
    $<TARGET_FILE_DIR:PongGame>/Fonts
)

if(WIN32)
    add_custom_command(TARGET PongGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:PongGame>
    )
endif()

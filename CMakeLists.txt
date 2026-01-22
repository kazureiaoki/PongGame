cmake_minimum_required(VERSION 3.21)
project(PongGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/SFML)

add_executable(PongGame
    src/PongGame.cpp
    src/include/Constants.h
    src/include/GameObject.h
    src/include/Game.h
    src/Game.cpp
    src/include/Paddle.h
    src/Paddle.cpp
    src/include/Ball.h
    src/Ball.cpp
    src/include/TextObject.h
    src/TextObject.cpp
    src/include/ScoreText.h
    src/ScoreText.cpp
    src/include/GameOverText.h
    src/GameOverText.cpp
    src/include/RestartHintText.h 
    src/RestartHintText.cpp 
)

target_include_directories(PongGame PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include
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

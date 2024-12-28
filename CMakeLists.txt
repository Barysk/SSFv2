cmake_minimum_required(VERSION 3.16)
project(SSF2 LANGUAGES CXX)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SSF2 main.cpp
    include/player.h src/player.cpp
    include/game.h src/game.cpp
    include/background.h src/background.cpp
    include/playerbullet.h src/playerbullet.cpp
    include/enemy.h src/enemy.cpp
    include/enemybullet.h src/enemybullet.cpp
    include/menu.h src/menu.cpp)

target_link_libraries(SSF2 raylib)

include(GNUInstallDirs)
install(TARGETS SSF2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/)

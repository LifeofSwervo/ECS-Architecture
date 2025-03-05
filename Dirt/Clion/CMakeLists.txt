cmake_minimum_required(VERSION 3.30)
project(Clion)

set(CMAKE_CXX_STANDARD 20)

add_executable(Clion main.cpp
        Chunk.cpp
        Chunk.hpp
        Common.hpp
        Vec2.cpp
        Vec2.hpp
        ChunkManager.cpp
        ChunkManager.hpp
        Entity.cpp
        Entity.hpp
        Components.hpp
        EntityManager.cpp
        EntityManager.hpp
        Game.cpp
        Game.hpp
        ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/include/SDL2_gfx/SDL2_framerate.c
        ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/include/SDL2_gfx/SDL2_gfxPrimitives.c
        ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/include/SDL2_gfx/SDL2_imageFilter.c
        ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/include/SDL2_gfx/SDL2_rotozoom.c
)


# SDL2 include
target_include_directories(Clion PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/SDL2/include
        ${CMAKE_SOURCE_DIR}/lib/SDL2/include/SDL2
)


# SDL2_gfx include
target_include_directories(Clion PRIVATE ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/include)

# SDL2 lib
target_link_directories(Clion PRIVATE ${CMAKE_SOURCE_DIR}/lib/SDL2/lib)

# SDL2_gfx lib
#target_link_directories(Clion PRIVATE ${CMAKE_SOURCE_DIR}/lib/sdl2_gfx/1.0.4/lib)

# SDL2_gfx Library link
target_link_libraries(Clion PRIVATE mingw32 SDL2main SDL2)


#target_link_libraries(Clion PRIVATE SDL2_gfx)

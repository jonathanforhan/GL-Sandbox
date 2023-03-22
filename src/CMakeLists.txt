add_executable(${PROJECT_NAME} main.cpp ${GLAD_SOURCE})

#
# GLOB_RECURSE the subdirs so that tests and such can
# still exist without messing up the build
#
file(GLOB_RECURSE SHADER_SOURCE shader/*.cpp)
file(GLOB_RECURSE TEXTURE_SOURCE texture/*.cpp)
file(GLOB_RECURSE OBJECT_SOURCE object/*.cpp)

add_library(APP_LIB STATIC
        application.cpp
        ${SHADER_SOURCE}
        ${TEXTURE_SOURCE}
        ${OBJECT_SOURCE}
        )

target_include_directories(APP_LIB PRIVATE
        shader
        texture
        object
        )

target_link_libraries(${PROJECT_NAME} PRIVATE APP_LIB)
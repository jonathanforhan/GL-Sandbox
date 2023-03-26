add_executable(${PROJECT_NAME} main.cpp ${GLAD_SOURCE})

#
# GLOB_RECURSE the subdirs so that tests and such can
# still exist without messing up the build
#
file(GLOB_RECURSE SHADER_SOURCE shader/*.cpp)
file(GLOB_RECURSE TEXTURE_SOURCE texture/*.cpp)
file(GLOB_RECURSE OBJECT_SOURCE object/*.cpp)
file(GLOB_RECURSE CAMERA_SOURCE camera/*.cpp)
file(GLOB_RECURSE LIGHT_SOURCE lighting/*.cpp)
file(GLOB_RECURSE MESH_SOURCE mesh/*.cpp)
file(GLOB_RECURSE MODEL_SOURCE model/*.cpp)

add_library(APP_LIB STATIC
        application.cpp
        ${SHADER_SOURCE}
        ${TEXTURE_SOURCE}
        ${OBJECT_SOURCE}
        ${CAMERA_SOURCE}
        ${LIGHT_SOURCE}
        ${MESH_SOURCE}
        ${MODEL_SOURCE}
        )

target_include_directories(APP_LIB PRIVATE
        shader
        texture
        object
        camera
        lighting
        mesh
        model
        )

target_link_libraries(${PROJECT_NAME} PRIVATE APP_LIB)
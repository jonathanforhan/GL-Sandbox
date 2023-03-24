#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 vs_position;
out vec2 vs_texCoord;
out vec3 vs_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 texCoordScale;

void main(void) {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vs_texCoord = texCoord * texCoordScale;
    vs_normal = normal;
    vs_position = vec3(model * vec4(pos, 1.0));
}
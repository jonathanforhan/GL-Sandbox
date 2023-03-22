#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 vs_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 texCoordScale;

void main(void) {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vs_texCoord = texCoord * texCoordScale;
}
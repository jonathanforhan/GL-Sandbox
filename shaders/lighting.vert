#version 450 core

out vec4 fs_color;

in vec2 vs_texCoord;

uniform sampler2D tex;

void main(void) {
    fs_color = texture(tex, vs_texCoord);
}

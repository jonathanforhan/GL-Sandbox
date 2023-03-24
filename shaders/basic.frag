#version 450 core

out vec4 fs_color;

in vec3 vs_position;
in vec2 vs_texCoord;
in vec3 vs_normal;

uniform sampler2D tex;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main(void) {
    // texture
    fs_color = texture(tex, vs_texCoord);

    // ambient lighting
    float ambient = 0.2f;
    vec4 ambientColor = vec4(1.0, 1.0, 1.0, 1.0);
    fs_color *= ambientColor * ambient;

    // diffuse lighting
    vec3 normal = normalize(vs_normal);
    vec3 lightDirection = normalize(lightPos - vs_position);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    fs_color += lightColor * diffuse;

    float specularLight = 0.1;
    vec3 viewDirection = normalize(camPos - vs_position);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = max(dot(viewDirection, reflectionDirection), 0.0);

    fs_color += lightColor * specAmount * 0.5;
}
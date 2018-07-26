#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec4 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightColor;

void main()
{
    ourColor = color;
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    // Normal Matrix
    Normal = mat3(transpose(inverse(model))) * normal;
    WorldPos = model * vec4(position, 1.0f);

    gl_Position = projection * view * WorldPos;
}

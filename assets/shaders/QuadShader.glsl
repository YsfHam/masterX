#type vertex
#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoords;
layout (location = 2) in vec4 a_color;
layout (location = 3) in float a_texIndex;
layout (location = 4) in float a_tillingFactor;

out vec2 v_texCoords;
out vec4 v_color;
out float v_texIndex;

//uniform mat3 u_model;
uniform mat3 u_pv;

void main()
{
    vec3 position = u_pv * a_pos;
    gl_Position = vec4(position.xy, 0.0, 1.0);

    v_texCoords = a_texCoords * a_tillingFactor;
    v_color = a_color;
    v_texIndex = a_texIndex;
}

#type fragment
#version 330 core



out vec4 color;

in vec2 v_texCoords;
in vec4 v_color;
in float v_texIndex;

uniform sampler2D u_textures[16];

void main()
{
    int texIndex = int(v_texIndex);
    vec4 tex = texture(u_textures[texIndex], v_texCoords);
    /*vec4 tex;
    if (texIndex == 0)
        tex = texture(u_textures[0], v_texCoords);
    if (texIndex == 1)
        tex = texture(u_textures[1], v_texCoords);
    */
    color = v_color * tex;
}


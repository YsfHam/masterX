// here comment

#type vertex
#version 330 core

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_texCoords;

out vec2 v_texCoords;

uniform mat3 u_model;
uniform mat3 u_pv;

void main()
{
    vec3 position = u_pv * u_model * vec3(a_pos, 1.0);
    gl_Position = vec4(position.xy, 0.0, 1.0);

    v_texCoords = a_texCoords;
}

#type fragment
#version 330 core

out vec4 color;

in vec2 v_texCoords;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, v_texCoords);
    //color = vec4(v_texCoords.xy, 0.0, 1.0);
}


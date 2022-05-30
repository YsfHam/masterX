// here comment

#type vertex
#version 330 core

layout (location = 0) in vec2 a_pos;

uniform mat3 u_model;
uniform mat3 u_pv;

void main()
{
    vec3 position = u_pv * u_model * vec3(a_pos, 1.0);
    gl_Position = vec4(position.xy, 0.0, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

uniform vec4 u_color;

void main()
{
    color = u_color;
}


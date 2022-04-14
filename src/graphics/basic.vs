#version 460 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 TexCoord;

uniform mat4 uni_mvp;

void main()
{
    gl_Position = uni_mvp * vec4(in_pos, 1.0);
    TexCoord = vec2(in_tex_coord.x, 1.0-in_tex_coord.y);
}
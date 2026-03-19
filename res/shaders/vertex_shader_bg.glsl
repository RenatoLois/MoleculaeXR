#version 330 core 

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_tex_coords;

out vec2 tex_coords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(a_pos, 1.0);
  tex_coords = a_tex_coords;
}

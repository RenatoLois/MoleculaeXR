#version 330 core 

in vec2 tex_coords;
uniform sampler2D material_texture_diffuse1;

out vec4 frag_color;

void main() {
  frag_color = texture(material_texture_diffuse1, tex_coords);
}

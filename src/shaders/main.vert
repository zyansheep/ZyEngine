#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform float scale;
uniform vec2 translation;
out vec3 colour;

void main() {
  colour = vertex_colour;
  gl_Position = vec4(
    scale * vertex_position.x + translation.x, 
    vertex_position.y + translation.y, 
    vertex_position.z, 
    1.0);
}
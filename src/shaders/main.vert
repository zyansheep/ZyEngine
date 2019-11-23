#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform mat4 MVPMatrix;
out vec3 colour;

void main() {
  colour = vertex_colour;
  gl_Position = MVPMatrix * vec4(vertex_position, 1);
}
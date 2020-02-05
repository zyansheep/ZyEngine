#version 330 core

layout(location = 0) in vec3 a_position;
//layout(location = 1) in vec3 a_color;
layout(location = 1) in mat4 a_transform;

uniform mat4 u_view;
uniform mat4 u_matrix;
out vec3 i_color;

void main() {
  i_color = sin(a_position);
  //Prespective * View * Model * Vertex
  gl_Position = a_transform * vec4(a_position, 1);
  //gl_Position = vec4(a_position, 1);
}
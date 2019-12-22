#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_transform;
out vec3 u_color;

void main() {
  u_color = sin(a_position);
  gl_Position = u_transform * vec4(a_position, 1);
}
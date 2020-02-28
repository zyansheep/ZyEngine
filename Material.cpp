#include "Material.h"
Material::Material(unsigned int m_x) {
    x = m_x;
}

void Material::changeColor(float xx, float yy, float zz, float w = 1.0f) {
    auto temp = glm::vec4(xx, yy, zz, w);
    glUniform4f(glGetUniformLocation(x, "RGB_DATA"), xx, yy, zz, w);
}
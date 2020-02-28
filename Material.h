
#include <glad/glad.h>
#include <glm/vec4.hpp>
#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
class Material {
    public: 
        uint x;
        Material(uint m_x);
        void changeColor(float v_x, float v_y, float v_z, float w = 1.0f);
};

#endif
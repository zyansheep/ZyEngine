#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.cpp"

#pragma once

class Camera {
public:
  Camera(float fov, Window* window, glm::vec3 position){
    m_projection = glm::perspective(
      glm::radians(fov), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
      (float)window->getWidth() / (float)window->getHeight(),       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
      0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
      100.0f             // Far clipping plane. Keep as little as possible.
    );
    m_view = glm::lookAt(
      position, // the position of your camera, in world space
      glm::vec3(0,0,0),   // where you want to look at, in world space
      glm::vec3(0,1,0)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
    );
    
    //m_view = glm::translate(glm::mat4(), -position);
    
    matrix = m_projection * m_view;
  }
  glm::mat4 matrix;
//private:
  glm::mat4 m_projection;
  glm::mat4 m_view;
  
};
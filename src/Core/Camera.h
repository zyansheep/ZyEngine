#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.cpp"

#pragma once

struct CameraProperties {
  float FieldOfView = 60;
  float AspectRatio = 16/9;
  float NearField = 0.01f;
  float FarField = 100.0f;
  
  CameraProperties(){};
  CameraProperties(float fov, Window* window)
  :FieldOfView(fov),
  AspectRatio((float)window->GetWidth() / (float)window->GetHeight()){}
};

class Camera {
public:
  float m_horizontalAngle = 3.14f; // horizontal angle : toward -Z
  float m_verticalAngle = 0.0f; // vertical angle : 0, look at the horizon
  Camera(glm::vec3 position, glm::vec3 direction = glm::vec3(0, 0, -1), glm::vec3 upvec = glm::vec3(0,1,0))
  :Camera(CameraProperties(), position, direction, upvec){}
  Camera(CameraProperties properties, glm::vec3 position, glm::vec3 direction = glm::vec3(0, 0, -1), glm::vec3 upvec = glm::vec3(0,1,0))
  :Properties(properties), Position(position), Direction(direction), UpVec(upvec){
    Update();
  }
  void Update(){
    UpdateProjection();
    UpdateView();
    matrix = projection * view;
  }
  void UpdateProjection(){
    projection = glm::perspective(
      glm::radians(Properties.FieldOfView), 
      Properties.AspectRatio, 
      Properties.NearField, 
      Properties.FarField
    );
    matrix = projection * view;
  }
  void UpdateView(){
    // Camera matrix
    view = glm::lookAt(
      Position,           // Camera is here
      Position+Direction, // and looks here : at the same position, plus "direction"
      UpVec                  // Head is up (set to 0,-1,0 to look upside-down)
    );
    matrix = projection * view;
  }
public:
  CameraProperties Properties;
  glm::vec3 Position;
  glm::vec3 Direction;
  glm::vec3 UpVec;
  
  glm::mat4 matrix;
  glm::mat4 projection;
  glm::mat4 view;
};
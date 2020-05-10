#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Core/Window.h"

#pragma once

struct CameraProperties {
  float FieldOfView = 60;
  float AspectRatio = 16/9;
  float NearField = 0.01f;
  float FarField = 100.0f;
  bool Ortho = false;
  float ZoomX = 1;
  float ZoomY = 1;
  
  CameraProperties(){};
  CameraProperties(float aspectRatio)
  :AspectRatio(aspectRatio){}
  
  CameraProperties(Window* window)
  :AspectRatio((float)window->GetWidth() / (float)window->GetHeight()){}
  
  CameraProperties(float fov, Window* window)
  :FieldOfView(fov),
  AspectRatio((float)window->GetWidth() / (float)window->GetHeight()){}
  
  void Update(Window& window){ AspectRatio = (window.GetWidth() / window.GetHeight()); }
};

class Camera {
public:
  Camera(Window* window, glm::vec3 position, glm::vec3 direction = glm::vec3(0, 0, -1), glm::vec3 upvec = glm::vec3(0,1,0))
  :Camera(CameraProperties(window), position, direction, upvec){}
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
    if(!Properties.Ortho){
      projection = glm::perspective(
        glm::radians(Properties.FieldOfView), 
        Properties.AspectRatio, 
        Properties.NearField, 
        Properties.FarField
      );
    }else{
      projection = glm::ortho(
        -Properties.ZoomX,
        Properties.ZoomX,
        -Properties.ZoomY,
        Properties.ZoomY,
        Properties.NearField, 
        Properties.FarField
      );
    }
    
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
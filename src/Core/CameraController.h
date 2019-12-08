#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include "m_window.cpp"
//#include "Camera.h"

class CameraController {
public:
  CameraController(Camera* camera, Window* window)
  :m_window(window){
    Bind(camera);
  }
  void Bind(Camera* camera){
    if (true){//(glfwRawMouseMotionSupported()){
      glfwSetInputMode(m_window->GetNative(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      //glfwSetInputMode(m_window->GetNative(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
      m_camera = camera;
    }else{
      std::cout << "Error Raw Mouse Motion is not supported" << std::endl;
    }
  }
  void Unbind(){
    m_camera = NULL;
  }
  void Update(){
    if(m_camera == NULL){return;}
    //double currentTime = glfwGetTime();
    //deltaTime = float(currentTime - m_lastTime);
    float deltaTime = m_window->GetFrameTime();
    double xpos, ypos;
    
    glfwGetCursorPos(m_window->GetNative(), &xpos, &ypos);
    
    glfwSetCursorPos(m_window->GetNative(), m_window->GetWidth()/2, m_window->GetHeight()/2);
    m_horizontalAngle += m_mouseSpeed * deltaTime * float(m_window->GetWidth()/2 - xpos );
    m_verticalAngle   += m_mouseSpeed * deltaTime * float( m_window->GetHeight()/2 - ypos );
    
    m_camera->Direction = glm::vec3(
      cos(m_verticalAngle) * sin(m_horizontalAngle),
      sin(m_verticalAngle),
      cos(m_verticalAngle) * cos(m_horizontalAngle)
    );
    glm::vec3 right = glm::vec3(
      sin(m_horizontalAngle - 3.14f/2.0f),
      0,
      cos(m_horizontalAngle - 3.14f/2.0f)
    );
    glm::vec3 forward = glm::vec3(
      sin(m_horizontalAngle),
      0,
      cos(m_horizontalAngle)
    );
    glm::vec3 up = glm::cross( right, m_camera->Direction );
    
    // Move directions
    // Move Forward
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_W ) == GLFW_PRESS){
      m_camera->Position += forward * deltaTime * m_speed;
    }
    // Move backward
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_S ) == GLFW_PRESS){
      m_camera->Position -= forward * deltaTime * m_speed;
    }
    // Strafe right
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_D ) == GLFW_PRESS){
      m_camera->Position += right * deltaTime * m_speed;
    }
    // Strafe left
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_A ) == GLFW_PRESS){
      m_camera->Position -= right * deltaTime * m_speed;
    }
    // Go Up
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_SPACE ) == GLFW_PRESS){
      m_camera->Position += m_camera->UpVec * deltaTime * m_speed;
    }
    // Go Down
    if (glfwGetKey( m_window->GetNative(), GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
      m_camera->Position -= m_camera->UpVec * deltaTime * m_speed;
    }
    
    m_camera->Properties.AspectRatio = (float)m_window->GetWidth() / (float)m_window->GetHeight();
    
    //Update camera matricies
    m_camera->Update();
  }
private:
  Camera* m_camera;
  Window* m_window;
  
  float m_horizontalAngle = 3.14f; // horizontal angle : toward -Z
  float m_verticalAngle = 0.0f; // vertical angle : 0, look at the horizon
  float m_speed = 10.0f; // 3 units / second
  float m_mouseSpeed = 0.05f;
};
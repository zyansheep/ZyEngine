#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#define PI 3.14159264

class CameraController {
public:
  CameraController(Window* window)
  :m_Window(window){
  }
  void Bind(Camera* camera){
    if (true){//(glfwRawMouseMotionSupported()){
      glfwSetCursorPos(m_Window->GetNative(), m_Window->GetWidth()/2, m_Window->GetHeight()/2);
      glfwSetInputMode(m_Window->GetNative(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      m_Camera = camera;
    }else{
      std::cout << "Error Raw Mouse Motion is not supported" << std::endl;
    }
  }
  void Unbind(){
    glfwSetInputMode(m_Window->GetNative(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    m_Camera = NULL;
    m_HorizontalAngle = 3.14f;
    m_VerticalAngle = 0.0f;
    bindDelay = 2;
  }
  void Update(){
    if(m_Camera == NULL){return;}
    
    //double currentTime = glfwGetTime();
    //deltaTime = float(currentTime - m_lastTime);
    float deltaTime = m_Window->GetFrameTime();
    double xpos, ypos;
    
    glfwGetCursorPos(m_Window->GetNative(), &xpos, &ypos);
    glfwSetCursorPos(m_Window->GetNative(), m_Window->GetWidth()/2, m_Window->GetHeight()/2);
    
    if(bindDelay > 0){bindDelay--; return;}
    m_HorizontalAngle += m_MouseSpeed * deltaTime * float( m_Window->GetWidth()/2 - xpos );
    m_VerticalAngle   += m_MouseSpeed * deltaTime * float( m_Window->GetHeight()/2 - ypos );
    if(m_VerticalAngle > PI/2){m_VerticalAngle = PI/2 - 0.00001;}
    if(m_VerticalAngle < -(PI/2)){m_VerticalAngle = -PI/2 + 0.00001;}
    
    m_Camera->Direction = glm::vec3(
      cos(m_VerticalAngle) * sin(m_HorizontalAngle),
      sin(m_VerticalAngle),
      cos(m_VerticalAngle) * cos(m_HorizontalAngle)
    );
    glm::vec3 right = glm::vec3(
      sin(m_HorizontalAngle - 3.14f/2.0f),
      0,
      cos(m_HorizontalAngle - 3.14f/2.0f)
    );
    glm::vec3 forward = glm::vec3(
      sin(m_HorizontalAngle),
      0,
      cos(m_HorizontalAngle)
    );
    glm::vec3 up = glm::cross( right, m_Camera->Direction );
    
    // Move directions
    // Move Forward
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_W ) == GLFW_PRESS){
      m_Camera->Position += forward * deltaTime * m_Speed;
    }
    // Move backward
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_S ) == GLFW_PRESS){
      m_Camera->Position -= forward * deltaTime * m_Speed;
    }
    // Strafe right
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_D ) == GLFW_PRESS){
      m_Camera->Position += right * deltaTime * m_Speed;
    }
    // Strafe left
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_A ) == GLFW_PRESS){
      m_Camera->Position -= right * deltaTime * m_Speed;
    }
    // Go Up
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_SPACE ) == GLFW_PRESS){
      m_Camera->Position += m_Camera->UpVec * deltaTime * m_Speed;
    }
    // Go Down
    if (glfwGetKey( m_Window->GetNative(), GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
      m_Camera->Position -= m_Camera->UpVec * deltaTime * m_Speed;
    }
    
    m_Camera->Properties.AspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
    
    //Update camera matricies
    m_Camera->Update();
    
    //std::cout << glm::to_string(m_Camera->Position)<<" --- " << m_HorizontalAngle<<", "<<m_VerticalAngle<<"\t\r"<<std::flush;
  }
private:
  unsigned int bindDelay = 2;
  
  Camera* m_Camera;
  Window* m_Window;
  
  float m_HorizontalAngle = 3.14f; // horizontal angle : toward -Z
  float m_VerticalAngle = 0.0f; // vertical angle : 0, look at the horizon
  float m_Speed = 10.0f; // 3 units / second
  float m_MouseSpeed = 0.05f;
};

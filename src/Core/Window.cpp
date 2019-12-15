#include "Window.h"

Window::Window(int width, int height, std::string title, bool vsync)
: m_Width(width), m_Height(height), m_Title(title){
  /* Initialize the library */
  if (!glfwInit()){
    std::cout << "Could not initialize GLFW" << std::endl;
    exit(-1);
  }
  
  /* Create a windowed mode window and its OpenGL context */
  //Enable opengl 3.3 core
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
  if (!m_Window){
    glfwTerminate();
    
    std::cout << "Error could not create window: \"" + title + "\" Exiting..." << std::endl;
    exit(-1);
  }
  glfwSetWindowUserPointer(m_Window, (void *)(this));
  
  glfwMakeContextCurrent(m_Window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  glfwSetWindowSizeCallback(m_Window, GlobalWindowResizeCallback);
  
  glfwSetKeyCallback(m_Window, GlobalKeyButtonCallback);
  
  glfwSetCursorPosCallback(m_Window, GlobalMouseMoveCallback);
  glfwSetCursorEnterCallback(m_Window, GlobalMouseEnterCallback);
  glfwSetMouseButtonCallback(m_Window, GlobalMouseButtonCallback);
  glfwSetScrollCallback(m_Window, GlobalMouseScrollCallback);
  
  m_IsOpen = true;
}

void Window::Start(void (*loop)()){
  while (!glfwWindowShouldClose(m_Window)) {
    // Measure speed
    RunTime = glfwGetTime();
    FrameTime = RunTime - m_PreviousFrameTime;
    m_PreviousFrameTime = RunTime;

    /* Render here */
    loop();
    
    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);
    
    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}
GLFWwindow* Window::GetNative(){
  return m_Window;
}
Window* Window::GetHandler(GLFWwindow* window){
  return (Window*)(glfwGetWindowUserPointer(window));
}

//Callbacks
void Window::WindowResizeCallback(int w, int h){
  m_Width = w;
  m_Height = h;
}
void Window::KeyButtonCallback(int key, int scancode, int action, int mods){
  
}
void Window::MouseEnterCallback(int entered){
  
}
void Window::MouseMoveCallback(double xpos, double ypos){
  MouseX = xpos;
  MouseY = ypos;
}
void Window::MouseButtonCallback(int button, int action, int mods){
  
}
void Window::MouseScrollCallback(double xoffset, double yoffset){
  
}
//Global Callbacks
void Window::GlobalWindowResizeCallback(GLFWwindow* window, int w, int h){
  Window::GetHandler(window)->WindowResizeCallback(w, h);
}
void Window::GlobalKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  Window::GetHandler(window)->KeyButtonCallback(key, scancode, action, mods);
}
void Window::GlobalMouseEnterCallback(GLFWwindow* window, int entered){
  Window::GetHandler(window)->MouseEnterCallback(entered);
}
void Window::GlobalMouseMoveCallback(GLFWwindow* window, double xpos, double ypos){
  Window::GetHandler(window)->MouseMoveCallback(xpos, ypos);
}
void Window::GlobalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
  Window::GetHandler(window)->MouseButtonCallback(button, action, mods);
}
void Window::GlobalMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
  Window::GetHandler(window)->MouseScrollCallback(xoffset, yoffset);
}

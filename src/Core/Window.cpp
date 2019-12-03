#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#pragma once

class Window{
public:
  Window(int width, int height, std::string title, bool vsync = true)
  :m_width(width), m_height(height), m_title(title){
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
    
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (!m_window)
    {
      glfwTerminate();
      
      std::cout << "Error could not create window: \"" + title + "\" Exiting..." << std::endl;
      exit(-1);
    }
    glfwSetWindowUserPointer(m_window, (void *)(this));
    
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    
    glfwSetWindowSizeCallback(m_window, GlobalWindowResizeCallback);
    glfwSetKeyCallback(m_window, GlobalKeyButtonCallback);
    glfwSetCursorPosCallback(m_window, GlobalMouseMoveCallback);
    glfwSetCursorEnterCallback(m_window, GlobalMouseEnterCallback);
    glfwSetMouseButtonCallback(m_window, GlobalMouseButtonCallback);
    glfwSetScrollCallback(m_window, GlobalMouseScrollCallback);
    
    m_isOpen = true;
  }
  static Window* getHandler(GLFWwindow* window){
    return (Window*)(glfwGetWindowUserPointer(window));
  }
  
  //Callbacks
  void WindowResizeCallback(int w, int h){
    m_width = w;
    m_height = h;
  }
  void KeyButtonCallback(int key, int scancode, int action, int mods){
    
  }
  void MouseEnterCallback(int entered){
    
  }
  void MouseMoveCallback(double xpos, double ypos){
    
  }
  void MouseButtonCallback(int button, int action, int mods){
    
  }
  void MouseScrollCallback(double xoffset, double yoffset){
    
  }
  //Global Callbacks
  static void GlobalWindowResizeCallback(GLFWwindow* window, int w, int h){
    Window::getHandler(window)->WindowResizeCallback(w, h);
  }
  static void GlobalKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Window::getHandler(window)->KeyButtonCallback(key, scancode, action, mods);
  }
  static void GlobalMouseEnterCallback(GLFWwindow* window, int entered){
    Window::getHandler(window)->MouseEnterCallback(entered);
  }
  static void GlobalMouseMoveCallback(GLFWwindow* window, double xpos, double ypos){
    Window::getHandler(window)->MouseMoveCallback(xpos, ypos);
  }
  static void GlobalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    Window::getHandler(window)->MouseButtonCallback(button, action, mods);
  }
  static void GlobalMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    Window::getHandler(window)->MouseScrollCallback(xoffset, yoffset);
  }
private:
  bool m_isOpen;
  GLFWwindow* m_window;
  int m_width;
  int m_height;
  std::string m_title;
  
  double previousTime;
  double currentTime;
  double frameTime = 0;
public:
  void start(void (*loop)()){
    /* Loop until the user closes the window */
    previousTime = glfwGetTime();
    currentTime = previousTime;
    while (!glfwWindowShouldClose(m_window))
    {
      // Measure speed
      currentTime = glfwGetTime();
      frameTime = currentTime - previousTime;
      previousTime = currentTime;

      /* Render here */
      loop();
      
      /* Swap front and back buffers */
      glfwSwapBuffers(m_window);
      
      /* Poll for and process events */
      glfwPollEvents();
      
      //Close if escape key hit
      if(glfwGetKey(m_window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_window, 1);
    }
    
    glfwTerminate();
  }
  
  void setVerticalSync(bool val){
    glfwSwapInterval((int)val);
  }
  
  int getWidth(){
    return m_width;
  }
  void setWidth(){
    
  }
  
  int getHeight(){
    return m_height;
  }
  void setHeight(){
    
  }
  
  void getTitle(){
    
  }
  void setTitle(){
    
  }
};
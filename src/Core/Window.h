#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window{
public:
  Window(int width, int height, std::string title, bool vsync = true);
  GLFWwindow* GetNative();
  static Window* GetHandler(GLFWwindow* window);
private:
  //Callbacks
  void WindowResizeCallback(int w, int h);
  void KeyButtonCallback(int key, int scancode, int action, int mods);
  void MouseEnterCallback(int entered);
  void MouseMoveCallback(double xpos, double ypos);
  void MouseButtonCallback(int button, int action, int mods);
  void MouseScrollCallback(double xoffset, double yoffset);
  //Global Callbacks
  static void GlobalWindowResizeCallback(GLFWwindow* window, int w, int h);
  static void GlobalKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void GlobalMouseEnterCallback(GLFWwindow* window, int entered);
  static void GlobalMouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
  static void GlobalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void GlobalMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  
  bool m_IsOpen;
  GLFWwindow* m_Window;
  int m_Width;
  int m_Height;
  std::string m_Title;
public:
  double m_PreviousFrameTime = 0;
public:
  double RunTime;
  double FrameTime;
  unsigned int MouseX, MouseY;
  
  void Start(void (*loop)());
  
  double GetFrameTime(){ return FrameTime; }
  void SetVerticalSync(bool val){ glfwSwapInterval((int)val); }
  bool GetKey(int key){ return glfwGetKey(m_Window, key); }
  int GetWidth(){ return m_Width; }
  int GetHeight(){ return m_Height; }
  void SetWindowDimensions(int width, int height);
  std::string GetTitle(){ return m_Title; }
  void SetTitle(std::string title){ m_Title = title; }
};

#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h> // IMPORTANT Include glad BEFORE glfw to prevent include errors!
#include <GLFW/glfw3.h>

#include "Preprocessor.h"

//Evaluate preprocessor arguments
#include "Core/Image.h"


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
  static void GlobalFrameResizeCallback(GLFWwindow* window, int w, int h);
  static void GlobalWindowResizeCallback(GLFWwindow* window, int w, int h);
  static void GlobalKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void GlobalMouseEnterCallback(GLFWwindow* window, int entered);
  static void GlobalMouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
  static void GlobalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void GlobalMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  static void GlobalErrorCallback(int id, const char* error);
  
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
  unsigned long FrameCount;
  unsigned int MouseX, MouseY;
  
  void Start(void (*loop)());
  bool Screenshot(const std::string& path);
  
  double GetFrameTime(){ return FrameTime; }
  void SetVerticalSync(bool val){ glfwSwapInterval((int)val); }
  bool GetKey(int key){ return glfwGetKey(m_Window, key); }
  int GetWidth(){ return m_Width; }
  int GetHeight(){ return m_Height; }
  void SetWindowDimensions(int width, int height);
  std::string GetTitle(){ return m_Title; }
  void SetTitle(std::string title){ m_Title = title; }
  void SetIcons(Image* icons, size_t size);
};

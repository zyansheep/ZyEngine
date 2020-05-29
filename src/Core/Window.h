#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h> // IMPORTANT Include glad BEFORE glfw to prevent include conflicts when glad attempts to load OpenGL!
#include <GLFW/glfw3.h>

#include "Preprocessor.h"

//Evaluate preprocessor arguments
#include "Core/Image.h"


class Window{
public:
	Window(int width, int height, std::string title, bool vsync = true);
	~Window();
	GLFWwindow* GetNative();
	static Window* GetHandler(GLFWwindow* window);
	
private:
	void CreateContext();
	void DestroyContext();
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

	double m_PreviousRunTime = 0;
public:
	double RunTime;
	double FrameTime;
	unsigned long FrameCount;
	unsigned int MouseX, MouseY;
	
	void Start(void (*loop)());
	bool Screenshot(const std::string& path);
	
	double GetFrameTime() const { return FrameTime; }
	mutable float SmoothedFrameRate;
	int GetFrameRate(float smoothing = 0.9) const {
		SmoothedFrameRate = SmoothedFrameRate * smoothing + (1.0 / FrameTime) * (1.0 - smoothing);
		return (int)SmoothedFrameRate;
	}
	void SetVerticalSync(bool val) { glfwSwapInterval((int)val); }
	bool GetKey(int key) const { return glfwGetKey(m_Window, key); }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	void SetWindowDimensions(int width, int height);
	std::string GetTitle() const { return m_Title; }
	void SetTitle(std::string title){ m_Title = title; }
	void SetIcons(const std::vector<Image>& icons);
};

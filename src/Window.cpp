#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window{
public:
  Window(int width, int height, const char* title, bool vsync = true){
    /* Initialize the library */
    if (!glfwInit()){
      std::cout << "Could not initialize GLFW" << std::endl;
      exit(-1);
    }
    
    /* Create a windowed mode window and its OpenGL context */
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
      glfwTerminate();
      
      std::cout << "Error could not create window: \"" + std::string(title) + "\" Exiting..." << std::endl;
      exit(-1);
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    
    //Special enable glsl 3.3 sauce
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    isOpen = true;
  }
  
  bool isOpen;
  GLFWwindow* window;
  
  void start(void (*loop)()){
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      /* Render here */
      loop();
      
      /* Swap front and back buffers */
      glfwSwapBuffers(window);
      
      /* Poll for and process events */
      glfwPollEvents();
    }
    
    glfwTerminate();
  }
  
  void setVerticalSync(bool val){
    glfwSwapInterval((int)val);
  }
  void soemthing(){}
  
  
};
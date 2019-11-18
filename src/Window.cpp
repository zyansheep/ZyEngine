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
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
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
    
    isOpen = true;
  }
  
  bool isOpen;
  GLFWwindow* window;
  
  double previousTime = glfwGetTime();
  int frameCount = 0;
  
  void start(void (*loop)()){
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      // Measure speed
      double currentTime = glfwGetTime();
      frameCount++;
      // If a second has passed.
      if ( currentTime - previousTime >= 1.0 ){
          // Display the frame count here any way you want.
          //displayFPS(frameCount);
          //std::cout << "fps:"<<frameCount << '\n';
          frameCount = 0;
          previousTime = currentTime;
      }

      /* Render here */
      loop();
      
      /* Swap front and back buffers */
      glfwSwapBuffers(window);
      
      /* Poll for and process events */
      glfwPollEvents();
      
      if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);
    }
    
    glfwTerminate();
  }
  
  void setVerticalSync(bool val){
    glfwSwapInterval((int)val);
  }
  
};
#include "Window.h"

Window::Window(int width, int height, const std::string& title, bool vsync)
: m_Width(width), m_Height(height), m_Title(title){
	Create();
}
Window::Window(int width, int height, std::string&& title, bool vsync)
: m_Width(width), m_Height(height), m_Title(std::move(title)){
	Create();
}
Window::~Window(){
	Destroy();
}

unsigned int Window::s_WindowCount = 0;
void Window::Create(){
	/* Initialize the library */
	if(s_WindowCount == 0){
		#ifdef ZY_WINDOW_LOG
		glfwSetErrorCallback(&GlobalGLFWErrorCallback);
		#endif
		if (!glfwInit()){
			std::cout << "Could not initialize GLFW" << std::endl;
			exit(-1);
		}

		/* Create a windowed mode window and its OpenGL context */
		//Enable opengl 3.3 core (compatible with most OSs)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	
	//glfwWindowHint( GLFW_DOUBLEBUFFER, GL_FALSE );
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
	if (!m_Window){
		glfwTerminate();

		std::cout << "Error could not create window: \"" + m_Title + "\" Exiting..." << std::endl;
		exit(-1);
	}
	glfwSetWindowUserPointer(m_Window, (void *)(this));
	glfwMakeContextCurrent(m_Window);
	
	//Load OpenGL if there are windows
	if(s_WindowCount <= 1){
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		glEnable              ( GL_DEBUG_OUTPUT );
		#ifdef ZY_WINDOW_LOG
		glDebugMessageCallback(GlobalGLErrorCallback, 0);
		#endif
	}
	
	glfwSwapInterval(1); //Vsync enable
	
	glfwSetWindowSizeCallback(m_Window, GlobalWindowResizeCallback);
	
	glfwSetKeyCallback(m_Window, GlobalKeyButtonCallback);
	
	glfwSetCursorPosCallback(m_Window, GlobalMouseMoveCallback);
	glfwSetCursorEnterCallback(m_Window, GlobalMouseEnterCallback);
	glfwSetMouseButtonCallback(m_Window, GlobalMouseButtonCallback);
	glfwSetScrollCallback(m_Window, GlobalMouseScrollCallback);
	
	m_IsOpen = true;
	s_WindowCount++;
}
void Window::Destroy(){
	glfwDestroyWindow(m_Window);
	s_WindowCount--;
	if(s_WindowCount == 0){
		glfwTerminate();
	}

	m_IsOpen = false;
}

void Window::Start(void (*loop)()){
	while (!glfwWindowShouldClose(m_Window)) {
		// Measure speed
		RunTime = glfwGetTime();
		FrameTime = RunTime - m_PreviousRunTime;
		m_PreviousRunTime = RunTime;
		FrameCount += 1;

		/* Render here */
		loop();
		
		/* Swap display and drawing buffers */
		glfwSwapBuffers(m_Window);
		
		/* Poll for and process events */
		glfwPollEvents();
	}
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//Save screenshot to file
bool Window::Screenshot(const std::string& path) {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  int x = viewport[0];
  int y = viewport[1];
  int width = viewport[2];
  int height = viewport[3];

  char *data = (char*) malloc((size_t) (width * height * 3)); // 3 components (R, G, B)
  if (!data)
    return 0;

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  int saved = stbi_write_png(path.c_str(), width, height, 3, data, 0);

  free(data);

  return saved;
}

GLFWwindow* Window::GetNative(){
  return m_Window;
}
Window* Window::GetHandler(GLFWwindow* window){
  return (Window*)(glfwGetWindowUserPointer(window));
}

void Window::SetIcons(const std::vector<Image>& icons){
  GLFWimage images[icons.size()];
  for(size_t i = 0; i < icons.size(); i++){
    images[i] = icons[i].CreateGLFWImage();
  }
  glfwSetWindowIcon(m_Window, icons.size(), images);
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
void Window::GlobalFrameResizeCallback(GLFWwindow* window, int w, int h){
  glViewport(0, 0, w, h);
}
void Window::GlobalWindowResizeCallback(GLFWwindow* window, int w, int h){
  glViewport(0, 0, w, h);
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

#ifdef ZY_WINDOW_LOG
void Window::GlobalGLErrorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
	fprintf( stdout, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
        type, severity, message );
}
void Window::GlobalGLFWErrorCallback(int id, const char* error){
	fprintf(stdout, "Error: glfw: %d, %s", id, error);
}
#endif
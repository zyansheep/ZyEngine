#include "World/World.h"
#include "World/CameraController.h"
#include "Rendering/Texture.h"
#include "Model/Model.h"

#include "Core/Image.h"

void* operator new(size_t size){
	std::cout << "New Allocation: " << size << " bytes\n";

	return malloc(size);
}

//Window (Width, Height, Title)
Window window = Window(1280, 720, "Examples - Texture");

//Camera (See Camera.h for properties)
//Camera camera = Camera(&window, glm::vec3{0, 0, 8});
//Camera2D camera = Camera(&window, glm::vec2{0,0});

//CameraController controller = CameraController(&window);
//World world = World(&window, &camera);

Texture texture = Texture("examples/texture/tex.png");
Shader textureShader =  ShaderGeneration::Texture();
Model plane = ModelGeneration::Square(0.5,0.5);
std::shared_ptr<VertexArray> vao;

unsigned int u_matrix_location;

//Image image("examples/texture/tex.png");
void setup(){
	//window.SetIcons({image});
	//camera.Properties.Ortho = true; // Ortho because we are rendering 2d texture in world
	//shader = Shader("test/shaders/main.vert", "test/shaders/main.frag");
	
	plane.UVs = { // Must set UV coordinates, unless loading from model file that contains UVs
		{0,0},
		{0,1},
		{1,1},
		{1,0}
	};
	vao = plane.MakeVertexArray();
	u_matrix_location = textureShader.GetUniformLocation("u_matrix");
	
	
	//Enable depth culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void draw(){
	//Background Color (R,G,B,A)
	glClearColor(255,0,0,255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Update Controller input from glfw
	//controller.Update();
	//object->MatrixArray[0] = glm::mat4(1.0f);
	//object->Rotate(glfwGetTime()*180, {0,0,1});
	
	//Render and Draw World
	//world.Render();
	//world.Draw();
	texture.Bind();
	textureShader.Bind();
	textureShader.Uniform(u_matrix_location, glm::mat4(1.0f));
	vao->Draw();
	texture.Unbind();
	textureShader.Unbind();
}

int main(){
	setup();
	window.Start(draw);
	return 0;
}
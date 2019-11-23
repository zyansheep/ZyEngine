#include "Shader.cpp"
#include "Object.cpp"
#include "Window.cpp"
#include "Camera.cpp"

class World {
public:
  World(Window* window, Camera* camera, std::vector<Object*> objects)
   : m_window(window), m_camera(camera) , m_objects(objects){
  }
  World(Window* window, Camera* camera)
  :m_window(window), m_camera(camera){};
  void addObject(Object* object){
    m_objects.push_back(object);
  }
  void render(){
    for(Object* obj : m_objects){
      obj->render(m_camera->matrix);
    }
  }
  void draw(){
    for(Object* obj : m_objects){
      obj->draw();
    }
  }
  
  
private:
  Window* m_window;
  Camera* m_camera;
  std::vector<Object*> m_objects;
};
#include "Object.h"
#include "Window.cpp"
#include "Camera.h"

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
      obj->Render(m_camera);
    }
  }
  void draw(){
    for(Object* obj : m_objects){
      obj->Draw();
    }
  }
  
  
private:
  Window* m_window;
  Camera* m_camera;
  std::vector<Object*> m_objects;
};
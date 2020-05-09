#include "World.h"

World::World(Window* window, Camera* camera, std::vector<Object*> objects)
  :m_Window(window), m_Camera(camera) , m_Objects(objects){
}
World::World(Window* window, Camera* camera)
:m_Window(window), m_Camera(camera){};

void World::AddObject(Object* object){
  m_Objects.push_back(object);
}
void World::Render(){
  m_Camera->Update();
  for(Object* obj : m_Objects){
    obj->Render(*m_Camera);
  }
}
void World::Draw(){
  for(Object* obj : m_Objects){
    obj->Draw();
  }
}
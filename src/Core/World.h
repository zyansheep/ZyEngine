#include "Object.h"
#include "Window.h"
#include "Camera.h"

class World {
public:
  World(Window* window, Camera* camera, std::vector<Object*> objects);
  World(Window* window, Camera* camera);
  void AddObject(Object* object);
  void Render();
  void Draw();
  
private:
  Window* m_Window;
  Camera* m_Camera;
  std::vector<Object*> m_Objects;
};
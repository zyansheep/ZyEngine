
namespace ModelGenerator {
  static Model Icosphere(uint recusionLevel){
    float t = (1.0 + sqrt(5.0)) / 2.0;
    Model model = Model({
      {-1,  t,  0},
      { 1,  t,  0},
      {-1, -t,  0},
      { 1, -t,  0},
       
      { 0, -1,  t},
      { 0,  1,  t},
      { 0, -1, -t},
      { 0,  1, -t},
       
      { t,  0, -1},
      { t,  0,  1},
      {-t,  0, -1},
      {-t,  0,  1},
    },{
      {0,11,5},
      {0,5,1},
      {0,1,7},
      {0,7,10},
      {0,10,11},
      
      {1,5,9},
      {5,11,4},
      {11,10,2},
      {10,7,6},
      {7,1,8},
      
      {3,9,4},
      {3,4,2},
      {3,2,6},
      {3,6,8},
      {3,8,9},
      
      {4,9,5},
      {2,4,11},
      {6,2,10},
      {8,6,7},
      {9,8,1}
    });
    std::map<std::pair<uint, uint>, uint> pointLookup;
    auto addMidpointVertex = [&] (glm::vec3 a, glm::vec3 b) {
      Lookup::key_type key(a, b);
      if (key.first > key.second)
        std::swap(key.first, key.second);
     
      auto inserted = lookup.insert({key, model.Vertices.size()});
      if (inserted.second){
        auto& edge0=model.Vertices[first];
        auto& edge1=model.Vertices[second];
        auto point=glm::normalize(edge0+edge1);
        model.Vertices.push_back(point);
      }
     
      return inserted.first->second;
    };
    for (int i = 0; i < recursionLevel; i++){
      std::vector<glm::uvec3> faces;
      for (glm::vec3 &tri : model.Indices){
        glm::vec3 newvec = glm::normalize(( model.Vertices[tri.x] + model.Vertices[tri.y] ) / 2);
        
        m.Vertices.push_back(vec);
        m.Vertices.push_back(( model.Vertices[tri.y] + model.Vertices[tri.z] ) / 2);
        m.Vertices.push_back(( model.Vertices[tri.z] + model.Vertices[tri.x] ) / 2);
        
        faces2.Add(new TriangleIndices(tri.v1, a, c));
        faces2.Add(new TriangleIndices(tri.v2, b, a));
        faces2.Add(new TriangleIndices(tri.v3, c, b));
        faces2.Add(new TriangleIndices(a, b, c));
      }
      faces = faces2;
    }
    
    return m;
  }
  static Model Cube(){
    return Model({
      {-1, -1, -1},
      { 1, -1, -1},
      { 1,  1, -1},
      {-1,  1, -1},
      {-1, -1,  1},
      { 1, -1,  1},
      { 1,  1,  1},
      {-1,  1,  1}
    },{
      {0, 1, 3},
      {3, 1, 2},
      {1, 5, 2},
      {2, 5, 6},
      {5, 4, 6},
      {6, 4, 7},
      {4, 0, 7},
      {7, 0, 3},
      {3, 2, 7},
      {7, 2, 6},
      {4, 5, 0},
      {0, 5, 1}
    });
  }
  static Model LoadObj(){
    
  }
}
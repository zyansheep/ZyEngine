#include <map>

namespace ModelGeneration {
  static Model Icosphere(uint recursionLevel){
    float t = (1.0 + sqrt(5.0)) / 10.0;
    float s = (1.0 - sqrt(5.0)) / 10.0;
    Model model = Model({
      {-s,  t,  0},
      { s,  t,  0},
      {-s, -t,  0},
      { s, -t,  0},
       
      { 0, -s,  t},
      { 0,  s,  t},
      { 0, -s, -t},
      { 0,  s, -t},
       
      { t,  0, -s},
      { t,  0,  s},
      {-t,  0, -s},
      {-t,  0,  s},
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
    
    //mapping vert indexs of line where midpoint is generated to midpooint index
    //used to check if midpoint index was allready generated
    std::map<std::pair<uint, uint>, uint> midpointLookup;
    auto getMidpointIndex = [&] (uint indexA, uint indexB) {
      std::pair<uint, uint> key(indexA, indexB);
      if(midpointLookup.find(key) == midpointLookup.end()){
        //not found, create new vertex
        
        //Adding vectors together gets the midpoint directionally
        //See "finding midpoint of line in 3d space"
        //midpoint formula = (vec_a + vec_b)/2
        glm::vec3 point = glm::normalize(model.Vertices[indexA] + model.Vertices[indexB]);
        model.Vertices.push_back(point);
        midpointLookup.insert({key, model.Vertices.size()-1}); 
      }
      return midpointLookup.at(key);
    };
    for (uint i = 0; i < recursionLevel; i++){
      midpointLookup.clear();
      std::vector<glm::uvec3> faces;
      for (glm::uvec3 &tri : model.Indices){
        //get midpoint (and add vertices of midpoints if don't exist)
        uint sub1 = getMidpointIndex(tri.x, tri.y);
        uint sub2 = getMidpointIndex(tri.y, tri.z);
        uint sub3 = getMidpointIndex(tri.z, tri.x);
        
        //take the 6 vertices and make 4 triangles
        faces.emplace_back(sub1, sub2, sub3); //center triangle
        
        faces.emplace_back(sub1, sub2, tri.y);
        faces.emplace_back(sub3, sub2, tri.z);
        faces.emplace_back(sub3, sub1, tri.x);
      }
      model.Indices = faces;
    }
    
    return model;
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
class ObjectArray : public Object{
public:
  void Render(Camera* viewport){
    m_MVPMatrix = viewport->matrix * m_ModelMatrix;
  }
  void Draw(){
    m_Shader.Bind();
    m_Shader.Uniform(m_MVPLocation, m_MVPMatrix);
    m_VertexArray->Draw();
  }
  friend Object;
private:
  std::vector<glm::mat4> m_MatrixArray;
};
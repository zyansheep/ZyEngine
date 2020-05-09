#pragma once

//Base class for opengl Assets
class Asset {
public:
  virtual void Bind() const;
  virtual void Unbind() const;
protected:
  unsigned int m_ID;
};
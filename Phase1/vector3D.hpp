#ifndef _VECTOR_3D_
#define _VECTOR_3D_

class Vector3D {
  
private:
  float x;
  float y;
  float z;
  
public:
  Vector3D();
  Vector3D(float x0, float y0, float z0);
  Vector3D add(Vector3D *v);
  Vector3D mult_scal(float k);
  Vector3D composant_product(Vector3D *v);
  float dot_product(Vector3D *v);
  Vector3D cross_product(Vector3D *v);
  float norm();
  Vector3D proj( Vector3D *v);
  float distance(Vector3D *v);
  float triple_product(Vector3D *v,Vector3D *w);
  bool operator ==(Vector3D const& v);
  bool operator !=(Vector3D const& v);
  ~Vector3D();
};  
  
#endif

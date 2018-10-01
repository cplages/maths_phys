#ifndef _VECTOR_3D_
#define _VECTOR_3D_

/* Class representing 3D Vector

Attributes : x,y,z

Methods : usual vector operations

*/

class Vector3D {

private:
  float x;
  float y;
  float z;

public:
  //constructors
  Vector3D();
  Vector3D(float x0, float y0, float z0);

  //getters
  float get_x() const;
  float get_y() const;
  float get_z() const;

  //usual vector operations
  Vector3D add(Vector3D const *v) const;
  Vector3D mult_scal(float k) const;
  Vector3D composant_product(Vector3D *v) const;
  float dot_product(Vector3D const *v) const;
  Vector3D cross_product(Vector3D *v) const ;
  float norm() const;
  Vector3D proj( Vector3D *v) const;
  float distance(Vector3D *v) const;
  float triple_product(Vector3D *v,Vector3D *w) const;
  void display();

  //operators
  bool operator ==(Vector3D const& v);
  bool operator !=(Vector3D const& v);
  Vector3D& operator =(Vector3D const& v);
  Vector3D& operator += (Vector3D const& v);

  ~Vector3D();
};

//binary operators outside the class;
Vector3D operator +(Vector3D const& v, Vector3D const& w);
Vector3D operator -(Vector3D const& v, Vector3D const& w);
Vector3D operator *(Vector3D const& v, float const& k);

#endif

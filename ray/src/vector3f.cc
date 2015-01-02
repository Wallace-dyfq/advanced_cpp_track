#include "vector3f.hh"

Vector3F::Vector3F() {
  elems[0] = 0;
  elems[1] = 0;
  elems[2] = 0;
}

Vector3F::Vector3F(float x, float y, float z) {
  elems[0] = x;
  elems[1] = y;
  elems[2] = z;
}

Vector3F & Vector3F::operator+=(const Vector3F &v) {
  for (int i = 0; i < 3; ++i)
    elems[i] += v.elems[i];
  return *this;
}

Vector3F & Vector3F::operator-=(const Vector3F &v) {
 for (int i = 0; i < 3; ++i)
    elems[i] -= v.elems[i];
  return *this;
}

Vector3F & Vector3F::operator*=(const float f)
{
  for (int i = 0; i < 3; ++i)
    elems[i] *= f;
  return *this;
}

Vector3F & Vector3F::operator/=(const float f)
{
  for (int i = 0; i < 3; ++i)
    elems[i] /= f;
  return *this;
}

const Vector3F Vector3F::operator+ (const Vector3F &v) const {
  return Vector3F(*this) += v;
}

const Vector3F Vector3F::operator- (const Vector3F &v) const {
  return Vector3F(*this) -= v;
}

const Vector3F operator* (const Vector3F & v, float f) {
  Vector3F tmp(v);
  tmp *= f;
  return tmp;
}

const Vector3F operator* (float f, const Vector3F &v ) {
  return v * f;
}

const Vector3F Vector3F::operator/ (const float f) const {
  return Vector3F(*this) /= f;
}

const Vector3F Vector3F::operator- () const {
  return Vector3F(*this) *= -1;
}


float Vector3F::operator() (int i) const { // use in RHS
  assert(i >=0);
  assert(i < 3);
  return elems[i];
}


float & Vector3F::operator() (int i){  // use in LHS
  assert(i >=0);
  assert(i < 3);
  return elems[i];
}



std::ostream & operator<< (std::ostream &os, const Vector3F &v) {
  os<< "("
    << v(0) <<", "
    << v(1) <<", "
    << v(2) <<")";
  return os;
}

const  float Vector3F::operator* (const Vector3F &v) const { // dot product
  float sum = 0;
  for (int i = 0; i < 3; ++ i)
    sum += elems[i] * v.elems[i];
  return sum;
}

const Vector3F Vector3F::operator% (const Vector3F &v) const { // cross product operator

  float e0 = elems[1] * v.elems[2] - elems[2] * v.elems[1];
  float e1 = elems[2] * v.elems[0] - elems[0] * v.elems[2];
  float e2 = elems[0] * v.elems[1] - elems[1] * v.elems[0];
  return Vector3F(e0, e1, e2);
}




float Vector3F::magnitude_squred() const {
  return *this * *this;  //the dot-product of a vector with itself is equal to its magnitude-squared
}

float Vector3F::magnitude() const {

  float s = *this * *this;
  return sqrtf(s);
}

void Vector3F::normalize() {  // normalize the vector
  float mag = this->magnitude();
  *this /= mag;
}


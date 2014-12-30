#ifndef __VECTOR3F_HH__
#define __VECTOR3F_HH__
#include<cassert>
#include<cmath>
#include<iostream>

class Vector3F {
  
  float elems[3];
  
 public:

  // Constructors
  Vector3F();
  Vector3F(float x, float y, float z);

  // Compound assignment operators
  Vector3F & operator+=(const Vector3F &v);
  Vector3F & operator-=(const Vector3F &v);

  // Compound assignment operators
  Vector3F & operator*=(const float f);
  Vector3F & operator/=(const float f);

  // Simple arithmetic operatos
  const Vector3F operator+ (const Vector3F &v) const;
  const Vector3F operator- (const Vector3F &v) const;
  const Vector3F operator/ (const float f) const;

  // Unary minus operator
  const Vector3F operator- () const;

  // operators for geting and setting the individual elements of the vector
  float operator() (int i) const; // use in RHS
  float & operator() (int i); // use in LHS

  // dot product operator
  const  float operator* (const Vector3F &v) const;

  // cross product operator
  const Vector3F operator% (const Vector3F &v) const; 

   // return a vector's magnitude squred
  float magnitude_squred() const;

  // return a vector's magnitude
  float magnitude() const;          

  // normalize the vector
  void normalize() ;    

};



// Multiply a vector with a float
const Vector3F operator* (const Vector3F &v, float f) ;
const Vector3F operator* (float f, const Vector3F &v ) ;

// stream-output operator 
std::ostream & operator<< (std::ostream &os, const Vector3F &v) ;



#endif //__VECTOR3F_HH__


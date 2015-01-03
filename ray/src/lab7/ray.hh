/** A clas to represent rays being trace, rays require two data members:   the origin that the ray is emitted from, and the direction that the ray is headed. Represent both of these values with your vector3f class 

 */
#ifndef __RAY_HH_
#define __RAY_HH_

#include "vector3f.hh"
#include <cassert>
class Ray {
 private:
  Vector3F origin; // or P
  Vector3F direction; // or D
  bool normalize_or_not;  // true if need normalize


 public:

  // Constructor
  Ray(const Vector3F &orig, const Vector3F &dir, bool normalize = true) : origin(orig), direction(dir), normalize_or_not(normalize) {
    if (normalize_or_not)
      direction.normalize();
      }

  // Destructor
  ~Ray() {}
  // Getters
  // get the origin
  const  Vector3F get_origin() const {
    return origin;
  }
  // get the direction
  const Vector3F get_direction() const {
    return direction;
  }

  const Vector3F  getPointAtT(float t) const {
    assert(t >= 0);
    return origin + direction * t;
  }

  /** reflect a ray off a position with a surface normal */
  //  we add a small delta value to the intersectoin.
  //This ensures that the new ray doesn't immediately intersect
  //with the object that it is reflected from!
  Ray reflect(const Vector3F intersection, const Vector3F &N, const float delta = 0.0001) const
  {
    Vector3F D = direction;
    Vector3F D_par = Vector3F(-D).project(N);
    Vector3F D_r = D + 2 * D_par;
    return Ray(intersection + D_r * delta, D_r);
  }
    
  };
  


#endif // __RAY_HH_

/** a class to represent each object in a raytraced scene.  */
#ifndef __SCENEOBJECT_HH__
#define __SCENEOBJECT_HH__

#include "colors.hh"
#include "ray.hh"
#include "vector3f.hh"

#include<cmath>

// ============ class SceneObject ==============

/** This class should be an abstract base class, since there is no well-defined way that generic scene objects should behave. scene object will include detailed information about its surface characteristics,
 */
class SceneObject {
 protected:
  Colors _surface_color;
  
 public:

  static const float invalid;
  // Constructor
  SceneObject() {
    Colors c(0.5, 0.5, 0.5);
    _surface_color = c;
  }

  SceneObject(const Colors &c) {_surface_color = c; }
  
  virtual ~SceneObject() {}

  
  /**get the surface_color */
  Colors get_surface_color() const {
    return _surface_color;
  }

  
  /** mutator for surface color*/
  void set_surface_color(const Colors &c)
  {
    _surface_color = c;
  }

  /** A pure-virtual function that computes whether or not an intersection occurred*/
  virtual float intersection(const Ray &r) const = 0;

  /** A pure-virtual function that returns the surface normal of a point on an object.*/
  virtual Vector3F surface_normal(const Vector3F &point ) const = 0;

  virtual void display() const = 0;
  Colors color_of_point(const Vector3F &point) const {
    return _surface_color;
  }


};

// ============== class PlaneObject ============

/** A plane object of infinite size. Planes are specified by two values, a distance d from the origin, and a surface-normal N for the plane.
     f(X) = X · N + d = 0

 the plane class should have two data members:

    A scalar specifying the distance of the plane from the origin. (Use the same type as your vector element type.)
    A vector specifying the surface normal for the plane. */
class PlaneObject : public SceneObject {
 private:
  float _distance;
  Vector3F _surfaceNormal;

public:
PlaneObject(const float d, const Vector3F &v, const Colors &c) :SceneObject(c), _distance(d), _surfaceNormal(v) {
    _surfaceNormal.normalize(); // incase it's not normalized 
  }

  // getters
  float get_distance() const {
    return _distance;
  }

  Vector3F get_surface_normal() const {
    return _surfaceNormal;
  }
  void display() const;
  

  Vector3F surface_normal(const Vector3F &point) const {
    // assume the point is on the plane
        return _surfaceNormal;
  }

  /** For a ray P + D * t, the intersection point is:

      t = -(P · N + d) / (D · N)*/
  float intersection(const Ray &r) const;
};

// ================ class SphereObject =========

/** A sphere object with a particular location and radius.

The sphere class should have two data members:

    A vector specifying the sphere's center.
    A scalar specifying the sphere's radius.

 */
class SphereObject : public SceneObject
{
 private:
  Vector3F _center;
  float _radius;

 public:
  // constructor
  SphereObject(const Vector3F &center, const float radius, const Colors &surface_color) : SceneObject(surface_color), _center(center), _radius(radius) {}

  // Getters
  Vector3F get_center() const {
    return _center;
  }
  float get_radius() const {
    return _radius;
  }
  void display() const;
  /** a public helper function that returns all of the sphere's intersection points, not just the closest one.
  */
  int getIntersections(const Ray &r, float &t1, float &t2) const;

  /** a public helper function that returns all of the sphere's intersection points, not just the closest one. */
  float intersection(const Ray &r) const;

  /**  he surface normal of any point on the sphere is:

    n(X) = (X - C) / |X - C|
   */
  Vector3F surface_normal(const Vector3F &point ) const;

};

  
  


// static member
const float SceneObject::invalid = -1;

//A pure-virtual function that computes
//whether or not an intersection occurred.


// float SceneObject::intersection(const Ray &r) const {

// }


    // When there are two valid intersection points, store the smaller one in t1, and the larger one in t2.
    // When there is only one valid intersection point, always store it in t1, and set t2 to "no intersection".
    // When there are no valid intersection points, set both t1 and t2 to "no intersection" before returning 0.


float PlaneObject::intersection(const Ray &r) const {

    Vector3F P = r.get_origin();
    Vector3F D = r.get_direction();

    float d = _distance; // just to make life easier
    Vector3F N = _surfaceNormal;

    float t;
    float tmp = D * N;
    if (tmp == 0)
      return invalid;
    else {
      t = -(P * N + d) / tmp;
      if (t >= 0)
        return t;
      else
        return invalid;
    }
  }


  int SphereObject::getIntersections(const Ray &r, float &t1, float &t2) const {

       
    Vector3F D = r.get_direction();
    Vector3F P = r.get_origin();
    Vector3F C = _center;
    float rr = _radius;
    float a = D * D;
    float b = 2 * (P * D - D * C);
    float c = P * P + C * C - 2 * (P * C) - rr * rr;

    float tmp = b * b - 4 * a * c;
    if (tmp > 0)
    {
      t1 = (-b - sqrtf(tmp)) / (2 * a);
      t2 = (-b + sqrtf(tmp)) / (2 * a);
      if (t1 < 0 )
      {
        t1 = t2;
        t2 = invalid;
        if (t1 < 0)
        {
          t1 = invalid;
          return 0;
        }
        else
          return 1;
        
      }
      else
        return 2;
    }
    else if (tmp == 0)
    {
      t1 = (-b) / (2 * a);
      t2 = invalid;
      if (t1 < 0)
      {
        t1 = invalid;
        return 0;
      }
      else
        return 1;
    }
    else
    {
      t1 = t2 = invalid;
      return 0;
    }
  }



float SphereObject::intersection(const Ray &r) const
{
  // local variables t1, t2 to receive the results
  // of the computation
  float t1, t2;
  getIntersections(r, t1, t2);

  // t1 is either the closest intersection point, or
  // it is our "no intersection" value.
  return t1;
}

Vector3F SphereObject::surface_normal(const Vector3F &point ) const {
  Vector3F X = point;
  Vector3F C = _center;

  Vector3F tmp = X - C;
  float n = tmp.magnitude();
  return Vector3F(tmp/n);
}

void PlaneObject::display() const {
  std::cout<<"Plane "<<_surfaceNormal<< " " << _distance <<" "<< _surface_color<<std::endl;

}

void SphereObject::display() const {
  std::cout<<"Sphere "<< _center<<" "<< _radius << " "<<_surface_color<<std::endl;
}
#endif // __SCENEOBJECT_HH__

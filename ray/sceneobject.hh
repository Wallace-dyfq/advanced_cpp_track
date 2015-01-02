#ifndef __SCENEOBJECT_HH__
#define __SCENEOBJECT_HH__

#include "colors.hh"
#include "ray.hh"
#include "vector3f.hh"

#include<cmath>

// ============ class SceneObject ==============
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

  
  // get the surface_color
  Colors get_surface_color() const {
    return _surface_color;
  }

  
  // mutator for surface color
  void set_surface_color(const Colors &c)
  {
    _surface_color = c;
  }

  virtual float intersection(const Ray &r) const = 0;
  virtual Vector3F surface_normal(const Vector3F &point ) const = 0;

  Colors color_of_point(const Vector3F &point) const {
    return _surface_color;
  }


};

// ============== class PlaneObject ============
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

  

      Vector3F surface_normal(const Vector3F &point) const {
    // assume the point is on the plane
    return _surfaceNormal;
  }

      float intersection(const Ray &r) const;
};

// ================ class SphereObject =========

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
  // helper function returns all of sphere's intersection points
      int getIntersections(const Ray &r, float &t1, float &t2) const;
float intersection(const Ray &r) const;
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
      assert(t >= 0);
      return t;
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

#endif // __SCENEOBJECT_HH__

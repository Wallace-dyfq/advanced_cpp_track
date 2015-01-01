#ifndef __SCENE_HH__
#define __SCENE_HH__
#include <vector>
#include "sceneobject.hh"
#include "lights.hh"
#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath>

using namespace std;

class Scene {

 private:
  vector<Lights *> _lights;
  vector<SceneObject *> _sceneobject;

  struct DeleteObject {
    template<typename T>
    void operator() (const T *ptr) const
    {
      delete ptr;
    }    
  };

 public:
  // default constructor that does nothing
  Scene() {}

  // destructor that cleans up dynamically allocated object
  ~Scene() {
    for_each(_lights.begin(), _lights.end(), DeleteObject() );
    for_each(_sceneobject.begin(), _sceneobject.end(), DeleteObject() );
    
  }

  
  void add_scene_object(SceneObject * s) {
    assert(s != 0);
    _sceneobject.push_back(s);
  }
  
  void add_light (Lights * l) {
    assert(l != 0);
    _lights.push_back(l);
  }
  

  /** traceRay function take a single argument, a Ray, to trac
      in the scene.

      Return: a Color - the actual color value for that ray.

      this function should be a const */
  Color traceRay(const Ray &r) const;

  /** A helper function that takes a ray and returns the closest
      scene object and time of intersection.

      The return value indicates whether an intersection occurs or not.
      If the return value is 0 then there is no intersection.
      Otherwise, if the return value is not 0, it points to the
      closest scene-object, and tIntersect is also set to the time of
      the closest intersection. (tIntersect is another out-parameter.
      There are several ways to pass multiple values back to the caller,
      but this is a simple and effective mechanism.) 
   */

  ceneObject * findClosestObject(const Ray &r, float &tIntersect) const;

};


#endif // __SCENE_HH__




Color Scene::traceRay(const Ray &r) const{
  float tIntersect;
  SceneObject *sc ;
  sc = findClosestObject(r, tIntersect);
  if (sc == 0 )
    return Color(0, 0, 0);
  else
  {
    Colors FinalColor;
    Vector<*Lights> :: iterator iter;
    
    for(iter = _lights.begin(); iter != _lights.end(); ++iter) {

      Vector3F light_loc = iter->get_position();
      Vector3F intersect_loc = r.get_origin() + r.get_direction() * tIntersect;
      Vector3F L = light_loc - intersect_loc;
      Vector3F N = sc->get_surface_normal();
      L.normalize();
      FinalColor += iter->get_color() * sc->get_surface_color() * fmaxf((N * L), 0);      
    }
  }

  return FinalColor;
}


SceneObject * Scene::findClosestObject(const Ray &r, float &tIntersect) const{

  /** Function generator to be used in the function findClosestObject
    
   */
  struct min_t : public unary_function<SceneObject *, void> {
    float tIntersect ; // closest intersection time;
    SceneObject * closest_object;  // keep track of the closest object
    closest_object = 0;  // assume no intersection
    min_t () : tIntersect(1000000) {}

    void  operator() (const SceneObject * sc) {
      float tmp_t = sc->intersection(r);
      if (tmp_t >= 0 && tmp_t < tIntersect)
      {
        tIntersect = tmp_t;
        closest_object = sc;
      }
    }
  } ;
  
  min_t result = for_each(_sceneobject.begin(), _sceneobject.end(), min_t());
  tIntersect = result.tIntersect;
  return result.closest_object;


}

/** a class to represent a scene. The objects in the scene will be dynamically allocated, as will the lights.
 */
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
#include "camera.hh"
#include<fstream>
#include <iterator>
#include <algorithm>  // for_each
#include "boost/shared_ptr.hpp"

using namespace std;

class Scene {
 public:
  typedef boost::shared_ptr<Lights> SPLights ;
  typedef boost::shared_ptr<SceneObject> SPSceneObject;

  // no need to use them
  //  typedef boost::shared_ptr<SphereObject> SPSphereObject;
  //typedef boost::shared_ptr<PlaneObject> SPPlaneObject;

 private:
  
  // vector<Lights *> _lights;
  // vector<SceneObject *> _sceneobject;

  // struct DeleteObject {
  //   template<typename T>
  //   void operator() (const T *ptr) const
  //   {
  //     delete ptr;
  //   }    
  // };

  // use boost
  
  vector<SPLights> _lights;
  vector<SPSceneObject> _sceneobject;
  const int depth_limit;
 public:
  // default constructor that does nothing
  Scene() : depth_limit(6) {}

  // destructor that cleans up dynamically allocated object
  ~Scene() {
    // no need to clean up since we are using the boost shared_ptr
    
    // for_each(_lights.begin(), _lights.end(), DeleteObject() );
    // for_each(_sceneobject.begin(), _sceneobject.end(), DeleteObject() );
    
  }

  /** A member function to add a new scene-object, that takes a pointer to the scene-object to add. */
  //void add_scene_object(SceneObject * s) {
  void add_scene_object(SPSceneObject  s) {
    assert(s != 0);
    _sceneobject.push_back(s);
  }

  /** A member function to add a new light, that takes a pointer to the light to add.*/
  void add_light (SPLights  l) {
    assert(l != 0);
    _lights.push_back(l);
  }
  

  /** traceRay function take a single argument, a Ray, to trac
      in the scene.

      Return: a Color - the actual color value for that ray.

      this function should be a const */
  Colors traceRay(const Ray &r, int depth = 0) const;

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

  SPSceneObject  findClosestObject(const Ray &r, float &tIntersect) const;
  //   SceneObject * findClosestObject(const Ray &r, float &tIntersect) const;

  /** The render function should take the following arguments:

    A reference to a camera object for generating rays into the scene. This should be const.
    An image size in pixels. Again, we are simplifying the code by assuming that the width and height are identical.
    An ostream-reference to write the image data to. This will be where the actual image data is written to. This cannot be const.

   */
  void render(const Camera &cam, int imgSize, ostream &os);

};



// ================= implementations ======================



Colors Scene::traceRay(const Ray &r, int depth ) const{
  float bigNumber = 1000000;
  float tIntersect(bigNumber);
  SPSceneObject sc ;

  //SceneObject *sc ;
  
  sc = findClosestObject(r, tIntersect);
 
  if (sc ==0 || tIntersect == bigNumber ) 
    
    return Colors(0, 0, 0);
  else // we do have intersection
  {
   
    Colors FinalColor;
    // typename vector<Lights *> ::const_iterator iter;

    // get the color due to the lights
    typename vector<SPLights> ::const_iterator iter;
    for(iter = _lights.begin(); iter != _lights.end(); ++iter) {
     
      Vector3F light_loc = (*iter)->get_position();
      Vector3F intersect_loc = r.get_origin() + r.get_direction() * tIntersect;
      Vector3F L = light_loc - intersect_loc;
      Vector3F N = sc->surface_normal(light_loc);
      
     
      L.normalize();
      FinalColor += (*iter)->get_color() * sc->get_surface_color() * fmaxf((N * L), 0);      
    }

    // get the color due to reflection
    if (sc->getReflectivity() != 0 && depth < depth_limit) {
      float t = sc->intersection(r);
      Vector3F P = r.get_origin();
      Vector3F D = r.get_direction();
      Vector3F X = P + D * t;  // intersection point
      Vector3F N = sc->surface_normal(X); // normal 
      Ray reflected_ray = r.reflect(X, N);
      Colors reflected_color = traceRay(reflected_ray, depth+1);
      FinalColor += sc->getReflectivity() * reflected_color;
    }
    
    return FinalColor;
  }

  
}

/** Function generator to be used in the function findClosestObject
 */
//Ray rr = r;
 
// struct min_t : public unary_function<SceneObject* , void> {
struct min_t : public unary_function<Scene::SPSceneObject , void> {
    float tIntersect ; // closest intersection time;
  //    SceneObject* oIntersection ;  // keep track of the closest object
  Scene::SPSceneObject oIntersection ;  // keep track of the closest object
    // oIntersection = 0;  // assume no intersection
    Ray rr;

    
    min_t (const Ray & ray, float t=1000000) : rr(ray),tIntersect(t) {}
  //  void  operator() ( SceneObject * sc) {
  void  operator() ( Scene::SPSceneObject  sc) {
      float tmp_t = sc->intersection(rr);
      if (tmp_t >= 0 && tmp_t < tIntersect)
      {
        tIntersect = tmp_t;
        oIntersection = sc;
      
      }
    }
  };

//SceneObject*  Scene::findClosestObject(const Ray &r, float &tIntersect) const{
Scene::SPSceneObject  Scene::findClosestObject(const Ray &r, float &tIntersect) const{
  min_t result= for_each(_sceneobject.begin(), _sceneobject.end(), min_t(r));
  tIntersect = result.tIntersect;
  return result.oIntersection;;
}


void Scene::render(const Camera &cam, int imgSize, ostream &os)
{
  os<<"P3 " << imgSize <<" " << imgSize <<" 255" << endl;
  
  // This code is rife with opportunities to optimize...


  for (int y = 0; y < imgSize; y++)
  {
    for (int x = 0; x < imgSize; x++)
    {
      Ray pixelRay = cam.getRayForPixel(x, y, imgSize);
      Colors pixelColor = traceRay(pixelRay);
      // Output color value to output stream, in proper image format.

      pixelColor *= 255;
      pixelColor.clamp(0, 255);
      int r = 255 * pixelColor.get_red();
      int b = 255 * pixelColor.get_blue();
      int g = 255 * pixelColor.get_green();
      os << r << " " << g << " " << b << std::endl;

    }
  }
}
#endif // __SCENE_HH__

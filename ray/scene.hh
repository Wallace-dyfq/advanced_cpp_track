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
  Colors traceRay(const Ray &r) const;

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

  SceneObject * findClosestObject(const Ray &r, float &tIntersect) const;

  void render(const Camera &cam, int imgSize, ostream &os);

};



// ================= implementations ======================



Colors Scene::traceRay(const Ray &r) const{
  float tIntersect;
  SceneObject *sc ;
  sc = findClosestObject(r, tIntersect);
  cerr<<"line 90"<<endl;
  cout<<"sc color is"<<sc->get_surface_color()<<endl;

  cerr<<"inside traceRay, after calling findClosestObject"<<endl;
  if (tIntersect == -1 )
    return Colors(0, 0, 0);
  else
  {
   
    Colors FinalColor;
     typename vector<Lights *> ::const_iterator iter;
    for(iter = _lights.begin(); iter != _lights.end(); ++iter) {
     
      Vector3F light_loc = (*iter)->get_position();
      Vector3F intersect_loc = r.get_origin() + r.get_direction() * tIntersect;
      Vector3F L = light_loc - intersect_loc;
      cerr<<"inside traceRay, at line 104"<<endl;
      cout<<"light_loc is: "<<light_loc<<endl;
      Vector3F N = sc->surface_normal(light_loc);
      
       cerr<<"inside traceRay, at line 106"<<endl;
      L.normalize();
      cerr<<"inside traceRay, at line 106"<<endl;
      FinalColor += (*iter)->get_color() * sc->get_surface_color() * fmaxf((N * L), 0);      
    }
    return FinalColor;
  }

  
}

 /** Function generator to be used in the function findClosestObject
   */
  //Ray rr = r;
 
 struct min_t : public unary_function<SceneObject *, void> {
    float tIntersect ; // closest intersection time;
    SceneObject* oIntersection ;  // keep track of the closest object
    // oIntersection = 0;  // assume no intersection
    Ray rr;

    
    min_t (const Ray & ray, float t=1000000) : rr(ray),tIntersect(t) {}

    void  operator() ( SceneObject * sc) {
      float tmp_t = sc->intersection(rr);
      cerr<<"tmp_t is "<<tmp_t<<endl;
      if (tmp_t >= 0 && tmp_t < tIntersect)
      {
        tIntersect = tmp_t;
        oIntersection = sc;
        cerr<<"inside find object"<<endl;
      }
    }
  };

SceneObject * Scene::findClosestObject(const Ray &r, float &tIntersect) const{

 

 
  
  min_t result= for_each(_sceneobject.begin(), _sceneobject.end(), min_t(r));
  tIntersect = result.tIntersect;
  return result.oIntersection;;


}
void Scene::render(const Camera &cam, int imgSize, ostream &os)
{
  os<<"P3 " << imgSize <<" " << imgSize <<" 255" << endl;
  
  // This code is rife with opportunities to optimize...

  cerr<<"inside render function"<<endl;
  for (int y = 0; y < imgSize; y++)
  {
    for (int x = 0; x < imgSize; x++)
    {
      Ray pixelRay = cam.getRayForPixel(x, y, imgSize);
      cerr<<"line 159 of scene.hh inside the render function, after calling camere.getRayForPixel"<<endl;
      Colors pixelColor = traceRay(pixelRay);
      cerr<<"line 161 of scene.hh inside the render function, after calling traceRay"<<endl;
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

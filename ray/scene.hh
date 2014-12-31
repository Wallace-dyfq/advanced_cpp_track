#ifndef __SCENE_HH__
#define __SCENE_HH__
#include <vector>
#include "sceneobject.hh"
#include "lights.hh"
#include <cassert>
#include <algorithm>

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
    for_each(_lights.begin(), _lights.end(), DeleteObject<Lights>() );
    for_each(_sceneobject.begin(), _sceneobject.end(), DeleteObject<SceneObject>() );
    
  }

  
  void add_scene_object(SceneObject * s) {
    assert(s != 0);
    _sceneobject.push_back(s);
  }

  void add_light (Lights * l) {
    assert(l != 0);
    _lights.push_back(l);
  }
  
        

};


#endif // __SCENE_HH__

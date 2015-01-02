#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "vector3f.hh"
#include <cmath>
#include <cassert>
#define _USE_MATH_DEFINES

class Camera {
  Vector3F _location;  //camera's location in the scene.
  Vector3F _direction;  //the direction the camera is facing. normalized
  float _fov;  // field of view value pecifying the horizontal viewing angle of the camera. use radians

  // these are perpindicular to the camera's direction vector,
  //and they fully specify the camera's orientation.
  //These should all be normalized. 
  Vector3F _camera_up;
  Vector3F _camera_right;

  float _distance; // which the camera computes to achieve the desired field of view.

 public:
  Camera(const Vector3F &position, const Vector3F &look_at, const Vector3F &up = Vector3F(0, 1, 0), const float fov = M_PI / 3 ) :
      _location(position), _fov(fov) {  // default _fov is 60 deg 
    _direction = look_at - _location;
    _direction.normalize(); // normalize it

    _camera_right = _direction % up;  // cross product
    _camera_up = _camera_right % _direction; // cross product

    _distance = 0.5 / tanf(_fov / 2);
  }
    
  Ray getRayForPixel(int x, int y, int imgSize) const;

    
  

};



Ray Camera::getRayForPixel(int x, int y, int imgSize) const {
  assert(x >= 0);
  assert(y >= 0);
  assert(x < imgSize);
  assert(y < imgSize);
 
  Vector3F pixelDir = _distance * _direction +
      (0.5 - (float) y / (float) (imgSize - 1)) * _camera_up +
      ((float) x / (float) (imgSize - 1) - 0.5) * _camera_right;

  Ray pixelRay(_location, pixelDir);
  return pixelRay;
}



#endif

#ifndef __LIGHT_HH__
#define __LIGHT_HH__
#include "vector3f.hh"
#include "colors.hh"
class Lights {
 private:
  Vector3F _position;
  Colors _color;
 public:

  // Constructor
  Lights(const Vector3F & v, const Colors & c) : _position(v), _color(c) {}

  // Destructor
  ~Lights() {}
  // get _position
  Vector3F get_position() const {
    return _position;
  }
  // get _color
  Colors get_color() const {
    return _color;
  }
};
  
  
#endif  // __LIGHT_HH__

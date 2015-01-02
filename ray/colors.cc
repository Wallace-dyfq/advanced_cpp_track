#include "colors.hh"
#include<cmath>

// component-wise adding
Colors & Colors::operator+= (const Colors & c) {
  red += c.red;
  blue += c.blue;
  green += c.green;

  return *this;
}

const Colors Colors::operator+ (const Colors &c) const {
  return Colors(*this) += c;
}

  // component-wise subtracting
Colors & Colors::operator-= (const Colors & c) {
  red -= c.red;
  blue -= c.blue;
  green -= c.green;

  return *this;
}

const Colors Colors::operator- (const Colors &c) const {
  return Colors(*this) -= c;
}

  // component-wise multiplying
Colors & Colors::operator *= (const Colors & c) {
  red *= c.red;
  blue *= c.blue;
  green *= c.green;

  return *this;
}

const Colors Colors::operator* (const Colors &c) const {
  return Colors(*this) *= c;
}


 // Compound assignment operators *= and /= for
  //multiplying and dividing a color by a scalar.
Colors & Colors::operator *= (const float f) {
  red *= f;
  blue *= f;
  green *= f;
  return *this;
}
const Colors Colors:: operator* (const float f)  const {
  return Colors(*this) *= f;
}


Colors & Colors::operator /= (const float f) {
  red /= f;
  blue /= f;
  green /= f;
  return *this;

}
const  Colors Colors::operator/ (const float t) const {
  return Colors(*this) /= t;
}

std::ostream & operator<< (std::ostream &os, const Colors &c) {
  os<<"("
    <<c.get_red() << ", "
    << c.get_green() << ", "
    << c.get_blue() << ")";

  return os;
}


void Colors::clamp(int minVal, int maxVal) {
  
  float mymax = fmaxf(red, blue);
  mymax = fmaxf(mymax, green);
  mymax = fmaxf(mymax, maxVal);

  red = red / mymax;
  blue = blue / mymax;
  green = green / mymax;
  assert( red <= 1);
  assert(blue <= 1);
  assert(green <= 1);

};

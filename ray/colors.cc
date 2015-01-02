#include "colors.hh"

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
  assert(red < maxVal);
  assert(red > minVal);
  assert(blue < maxVal);
  assert(blue > minVal);
  assert(green < maxVal);
  assert(green > minVal);

  red = red / maxVal;
  blue = blue / maxVal;
  green = green / maxVal;
};

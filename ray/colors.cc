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

Colors & Colors::operator /= (const float f) {
  red /= f;
  blue /= f;
  green /= f;
  return *this;

}


std::ostream & operator<< (std::ostream &os, const Colors &c) {
  os<<"("
    <<c.get_red() << ", "
    << c.get_green() << ", "
    << c.get_blue() << ")";

  return os;
}

/**
to represent colors in the RGB color-space. That is, each color will have a red component, a green component, and a blue component. Each color value should be represented by a floating-point number.

Normally these values will be between 0 and 1, but in some cases they may go outside that range when particular values are being computed. 
 */

#ifndef __COLORS_HH__
#define __COLORS_HH__
#include<iostream>
#include <cassert>

class Colors {

 private:
  float red;
  float green;
  float blue;

 public:

  // constructors
  Colors() : red(0), green(0), blue(0) {}
  Colors(float r, float g, float b) : red(r), green(g), blue(b) {}

  // Destructor
  ~Colors() {}
  // Getters // Accessors
  const float get_red() const {return red; }
  const float get_blue() const {return blue;}
  const float get_green() const {return green; }

  // Setters / mutators
  // set red
  void set_red(const float r) {
    red = r;
  }

  // set blue
  void set_blue(const float b) {
    blue = b;
  }

  // set green 
  void set_green (const float g) {
    green = g;
  }

  // Compound assignment operators

  /** component-wise adding*/
  Colors & operator+= (const Colors & c) ;
  const Colors operator+ (const Colors &c) const;

  /** component-wise subtracting*/
  Colors & operator-= (const Colors & c) ;
  const  Colors operator- (const Colors &c) const;
  
  // component-wise multiplying
  Colors & operator *= (const Colors & c) ;
  const  Colors operator* (const Colors &c) const;

  /**Compound assignment operators *= and /= for
   multiplying and dividing a color by a scalar.*/
  Colors & operator*= (const float f) ;
  
  //const   Colors operator* (const float f)  const;
  
  Colors & operator/= (const float f) ;

  const  Colors operator/ (const float t) const;

  void clamp(int minVal = 0, int maxVal = 255);
  friend  std::istream & operator>> (std::istream &is, Colors &c);

};

/** stream-output operator << for  color class*/
std::ostream & operator<< (std::ostream &os, const Colors &c) ;
std::istream & operator>> (std::istream &is, Colors &c);

const Colors operator* (float f, Colors color);
const Colors operator* (Colors color , float f);
#endif // __COLORS_HH__

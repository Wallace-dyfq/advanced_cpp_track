#include "colors.hh"
#include "gtest/gtest.h"
#include <iostream>

// This is the namespace that the Google C++ Testing Framework uses.
using namespace testing;


TEST(ColorsTest, Construct) {
  Colors color(1,0.2,0.4);
  ASSERT_FLOAT_EQ(color.get_red(), 1) <<"get_red() wrong!";
  ASSERT_FLOAT_EQ(color.get_blue(),0.4)<< "get_blue() wrong!";
  ASSERT_FLOAT_EQ(color.get_green(), 0.2) << "get_green() wrong!";
  
  color.set_red(0.5);
  color.set_blue(0.9);
  color.set_green(0.7);

  ASSERT_FLOAT_EQ(color.get_red(), 0.5) <<"get_red() after set wrong!";
  ASSERT_FLOAT_EQ(color.get_blue(),0.9)<< "get_blue() after set wrong!";
  ASSERT_FLOAT_EQ(color.get_green(), 0.7) << "get_green() wrong after set!";
      
}


TEST(ColorsTest, Assignment_Operators) {
  Colors color(0.1, 0.2, 0.3);
  
  color += color;

  ASSERT_FLOAT_EQ(color.get_red(), 0.2) <<"get_red() wrong! for +=";
  ASSERT_FLOAT_EQ(color.get_blue(),0.6)<< "get_blue() wrong! for +=";
  ASSERT_FLOAT_EQ(color.get_green(), 0.4) << "get_green() wrong! for +=";
  Colors color1(0.1, 0.1, 0.1);
  color -= color1;
  ASSERT_FLOAT_EQ(color.get_red(), 0.1) <<"get_red() wrong! for -=";
  ASSERT_FLOAT_EQ(color.get_blue(),0.5)<< "get_blue() wrong! for -=";
  ASSERT_FLOAT_EQ(color.get_green(), 0.3) << "get_green() wrong! for -=";
  color *= color ;
  ASSERT_FLOAT_EQ(color.get_red(), 0.01) <<"get_red() wrong! for *=";
  ASSERT_FLOAT_EQ(color.get_blue(),0.25)<< "get_blue() wrong! for *=";
  ASSERT_FLOAT_EQ(color.get_green(), 0.09) << "get_green() wrong! for *=";

  float f = 0.10;
  color /= f;

  ASSERT_FLOAT_EQ(color.get_red(), 0.1) <<"get_red() wrong! for /=";
  ASSERT_FLOAT_EQ(color.get_blue(),2.5)<< "get_blue() wrong! for /=";
  ASSERT_FLOAT_EQ(color.get_green(), 0.9) << "get_green() wrong! for /=";

}


TEST(ColorsTest, Simple_Arithmetic) {
  Colors color1(0.1, 0.2, 0.3);
  Colors color2(0.3,0.4, 0.5);
  Colors color;
  color = color1 + color2;
  ASSERT_FLOAT_EQ(color.get_red(), 0.4) <<"get_red() wrong! for +";
  ASSERT_FLOAT_EQ(color.get_blue(),0.8)<< "get_blue() wrong! for +";
  ASSERT_FLOAT_EQ(color.get_green(), 0.6) << "get_green() wrong! for +";

  color = color2 - color1;
  ASSERT_FLOAT_EQ(color.get_red(), 0.2) <<"get_red() wrong! for -";
  ASSERT_FLOAT_EQ(color.get_blue(),0.2)<< "get_blue() wrong! for -";
  ASSERT_FLOAT_EQ(color.get_green(), 0.2) << "get_green() wrong! for -";

  color = color1 * color2;
  ASSERT_FLOAT_EQ(color.get_red(), 0.03) <<"get_red() wrong! for *";
  ASSERT_FLOAT_EQ(color.get_blue(),0.15)<< "get_blue() wrong! for *";
  ASSERT_FLOAT_EQ(color.get_green(), 0.08) << "get_green() wrong! for *";
      
  
}






int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    Colors color(0.1, 0.2, 0.3);
    //std::cout<<"color = "<<color<<std::endl;
    return RUN_ALL_TESTS();
}

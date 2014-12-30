#include "vector3f.hh"
#include <gtest/gtest.h>

using namespace testing;

TEST(VectorTest, Construct) {
  Vector3F vec(1.1, 2.2, 3.3);
  ASSERT_FLOAT_EQ(vec(0), 1.1) << "v[0]";
  ASSERT_FLOAT_EQ(vec(1), 2.2) << "v[1]";
  ASSERT_FLOAT_EQ(vec(2), 3.3) << "v[2]";


}

TEST(VectorTest, Compound_Operators)
{
  Vector3F vec(1.1, 2.2, 3.3);
  Vector3F vec1(0.1, 0.2, 0.3);
  vec += vec1;

  ASSERT_FLOAT_EQ(vec(0), 1.2) << "v[0] for +=";
  ASSERT_FLOAT_EQ(vec(1), 2.4) << "v[1] for +=";
  ASSERT_FLOAT_EQ(vec(2), 3.6) << "v[2] for +=";

  vec = vec;
  ASSERT_FLOAT_EQ(vec(0), 1.2) << "v[0] for =";
  ASSERT_FLOAT_EQ(vec(1), 2.4) << "v[1] for =";
  ASSERT_FLOAT_EQ(vec(2), 3.6) << "v[2] for =";

  float ff = 2.0;
  vec = vec - ff * vec1;

  ASSERT_FLOAT_EQ(vec(0), 1.0) << "v[0] for *";
  ASSERT_FLOAT_EQ(vec(1), 2.0) << "v[1] for *";
  ASSERT_FLOAT_EQ(vec(2), 3.0) << "v[2] for *";

  float mag = vec.magnitude_squred();
  ASSERT_FLOAT_EQ(mag, 14) << "magnitude_squred wrong!";

  float f = 2.0;
  vec /= f;
  ASSERT_FLOAT_EQ(vec(0), 0.5) << "v[0] for +=";
  ASSERT_FLOAT_EQ(vec(1), 1.0) << "v[1] for +=";
  ASSERT_FLOAT_EQ(vec(2), 1.5) << "v[2] for +=";

  vec = vec + vec1;
  ASSERT_FLOAT_EQ(vec(0), 0.6) << "v[0] for +";
  ASSERT_FLOAT_EQ(vec(1), 1.2) << "v[1] for +";
  ASSERT_FLOAT_EQ(vec(2), 1.8) << "v[2] for +";

  Vector3F vec2(1, 2, 3);
  Vector3F vec3(3, 4, 5);
  vec = vec2 % vec3;

  ASSERT_FLOAT_EQ(vec(0), -2) << "v[0] for %";
  ASSERT_FLOAT_EQ(vec(1), 4) << "v[1] for %";
  ASSERT_FLOAT_EQ(vec(2), -2) << "v[2] for %";

  f = vec2 * vec3;
  ASSERT_FLOAT_EQ(f, 26) << " dot product wrong!";

  vec = -vec2;
  ASSERT_FLOAT_EQ(vec(0), -1) << "v[0] for %";
  ASSERT_FLOAT_EQ(vec(1), -2) << "v[1] for %";
  ASSERT_FLOAT_EQ(vec(2), -3) << "v[2] for %";

}




int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

#include "scene.hh"
#include <gtest/gtest.h>
#include <iostream>

using namespace  testing;

TEST(SceneTest, ray)
{
  Scene myscene;

  // create a ray object
  Vector3F rayOrigan(0, 0, 0);
  Vector3F rayDirection(1,0,0);
  Ray * ray_p = new Ray(rayOrigan, rayDirection, true);

  // create a sphere object
  Vector3F  sphereCenter(2, 0, 0);
  float sphereRadius = 1;
  Colors sphereColor(0.1, 0.2, 0.3);
  SphereObject * mysphere_p = new SphereObject(sphereCenter, sphereRadius, sphereColor);

  myscene.add_scene_object(mysphere_p);
  

  float r = mysphere_p->intersection(*ray_p);
  ASSERT_FLOAT_EQ(r, 1);
  float t1, t2;
  mysphere_p->getIntersections(*ray_p, t1, t2);
  ASSERT_FLOAT_EQ(t2, 3)<<"another intersectoin t2";

  Vector3F point = rayDirection;
  Vector3F v = mysphere_p->surface_normal(point);
  ASSERT_EQ(-1, v(0))<<"surface normal for sphere";
}



int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
   
    
    return RUN_ALL_TESTS();
}

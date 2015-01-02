#include "scene.hh"
#include "camera.hh"
#include "sceneobject.hh"
#include "boost/shared_ptr.hpp"
#include <iostream>
#include <fstream>

int main()
{
  Scene myscene;

  // typedef boost::shared_ptr<SceneObject> SPSCeneObject;
  // typedef boost::shared_ptr<Lights> SPSLights;

  // create a few sceneobject
  //  Scene::SPSceneObject so3 = new SphereObject(Vector3F(1.2, 0.5, 0), 0.5, Colors(0, 0, 1) ); // this does not work
  Scene::SPSceneObject  po( new PlaneObject(0, Vector3F(0, 1, 0), Colors(0.5, 0, 0.5) ) );
  Scene::SPSceneObject  so1 (new SphereObject(Vector3F(-1.2, 0.5, 0), 0.5, Colors(1, 0, 0) ) );
  Scene:: SPSceneObject so2(new SphereObject(Vector3F(0, 0.5, 0), 0.5, Colors(0, 1, 0) ));
  Scene::SPSceneObject so3( new SphereObject(Vector3F(1.2, 0.5, 0), 0.5, Colors(0, 0, 1) ));

 

  // add some lights
  Scene::SPLights l1 ( new Lights(Vector3F(-10, 10, 5), Colors(0.8, 0.8, 0.8) ));
  Scene::SPLights l2 (new Lights(Vector3F(5, 3, 5), Colors(0.3, 0.3, 0.3) ));
  //  cerr<< "here at line 27"<<endl;
  //  add them to the scene
  myscene.add_light(l1);
  myscene.add_light(l2);
   // add them to the scene 
  myscene.add_scene_object(po);
  myscene.add_scene_object(so1);
  myscene.add_scene_object(so2);
  myscene.add_scene_object(so3);

  
  // // create a few sceneobject
  // PlaneObject * po = new PlaneObject(0, Vector3F(0, 1, 0), Colors(0.5, 0, 0.5) );
  // SphereObject * so1 = new SphereObject(Vector3F(-1.2, 0.5, 0), 0.5, Colors(1, 0, 0) );
  // SphereObject *so2 = new SphereObject(Vector3F(0, 0.5, 0), 0.5, Colors(0, 1, 0) );
  // SphereObject *so3 = new SphereObject(Vector3F(1.2, 0.5, 0), 0.5, Colors(0, 0, 1) );

 

  // // add some lights
  // Lights *l1 = new Lights(Vector3F(-10, 10, 5), Colors(0.8, 0.8, 0.8) );
  // Lights *l2 = new Lights(Vector3F(5, 3, 5), Colors(0.3, 0.3, 0.3) );
  // //  cerr<< "here at line 27"<<endl;
  // //  add them to the scene
  // myscene.add_light(l1);
  // myscene.add_light(l2);
  //  // add them to the scene 
  // myscene.add_scene_object(po);
  // myscene.add_scene_object(so1);
  // myscene.add_scene_object(so2);
  // myscene.add_scene_object(so3);

  
  
  // configure the camera
  
  Camera cam(Vector3F(-1.5, 1, 3), Vector3F(-0.3, 0.5, 0), Vector3F(0, 1, 0) );

  // output to a file

  ofstream os;
  os.open("myscene2.ppm");
 
  myscene.render(cam, 10, os);

}
  
                

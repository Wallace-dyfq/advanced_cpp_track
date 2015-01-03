/* this is the code for lab 6 for read in input from a file and generate rendered image */

#include "scene.hh"
#include "camera.hh"
#include "sceneobject.hh"
#include "boost/shared_ptr.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream> //istringstream

using namespace std;
//typedef boost::shared_ptr<SceneObject> SPSceneObject;
//typedef boost::shared_ptr<Lights> SPLight;
typedef Scene:: SPSceneObject SPSceneObject ;
typedef Scene:: SPLights SPLights;

// Define a type for functions that take an input-stream, and construct a
// SceneObject from thisem.  (Don't forget the * even though it isn't strictly
// required by the C++ syntax for function pointers!  If you leave it out,
// the g++ STL implementation gets very crabby.)
typedef SPSceneObject (*SceneObjectReader)(istream &is);

// Functions for reading different kinds of scene objects, with same signature:
SPSceneObject ReadPlane(istream &is) {
  Vector3F surfaceNormal;
  float distance;
  Colors color;
  float r; // reflectivity
  is >> surfaceNormal >> distance >> color >> r;
  SPSceneObject plane(new PlaneObject(distance, surfaceNormal, color, r) );
  return plane;
}

SPSceneObject ReadSphere(istream &is) {
  float radius;
  Vector3F center;
  Colors color;
  float r; // reflectivity
  is >> center >> radius >> color >> r;
  SPSceneObject sphere(new SphereObject(center, radius, color, r) );
  return sphere;
}

SPSceneObject ReadCylinder(istream &is) {
  Vector3F position;
  Vector3F orientation;
  float radius;
  float height;
  Colors color;
  float r; // relectivity
  is >> position >> orientation >> radius >> height >> color >> r;

  SPSceneObject cylinder(new CylinderObject(position, orientation, radius, height, color, r) );

  return cylinder;

}
SPLights ReadLight(istream &is) {
  Vector3F pos;
  Colors color;
  is >> pos >> color;
  SPLights light(new Lights(pos, color) );
  return light;
}

Camera* ReadCamera(istream &is) {
  Vector3F pos;
  Vector3F lookat;
  Vector3F up;
  is >> pos >> lookat >> up;
  Camera *cam = new Camera(pos, lookat, up);
  return cam;
}
  

int main() {
  map<string, SceneObjectReader> readFuncs;
  readFuncs["plane" ] = ReadPlane;
  readFuncs["sphere"] = ReadSphere;
  readFuncs["cylinder"] = ReadCylinder;
  Scene myscene;
  ifstream is;
  string filename;
  cout << " Input the name of the testcase file [testcase.txt]: "<<endl;
  getline(cin,filename);
  //  cin>>filename;
  if(filename.empty()) filename = "testcase.txt";
  is.open(filename.c_str());
  string type;
  Camera *newCamera;
  // "is" is the input stream being read
  string line;
  cout <<"========================================= " << endl;
  while (getline(is, line))
  {
    istringstream iss(line);
    if (line.empty()) {
      cout<<"\n===============\t Empty line \t==========="<<endl;
      continue;
    }
    
    iss >> type;
    
    if (readFuncs.find(type) != readFuncs.end())
    {
      SPSceneObject newObj;
      
      // Retrieve and invoke the function.
      newObj = readFuncs[type](iss);
      myscene.add_scene_object(newObj);
      cerr<<" \nFind " ; 
      newObj->display();
    }
    else if (type == "light")
    {
      SPLights newLight;
      
      newLight = ReadLight(iss);
      myscene.add_light(newLight);
      cerr<<" \nFind ";
      newLight->display();
    }
    else if (type == "camera")
    {
    
      newCamera = ReadCamera(iss);
      cerr<<" \nFind ";
      newCamera->display();
    
    }
    
    else
    {
      cerr<<"\nInvalid input !!" << type <<" Please check your input file!!! " <<endl;
    }
  }

  //cerr<< " found in total " << myscene.size() << "scene objects" <<endl;
 cout <<"\n========================================= " << endl;
  ofstream os;
  cout<<"\n\nEnter the name of the file you want to write the data into, please [end with .ppm] \t[\"myscene_lab7.ppm \"] " <<endl;
  string file_out;
  //cin>>file_out;
  getline(cin, file_out);
  if (file_out.empty()) file_out = "myscene_lab7.ppm";
  os.open(file_out.c_str());
 
   myscene.render(*newCamera, 250, os);
  // myscene.render(*newCamera, 10, cout);

   cout <<"\n\nWritten data into file named "<< file_out<<endl;
   cout<< "\n Sucess!!!"<<endl;
   
}

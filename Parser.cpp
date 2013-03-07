#include "Parser.h"


void loadScene(string file, Scene* scene) {

  //store variables and set stuff at the end
  int width, height;
  string fname = "output.png";

  ifstream inpfile(file.c_str());
  if(!inpfile.is_open()) {
    cout << "Unable to open file" << endl;
  } else {
    string line;
    //MatrixStack mst;

    Material currentMaterial;
    GeometricPrimitive* currentPrimitive = new GeometricPrimitive();
    Matrix m;
    Transformation currentTransform(m);
    while(inpfile.good()) {
      vector<string> splitline;
      string buf;

      getline(inpfile,line);
      stringstream ss(line);

      while (ss >> buf) {
        splitline.push_back(buf);
      }
      //Ignore blank lines
      if(splitline.size() == 0) {
        continue;
      }

      //Ignore comments
      if(splitline[0][0] == '#') {
        continue;
      }

      //Valid commands:
      //size width height
      //  must be first command of file, controls image size
      else if(!splitline[0].compare("size")) {
        width = atoi(splitline[1].c_str());
        height = atoi(splitline[2].c_str());
        width = width;
        height = height;
        scene->screenWidth = width;
        scene->screenHeight = height;
      }
      //maxdepth depth
      //  max # of bounces for ray (default 5)
      else if(!splitline[0].compare("maxdepth")) {
        // maxdepth: atoi(splitline[1].c_str())
      }
      //output filename
      //  output file to write image to 
      else if(!splitline[0].compare("output")) {
        fname = splitline[1];
        scene->filename = fname;
      }

      //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
      //  speciï¬es the camera in the standard way, as in homework 2.
      else if(!splitline[0].compare("camera")) {
        // lookfrom:
        float lookfromX =    atof(splitline[1].c_str());
        float lookfromY =    atof(splitline[2].c_str());
        float lookfromZ =    atof(splitline[3].c_str());
        Point cameraPos(lookfromX, lookfromY, lookfromZ);
        // lookat:
        float lookatX =    atof(splitline[4].c_str());
        float lookatY =    atof(splitline[5].c_str());
        float lookatZ =    atof(splitline[6].c_str());
        Point cameraLookAt(lookatX, lookatY, lookatZ);
        // up:
        float upX =    atof(splitline[7].c_str());
        float upY =    atof(splitline[8].c_str());
        float upZ =    atof(splitline[9].c_str());
        Vector3 upVector(upX, upY, upZ);
        float fov = atof(splitline[10].c_str());

        Camera camera(cameraPos, cameraLookAt, upVector, fov, scene->screenWidth, scene->screenHeight);
        scene->camera = camera;
      }

      //sphere x y z radius
      //  Deï¬nes a sphere with a given position and radius.
      else if(!splitline[0].compare("sphere")) {
        //POTENTIALLY ANNOYING
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
        Point p(x, y, z);

        float r = atof(splitline[4].c_str());
        currentPrimitive->objToWorld = currentTransform;
        Transformation invt(currentTransform.minvt);
        currentPrimitive->worldToObj = invt;
        //cout<<"I'm going in!"<<endl;
        scene->aggPrimitives.allPrimitives.push_back(
            new GeometricPrimitive(new Sphere(p, r), new Material(currentMaterial.constantBRDF), currentTransform, invt)
          );
        //cout<<"I'm wrong!!!"<<endl;

        //HOW TO ADD TO POINTERS

        // Create new sphere:
        //   Store 4 numbers
        //   Store current property values
        //   Store current top of matrix stack
      }
      //maxverts number
      //  Deï¬nes a maximum number of vertices for later triangle speciï¬cations. 
      //  It must be set before vertices are deï¬ned.
      else if(!splitline[0].compare("maxverts")) {
        // Care if you want
        // Here, either declare array size
        // Or you can just use a STL vector, in which case you can ignore this
      }
      //maxvertnorms number
      //  Deï¬nes a maximum number of vertices with normals for later speciï¬cations.
      //  It must be set before vertices with normals are deï¬ned.
      else if(!splitline[0].compare("maxvertnorms")) {
        // Care if you want
      }
      //vertex x y z
      //  Deï¬nes a vertex at the given location.
      //  The vertex is put into a pile, starting to be numbered at 0.
      else if(!splitline[0].compare("vertex")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // Create a new vertex with these 3 values, store in some array
      }
      //vertexnormal x y z nx ny nz
      //  Similar to the above, but deï¬ne a surface normal with each vertex.
      //  The vertex and vertexnormal set of vertices are completely independent
      //  (as are maxverts and maxvertnorms).
      else if(!splitline[0].compare("vertexnormal")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // nx: atof(splitline[4].c_str()),
        // ny: atof(splitline[5].c_str()),
        // nz: atof(splitline[6].c_str()));
        // Create a new vertex+normal with these 6 values, store in some array
      }
      //tri v1 v2 v3
      //  Create a triangle out of the vertices involved (which have previously been speciï¬ed with
      //  the vertex command). The vertices are assumed to be speciï¬ed in counter-clockwise order. Your code
      //  should internally compute a face normal for this triangle.
      else if(!splitline[0].compare("tri")) {
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
      }
      //trinormal v1 v2 v3
      //  Same as above but for vertices speciï¬ed with normals.
      //  In this case, each vertex has an associated normal, 
      //  and when doing shading, you should interpolate the normals 
      //  for intermediate points on the triangle.
      else if(!splitline[0].compare("trinormal")) {
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices (Different array than above)
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
      }

      //translate x y z
      //  A translation 3-vector
      else if(!splitline[0].compare("translate")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // Update top of matrix stack
      }
      //rotate x y z angle
      //  Rotate by angle (in degrees) about the given axis as in OpenGL.
      else if(!splitline[0].compare("rotate")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // angle: atof(splitline[4].c_str())
        // Update top of matrix stack
      }
      //scale x y z
      //  Scale by the corresponding amount in each axis (a non-uniform scaling).
      else if(!splitline[0].compare("scale")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // Update top of matrix stack
      }
      //pushTransform
      //  Push the current modeling transform on the stack as in OpenGL. 
      //  You might want to do pushTransform immediately after setting 
      //   the camera to preserve the â€œidentityâ€ transformation.
      else if(!splitline[0].compare("pushTransform")) {
        //mst.push();
      }
      //popTransform
      //  Pop the current transform from the stack as in OpenGL. 
      //  The sequence of popTransform and pushTransform can be used if 
      //  desired before every primitive to reset the transformation 
      //  (assuming the initial camera transformation is on the stack as 
      //  discussed above).
      else if(!splitline[0].compare("popTransform")) {
        //mst.pop();
      }

      //directional x y z r g b
      //  The direction to the light source, and the color, as in OpenGL.
      else if(!splitline[0].compare("directional")) {
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
        Vector3 lightDirection(-x, -y, -z);
  
        float r = atof(splitline[4].c_str());
        float g = atof(splitline[5].c_str());
        float b = atof(splitline[6].c_str());
        Color lightColor(r, g, b);
      //DirectionalLight directionalLight(lightDirection, lightColor);
        scene->allSceneLights.push_back(new DirectionalLight(lightDirection, lightColor));
        // add light to scene...
      }
      //point x y z r g b
      //  The location of a point source and the color, as in OpenGL.
      else if(!splitline[0].compare("point")) {
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
        Point position(x, y, z);

        float r = atof(splitline[4].c_str());
        float g = atof(splitline[5].c_str());
        float b = atof(splitline[6].c_str());
        Color lightColor(r, g, b);

        //PointLight pointLight(position, lightColor);
        scene->allSceneLights.push_back(new PointLight(position, lightColor));
      }
      //attenuation const linear quadratic
      //  Sets the constant, linear and quadratic attenuations 
      //  (default 1,0,0) as in OpenGL.
      else if(!splitline[0].compare("attenuation")) {
        // const: atof(splitline[1].c_str())
        // linear: atof(splitline[2].c_str())
        // quadratic: atof(splitline[3].c_str())
      }
      //ambient r g b
      //  The global ambient color to be added for each object 
      //  (default is .2,.2,.2)
      else if(!splitline[0].compare("ambient")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());
        Color ka(r, g, b);
        currentMaterial.constantBRDF.ka = ka;
      }

      //diï¬€use r g b
      //  speciï¬es the diï¬€use color of the surface.
      else if(!splitline[0].compare("diffuse")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());
        Color kd(r, g, b);
        currentMaterial.constantBRDF.kd = kd;
        // Update current properties
      }
      //specular r g b 
      //  speciï¬es the specular color of the surface.
      else if(!splitline[0].compare("specular")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());
        Color ks(r, g, b);
        currentMaterial.constantBRDF.ks = ks;
        // Update current properties
      }
      //shininess s
      //  speciï¬es the shininess of the surface.
      else if(!splitline[0].compare("shininess")) {
        float s = atof(splitline[1].c_str());
        currentMaterial.constantBRDF.alphaConstant = s;
        // Update current properties
      }
      //emission r g b
      //  gives the emissive color of the surface.
      else if(!splitline[0].compare("emission")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
      } else {
        cerr << "Unknown command: " << splitline[0] << endl;
      }
    }

    inpfile.close();
  }

}
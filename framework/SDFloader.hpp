#include <iostream>
#include <fstream>

class SDFloader{
  /*bekommt einen file im SDF Format übergeben,
  *liest ihn ein und gibt eine Scene zurück
  */

  Scene loadScene(/*datentyp??*/ const& file){

    std::ifstream sceneFile;
    sceneFile.open(file);

    Scene beautifulScene;

    return beautifulScene;

  }



}

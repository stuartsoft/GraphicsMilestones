#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

#include "glm\glm.hpp"

using namespace std;

class SceneGraph {
public:
	SceneGraph(){};
	void Parse(string fname);

private:
	int xSize;
	int zSize;
};
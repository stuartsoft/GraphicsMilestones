#include "SceneGraph.h"

void SceneGraph::Parse(string fname){
	ifstream file(fname);

	string line = "";
			//RESO
	getline(file, line);
	stringstream ss(line);
	string tok = "";
	ss >> tok;
	xSize = stoi(tok);
	ss >> tok;
	zSize = stoi(tok);
	ss >> tok;
	int numItems = stoi(tok);

	//Build the scene graph nodes as we read the file

	for (int i = 0;i<numItems;i++){
		getline(file, line);
		getline(file, line);
		string geoType = line;
		getline(file, line);
		ss >> tok;
		int xIndex = stoi(tok);
		ss >> tok;
		int zIndex = stoi(tok);
		getline(file, line);
		ss = stringstream(line);
		ss >> tok;
		int rotation = stoi(tok);
		glm::vec3 scale = glm::vec3(0,0,0);
		line = "";
		getline(file,line);
		ss = stringstream(line);
		ss >> tok;
		scale.x = stoi(tok);
		ss >> tok;
		scale.y = stoi(tok);
		ss >> tok;
		scale.z = stoi(tok);
	}

	file.close();

}


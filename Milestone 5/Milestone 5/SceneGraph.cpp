#include "SceneGraph.h"

SceneGraph::SceneGraph(){
	geometry = NULL;
	translation = glm::mat4();
	scale = glm::mat4();
	rotation = glm::mat4();
	parentSG = NULL;
}

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

	//initialize the root node's TRS
	translation = glm::mat4();
	glm::translate(translation,glm::vec3(xSize/2, 0, zSize/2));//translate the root to the center
	scale = glm::mat4();
	rotation = glm::mat4();
	rootSG = this;

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
		
		//figure out where this should go in the scene graph
		//first check if any objects exist in this pos, if there are, stack this one on top
		float yIndex = 0;
		bool check = true;
		glm::vec3 targetPos = glm::vec3(xIndex, yIndex, zIndex);
		while (check)
		{
			SceneGraph* tempSG = checkIfObjectExistsHere(glm::vec3(xIndex,0,zIndex));
			yIndex = tempSG.
		}
	}

	file.close();
}

SceneGraph* SceneGraph::checkIfObjectExistsHere(glm::vec3 pos){
	for(int i = 0;i<decendents.size;i++){
		SceneGraph* temp = decendents[i].checkIfObjectExistsHere(pos);
	}
}

void SceneGraph::addChild(SceneGraph child){
	child.rootSG = rootSG;
	child.parentSG = this;
	decendents.push_back(child);
}

void SceneGraph::traverse(glm::mat4 mat){

	for (int i = 0;i<decendents.size;i++){
		decendents[i].traverse(mat);
	}
}
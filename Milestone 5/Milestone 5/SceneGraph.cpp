#include "SceneGraph.h"

SceneGraph::SceneGraph(){
	geometry = NULL;
	translation = glm::mat4();
	scale = glm::mat4();
	rotation = glm::mat4();
	parentSG = NULL;
}

void SceneGraph::Parse(string fname){
	//initialize the geometry object list
	geometryObjectRef.push_back(new Geometry());//creates a cube. yay

	ifstream file(fname);

	string line = "";
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
	translation = glm::translate(translation,glm::vec3(xSize/2, 0, zSize/2));//translate the root to the center
	scale = glm::mat4();
	rotation = glm::mat4();
	rootSG = this;

	vector<SceneGraph*> allSceneGraphs;//reference list of all scene graphs to be used with allSGPos
	vector<glm::vec3> allSGPos;//records the x,z pos index from the file for use during parsing. Allows us to quickly check if an object already exists at this location in the world

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
		glm::vec3 targetPos;
		SceneGraph* parent;
		while(check){
			targetPos = glm::vec3(xIndex, yIndex, zIndex);
			for (int j = 0;j<allSceneGraphs.size;j++){
				if (allSGPos[j].x == targetPos.x && allSGPos[j].y == targetPos.y && allSGPos[j].z == targetPos.z){
					yIndex += 1;//move up one unit length and check again
					parent = allSceneGraphs[j];
					break;
				}
			}
			check = false;//we didn't find anything in this pos, everything should be fine
		}

		//actually create and add the new node
		SceneGraph* node = new SceneGraph();
		node->rootSG = this;
		node->geometry = geometryObjectRef[0];//set it to point to the cube geometry
		if (parent == NULL){
			//no parent was found, just connect this object to the root node
			node->parentSG = this;
			const float* valuePtr = (const float*) glm::value_ptr(parent->translation);
			node->translation = glm::translate(node->translation, glm::vec3(valuePtr[3] - xIndex, 0, valuePtr[11] - zIndex));
			addChild(node);
		}
		else{//a parent object was found, set the new object to point to the parent
			node->parentSG = parent;
			node->translation = glm::translate(node->translation, glm::vec3(0, 1, 0));
			parent->addChild(node);
		}
		allSceneGraphs.push_back(node);
		allSGPos.push_back(targetPos);
	}
	file.close();
}

void SceneGraph::addChild(SceneGraph* child){
	child->rootSG = rootSG;
	child->parentSG = this;
	decendents.push_back(child);
}

void SceneGraph::traverse(glm::mat4 mat){
	for (int i = 0;i<decendents.size;i++){
		decendents[i]->traverse(mat);
	}

	if(geometry != NULL){
		//do something
	}
}
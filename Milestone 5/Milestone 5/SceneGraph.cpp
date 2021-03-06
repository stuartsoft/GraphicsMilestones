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
	translation = glm::translate(translation,glm::vec3(xSize/2.0f, 0, zSize/2.0f));//translate the root to the center
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
		ss = stringstream(line);
		ss >> tok;
		int xIndex = stoi(tok);
		ss >> tok;
		int zIndex = stoi(tok);
		getline(file, line);
		ss = stringstream(line);
		ss >> tok;
		float yrotation = stoi(tok);
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
		SceneGraph* parent = NULL;
		while(check){
			targetPos = glm::vec3(xIndex, yIndex, zIndex);
			for (int j = 0;j<allSceneGraphs.size();j++){
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
		node->scale[0][0] = scale.x;
		node->scale[1][1] = scale.y;
		node->scale[2][2] = scale.z;
		node->rotation = glm::rotate(glm::mat4(), (3.1415f/180)*yrotation, glm::vec3(0,1,0));

		if (parent == NULL){
			//no parent was found, just connect this object to the root node
			node->parentSG = this;
			float halfxSize = xSize/2.0f;
			float halfzSize = zSize/2.0f;
			node->translation = glm::translate(node->translation, glm::vec3(xIndex - halfxSize, 0, zIndex - halfzSize));
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
	M = translation * rotation * scale;
	printMatrix(M);

	for (int i = 0;i<decendents.size();i++){
		decendents[i]->traverse(M);
	}
}

void SceneGraph::printMatrix(glm::mat4 mat){
	if (rootSG == this)
		cout<<"root"<<endl;
	for (int i = 0;i<4;i++){
		for (int j = 0;j<4;j++){
			cout << mat[j][i]<<" ";
		}
		cout <<endl;
	}
	cout << endl;
}

vector<glm::vec4> SceneGraph::getFinalGeometryPoints(){
	vector<glm::vec4> results;
	if (geometry != NULL){
		for (int i = 0;i<geometry->numPoints;i++){
			results.push_back(M * geometry->points[i]);
		}
	}
	return results;
}

string SceneGraph::writeToFile(string fname){
	ofstream f;
	string data = "";
	if (rootSG == this){
		f.open(fname);
	}

	std::stringstream stream;
	stream << std::fixed << setprecision(1);
	

	if (geometry != NULL){
		stream << "** Cube **\n";
		vector<glm::vec4> finalPoints = getFinalGeometryPoints();
		for (int i = 0;i< finalPoints.size();i++){
			stream<<"Point" <<i <<": (" <<finalPoints[i].x << ", ";
			stream << finalPoints[i].y << ", " << finalPoints[i].z << ")\n";
		}
		stream << "**********\n\n";
		data = stream.str();
	}

	for (int i = 0;i<decendents.size();i++){
		string decendentStr = decendents[i]->writeToFile(fname);
		data += decendentStr;
	}

	if (rootSG == this){
		f<<data;
		f.close();
	}

	return data;
}
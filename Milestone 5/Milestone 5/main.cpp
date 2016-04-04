#include "SceneGraph.h"

int main(int argc, char** argv) {
	SceneGraph sg;
	sg.Parse("scene2.txt");
	sg.traverse(glm::mat4());//begin traversing
}

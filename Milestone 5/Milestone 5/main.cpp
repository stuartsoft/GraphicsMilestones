#include "SceneGraph.h"

int main(int argc, char** argv) {
	SceneGraph* sg = new SceneGraph();
	sg->Parse("scene2.txt");
	sg->traverse(glm::mat4());//begin traversing
	sg->writeToFile("scene2_results.txt");

	//system("pause");
}
